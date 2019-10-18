 /*

*/
#include <Servo.h>
#include <AFMotor.h>
const int grace = 100; //500 millisecond grace period for beam break
const int mazegrace = 100; // 500 millisecond grace period while mouse is in maze

//define ports on the arduino board

//definepins
const int MidIRread = A8; 
const int Right1IRread = A9;
const int Right2IRread = A10;
const int Left1IRread = A11; 
const int Left2IRread = A12; 
const int FrontIRread = A13;
const int RewardIRread = A14;
const int rewarddirect = 12; // Motor A Direction pin
const int rewardbrake = 9; //Motor A Brake pin
const int rewardspeed = 3; //Motor A Speed pin

//define motor information
#include <AFMotor.h>
// FORWARD = COUNTERCLOCKWISE
// BACKWARD = CLOCKWISE
// Number of steps per output rotation
// Change this as per your motor's specification
const int stepsPerRevolution = 200;
AF_Stepper motor(stepsPerRevolution, 2);
int x;
int currentface = 1;
int panelindex = 0;
AF_DCMotor water(1);

//defineservos
Servo rightDoorServo;
int rightDoorServoPin = 15;
const int rightDoorServoOpenVal= 180;
const int rightDoorServoCloseVal= 90;
Servo leftDoorServo;
int leftDoorServoPin = 14;
const int leftDoorServoOpenVal= 0;
const int leftDoorServoCloseVal= 90;
const int leftDoorServoShutVal = 180;

//definebools
  // Trial Phases: Start > Touch > Decide > Reward (or no reward)
bool TrialStart = true;
bool TrialTouch = false;
bool TrialDecide = false;
bool TrialReward = false;
  // Initialize all the Beams as Not Having Been Broken
bool Left1Broken = false;
bool Left2Broken = false;
bool Right1Broken = false;
bool Right2Broken = false;
bool MidBroken = false;
bool FrontBroken = false;
bool RewardBroken = false;
  //Initialize all the Beams as Clear
bool Left1Temp = false;
bool Left2Temp = false;
bool Right1Temp = false;
bool Right2Temp = false;
bool MidTemp = false;
bool FrontTemp = false;
bool RewardTemp = false;
  //Initialize the Mouse as Not Having Made a Decision


//intialize
int inc;
int Midtotal;
int L1total;
int L2total;bool MiceLeft = false;
bool MiceRight = false; 
  //Initialize the Reward as not given
bool rewardgiven = false;
int R1total;
int R2total;
int Fronttotal;
int Rewardtotal;
float MidIRvalArray[4];
float Left1IRvalArray[4];
float Left2IRvalArray[4];
float Right1IRvalArray[4];
float Right2IRvalArray[4];
float FrontIRvalArray[4];
float RewardIRvalArray[4];

String paneldirection = "left";

int Midbaseline;
int L1baseline;
int L2baseline;
int R1baseline;
int R2baseline;
int Frontbaseline;
int Rewardbaseline;

int midtime0;
int left1time0;
int left2time0;
int right1time0;
int right2time0;
int fronttime0;
int rewardtime0;

int trialNumber;
unsigned long a;
unsigned long b;
unsigned long c;
int w;

void setup() {
  definepins();
  defineservos();
  Serial.begin(9600);
  initialize();
  closedoors();
  water.setSpeed(255);
  motor.setSpeed(20);  // 10 rpm   
  randomSeed(analogRead(33));
  water.run(RELEASE);
  Serial.println("CLEARDATA"); 
  Serial.println("LABEL,Trial Number,Trial Start(Milli Sec.),Direction (L)eft or (R)ight, Decision Time, Mouse Choice L or R, Success, Reward Time");
}

