#include <math.h>
#define BLUE_PIN 6;
#define GREEN_PIN 5
#define RED_PIN 3
#define yPin A1
#define xPin A0
const double GREEN_MAX_VAL = 255;
const double RED_MAX_VAL = 255 * .5;
const double BLUE_MAX_VAL = 255;
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
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);

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
    analogWrite(BLUE_PIN, BLUE_MAX_VAL);
    analogWrite(GREEN_PIN, GREEN_MAX_VAL);
    analogWrite(RED_PIN, RED_MAX_VAL);
  }
  else if(deg > 0 && deg <= 120){
    pwm = map(deg, 0, 120, 0, 255);
    analogWrite(GREEN_PIN, 0);
    analogWrite(BLUE_PIN, 255 - pwm);
    analogWrite(RED_PIN, pwm);
  }
  else if (deg > 120 && deg <= 240){
    pwm = map(deg, 120, 240, 0, 255);
    analogWrite(BLUE_PIN, 0);
    analogWrite(RED_PIN, 255 - pwm);
    analogWrite(GREEN_PIN, pwm);
  }
  else if (deg > 240 && deg < 360){
    pwm = map(deg, 240, 360, 0, 255);
    analogWrite(RED_PIN, 0);
    analogWrite(GREEN_PIN, 255 - pwm);
    analogWrite(BLUE_PIN, pwm);
  }
}


