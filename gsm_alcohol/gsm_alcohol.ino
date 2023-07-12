#include <SoftwareSerial.h>

// Define the pins for GSM module
#define GSM_TX_PIN 2
#define GSM_RX_PIN 3

// Define the pin for alcohol sensor
#define ALCOHOL_SENSOR_PIN A0

// Replace with your desired phone number
const char* phoneNumber = "+919429756022";

SoftwareSerial gsmSerial(GSM_TX_PIN, GSM_RX_PIN);

void setup() {
  // Start the serial communication
  Serial.begin(9600);
  gsmSerial.begin(9600);

  // Initialize GSM module
  delay(1000);
  sendATCommand("AT");
  delay(2000);
  sendATCommand("AT+CMGF=1");
  delay(1000);
}

void loop() {
  // Read the alcohol sensor value
  int alcoholValue = analogRead(ALCOHOL_SENSOR_PIN);

  // Threshold value to detect alcohol
  int threshold = 500;

  if (alcoholValue > threshold) {
    // Send SMS if alcohol is detected
    sendSMS(phoneNumber, "Alcohol detected!");
    delay(5000); // Wait for 5 seconds before sending another SMS
  }
}

void sendSMS(const char* number, const char* message) {
  // Set the recipient number
  gsmSerial.print("AT+CMGS=\"");
  gsmSerial.print(number);
  gsmSerial.println("\"");

  delay(1000);

  // Set the message content
  gsmSerial.print(message);
  gsmSerial.println((char)26);

  delay(5000); // Wait for the message to be sent

  // Print the response from the GSM module
  while (gsmSerial.available()) {
    Serial.write(gsmSerial.read());
  }
}

void sendATCommand(const char* command) {
  gsmSerial.println(command);
  delay(1000);

  // Print the response from the GSM module
  while (gsmSerial.available()) {
    Serial.write(gsmSerial.read());
  }
}
