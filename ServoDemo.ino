#include <Adafruit_MPU6050.h> 
#include <Adafruit_Sensor.h>  
#include <ESP32Servo.h>       

// Pin yang digunakan
#define TRIGPIR_PIN 33      // Pin sensor PIR (pendeteksi gerakan)
#define SERVO1_PIN 13       
#define SERVO2_PIN 35       
#define SERVO3_PIN 14       
#define SERVO4_PIN 27       
#define SERVO5_PIN 32       

// Inisialisasi objek servo
Servo motorRotasi1; 
Servo motorRotasi2; 
Servo motorRotasi3; 
Servo motorRotasi4; 
Servo motorRotasi5; 

// Inisialisasi sensor MPU6050
Adafruit_MPU6050 sensorAkselerasi;

void setup() {
  Serial.begin(115200);

  while (!Serial)
    delay(10);

  Serial.println("Adafruit MPU6050 test!"); 

  // Cek apakah sensor MPU6050 terdeteksi
  if (!sensorAkselerasi.begin()) {
    Serial.println("Failed to find MPU6050 chip");
  }
  Serial.println("MPU6050 Found!");
  
  pinMode(TRIGPIR_PIN, OUTPUT); 

  // Pasangkan setiap objek servo ke pin masing-masing
  motorRotasi1.attach(SERVO1_PIN);
  motorRotasi2.attach(SERVO2_PIN);
  motorRotasi3.attach(SERVO3_PIN);
  motorRotasi4.attach(SERVO4_PIN);
  motorRotasi5.attach(SERVO5_PIN);

  // Set posisi awal semua servo ke tengah (90 derajat)
  motorRotasi1.write(90);
  motorRotasi2.write(90);
  motorRotasi3.write(90);
  motorRotasi4.write(90);
  motorRotasi5.write(90);

  delay(1000); 
}

void loop() {
  // Baca data dari sensor MPU6050
  sensors_event_t eventAkselerasi, eventGyro, eventSuhu; 
  sensorAkselerasi.getEvent(&eventAkselerasi, &eventGyro, &eventSuhu);

  // Baca status deteksi dari sensor PIR
  bool deteksiGerak = digitalRead(TRIGPIR_PIN); 
  Serial.print("\nGERAKAN: "); 
  Serial.print(deteksiGerak);
  Serial.print("\n"); 

  // Jika ada gerakan, servo bergerak ke posisi tertentu lalu kembali
  if (deteksiGerak == true){ 
    motorRotasi1.write(40);
    motorRotasi2.write(70);
    motorRotasi3.write(100);
    motorRotasi4.write(130);
    motorRotasi5.write(160);
    delay(2000);

    // Kembalikan semua servo ke posisi tengah
    motorRotasi1.write(90); 
    motorRotasi2.write(90);
    motorRotasi3.write(90);
    motorRotasi4.write(90);
    motorRotasi5.write(90);
    delay(2000);
  }
  else {
    // Jika tidak ada gerakan, kontrol servo berdasarkan data gyro
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

    // Jika motor 5 bergerak menjauh dari posisi 90 derajat, kembalikan setelah 1 detik
    if (abs(posisiMotor5 - 90) > 0) { 
      delay(1000); 
      motorRotasi5.write(90);
      delay(100);
    }
  }

  delay(100);
}
