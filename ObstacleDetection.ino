#include "Ultrasonic.h"

#define RX 10
#define TX 11
#define BAUD 19200
#define SPEED 343

Ultrasonic ultra(RX,TX,BAUD);


void setup() {
  Serial.begin(57600);
  Serial.println("Serial started!");
}

void testUART() {
  ultra.testUart();
  while(ultra.serial.available()) {
    Serial.println(ultra.serial.read(), HEX);
  }
}

void command1() {
  //Serial.println("com1");
  ultra.burstAndThreshold(LONG);
  
  uint16_t high = ultra.serial.read();
  uint16_t low = ultra.serial.read();
  uint16_t timeOfFlight = ((high<<8) + low);
  Serial.print(timeOfFlight, HEX);
  Serial.print("\t");
  double distance = ((double) timeOfFlight) * SPEED/2000;
  Serial.println(distance);
  uint8_t checksum = ultra.serial.read();
  
  //Serial.println("done");
}
void loop() {
  /*
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
  */
  //testUART();
  command1();
  delay(100);
}
