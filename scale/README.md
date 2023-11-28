# ESP32-S3 test project

Elecrow 7 inch project demonstrating basic usage with LovyanGFX library.
It animates many circles along with displaying the frame rate.

## Install libraries

```
arduino-cli.exe lib install <library name> # e.g TFT_eSPI
```

## Compile

```
arduino-cli.exe compile --profile esp32s3 --build-property "platform=espressif32,board=esp32-s3-devkitc-1,framework=arduino,build_flags=-DBOARD_HAS_PSRAM,board_build.arduino.memory_type=qio_opi,board_build.f_flash=80000000L,board_build.flash_mode=qio,board_upload.flash_size=4MB"
```

## Upload

```
arduino-cli.exe upload -p <port number> -b esp32:esp32:esp32s3
```

## Monitor

Connect to board to view serial output

```
arduino-cli.exe monitor -p COM4 -b esp32:esp32:esp32s3
```

## Attach

```
arduino-cli.exe board attach -p com3 .\test.ino
```
