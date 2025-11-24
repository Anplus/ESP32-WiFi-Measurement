#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);   // Station mode
  WiFi.disconnect(true); // Disconnect before scanning
  delay(1000);
  Serial.println("ESP32 WiFi Scanner Started");
}

void loop() {
  Serial.println("\n--- Scanning WiFi ---");

  // Perform WiFi scan
  int numNetworks = WiFi.scanNetworks(/*async=*/false, /*hidden=*/true);

  if (numNetworks == 0) {
    Serial.println("No networks found.");
  } else {
    Serial.printf("Found %d networks:\n", numNetworks);

    for (int i = 0; i < numNetworks; i++) {
      String ssid = WiFi.SSID(i);
      int32_t rssi = WiFi.RSSI(i);
      wifi_auth_mode_t auth = WiFi.encryptionType(i);

      Serial.printf("[%02d] SSID: %-20s RSSI: %4d dBm  Security: %d\n",
                    i, ssid.c_str(), rssi, auth);
    }
  }

  // Clean up memory from scan
  WiFi.scanDelete();

  // Scan every 5 seconds
  delay(5000);
}
