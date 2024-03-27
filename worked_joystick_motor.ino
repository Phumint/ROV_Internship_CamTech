const int RENa = 8; const int LENa = 9;
const int RPWMa = 10; const int LPWMa = 11;
const int RENb = 3; const int LENb = 2;
const int RPWMb = 5; const int LPWMb = 4;
const int joyY = A1;
const int joyX = A0;
int deadzone = 15;
int center = 495;
int pwmL = 0;
int pwmR = 0;
int mapY = 0;
int mapX = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for (int i =2; i<=11; i++) {
  pinMode(i, 1);
  }
  digitalWrite(RENa, HIGH);
  digitalWrite(RENb, HIGH);
  digitalWrite(LENa, HIGH);
  digitalWrite(LENb, HIGH);
}


void loop() {
  // put your main code here, to run repeatedly:
  int yRead = analogRead(joyY);
  int xRead = analogRead(joyX);

  //turn clockwise
  if (yRead > center + deadzone){
    mapY = map(yRead, center + deadzone, 1023, 0, 255);
    pwmL = mapY;
    pwmR = mapY;
    //turn left
    if (xRead > center + deadzone){
      mapX = map(xRead, center + deadzone, 1023, 0, 255);
      pwmL = pwmL - mapX;
      pwmL = constrain(pwmL, 0, 255);
    }
    //turn right
    else if(xRead < center - deadzone){
      mapX = map(xRead, center - deadzone, 0, 0, 255);
      pwmR = pwmR - mapX;
      pwmR = constrain(pwmR, 0, 255);
    }
    //no turn 
    else{
      mapX = 0;
    }    
    analogWrite(RPWMa, pwmR);
    analogWrite(LPWMa, 0);
    analogWrite(RPWMb, pwmL);
    analogWrite(LPWMb, 0);
  }
  else if (yRead < center - deadzone){
    mapY = map(yRead, center + deadzone, 0, 0, 255);
    pwmL = mapY;
    pwmR = mapY;
    //turn left
    if (xRead > center + deadzone){
      mapX = map(xRead, center + deadzone, 1023, 0, 255);
      pwmL = pwmL - mapX;
      pwmL = constrain(pwmL, 0, 255);
    }
    //turn right
    else if(xRead < center - deadzone){
      mapX = map(xRead, center - deadzone, 0, 0, 255);
      pwmR = pwmR - mapX;
      pwmR = constrain(pwmR, 0, 255);
    }
    //no turn 
    else{
      mapX = 0;
    }    
    analogWrite(RPWMa, 0);
    analogWrite(LPWMa, pwmR);
    analogWrite(RPWMb, 0);
    analogWrite(LPWMb, pwmL);
  }
  else{
    pwmL = 0;
    pwmR = 0;
    analogWrite(RPWMa, pwmL);
    analogWrite(LPWMa, 0);
    analogWrite(RPWMb, pwmR);
    analogWrite(LPWMb, 0);
  }
  
  // Print motor speed and joy value for debugging
  Serial.print("PWML: ");
  Serial.print(pwmL);
  Serial.print(" | ");
  Serial.print("PWMR: ");
  Serial.print(pwmR);
  Serial.print(" | ");
  Serial.print("Joy Y: ");
  Serial.print(yRead);
  Serial.print(" | ");
  Serial.print("Joy X: ");
  Serial.print(xRead);
  Serial.println();
}
