#include <WiFi.h>

// ====== USER CONFIG ======
const char* ssid     = "ATTF2FwUQX";
const char* password = "t86#6xfcgxw6";
// ==========================

#define RGB_BUILTIN 48   // Onboard RGB LED pin

void setup() {
  Serial.begin(115200);
  delay(100);

  Serial.println("\nConnecting to WiFi...");
  WiFi.begin(ssid, password);

  int retry = 0;
  while (WiFi.status() != WL_CONNECTED && retry < 40) {
    delay(500);
    Serial.print(".");
    retry++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✅ WiFi Connected!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\n❌ Failed to connect WiFi");
  }
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    long rssi = WiFi.RSSI();
    Serial.print("RSSI: ");
    Serial.print(rssi);
    Serial.println(" dBm");

    // ---- LED color logic ----
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

  delay(2000);
}

// ---- Helper: set RGB color smoothly ----
void showColor(uint8_t r, uint8_t g, uint8_t b) {
  // fade-in
  for (uint8_t i = 0; i < 255; i += 15) {
    neopixelWrite(RGB_BUILTIN, r * i / 255, g * i / 255, b * i / 255);
    delay(5);
  }
  // small hold
  delay(100);
  // fade-out
  for (uint8_t i = 255; i > 0; i -= 15) {
    neopixelWrite(RGB_BUILTIN, r * i / 255, g * i / 255, b * i / 255);
    delay(5);
  }
}
