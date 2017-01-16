#include <SoftwareSerial.h>

SoftwareSerial mySerial(10,11); //RX, TX


void setup() {
  Serial.begin(57600);
  Serial.println("Serial started!");
  mySerial.begin(19200);
}

void loop() {
  // Tell board to do a long pulse
  Serial.println("Sending sensing command to board");
  mySerial.write((uint8_t)0x00);
  mySerial.write((uint8_t)0x55);
  mySerial.write((uint8_t)0x51);
  mySerial.write((uint8_t)0x02);
  mySerial.write((uint8_t)0x00);
  delay(1000);

  //Read the FIFO memory
  Serial.println("Sending read command");
  mySerial.write((uint8_t)0x00);
  mySerial.write((uint8_t)0x55);
  mySerial.write((uint8_t)0x41);
  mySerial.write((uint8_t)0x00);

  uint8_t i = 0;
  while(mySerial.available()) {
    Serial.print("Current count: ");
    Serial.print(i);
    Serial.print(" Byte: ");
    Serial.println(mySerial.read(), HEX);
    ++i;
  }
  delay(5000);
  while(mySerial.available()) {
    Serial.print("Current count: ");
    Serial.print(i);
    Serial.print(" Byte: ");
    Serial.println(mySerial.read(), HEX);
    ++i;
  }
  Serial.println("\nEnd of message");
  delay(10000);
}