void loop() {
  if (trialNumber == -1){
    get3random();
    trialNumber = 0;
  }
  if (TrialStart == true) {
    MidBroken = false;
    resetBeams();
    rewardgiven = false; 
    while (MidBroken == false) {
      checkmid();
    }
    //once the mouse is in the central cooridor the tactile wheel must rotate into place for the mouse to whisk against it
    trialNumber++;
    Serial.print("DATA,");
    Serial.print(trialNumber);
    Serial.print(",");
    Serial.print("TIME");
    w = 0;
    a = millis();
    Serial.print(",");
    TrialStart = false;
    leftright();
    resetBeams();
    TrialTouch = true;
  }
  else if (TrialTouch == true) {
    while (FrontBroken == false){
      checkfront();
    }
    TrialTouch = false;
    TrialDecide = true;
    if ((currentface == 1) or (currentface ==3)){
      openleft();
      Serial.print("L" + String(currentface) + ",");
      paneldirection = "left";
    }
    else if ((currentface == 2) or (currentface == 4)){
      openright();
      Serial.print("R" + String(currentface) + ",");
      paneldirection = "right";
    }
  }
  else if (TrialDecide == true) {
    //check for both Left1 and Left2
    //Serial.println("Trial Decision Point");
    while (Left2Broken == false and Right2Broken == false){
    //(not (Left1Broken == true and Left2Broken == true) and not (Right1Broken == true and Right2Broken == true) and not (Right2Broken == true and Right1Broken == false) or (Left2Broken == true and Left1Broken == false)){
      if (MidBroken == false){
          checkmid();
        }
      if (Left1Broken == false){
        checkleft1();
      }
      if (Left2Broken == false){ 
        checkleft2();
      }
      if (Right1Broken == false){
        checkright1();
      }
      if (Right2Broken == false){
        checkright2();
      }  
    }
    
    if (Left1Broken == true and Left2Broken == true){
      closedoors();
      MiceLeft = true;
      TrialDecide = false;
      TrialReward = true;
      //Serial.println("The Mouse Went Left");
      b = millis();
      Serial.print((b-a));
      Serial.print(",");
      Serial.print("L");
      Serial.print(",");

    }
    //check for both Right1 and Right2
    if (Right1Broken == true and Right2Broken == true){
      closedoors();
      MiceRight = true;
      TrialDecide = false;
      TrialReward = true;
      //Serial.println("The Mouse Went Right");
      b = millis();
      Serial.print((b-a));
      Serial.print(",");
      Serial.print("R");
      Serial.print(",");

    }
    if (Right1Broken == false){
      if (Right2Broken == true){
        // test to see if the mouse has gone back through the maze
      //Serial.println("The Mouse Failed the Trial");
      b = millis();
      Serial.print(b-a);
      Serial.print(",");
      Serial.print("N");
      Serial.print(",");
      Serial.print("F-R");
      Serial.print(",");
      Serial.println("NA");
      TrialReward = false;

      failtrial();
      }
    }
    if (Left2Broken == true){
      if (Left1Broken == false){
        b = millis();
        Serial.print(b-a);
        Serial.print(",");
        Serial.print("N");
        Serial.print(",");
        Serial.print("F-L");
        Serial.print(",");
        Serial.println("NA");
        TrialReward = false;
        failtrial();
      }
    }
    /*
    else { //check to see if beams are broken
      if (MidBroken == false){
        checkmid();
      }
      if (Left1Broken == false){
        checkleft1();
      }
      if (Left2Broken == false){
        checkleft2();
      }
      if (Right1Broken == false){
        checkright1();
      }
      if (Right2Broken == false){
        checkright2();
      }
    }
    */
  }
  else if (TrialReward == true) {
    //Serial.println("Trial Reward");
   
    if (((MiceRight == true) and (paneldirection = "right")) or ((MiceLeft == true) and (paneldirection = "left"))) {
      //Serial.println("Mouse gets reward");
      Serial.print("T");
      Serial.print(",");
      while(RewardBroken == false){
        checkreward();
        c = millis();
        if ((c-b) > 60000){
           Serial.println("Mouse Waited Too Long");
           failtrial();
           w = 3;
           break;
        }
        //Serial.println(analogRead(RewardIRread));
      }
      if (w==0){
        givereward();
        Serial.println((c-b));
      }
      RewardBroken = false;
      TrialReward = false;
      MiceRight = false;
      MiceLeft = false;
      beginnewtrial();
    }
    else{
      noreward();
      Serial.print("F");
      Serial.print(",");
      Serial.println("NA");
      failtrial();
      resetBeams();
      //Serial.println("Mouse Does Not Get a Reward");
      TrialReward = false;
      beginnewtrial();
    }
  }
}
// ---------------------
//Setup Functions

