# 📶 ESP32-S3 Wi-Fi Signal Strength Measurement

This project demonstrates how to connect an **ESP32-S3** development board (e.g., YD-ESP32-23) to a Wi-Fi network and use its **on-board RGB LED** to visualize the wireless signal strength (RSSI).  
It’s designed as a simple student exercise for learning **IoT networking**, **signal measurement**, and **embedded programming** on the ESP32 platform.

---

## 🧭 Introduction

Once powered on, the ESP32 connects to a known Wi-Fi network using the SSID and password you provide in the sketch.  
Every few seconds, it measures the **RSSI (Received Signal Strength Indicator)** and displays the result both in the **Serial Monitor** and with the **on-board RGB LED**:

| Signal Level | RSSI Range (dBm) | LED Color |
|---------------|------------------|------------|
| Strong        | > −55 dBm        | 🟢 Green   |
| Medium        | −70 to −55 dBm   | 🟡 Yellow  |
| Weak          | < −70 dBm        | 🔴 Red     |
| Disconnected  | —                | 🔵 Blue    |

This allows you to *see* how Wi-Fi strength changes as you move the board around or change the environment.

---

## ⚙️ Hardware Setup

| Component | Description |
|------------|--------------|
| **ESP32-S3 Dev Board (YD-ESP32-23)** | Main MCU with on-board RGB LED |
| **USB-C cable** | For power, programming, and serial monitoring |
| **Wi-Fi access point** | Your router or mobile hotspot |

**Connections:**  
No external wiring needed — the RGB LED is built-in (on GPIO 48).

---

## 💻 Software Setup

### 1. Install Arduino IDE
Download from [https://www.arduino.cc/en/software](https://www.arduino.cc/en/software).

### 2. Install ESP32 Board Support

1. Open **Tools → Board → Boards Manager**, search **ESP32**, and install the latest version.

### 3. Select the Correct Board & Port
- **Board:** `ESP32S3 Dev Module`  
- **Port:** e.g. `/dev/cu.usbmodemXXXX` (Mac) or `COMx` (Windows)
- **USB CDC On Boot:** Enabled  
- **PSRAM:** OPI PSRAM  
- **Flash Size:** 8MB  
- **Upload Speed:** 115200  
- **Upload Mode:** UART0 / Hardware CDC

### 4. 🚀 Upload & Run
1. Open the `.ino` sketch.  
2. Update your Wi-Fi credentials:
```cpp
const char* ssid = "Your_SSID";
const char* password = "Your_PASSWORD";
```
3. Connect the board via USB.

4. Hold BOOT, press RESET, release RESET, then release BOOT (to enter flash mode).

5. Click Upload in Arduino IDE.

6. Open Serial Monitor at 115200 baud.

You should see:
```cpp
Connecting to WiFi...
✅ WiFi Connected!
RSSI: -62 dBm
```
and the RGB LED color changing based on signal strength.

🧩 Extension Ideas

- Log RSSI over time to a file or cloud database (e.g., ThingSpeak, Firebase).
- Plot RSSI vs. distance for wireless characterization.
- Integrate with ROS 2 to publish signal data from a mobile robot.
- Use multiple boards to visualize signal distribution in a room.