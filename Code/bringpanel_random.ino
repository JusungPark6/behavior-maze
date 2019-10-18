//texture panel using a stepper motor
//4 panels

const int Paneldir = 2;  // Direction
const int Panelstep = 3; // Step
// Motor steps per rotation
const int rotation = 200; // 200 steps = 360 degrees per full rotation
int currentdirection;
int currentposition = 1; //which panel is currently being presented
int r;

void setup() {
  // Setup the pins as Outputs
  pinMode(Panelstep,OUTPUT); 
  pinMode(Paneldir,OUTPUT);
  Serial.begin(9600);
}
void loop() {
  r = random(1,9);
  
  if (r == 1){ //bring panel 1 clockwise
    currentdirection = HIGH; //set direction to clockwise
    digitalWrite(Paneldir, currentdirection);
    Serial.println("bringing panel 1");
    if(currentposition == 1){
      for(int x = 0; x < (rotation); x++) {
      digitalWrite(Panelstep,HIGH);
      delayMicroseconds(1000);
      digitalWrite(Panelstep,LOW);
      delayMicroseconds(1000);
      }
    }
    
    if(currentposition == 2){
      for(int x = 0; x < (rotation/4); x++) {
      digitalWrite(Panelstep,HIGH);
      delayMicroseconds(1000);
      digitalWrite(Panelstep,LOW);
      delayMicroseconds(1000);
      }
    }
    if(currentposition == 3){
      for(int x = 0; x < (rotation/2); x++) {
      digitalWrite(Panelstep,HIGH);
      delayMicroseconds(1000);
      digitalWrite(Panelstep,LOW);
      delayMicroseconds(1000);
      }
    }
    if(currentposition == 4){
      for(int x = 0; x < (rotation*.75); x++) {
      digitalWrite(Panelstep,HIGH);
      delayMicroseconds(1000);
      digitalWrite(Panelstep,LOW);
      delayMicroseconds(1000);
      }
    }
    delay(1000);
    currentposition = 1;
    
  }
  
  if (r == 2){ //bring panel 2 clockwise
    currentdirection = HIGH; //set direction to clockwise
    digitalWrite(Paneldir, currentdirection);
    Serial.println("bringing panel 2");
    if(currentposition == 1){
      for(int x = 0; x < (rotation*.75); x++) {
      digitalWrite(Panelstep,HIGH);
      delayMicroseconds(1000);
      digitalWrite(Panelstep,LOW);
      delayMicroseconds(1000);
      }
    }
    
    if(currentposition == 2){
      for(int x = 0; x < (rotation); x++) {
      digitalWrite(Panelstep,HIGH);
      delayMicroseconds(1000);
      digitalWrite(Panelstep,LOW);
      delayMicroseconds(1000);
      }
    }
    if(currentposition == 3){
      for(int x = 0; x < (rotation/4); x++) {
      digitalWrite(Panelstep,HIGH);
      delayMicroseconds(1000);
      digitalWrite(Panelstep,LOW);
      delayMicroseconds(1000);
      }
    }
    if(currentposition == 4){
      for(int x = 0; x < (rotation/2); x++) {
      digitalWrite(Panelstep,HIGH);
      delayMicroseconds(1000);
      digitalWrite(Panelstep,LOW);
      delayMicroseconds(1000);
      }
    }
    delay(1000);
    currentposition = 2;
  }
  if (r == 3){ //bring panel 3 clockwise
    currentdirection = HIGH; //set direction to clockwise
    digitalWrite(Paneldir, currentdirection);
    Serial.println("bringing panel 3");
    if(currentposition == 1){
      for(int x = 0; x < (rotation/2); x++) {
      digitalWrite(Panelstep,HIGH);
      delayMicroseconds(1000);
      digitalWrite(Panelstep,LOW);
      delayMicroseconds(1000);
      }
    }
    
    if(currentposition == 2){
      for(int x = 0; x < (rotation*.75); x++) {
      digitalWrite(Panelstep,HIGH);
      delayMicroseconds(1000);
      digitalWrite(Panelstep,LOW);
      delayMicroseconds(1000);
      }
    }
    if(currentposition == 3){
      for(int x = 0; x < (rotation); x++) {
      digitalWrite(Panelstep,HIGH);
      delayMicroseconds(1000);
      digitalWrite(Panelstep,LOW);
      delayMicroseconds(1000);
      }
    }
    if(currentposition == 4){
      for(int x = 0; x < (rotation/4); x++) {
      digitalWrite(Panelstep,HIGH);
      delayMicroseconds(1000);
      digitalWrite(Panelstep,LOW);
      delayMicroseconds(1000);
      }
    }
    delay(1000);
    currentposition = 3;
    
  }
  
  if (r == 4){ //bring panel 4 clockwise
    currentdirection = HIGH; //set direction to clockwise
    digitalWrite(Paneldir, currentdirection);
    Serial.println("bringing panel 4");  
    if(currentposition == 1){
      for(int x = 0; x < (rotation/4); x++) {
      digitalWrite(Panelstep,HIGH);
      delayMicroseconds(1000);
      digitalWrite(Panelstep,LOW);
      delayMicroseconds(1000);
      }
    }
    
    if(currentposition == 2){
      for(int x = 0; x < (rotation/2); x++) {
      digitalWrite(Panelstep,HIGH);
      delayMicroseconds(1000);
      digitalWrite(Panelstep,LOW);
      delayMicroseconds(1000);
      }
    }
    if(currentposition == 3){
      for(int x = 0; x < (rotation*.75); x++) {
      digitalWrite(Panelstep,HIGH);
      delayMicroseconds(1000);
      digitalWrite(Panelstep,LOW);
      delayMicroseconds(1000);
      }
    }
    if(currentposition == 4){
      for(int x = 0; x < (rotation); x++) {
      digitalWrite(Panelstep,HIGH);
      delayMicroseconds(1000);
      digitalWrite(Panelstep,LOW);
      delayMicroseconds(1000);
      }
    }
    delay(1000);
    currentposition = 4;
  }
  
  if (r == 5){ //bring panel 1 counterclockwise
    currentdirection = LOW; //set direction to counterclockwise
    digitalWrite(Paneldir, currentdirection);
     Serial.println("bringing panel 1");
    if(currentposition == 1){
      for(int x = 0; x < (rotation); x++) {
      digitalWrite(Panelstep,HIGH);
      delayMicroseconds(1000);
      digitalWrite(Panelstep,LOW);
      delayMicroseconds(1000);
      }
    }
    
    if(currentposition == 2){
      for(int x = 0; x < (rotation*.75); x++) {
      digitalWrite(Panelstep,HIGH);
      delayMicroseconds(1000);
      digitalWrite(Panelstep,LOW);
      delayMicroseconds(1000);
      }
    }
    if(currentposition == 3){
      for(int x = 0; x < (rotation/2); x++) {
      digitalWrite(Panelstep,HIGH);
      delayMicroseconds(1000);
      digitalWrite(Panelstep,LOW);
      delayMicroseconds(1000);
      }
    }
    if(currentposition == 4){
      for(int x = 0; x < (rotation/4); x++) {
      digitalWrite(Panelstep,HIGH);
      delayMicroseconds(1000);
      digitalWrite(Panelstep,LOW);
      delayMicroseconds(1000);
      }
    }
    delay(1000);
    currentposition = 1;
  }
  
  if (r == 6){ //bring panel 2 counterclockwise
    currentdirection = LOW; //set direction to counterclockwise
    digitalWrite(Paneldir, currentdirection);
     Serial.println("bringing panel 2");
    if(currentposition == 1){
      for(int x = 0; x < (rotation/4); x++) {
      digitalWrite(Panelstep,HIGH);
      delayMicroseconds(1000);
      digitalWrite(Panelstep,LOW);
      delayMicroseconds(1000);
      }
    }
    
    if(currentposition == 2){
      for(int x = 0; x < (rotation); x++) {
      digitalWrite(Panelstep,HIGH);
      delayMicroseconds(1000);
      digitalWrite(Panelstep,LOW);
      delayMicroseconds(1000);
      }
    }
    if(currentposition == 3){
      for(int x = 0; x < (rotation*.75); x++) {
      digitalWrite(Panelstep,HIGH);
      delayMicroseconds(1000);
      digitalWrite(Panelstep,LOW);
      delayMicroseconds(1000);
      }
    }
    if(currentposition == 4){
      for(int x = 0; x < (rotation/2); x++) {
      digitalWrite(Panelstep,HIGH);
      delayMicroseconds(1000);
      digitalWrite(Panelstep,LOW);
      delayMicroseconds(1000);
      }
    }
    delay(1000);
    currentposition = 2;
    
  }
  
  if (r == 7){ //bring panel 3 counterclockwise
    currentdirection = LOW; //set direction to counterclockwise
    digitalWrite(Paneldir, currentdirection);
     Serial.println("bringing panel 3");
    if(currentposition == 1){
      for(int x = 0; x < (rotation/2); x++) {
      digitalWrite(Panelstep,HIGH);
      delayMicroseconds(1000);
      digitalWrite(Panelstep,LOW);
      delayMicroseconds(1000);
      }
    }
    
    if(currentposition == 2){
      for(int x = 0; x < (rotation/4); x++) {
      digitalWrite(Panelstep,HIGH);
      delayMicroseconds(1000);
      digitalWrite(Panelstep,LOW);
      delayMicroseconds(1000);
      }
    }
    if(currentposition == 3){
      for(int x = 0; x < (rotation); x++) {
      digitalWrite(Panelstep,HIGH);
      delayMicroseconds(1000);
      digitalWrite(Panelstep,LOW);
      delayMicroseconds(1000);
      }
    }
    if(currentposition == 4){
      for(int x = 0; x < (rotation*.75); x++) {
      digitalWrite(Panelstep,HIGH);
      delayMicroseconds(1000);
      digitalWrite(Panelstep,LOW);
      delayMicroseconds(1000);
      }
    }
    delay(1000);
    currentposition = 3;
    
  }
  
  if (r == 8){ //bring panel 4 counterclockwise
    currentdirection = LOW; //set direction to counterclockwise
    digitalWrite(Paneldir, currentdirection);
     Serial.println("bringing panel 4");
    if(currentposition == 1){
      for(int x = 0; x < (rotation*.75); x++) {
      digitalWrite(Panelstep,HIGH);
      delayMicroseconds(1000);
      digitalWrite(Panelstep,LOW);
      delayMicroseconds(1000);
      }
    }
    
    if(currentposition == 2){
      for(int x = 0; x < (rotation/2); x++) {
      digitalWrite(Panelstep,HIGH);
      delayMicroseconds(1000);
      digitalWrite(Panelstep,LOW);
      delayMicroseconds(1000);
      }
    }
    if(currentposition == 3){
      for(int x = 0; x < (rotation/4); x++) {
      digitalWrite(Panelstep,HIGH);
      delayMicroseconds(1000);
      digitalWrite(Panelstep,LOW);
      delayMicroseconds(1000);
      }
    }
    if(currentposition == 4){
      for(int x = 0; x < (rotation); x++) {
      digitalWrite(Panelstep,HIGH);
      delayMicroseconds(1000);
      digitalWrite(Panelstep,LOW);
      delayMicroseconds(1000);
      }
    }
    delay(1000);
    currentposition = 4;
    
  }
  delay(5000);
}