void definepins() {

  pinMode(MidIRread, INPUT);
  pinMode(Right1IRread, INPUT);
  pinMode(Right2IRread, INPUT);
  pinMode(Left1IRread, INPUT);
  pinMode(Left2IRread, INPUT);
  pinMode(FrontIRread, INPUT);
  pinMode(RewardIRread, INPUT);
  pinMode(rewarddirect, OUTPUT);
  digitalWrite(rewarddirect, HIGH); //set forward direction
  pinMode(rewardbrake, OUTPUT);
}
void defineservos() {

  rightDoorServo.attach(rightDoorServoPin);

  leftDoorServo.attach(leftDoorServoPin);
}


void initialize() {

  
  /*
  digitalWrite(MidIRread, HIGH);
  digitalWrite(Right1IRread, HIGH);
  digitalWrite(Right2IRread, HIGH);
  digitalWrite(Left1IRread, HIGH);
  digitalWrite(Left2IRread, HIGH);
  digitalWrite(FrontIRread, HIGH);
  digitalWrite(RewardIRread, HIGH);
  */
  
  
  while (Midtotal!=3 && L1total!=3 && L2total!=3 && R1total!=3 && R2total!=3 && Fronttotal!=3 && Rewardtotal!=3){
    Midtotal=0;
    L1total=0;
    L2total=0;
    R1total=0;
    R2total=0;
    Fronttotal=0;
    Rewardtotal=0;
    
    for (inc=0; inc < 4 ; inc++ ){
      MidIRvalArray[inc] = analogRead(MidIRread);
      Left1IRvalArray[inc] = analogRead(Left1IRread);
      Left2IRvalArray[inc] = analogRead(Left2IRread);
      Right1IRvalArray[inc] = analogRead(Right1IRread);
      Right2IRvalArray[inc] = analogRead(Right2IRread);
      FrontIRvalArray[inc] = analogRead(FrontIRread);
      RewardIRvalArray[inc] = analogRead(RewardIRread);
      
      if ((inc>0) && MidIRvalArray[inc]==MidIRvalArray[inc-1]){
        Midtotal++;
      }
      if ((inc>0) && Left1IRvalArray[inc]==Left1IRvalArray[inc-1]){
        L1total++;
      }
      if ((inc>0) && Left2IRvalArray[inc]==Left2IRvalArray[inc-1]){
        L2total++;
      }
      if ((inc>0) && Right1IRvalArray[inc]==Right1IRvalArray[inc-1]){
        R1total++;
      }   
      if ((inc>0) && Right2IRvalArray[inc]==Right2IRvalArray[inc-1]){
        R2total++;
      } 
      if ((inc>0) && FrontIRvalArray[inc]==FrontIRvalArray[inc-1]){
        Fronttotal++;
      }  
      if ((inc>0) && RewardIRvalArray[inc]==RewardIRvalArray[inc-1]){
        Rewardtotal++;
      }  
      delay(10);
      Serial.print("\t");
      Serial.print("Mid IR val ");
      Serial.print((long)MidIRvalArray[inc], DEC);
      Serial.print(" & Left1 IR val ");
      Serial.print((long)Left1IRvalArray[inc], DEC);
      Serial.print(" & Left2 IR val ");
      Serial.print((long)Left2IRvalArray[inc], DEC); 
      Serial.print(" & Right1 IR val "); 
      Serial.print((long)Right1IRvalArray[inc], DEC);
      Serial.print(" & Right2 IR val "); 
      Serial.print((long)Right2IRvalArray[inc], DEC);
      Serial.print(" & Front IR val "); 
      Serial.print((long)FrontIRvalArray[inc], DEC);
      Serial.print(" & Reward IR val "); 
      Serial.println((long)RewardIRvalArray[inc], DEC);
    }
  }
  Midbaseline=MidIRvalArray[3];
  L1baseline=Left1IRvalArray[3];
  L2baseline=Left2IRvalArray[3];
  R1baseline=Right1IRvalArray[3];
  R2baseline=Right2IRvalArray[3];
  Frontbaseline=FrontIRvalArray[3];
  Rewardbaseline=RewardIRvalArray[3];
  
  Serial.print("Middle Baseline value is ");
  Serial.print(Midbaseline);
  Serial.print("\t");
  Serial.print("Left 1 Baseline value is ");
  Serial.print(L1baseline);
  Serial.print("\t");
  Serial.print("Left 2 Baseline value is ");
  Serial.print(L2baseline);
  Serial.print("\t");
  Serial.print("and Right 1 Baseline value is ");
  Serial.print(R1baseline);
  Serial.print("\t");
  Serial.print("and Right 2 Baseline value is ");
  Serial.print(R2baseline);
  Serial.print("\t");
  Serial.print(" and Front Baseline value is ");
  Serial.print(Frontbaseline);
  Serial.print("\t");
  Serial.print(" and Reward Baseline value is ");
  Serial.print(Rewardbaseline);
  Serial.print("\t");
  Serial.println("End initialization");
  // tell the PC we are ready
  Serial.println("<Arduino is ready>");
  

}

