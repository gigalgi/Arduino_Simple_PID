// Simple PID Controller Template for Arduino
// Author: Gilberto Garcia

int sampleTime = 300;           // sample time in milliseconds
unsigned long timePrev = 0;     // previous time
unsigned long timeNow = 0;      // current time
int deltaTime = 0;              // actual elapsed time

int setpoint = 90;              // target value
int processVariable = 0;        // measured value from sensor

int outputMax = 255;            // upper output limit
int outputMin = 0;              // lower output limit

double error = 0;
double errorPrev = 0;
double errorIntegral = 0;
double errorDerivative = 0;

double U = 0;                   // raw PID output
double P = 0;
double I = 0;
double D = 0;
double MV = 0;                  // clamped output

double Kp = 0.0205;
double Ki = 0.00022;
double Kd = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  timeNow = millis();
  deltaTime = timeNow - timePrev;

  if (deltaTime >= sampleTime) {

    // read your sensor here
    // processVariable = analogRead(A0);

    error = setpoint - processVariable;

    // trapezoidal integration
    errorIntegral = ((error + errorPrev) / 2.0 * deltaTime) + errorIntegral;

    // anti-windup: freeze integral when output is saturated
    if (MV >= outputMax || MV <= outputMin) {
      errorIntegral -= (error + errorPrev) / 2.0 * deltaTime;
    }

    // derivative using real elapsed time
    errorDerivative = (error - errorPrev) / deltaTime;

    P = Kp * error;
    I = Ki * errorIntegral;
    D = Kd * errorDerivative;

    U = P + I + D;
    MV = constrain(U, outputMin, outputMax);

    // write to your actuator here
    // analogWrite(PIN, MV);

    // serial debug
    Serial.print("SP:"); Serial.print(setpoint);
    Serial.print(" PV:"); Serial.print(processVariable);
    Serial.print(" P:"); Serial.print(P);
    Serial.print(" I:"); Serial.print(I);
    Serial.print(" D:"); Serial.print(D);
    Serial.print(" Out:"); Serial.println(MV);

    errorPrev = error;
    timePrev = timeNow;
  }
}
