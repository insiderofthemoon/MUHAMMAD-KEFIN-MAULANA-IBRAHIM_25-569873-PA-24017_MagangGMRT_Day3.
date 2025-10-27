#include <Adafruit_MPU6050.h> 
#include <Adafruit_Sensor.h>  
#include <ESP32Servo.h>       


#define TRIGPIR_PIN 33      
#define SERVO1_PIN 13       
#define SERVO2_PIN 35       
#define SERVO3_PIN 14       
#define SERVO4_PIN 27       
#define SERVO5_PIN 32       

Servo motorRotasi1; 
Servo motorRotasi2; 
Servo motorRotasi3; 
Servo motorRotasi4; 
Servo motorRotasi5; 

Adafruit_MPU6050 sensorAkselerasi;

void setup() {
  Serial.begin(115200);

  while (!Serial)
    delay(10);

  Serial.println("Adafruit MPU6050 test!"); 

  if (!sensorAkselerasi.begin()) {
    Serial.println("Failed to find MPU6050 chip");
  }
  Serial.println("MPU6050 Found!");
  
  pinMode(TRIGPIR_PIN, OUTPUT); 
  motorRotasi1.attach(SERVO1_PIN);
  motorRotasi2.attach(SERVO2_PIN);
  motorRotasi3.attach(SERVO3_PIN);
  motorRotasi4.attach(SERVO4_PIN);
  motorRotasi5.attach(SERVO5_PIN);

  motorRotasi1.write(90);
  motorRotasi2.write(90);
  motorRotasi3.write(90);
  motorRotasi4.write(90);
  motorRotasi5.write(90);

  delay(1000); 
  
}

void loop() {
  sensors_event_t eventAkselerasi, eventGyro, eventSuhu; 
  sensorAkselerasi.getEvent(&eventAkselerasi, &eventGyro, &eventSuhu);

  bool deteksiGerak = digitalRead(TRIGPIR_PIN); 
  Serial.print("\n");
  Serial.print("GERAKAN: "); 
  Serial.print(deteksiGerak);

Serial.print("\n"); 
  if (deteksiGerak == true){ 
    motorRotasi1.write(40);
    motorRotasi2.write(70);
    motorRotasi3.write(100);
    motorRotasi4.write(130);
    motorRotasi5.write(160);
    delay(2000);

    motorRotasi1.write(90); 
    motorRotasi2.write(90);
    motorRotasi3.write(90);
    motorRotasi4.write(90);
    motorRotasi5.write(90);
    delay(2000);
  }
  else {
  Serial.print("Rotation X: ");
  Serial.print(eventGyro.gyro.x);
  int posisiMotor1 = map(eventGyro.gyro.x, +4.3, -4.3, 0, 180); 
  motorRotasi1.write(posisiMotor1);
  int posisiMotor2 = map(eventGyro.gyro.x, +4.3, -4.3, 0, 180);
  motorRotasi2.write(posisiMotor2);

  Serial.print(", Y: ");
  Serial.print(eventGyro.gyro.y);
  int posisiMotor3 = map(eventGyro.gyro.y, -4.3, +4.3, 0, 180);
  motorRotasi3.write(posisiMotor3);
  int posisiMotor4 = map(eventGyro.gyro.y, -4.3, +4.3, 0, 180);
  motorRotasi4.write(posisiMotor4);

  Serial.print(", Z: ");
  Serial.print(eventGyro.gyro.z);
  int posisiMotor5 = map(eventGyro.gyro.z, +4.3, -4.3, 0, 180);
  motorRotasi5.write(posisiMotor5); 
  if (abs(posisiMotor5 - 90) > 0) { 
    delay(1000); 
      motorRotasi5.write(90);
  delay(100);
}
}
delay(100);
}