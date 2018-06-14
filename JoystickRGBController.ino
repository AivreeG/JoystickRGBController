/*JoystickRGBController.ino
 * Created by Aivree Gomez 
 * Used to change the color of an RGB LED using 
 * an analog joystick.
 */
#include <math.h>
#define BLUE_PIN 6
#define GREEN_PIN 5
#define RED_PIN 3
#define X_PIN A0
#define Y_PIN A1
const double GREEN_MAX_VAL = 255;
const double RED_MAX_VAL = 255;
const double BLUE_MAX_VAL = 255;

double yVal;
double xVal;
double theta;
double pwm;
double deg;

void setup() {
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
}

void loop() {

  xVal = map(analogRead(X_PIN), 0, 1023, -127, 127);
  yVal = map(analogRead(Y_PIN), 0, 1023, -127, 127);

  theta = fabs(atan(yVal / xVal));
  deg = theta * 180 / M_PI;
  
  if (xVal < 0 && yVal >= 0) deg = 90 - deg + 90;
  else if (xVal <= 0 && yVal < 0) deg += 180;
  else if (xVal >= 0 && yVal < 0) deg = (90 - deg) + 270;
  
  if(fabs(xVal) <= 5 && fabs(yVal) <= 5){
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


