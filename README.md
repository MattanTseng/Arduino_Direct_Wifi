# Arduino_Direct_Wifi
Simple script for an arduino to be an access point and broadcast sensor data to its own network.  

## Setup

The code is created for the Arduino Nano 33 BLE IOT board.\
https://store-usa.arduino.cc/products/arduino-nano-33-iot

The Arduino WifiNINA library is required:
https://www.arduino.cc/reference/en/libraries/wifinina/

You will need to create a file arduino_secrets.h that contains the following information: 
> #define SECRET_SSID "YOURSSID" \
> #define SECRET_PASS "YOURPASS" \
> #define TARGET_PORT YOURTARGETNUMBER\

## Operation
Once the code is uploaded to the board, it will create a network YOURSSID. If you connect a device to this network, it will recieve data from the board via UDP. 

## Troubleshooting
If your device is able to connect to the network, but is not receiving packets, make sure that your device sees the arduino as a trusted network.
