# ESP32-S3 test project

Simple project to get developing with the arduino cli

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