//New Trial Commands

void beginnewtrial() {
  resetBeams();
  rightshut();
  get3random();
  closedoors();
  delay(500); // wait 5 seconds
  //Serial.println("New Trial has begun");
  TrialStart = true;
}

void resetBeams(){
  Left1Broken = false;
  Left2Broken = false;
  Right1Broken = false;
  Right2Broken = false;
  MidBroken = false;
  FrontBroken = false;
  RewardBroken = false;
  MiceRight = false;
  MiceLeft = false;
  //Serial.println("Beams Reset");
}

void leftright(){
  //alternates left or right
  if (paneldirection == "left"){
    paneldirection = "right";
  }
  else {
    paneldirection = "left";
  }
}

void randpanel(){
  // picks a random number
  int r = random(1,7);
  
  //puts that panel at decision point
  //bringpanel(r);
  
  //makes it a left or right task
  if (r == 1 or r == 2 or r == 4){
    paneldirection = "left";
    //Serial.println("Left Trial");
  }
  else {
    paneldirection = "right";
     //Serial.println("Right Trial");
  }
}

void bringpanel(int r){
  //spins a servo a full turn and then goes to integer r location
}

//Mechanical Functions

void opendoors() { //open both left and right doors
  
  rightDoorServo.attach(rightDoorServoPin);
  leftDoorServo.attach(leftDoorServoPin);
  rightDoorServo.write(rightDoorServoOpenVal);
  leftDoorServo.write(leftDoorServoOpenVal);
  delay(1000);
  rightDoorServo.detach();
  leftDoorServo.detach();
}
void openright() { //open both left and right doors
  
  rightDoorServo.attach(rightDoorServoPin);
  rightDoorServo.write(rightDoorServoOpenVal);
  delay(1000);
  rightDoorServo.detach();
}

void openleft() { //open both left and right doors
  
  leftDoorServo.attach(leftDoorServoPin);
  leftDoorServo.write(leftDoorServoOpenVal);
  delay(1000);
  leftDoorServo.detach();
}

void closedoors() { //close both left and right doors
  rightDoorServo.attach(rightDoorServoPin);
  leftDoorServo.attach(leftDoorServoPin);
  rightDoorServo.write(rightDoorServoCloseVal);
  leftDoorServo.write(leftDoorServoCloseVal);
  delay(1000);
  rightDoorServo.detach();
  leftDoorServo.detach();
}

