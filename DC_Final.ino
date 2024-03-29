#include <MPU9250_asukiaaa.h>
#include <Wire.h>

int MOTOR_PIN1 = 2;
int MOTOR_PIN2 = 3;

// Adjust these sensitivity values as needed
#define ACCEL_SENSITIVITY 1000
#define GYRO_SENSITIVITY 10

MPU9250_asukiaaa mySensor;
float aX, aY, aZ, aSqrt, gX, gY, gZ, mDirection;

void setup() {
 Serial.begin(115200);
 while (!Serial);
 Serial.println("started");

 Wire.begin();  // Use the correct Wire.begin() for Arduino Mega
 mySensor.setWire(&Wire);

 mySensor.beginAccel();  // Start accelerometer
 if (mySensor.accelUpdate() == 0) {
   Serial.println("MPU9250 connection successful");
 } else {
   Serial.println("Cannot connect to MPU9250");
   while (1) {}
 }

 mySensor.beginGyro();  // Start gyroscope

 pinMode(MOTOR_PIN1, OUTPUT);
 pinMode(MOTOR_PIN2, OUTPUT);
}

void loop() {
 // Read accelerometer and gyroscope values
 mySensor.accelUpdate();
 aX = mySensor.accelX();
 aY = mySensor.accelY();
 aZ = mySensor.accelZ();

 mySensor.gyroUpdate();
 gX = mySensor.gyroX();
 gY = mySensor.gyroY();
 gZ = mySensor.gyroZ();

 // Calculate motor speeds based on sensor readings
 int motorSpeed1 = map(aX * ACCEL_SENSITIVITY, -16000 * ACCEL_SENSITIVITY, 16000 * ACCEL_SENSITIVITY, 0, 255);
 int motorSpeed2 = map(gY * GYRO_SENSITIVITY, -250 * GYRO_SENSITIVITY, 250 * GYRO_SENSITIVITY, 0, 255);

 // Constrain motor speeds to valid range (0-255)
 motorSpeed1 = constrain(motorSpeed1, 0, 255);
 motorSpeed2 = constrain(motorSpeed2, 0, 255);

 // Set motor speeds using PWM
 analogWrite(MOTOR_PIN1, motorSpeed1);
 analogWrite(MOTOR_PIN2, motorSpeed2);

 // Print motor speeds to serial monitor (optional for debugging)
 Serial.print("Motor Speed 1: ");
 Serial.println(motorSpeed1);
 Serial.print("Motor Speed 2: ");
 Serial.println(motorSpeed2);

 delay(10);  // Adjust delay as needed for control responsiveness
}
