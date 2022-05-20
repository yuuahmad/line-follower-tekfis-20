#include <Arduino.h>
// kode untuk sesor ultrasonik
#define echoPin A1      // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin A0      // attach pin D3 Arduino to pin Trig of HC-SR04
long duration;          // variable for the duration of sound wave travel
int distance;           // variable for the distance measurement
int jarakHalangan = 20; // variabel untuk menghentikan robot ketika ada objek didepannya

#define enKanan 5 // untuk atur speed motor
#define enKiri 6  // untuk atur speed motor
#define kanan1 7  // attach pin D3 Arduino to pin Trig of HC-SR04
#define kanan2 8  // attach pin D3 Arduino to pin Trig of HC-SR04
#define kiri1 10  // attach pin D3 Arduino to pin Trig of HC-SR04
#define kiri2 9   // attach pin D3 Arduino to pin Trig of HC-SR04
int kecepatanMotor = 150;

#define sensorKanan 12 // attach pin D3 Arduino to pin Trig of HC-SR04
#define sensorKiri 11  // attach pin D3 Arduino to pin Trig of HC-SR04
int nilaiSensorkanan;
int nilaiSensorKiri;

void setup()
{
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT);  // Sets the echoPin as an INPUT

  // batasi speed motor
  pinMode(enKanan, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(enKiri, OUTPUT);  // Sets the trigPin as an OUTPUT
  analogWrite(enKanan, kecepatanMotor);
  analogWrite(enKiri, kecepatanMotor);

  pinMode(kanan1, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(kanan2, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(kiri1, OUTPUT);  // Sets the trigPin as an OUTPUT
  pinMode(kiri2, OUTPUT);  // Sets the trigPin as an OUTPUT

  pinMode(sensorKanan, INPUT); // Sets the trigPin as an OUTPUT
  pinMode(sensorKiri, INPUT);  // Sets the trigPin as an OUTPUT

  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
}
void belokKanan()
{
  digitalWrite(kanan1, LOW);
  digitalWrite(kanan2, HIGH);
  digitalWrite(kiri1, LOW);
  digitalWrite(kiri2, HIGH);
}
void belokKiri()
{
  digitalWrite(kanan1, HIGH);
  digitalWrite(kanan2, LOW);
  digitalWrite(kiri1, HIGH);
  digitalWrite(kiri2, LOW);
}
void maju()
{
  digitalWrite(kanan1, HIGH);
  digitalWrite(kanan2, LOW);
  digitalWrite(kiri1, LOW);
  digitalWrite(kiri2, HIGH);
}
void berhenti()
{
  digitalWrite(kanan1, LOW);
  digitalWrite(kanan2, LOW);
  digitalWrite(kiri1, LOW);
  digitalWrite(kiri2, LOW);
}

void loop()
{
  // baca sensor garis
  nilaiSensorkanan = digitalRead(sensorKanan);
  nilaiSensorKiri = digitalRead(sensorKiri);

  // kode untuk sensor ultrasonik
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  if (distance <= jarakHalangan)
  {
    berhenti();
    Serial.print("berhenti");
  }
  else
  {
    if (nilaiSensorkanan == 0 && nilaiSensorKiri == 0)
    {
      maju();
      Serial.print("maju");
    }
    else if (nilaiSensorkanan == 0 && nilaiSensorKiri == 1)
    {
      belokKanan();
      Serial.print("kanan");
    }
    else if (nilaiSensorkanan == 1 && nilaiSensorKiri == 0)
    {
      belokKiri();
      Serial.print("kiri");
    }
    else
    {
      berhenti();
      Serial.print("berhenti");
    }
  }

  // tampilkan data data yang didapatkan
  Serial.print("jarak: ");
  Serial.print(distance);
  // tampilkan data sensor garis
  Serial.print("kanan : ");
  Serial.print(nilaiSensorkanan);
  Serial.print("kiri : ");
  Serial.println(nilaiSensorKiri);
}