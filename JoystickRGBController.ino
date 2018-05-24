#include <math.h>
int blue = 6;
int green = 5;
int red = 3;
int yPin = A1;
int xPin = A0;
double greenMax = 255;
double redMax = 255 * .5;
double blueMax = 255;
double yVal;
double xVal;
double xIn;
double yIn;
double theta;
double pwm;
double deg;
double r;

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
    pinMode(red, OUTPUT);

}

// the loop routine runs over and over again forever:
void loop() {
  
  yIn = analogRead(yPin);
  xIn = analogRead(xPin);
  xVal = map(xIn, 0, 1023, -127, 127);
  yVal = map(yIn, 0, 1023, -127, 127);
  theta = fabs(atan(yVal / xVal));
  deg = theta * 180 / M_PI;
  r = sqrt(fabs(xVal * xVal) + fabs(yVal * yVal));
  
  if (xVal < 0 && yVal >= 0) deg = 90 - deg + 90;
  else if (xVal <= 0 && yVal < 0) deg += 180;
  else if (xVal >= 0 && yVal < 0) deg = (90 - deg) + 270;
  
  if(r <= 5){
    analogWrite(blue, blueMax);
    analogWrite(green, greenMax);
    analogWrite(red, redMax);
  }
  else if(deg > 0 && deg <= 120){
  pwm = map(deg, 0, 120, 0, 255);
  analogWrite(green, 0);
  analogWrite(blue, 255 - pwm);
  analogWrite(red, pwm);
  }
  else if (deg > 120 && deg <= 240){
  pwm = map(deg, 120, 240, 0, 255);
  analogWrite(blue, 0);
  analogWrite(red, 255 - pwm);
  analogWrite(green, pwm);
  }
  else if (deg > 240 && deg < 360){
    pwm = map(deg, 240, 360, 0, 255);
    analogWrite(red, 0);
    analogWrite(green, 255 - pwm);
    analogWrite(blue, pwm);
  }
}


