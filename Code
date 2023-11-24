#include "SPI.h"
#include "MFRC522.h"
#include "WiFi.h"
#include "HTTPClient.h"
#include <ArduinoJson.h> // Include ArduinoJson library

#define RST_PIN 3    // Reset pin
#define SS_PIN  4     // Slave Select (SS) pin
#define BLUE_LED_PIN 7 // Pin for the blue LED
#define RED_LED_PIN 6  // Pin for the red LED

const char* ssid     = "dLonelyPrince"; // Wifi Name
const char* password = "prince44";        // Wifi Password
const char* apiEndpoint = "http://192.168.192.179/api/badges/"; // API URL

byte readCard[4];
String tagID = "";

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(115200);
  SPI.begin();
  mfrc522.PCD_Init();
  pinMode(BLUE_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Turn off both LEDs initially
  digitalWrite(BLUE_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);
}

void loop() {
  while (true) {
    // Use the getID function in a loop until a valid ID is obtained
    while (!getID()) {
      // Add any other code you want to run while waiting for a valid ID
    }

    // Check access for the obtained ID
    boolean accessGranted = checkAccess(tagID);

    // Clear LED states
    digitalWrite(BLUE_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, LOW);

    // Handle LED based on access status
    if (accessGranted) {
      Serial.println("Access Granted!");
      digitalWrite(BLUE_LED_PIN, HIGH); // Turn on blue LED
    } else {
      Serial.println("Access Denied!");
      digitalWrite(RED_LED_PIN, HIGH); // Turn on red LED
    }

    Serial.print("ID: ");
    Serial.println(tagID);
    delay(2000);

    // Turn off both LEDs
    digitalWrite(BLUE_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, LOW);
  }
}

boolean getID() {
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return false;
  }

  if (!mfrc522.PICC_ReadCardSerial()) {
    return false;
  }

  tagID = "";

  for (uint8_t i = 0; i < 4; i++) {
    tagID.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  tagID.toUpperCase();
  mfrc522.PICC_HaltA();
  return true;
}

boolean checkAccess(String cardID) {
  // Use HTTPClient to send a request to the API
  HTTPClient http;

  // Build the URL with the card ID parameter
  String url = String(apiEndpoint) + cardID;
  Serial.print("Request URL: ");
  Serial.println(url);

  // Perform a GET request
  http.begin(url);

  // Get the response and parse JSON
  int httpCode = http.GET();
  if (httpCode == 200) {
    // Parse JSON
    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, http.getString());

    // Check for parsing errors
    if (error) {
      Serial.print("Error parsing JSON: ");
      Serial.println(error.c_str());
      return false;
    }

    // Check the status in the JSON
    const char* status = doc["status"];

    // Check if the status is "OK"
    if (status != nullptr && strcmp(status, "OK") == 0) {
      // If the status is "OK", access is granted
      Serial.println("Access Granted!");
      return true;
    } else {
      // Otherwise, access is denied
      Serial.println("Access Denied!");
      return false;
    }
  } else {
    Serial.print("Error during HTTP request. HTTP Code: ");
    Serial.println(httpCode);
    return false;
  }

  // Release resources
  http.end();
}
