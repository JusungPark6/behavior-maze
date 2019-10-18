//Run Solenoid with Arduino Motor Shield
const int rewarddirect = 12;
const int rewardbrake = 9;
const int rewardspeed = 3;
int x;
void setup() {
  //Motor A
  pinMode(rewarddirect, OUTPUT); //Motor A Direction pin
  pinMode(rewardbrake, OUTPUT); //Motor A Brake pin
  digitalWrite(rewarddirect, HIGH); //Set forward direction
  Serial.begin(9600);
}

void loop() {
  // open 
  while (x < 500) {
    digitalWrite(rewardbrake, LOW);  // Disengage the brake
  analogWrite(rewardspeed, 185);   // Run at minimum value
  delay(1000);           // open for 100 milliseconds
  // close
  digitalWrite(rewardbrake, HIGH); // Engage the brake 
  delay(1000);           // Keep close
  x++;
  Serial.println(x);
  }
  break;
}
