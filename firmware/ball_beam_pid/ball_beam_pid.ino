/*PID controller system with Arduino.
 * https://srituhobby.com
 */

#include <ESP32Servo.h>

Servo servo;

#define trig 4
#define echo 13

#define kp 8
#define ki 0.2
#define kd 3500

double priError = 0;
double toError = 0;

void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  servo.attach(8);
  Serial.begin(9600);
  servo.write(50);

}
void loop() {
  PID();
  //  int a = distance();
  //  Serial.println(a);
}

long distance () {
  digitalWrite(trig, LOW);
  delayMicroseconds(4);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long t = pulseIn(echo, HIGH);
  long cm = t / 40 / 2;
  Serial.println(cm);
  return cm;
}

void PID() {
  int dis = distance ();


  int setP = 20;
  double error = setP - dis;


  double Pvalue = error * kp;
  double Ivalue = toError * ki;
  double Dvalue = (error - priError) * kd;

  double PIDvalue = Pvalue + Ivalue + Dvalue;
  priError = error;
  toError += error;
  // Serial.println(PIDvalue);
  int Fvalue = (int)PIDvalue;
  //Serial.println(Fvalue);


  Fvalue = map(Fvalue, -150, 150, 0, 150);


  if (Fvalue < 0) {
    Fvalue = 0;
  }
  if (Fvalue > 40) {
    Fvalue = 40;
  }

  servo.write(Fvalue);
}