//RewardActions

void givereward() {   // tell solenoid to dispense water when mouse puts head in beam
  water.run(FORWARD);
  delay(1000);
  //water.run(BACKWARD);
  //delay(100);
  water.run(RELEASE);
    /* digitalWrite(rewardbrake, LOW); //disengage the brake
    analogWrite(rewardspeed, 255); //run at max value
    delay(200); //wait 100 milliseconds for the reward
    analogWrite(rewardspeed, 200); //run at max value
    digitalWrite(rewardbrake, HIGH); // engage the brake
*/
}

void noreward() {
  //tell solenoid to give no reward and pause before going into next trial
}

//Running Trial Functions

void checkmid(){
  if (analogRead(MidIRread) < Midbaseline - 50) {
    if (MidTemp == true) {
      if (millis() - midtime0 > grace) {
        MidBroken = true;
        Left1Broken = false;
        Left2Broken = false;
        Right1Broken = false;
        Right2Broken = false;
      }
    }
    else {
      midtime0 = millis();
      MidTemp = true;
    }
  }
  else {
    MidTemp = false;
  }
}

void checkfront() {
  if (analogRead(FrontIRread) < Frontbaseline - 50) {
    if (FrontTemp == true) {
      if (millis() - fronttime0 > grace) {
        FrontBroken = true;
      }
    }
    else {
      fronttime0 = millis();
      FrontTemp = true;
    }
  }
  else {
    FrontTemp = false;
  }
}

void checkleft1() {
  if (analogRead(Left1IRread) < L1baseline - 30) {
    if (Left1Temp == true) {
      if (millis() - left1time0 > grace) {
        Left1Broken = true;
        Right1Broken = false;
        Left2Broken = false;
        MidBroken = false;
        
      }
    }
    else {
      left1time0 = millis();
      Left1Temp = true;
    }
  }
  else {
    Left1Temp = false;
  }
}

void checkleft2() {
  if (analogRead(Left2IRread) < L2baseline - 50) {
    if (Left2Temp == true) {
      if (millis() - left2time0 > grace) {
        Left2Broken = true;
      }
    }
    else {
      left2time0 = millis();
      Left2Temp = true;
    }
  }
  else {
    Left2Temp = false;
  }
}

void checkright1() {
  if (analogRead(Right1IRread) < R1baseline - 60) {
    if (Right1Temp == true) {
      if (millis() - right1time0 > grace) {
        Right1Broken = true;
        Left1Broken = false;
        Left2Broken = false;
        MidBroken = false;
      }
    }
    else {
      right1time0 = millis();
      Right1Temp = true;
    }
  }
  else {
    Right1Temp = false;
  }
}

void checkright2() {
  if (analogRead(Right2IRread) < R2baseline - 50) {
    if (Right2Temp == true) {
      if (millis() - right2time0 > grace) {
        Right2Broken = true;
      }
    }
    else {
      right2time0 = millis();
      Right2Temp = true;
    }
  }
  else {
    Right2Temp = false;
  }
}

void checkreward() {
  if (analogRead(RewardIRread) < Rewardbaseline - 60) {
    if (RewardTemp == true) {
      if (millis() - rewardtime0 > grace) {
        RewardBroken = true;
        //Serial.println("Reward Broken");
      }
    }
    else {
      rewardtime0 = millis();
      RewardTemp = true;
    }
  }
  else {
    RewardTemp = false;
  }
}

//Ending a Trial

void failtrial(){
  rightshut();
  get3random();
  closedoors();
  TrialStart = true;
  TrialTouch = false;
  TrialDecide = false;
  TrialReward = false;
  
  delay(500); //wait 3 seconds
}

void rightshut();{
  closedoors();
  delay(100);
  leftDoorServo.attach(leftDoorServoPin);
  leftDoorServo.write(leftDoorServoShutVal);
  delay(300);
  leftDoorServo.detach();
}

// Panel Rotate

