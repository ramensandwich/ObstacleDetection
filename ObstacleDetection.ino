#include "Ultrasonic.h"

#define ULTRA_BAUD 19200 // Over Serial1
#define LAPTOP_BAUD 57600 // Over Serial
#define SPEED 343
#define MAX_FIFO 800
#define FIFO_TIMEOUT 1000

#define CMD_PRESET_DISTANCE 1
#define CMD_CUSTOM_DISTANCE 5
#define CMD_FIFO 4

Ultrasonic ultra(ULTRA_BAUD);


void setup() {
    Serial.begin(LAPTOP_BAUD);
    Serial1.begin(ULTRA_BAUD);

    //Serial.println("Serial started!");
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
    //Serial.print(timeOfFlight, HEX);
    //Serial.print("\t");
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
    uint8_t fifo[MAX_FIFO] = {0};

    delay(100);
    ultra.readFIFO();

    while (millis()-start < FIFO_TIMEOUT) {
        if (Serial1.available()) {
            fifo[l] = ultra.read();
            l++;
        }
    }

    //Serial.print("read FIFO with ");
    //Serial.println(l);
    
    Serial.println(l);

    for (int i=0 ; i<l ; i++) {
        //Serial.print(i);
        //Serial.print("\t");
        Serial.println(fifo[i]);
    }
}

void checkSerial() {
    if (Serial.available()) {
        uint8_t cmd = Serial.read();

        switch (cmd) {
            case CMD_PRESET_DISTANCE:
                command1();
            break;
            case CMD_CUSTOM_DISTANCE:
                command5();
            break;
            case CMD_FIFO:
                //Serial.println("About to read");
                readFIFO();
            break;
            default:
                Serial.println("Wrong cmd");
        }
    }
}


void loop() {
    checkSerial();

    //testUART();
    //command1();
    //delay(50);
    //readFIFO();
    //delay(1000);
}
