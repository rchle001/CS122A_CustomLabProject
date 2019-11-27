// Note: when uploading to esp32, boot may need to be held down
//during sketch and upload on com6, use com8 to see serial output
#include "BluetoothSerial.h"
#include "driver/uart.h"
//#include <winsock.h>

BluetoothSerial SerialBt; // COM8
uint8_t a;
bool rdy = false;

#define rx 17
#define tx 16


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, rx, tx);
  SerialBt.begin("esp32");
}

void loop() {
  // put your main code here, to run repeatedly:
  //SerialBt.println("Hello World");
  //Serial.print(char(Serial2.write('z')));
  Serial2.write('z');
  delay(500);
  char temp;
  while(Serial2.available())
  {
    temp = char(Serial2.read());
    Serial.print(temp);
    SerialBt.print(temp);
  }
}
