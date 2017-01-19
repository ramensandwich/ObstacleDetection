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

void command5() {
  Serial.println("cmd 5");
  ultra.burstAndCapture(LONG);
  
  uint16_t high = ultra.serial.read();
  uint16_t low = ultra.serial.read();
  uint16_t timeOfFlight = ((high<<8) + low);
  Serial.print(timeOfFlight, HEX);
  Serial.print("\t");
  double distance = ((double) timeOfFlight) * SPEED/2000;
  Serial.println(distance);
  uint8_t checksum = ultra.serial.read();
  
  Serial.println("cmd 5 end");
}
void loop() {
  //testUART();
  command5();
  delay(100);
}
