#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <DHT.h>

// Pin Definitions
#define SDA_PIN A0            // RFID SDA to A0
#define RST_PIN A4            // RFID Reset to A4
#define DISTANCE_SERVO_PIN 9  // Distance-based servo control
#define RFID_SERVO_PIN A5     // RFID-based servo control
#define DHTPIN 8              // DHT sensor connected to digital pin 8
#define DHTTYPE DHT11         // DHT11 sensor type
#define trigPin 5             // Ultrasonic trigger pin
#define echoPin 6             // Ultrasonic echo pin
#define ldrPin 2              // LDR digital output pin
#define ledPin 10             // LED pin
#define fanPin 7              // Fan control pin
#define SPEED_AIR 0.03434     // speed

// Initialize Components
DHT dht(DHTPIN, DHTTYPE);
MFRC522 rfid(SDA_PIN, RST_PIN);  // RFID initialization
Servo distanceServo;
Servo rfidServo;

// Constants and Variables
long duration;
int distance;
String tagUID;

void setup() {
  // Initialize SPI
  SPI.begin();
  rfid.PCD_Init();  // Initialize RFID module

  // Initialize DHT sensor
  dht.begin();

  // Initialize pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ldrPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(fanPin, OUTPUT);
  distanceServo.attach(DISTANCE_SERVO_PIN);
  rfidServo.attach(RFID_SERVO_PIN);
  distanceServo.write(0);  // Distance servo initially closed
  rfidServo.write(0);      // RFID servo initially closed

  // Serial communication
  Serial.begin(115200);
}

void loop() {
  // Measure distance with Ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  //duration = pulseIn(echoPin, HIGH, 30000);                // Timeout 30ms
  long T = pulseIn(echoPin, HIGH, 30000);
  distance = SPEED_AIR * (T / 2);  // Convert to cm
  if (distance < 0) {
    distance = 0;
  }

  //automaticGarageOpen();
  //automaticLedON();
  //automaticFanON();

  // Read temperature
  float temperature = dht.readTemperature();
  if (isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
  }

  // Read LDR state
  int ldrState = digitalRead(ldrPin); //integer because we only need either dark or bright

  // Check for RFID tag
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    tagUID = "";
    for (byte i = 0; i < rfid.uid.size; i++) {
      tagUID += String(rfid.uid.uidByte[i], HEX);
      if (i < rfid.uid.size - 1) tagUID += " ";
    }
    Serial.print("G");       // indicator that it's Tag
    Serial.println(tagUID);  //send to matlab the tagID
  }

  // Handle commands from MATLAB
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    handleCommand(command);
  }

  //sending to MATLAB Data...
  Serial.print("D");            // indicator that it's distance
  Serial.println(distance);     // send to matlab the distance
  Serial.print("T");            // indicator that it's temperature
  Serial.println(temperature);  //send to matlab the temperature
  Serial.print("L");            // indicator that it's LDR
  Serial.println(ldrState);     //send to matlab the LDR (lux value)

  delay(1500);
}

// Command Handler
void handleCommand(String command) {
  if (command == "LED_ON") {
    digitalWrite(ledPin, HIGH);  // Turn on LED
    //delay(2000);                 //wait 3 seconds
  } else if (command == "LED_OFF") {
    digitalWrite(ledPin, LOW);  // Turn off LED
    //delay(2000);                //wait 3 seconds
  } else if (command == "FAN_ON") {
    digitalWrite(fanPin, HIGH);  // Turn on fan
    delay(2000);                 //wait 3 seconds
  } else if (command == "FAN_OFF") {
    digitalWrite(fanPin, LOW);  // Turn off fan
    //delay(2000);                //wait 3 seconds
  } else if (command == "GARGAGE_OPEN") {
    distanceServo.write(110);  // turn servo to open garage door
    //delay(2000);               //wait 3 seconds
  } else if (command == "GARGAGE_CLOSE") {
    distanceServo.write(0);  // turn servo to close garage door
    //delay(2000);             //wait 3 seconds
  } else if (command == "DOOR_OPEN") {
    rfidServo.write(60);  // turn servo to close garage door
    //delay(2000);          //wait 3 seconds
  } else if (command == "DOOR_CLOSE") {
    rfidServo.write(0);  // turn servo to close garage door
    //delay(2000);         //wait 3 seconds
  } else if (command == "OBJECT_DETECT") {
    distanceServo.write(110);  // turn servo to open garage door
    delay(2000);               //wait 3 seconds
    distanceServo.write(0);    // turn servo to close garage door
  } else if (command == "ACCESS") {
    rfidServo.write(60);  // turn servo to close garage door
    delay(2000);          //wait 3 seconds
    rfidServo.write(0);  // turn servo to close garage door
  }
}
