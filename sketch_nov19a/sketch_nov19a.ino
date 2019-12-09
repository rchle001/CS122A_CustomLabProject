// Note: when uploading to esp32, boot may need to be held down
//during sketch and upload on com6, use com8 to see serial output
#include "BluetoothSerial.h"
#include <driver/uart.h>
//#include <winsock.h>

BluetoothSerial SerialBt; // COM8
bool rdy = false;
bool cnctd = false;
unsigned char temp;

#define rx 17
#define tx 16

//const int uart_num = UART_NUM_2;
//const int uart_buffer_size = (1024 * 2);\
//
//QueueHandle_t uart_queue;
//
//uart_config_t uart_config = {
//  .baud_rate = 9600,
//  .data_bits = UART_DATA_8_BITS,
//  .parity = UART_PARITY_DISABLE,
//  .stop_bits = UART_STOP_BITS_1,
//  .flow_ctrl = UART_HW_FLOWCTRL_CTS_RTS,
//  .rx_flow_ctrl_thresh = 122,
//  };
//

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
//  ESP_ERROR_CHECK(uart_param_config(UART_NUM_2, &uart_config));
//  ESP_ERROR_CHECK(uart_set_pin(UART_NUM_2, tx, rx, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
//  ESP_ERROR_CHECK(uart_driver_install(UART_NUM_2, uart_buffer_size, uart_buffer_size, 10, &uart_queue, 0));
  Serial2.begin(9600, SERIAL_8N1, rx, tx);
  SerialBt.begin("esp32");
}

void loop() {
  // put your main code here, to run repeatedly:
  //SerialBt.println("Hello World");
  //Serial.print(char(Serial2.write('z')));
  //SerialBt.println("Connected");
  //Serial.println("Connected");
  while(Serial2.available())
  {
    temp = Serial2.read();
  }
  //uint8_t data[128];
  //int length = 0;
  //uart_read_bytes(UART_NUM_2, data, length, 100);
  //temp = data[0];
  Serial.println(char(temp)+'0');
  SerialBt.write(temp);
  //Serial2.flush();
  //uart_flush(UART_NUM_2);
  //SerialBt.println(temp);
  delay(100);
}
