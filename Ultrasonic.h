#ifndef ULTRASONIC_H
#define ULTRASONIC_H
#include <SoftwareSerial.h>
#include "Arduino.h"

enum ReadingType {LISTEN, SHORT, LONG};

class Ultrasonic {
  public:
    Ultrasonic(const byte rxPin, const byte txPin, uint16_t baudrate);
    ~Ultrasonic() {}

    void send(uint8_t hex);
    void testUart();
    void burstAndThreshold(enum ReadingType type);
    uint16_t readFirstThreshold();
    void updateEEPROM(uint8_t address, uint8_t data);
    void readFIFO();
    void burstAndCapture(enum ReadingType type);
    void thresholdForMode(enum ReadingType type);

    SoftwareSerial serial;

  private:
    uint8_t hexFromReadingType(ReadingType type);
};

#endif
