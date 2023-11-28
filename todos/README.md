# ESP32-S3 todos project

Elecrow 7 inch project demonstrating basic usage with LovyanGFX library

The code is taken from [VolosProjects](https://github.com/VolosR/maTouch7/tree/main/7inch1024) and
modified for the 800x480 screen. Demonstrates a complex dislpay in the form of
a week todo planner.

## Install libraries

```
arduino-cli.exe lib install <library name> # e.g TFT_eSPI
```

## Compile

```
arduino-cli.exe compile --profile esp32
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
