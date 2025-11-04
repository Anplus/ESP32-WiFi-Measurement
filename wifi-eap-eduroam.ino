#include <WiFi.h>
#include "esp_wifi.h"
#include "esp_wpa2.h"  // deprecated but still functional

#define RGB_BUILTIN 48   // Onboard RGB LED pin

// ===== Eduroam credentials =====
const char *ssid      = "eduroam";
const char *username  = "xxxxxxxx"; // your username (e.g., your ID)
const char *password  = "xxxxxxxx"; // your passwords

// ===== Setup =====
void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\nConnecting to Eduroam...");

  WiFi.disconnect(true);
  WiFi.mode(WIFI_STA);

  // WPA2-Enterprise parameters
  esp_wifi_sta_wpa2_ent_set_identity((uint8_t *)username, strlen(username));
  esp_wifi_sta_wpa2_ent_set_username((uint8_t *)username, strlen(username));
  esp_wifi_sta_wpa2_ent_set_password((uint8_t *)password, strlen(password));
  esp_wifi_sta_wpa2_ent_enable();   // new ESP-IDF 5.x signature (no argument)

  // Start Wi-Fi
  WiFi.begin(ssid);

  Serial.print("Connecting");
  int retry = 0;
  while (WiFi.status() != WL_CONNECTED && retry < 40) {
    delay(500);
    Serial.print(".");
    retry++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✅ Connected to Eduroam!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\n❌ Failed to connect to Eduroam.");
  }
}

// ===== Main loop =====
void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    long rssi = WiFi.RSSI();  // Received Signal Strength Indicator
    Serial.print("RSSI: ");
    Serial.print(rssi);
    Serial.println(" dBm");

    // --- LED color logic based on RSSI ---
    if (rssi >= -55) {
      showColor(0, 255, 0);   // strong signal → Green
    } else if (rssi >= -70) {
      showColor(255, 255, 0); // medium → Yellow
    } else {
      showColor(255, 0, 0);   // weak → Red
    }
  } else {
    showColor(0, 0, 255);     // disconnected → Blue
    WiFi.reconnect();
  }

  delay(2000); // measure every 2 s
}

// ===== Helper: smooth RGB transitions =====
void showColor(uint8_t r, uint8_t g, uint8_t b) {
  // fade-in
  for (uint8_t i = 0; i < 255; i += 15) {
    neopixelWrite(RGB_BUILTIN, r * i / 255, g * i / 255, b * i / 255);
    delay(5);
  }
  delay(100);
  // fade-out
  for (uint8_t i = 255; i > 0; i -= 15) {
    neopixelWrite(RGB_BUILTIN, r * i / 255, g * i / 255, b * i / 255);
    delay(5);
  }
}