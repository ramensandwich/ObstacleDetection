#include "Ultrasonic.h"

#define BAUD 19200 // Over Serial1
#define SPEED 343

Ultrasonic ultra(BAUD);


void setup() {
    Serial.begin(57600);
    Serial.println("Serial started!");
}

void testUART() {
    ultra.testUart();
    while(Serial1.available()) {
        Serial.println(ultra.read(), HEX);
    }
}

void command1() {
    //Serial.println("com1");
    ultra.burstAndThreshold(LONG);

    uint16_t high = ultra.read();
    uint16_t low = ultra.read();
    uint16_t timeOfFlight = ((high<<8) + low);
    Serial.print(timeOfFlight, HEX);
    Serial.print("\t");
    double distance = ((double) timeOfFlight) * SPEED/2000;
    Serial.println(distance);
    uint8_t checksum = ultra.read();

    //Serial.println("done");
}

void command5() {
    //Serial.println("cmd 5");
    ultra.burstAndCapture(SHORT);

    uint16_t high = ultra.read();
    uint16_t low = ultra.read();
    uint16_t timeOfFlight = ((high<<8) + low);
    //Serial.print(timeOfFlight, HEX);
    //Serial.print("\t");
    double distance = ((double) timeOfFlight) * SPEED/2000;
    Serial.println(distance);
    uint8_t checksum = ultra.read();

    //Serial.println("cmd 5 end");
}

void readFIFO() {
    uint32_t start = millis();
    int l = 0;
    uint8_t fifo[800] = {0};

    ultra.readFIFO();


    while (millis()-start < 2000) {
        if (Serial1.available()) {
            fifo[l] = ultra.read();
            l++;
        }
    }

    for (int i=0 ; i<l ; i++) {
        Serial.print(i);
        Serial.print("\t");
        Serial.println(fifo[i]);
    }
}

void loop() {
    //testUART();
    command1();
    delay(50);
    readFIFO();
    delay(1000);
}
