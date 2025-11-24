import serial
import time

# -----------------------------
# User Settings
# -----------------------------
PORT = "/dev/cu.usbmodem31101"      # check your port (e.g., COM3 on Windows)
BAUD = 115200
OUTPUT_FILE = "wifi_log.txt"   # Or "wifi_log.csv"
# -----------------------------


def main():
    print(f"Opening serial port {PORT} at {BAUD} baud...")
    ser = serial.Serial(PORT, BAUD, timeout=1)

    # Open file in append mode
    with open(OUTPUT_FILE, "a") as f:
        print(f"Saving logs to: {OUTPUT_FILE}")

        while True:
            try:
                line = ser.readline().decode(errors="ignore").strip()
                if line:
                    # Print to console
                    print(line)

                    # Add timestamp & write to disk
                    timestamp = time.strftime("%Y-%m-%d %H:%M:%S")
                    f.write(f"{timestamp}, {line}\n")
                    f.flush()  # Ensure data is saved immediately

            except KeyboardInterrupt:
                print("\nStopped by user.")
                break

            except Exception as e:
                print("Error:", e)
                break

    ser.close()
    print("Serial closed.")


if __name__ == "__main__":
    main()
