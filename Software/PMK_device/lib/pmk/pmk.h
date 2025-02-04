#ifndef pmk_h
#define pmk_h



#include "Arduino.h"



//#include "pmkDevice.h"
#define DEVICEID_ADDRESS 0
#define DONGLE_MACADDRESS_ADDRESS 1 // 6 bits long
#define MAC_ADDRESS_SIZE 6



typedef struct {
    uint8_t deviceID;
    uint8_t packetType;
    uint8_t data[16];
}   packetStruct;

typedef struct {
    uint8_t deviceID;
    const uint8_t packetType = 0;
    uint8_t battery;
    uint8_t temperature;
    uint8_t macAddress;
    uint8_t error;
}   telemetryStruct;

typedef struct {
    uint8_t deviceID;
    const uint8_t packetType = 1;
    uint8_t key[8];
}   keyboardStruct;

typedef struct {
    uint8_t deviceID;
    const uint8_t packetType = 2;
    uint8_t x;
    uint8_t y;
    uint8_t w;
    uint8_t p;
    uint8_t k;  
}   mouseStruct;

typedef struct {
    uint8_t deviceID;
    const uint8_t packetType = 3;
    uint8_t x;
    uint8_t y;
    uint8_t z;
    uint8_t rz;
    uint8_t rx;
    uint8_t ry;
    uint8_t hh;
    uint8_t buttons[5];
}   gamepadStruct;

typedef struct {
    uint8_t deviceID;
    const uint8_t packetType = 4;
    uint8_t function;
    uint8_t ledNumberStart;
    uint8_t ledNumberEnd;
    uint8_t red;
    uint8_t green;
    uint8_t blue;
}   ledStruct;

typedef struct {
    uint8_t deviceID;
    const uint8_t packetType = 5;
    uint8_t knob[8];
}   knobStruct;

typedef struct {
    uint8_t deviceID;
    const uint8_t packetType = 6;
    uint8_t function;
    uint8_t position;
    uint8_t command;
}   actuatorStruct;

typedef struct {
    uint8_t deviceID;
    const uint8_t packetType = 7;
    uint8_t image;
    uint8_t x;
    uint8_t y;
    uint8_t brightness;
}   displayStruct;

typedef struct {
    uint8_t deviceID;
    const uint8_t packetType = 9;
    uint8_t packet[8];
}   serialStruct;

enum errorID {
    none, 
    tooManyKeysPressed,
    overTemperature,
    lowBattery,
    invalidPacket,
    internalSensorFailure
};



#endif