void get3random(){
  panelindex = random(0,8);
  rotate();
  panelindex = random(0,8);
  rotate();
  panelindex = random(0,8);
  rotate();
}

void rotate(){
  if (panelindex==0){
    for1();
  }
  else if (panelindex==1){
    for2();
  }
  else if (panelindex==2){
    for3();
  }
  else if (panelindex==3){
    for4();
  }
  else if (panelindex==4){
    back1();
  }
  else if (panelindex==5){
    back2();
  }
  else if (panelindex==6){
    back3();
  }
  else if (panelindex==7){
    back4();
  }
  delay(100);
}

void for1(){
 if (currentface == 1) {
    motor.step(200, FORWARD, SINGLE); 
  }
  else if (currentface == 2) {
    motor.step(150, FORWARD, SINGLE);
  }
  else if (currentface == 3) {
    motor.step(100, FORWARD, SINGLE); 
  }
  else if (currentface == 4) {
    motor.step(50, FORWARD, SINGLE);
  }
  currentface = 1;
}

void for2(){
  if (currentface == 1) {
    motor.step(50, FORWARD, SINGLE); 
  }
  else if (currentface == 2) {
    motor.step(200, FORWARD, SINGLE);
  }
  else if (currentface == 3) {
    motor.step(150, FORWARD, SINGLE); 
  }
  else if (currentface == 4) {
    motor.step(100, FORWARD, SINGLE);
  }
  currentface = 2;
}

void for3(){
 if (currentface == 1) {
    motor.step(100, FORWARD, SINGLE); 
  }
  else if (currentface == 2) {
    motor.step(50, FORWARD, SINGLE);
  }
  else if (currentface == 3) {
    motor.step(200, FORWARD, SINGLE); 
  }
  else if (currentface == 4) {
    motor.step(150, FORWARD, SINGLE);
  }
  currentface = 3;
}

void for4(){
  if (currentface == 1) {
    motor.step(150, FORWARD, SINGLE); 
  }
  else if (currentface == 2) {
    motor.step(100, FORWARD, SINGLE);
  }
  else if (currentface == 3) {
    motor.step(50, FORWARD, SINGLE); 
  }
  else if (currentface == 4) {
    motor.step(200, FORWARD, SINGLE);
  }
  currentface = 4;
}

void back1(){
 if (currentface == 1) {
    motor.step(200, BACKWARD, SINGLE); 
  }
  else if (currentface == 2) {
    motor.step(50, BACKWARD, SINGLE);
  }
  else if (currentface == 3) {
    motor.step(100, BACKWARD, SINGLE); 
  }
  else if (currentface == 4) {
    motor.step(150, BACKWARD, SINGLE);
  }
  currentface = 1;
}

void back2(){
  if (currentface == 1) {
    motor.step(150, BACKWARD, SINGLE); 
  }
  else if (currentface == 2) {
    motor.step(200, BACKWARD, SINGLE);
  }
  else if (currentface == 3) {
    motor.step(50, BACKWARD, SINGLE); 
  }
  else if (currentface == 4) {
    motor.step(100, BACKWARD, SINGLE);
  }
  currentface = 2;
}

void back3(){
 if (currentface == 1) {
    motor.step(100, BACKWARD, SINGLE); 
  }
  else if (currentface == 2) {
    motor.step(150, BACKWARD, SINGLE);
  }
  else if (currentface == 3) {
    motor.step(200, BACKWARD, SINGLE); 
  }
  else if (currentface == 4) {
    motor.step(150, BACKWARD, SINGLE);
  }
  currentface = 3;
}

void back4(){
  if (currentface == 1) {
    motor.step(50, BACKWARD, SINGLE); 
  }
  else if (currentface == 2) {
    motor.step(100, BACKWARD, SINGLE);
  }
  else if (currentface == 3) {
    motor.step(150, BACKWARD, SINGLE); 
  }
  else if (currentface == 4) {
    motor.step(200, BACKWARD, SINGLE);
  }
  currentface = 4;
}