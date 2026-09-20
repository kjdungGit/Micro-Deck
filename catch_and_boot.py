#!/usr/bin/env python3
"""
catch_and_bootload.py

Watches a serial port for the currently-running firmware to boot (i.e. any
data comes across the line), then immediately drives DTR/RTS to force the
ESP32-C3 into its ROM bootloader (download mode) and holds it there so you
have a window to run esptool.py / arduino-cli upload / platformio upload
without racing your firmware for control of the port.

Usage:
    python catch_and_bootload.py --port COM5
    python catch_and_bootload.py --port /dev/ttyACM0 --baud 115200 --hold 60

While it's holding the chip in bootloader mode, run your flash command in a
second terminal. The script releases the port (closes cleanly) after the
hold time so esptool can open it, OR you can pass --keep-open to leave the
port open in bootloader-held state (esptool will still be able to send its
own DTR/RTS sequence over the same open handle on most platforms, but a
clean close is usually more reliable for these boards).
"""

import argparse
import sys
import time

try:
    import serial
except ImportError:
    print("pyserial not installed. Run: pip install pyserial --break-system-packages")
    sys.exit(1)


def enter_bootloader(ser: serial.Serial):
    """
    Standard ESP32 auto-reset sequence used by esptool.py, replicated manually.
    EN (reset) is wired to DTR, GPIO9 (boot select) is wired to RTS on most
    ESP32-C3 boards with a CP2102/CH340/native-USB auto-program circuit.
    Pulling RTS low asserts GPIO9 low (boot-select = download mode), and
    toggling DTR low then high pulses EN (reset) with GPIO9 held down so
    the chip resets straight into the ROM bootloader instead of running
    your app.
    """
    # Assert boot-select (GPIO9 low = download mode)
    ser.rts = False   # NOTE: on many boards logic is inverted by the auto-reset
                      # circuit's transistor -- if this doesn't work, flip
                      # True/False on both rts and dtr lines below.
    time.sleep(0.1)

    # Pulse EN (reset) low then high while boot-select is held
    ser.dtr = False
    time.sleep(0.1)
    ser.dtr = True
    time.sleep(0.1)

    # Release boot-select line state (chip has already latched GPIO9 on reset)
    time.sleep(0.1)
    ser.rts = True


def main():
    parser = argparse.ArgumentParser(description="Catch a booted ESP32C3 and force bootloader mode")
    parser.add_argument("--port", required=True, help="Serial port, e.g. COM5 or /dev/ttyACM0")
    parser.add_argument("--baud", type=int, default=115200, help="Baud rate to watch at (match your Serial.begin())")
    parser.add_argument("--hold", type=int, default=60, help="Seconds to hold bootloader mode / keep port reserved")
    parser.add_argument("--timeout", type=float, default=0, help="Seconds to wait for boot data before giving up (0 = wait forever)")
    parser.add_argument("--keep-open", action="store_true", help="Keep the port open for the full hold duration instead of closing immediately")
    args = parser.parse_args()

    print(f"Opening {args.port} @ {args.baud}...")
    try:
        ser = serial.Serial(args.port, args.baud, timeout=1)
    except serial.SerialException as e:
        print(f"Could not open port: {e}")
        sys.exit(1)

    # Make sure lines start in a known "let it run normally" state
    ser.dtr = False
    ser.rts = False

    print("Waiting for firmware to boot (i.e. any serial output)...")
    start = time.time()
    got_data = False
    while True:
        chunk = ser.read(64)
        if chunk:
            print(f"Detected boot output: {chunk!r}")
            got_data = True
            break
        if args.timeout and (time.time() - start) > args.timeout:
            print("Timed out waiting for boot data.")
            break

    if got_data:
        print("Forcing chip into bootloader (download) mode now...")
        enter_bootloader(ser)
        print(f"Chip should now be sitting in ROM bootloader.")
        print(f"You have {args.hold} seconds to run your flash command, e.g.:")
        print(f"    esptool.py --port {args.port} --baud 460800 write_flash ...")
        print(f"    (or) arduino-cli upload -p {args.port} ...")
        print(f"    (or) pio run -t upload")

        if args.keep_open:
            print("Keeping port open for the hold duration (--keep-open set)...")
            time.sleep(args.hold)
        else:
            print("Closing port now so your flash tool can take over cleanly.")
            ser.close()
            time.sleep(args.hold)
    else:
        ser.close()

    print("Done.")


if __name__ == "__main__":
    main()