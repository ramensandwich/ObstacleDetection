#include "Ultrasonic.h"

// constructor
Ultrasonic::Ultrasonic(uint16_t baudrate) {
    Serial1.begin(baudrate);
}


// send to serial
void Ultrasonic::send(uint8_t hex) {
    Serial1.write(hex);
}

// read from serial
uint8_t Ultrasonic::read() {
    return Serial1.read();
}

// convert type to hex (listen, short or long
uint8_t Ultrasonic::hexFromReadingType(ReadingType type) {
    switch (type) {
        case LISTEN: return 0x00; break;
        case SHORT:  return 0x01; break;
        case LONG:   return 0x02; break;
    }

    return 0x00;
}

// should send back 0x12 0x34 0xB9
void Ultrasonic::testUart() {
    send(0x00);
    send(0x55);
    send(0x01);
    send(0x00);
}


void Ultrasonic::burstAndThreshold(enum ReadingType type) {
    send(0x00);
    send(0x55);
    send(0x11);
    send(hexFromReadingType(type));
    send(0x00);
}


uint16_t Ultrasonic::readFirstThreshold() {
    send(0x00);
    send(0x55);
    send(0x21);
    send(0x00);

    uint16_t highbyte  = Serial1.read();
    uint16_t lowbyte = Serial1.read();
    highbyte <<= 8;
    Serial1.read(); // dump checksum

    return highbyte+lowbyte;
}


void Ultrasonic::updateEEPROM(uint8_t address, uint8_t data) {
    send(0x00);
    send(0x55);
    send(0x31);
    send(address);
    send(data);
    send(0x00);
}


void Ultrasonic::readFIFO() {
    send(0x00);
    send(0x55);
    send(0x41);
    send(0x00);
}


void Ultrasonic::burstAndCapture(enum ReadingType type) {
    send(0x00);
    send(0x55);
    send(0x51);
    send(hexFromReadingType(type));
    send(0x00);
}


void Ultrasonic::thresholdForMode(enum ReadingType type) {
    send(0x00);
    send(0x55);
    send(0x61);
    send(hexFromReadingType(type));
    send(0x00);
}
