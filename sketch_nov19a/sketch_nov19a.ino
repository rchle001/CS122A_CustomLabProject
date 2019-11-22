// Note: when uploading to esp32, boot may need to be held down during sketch and upload on com6, use com8 to see serial output
#include "BluetoothSerial.h"
//#include <winsock.h>

BluetoothSerial SerialBt; // COM8
uint8_t a;

void setup() {
  // put your setup code here, to run once:
  digitalWrite(13,HIGH);
  SerialBt.begin("esp32");
}

void loop() {
  // put your main code here, to run repeatedly:
  SerialBt.println("Hello World");
  delay(500);
}
