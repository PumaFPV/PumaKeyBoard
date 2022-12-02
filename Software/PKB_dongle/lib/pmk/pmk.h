#include "Arduino.h"

typedef struct packetStruct {
    uint8_t deviceID;
    uint8_t packetType;
    uint8_t data[16];
}   packetStruct;

typedef struct keyboardStruct {
    uint8_t deviceID;
    const uint8_t packetType = 1;
    uint8_t key[8];
}   keyboardStruct;

typedef struct mouseStruct {
    uint8_t deviceID;
    const uint8_t packetType = 2;
    uint8_t x;
    uint8_t y;
    uint8_t w;
    uint8_t p;
    uint8_t k;  
}   mouseStruct;

typedef struct gamepadStruct {
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

typedef struct ledStruct {
    uint8_t deviceID;
    const uint8_t packetType = 4;
    uint8_t function;
    uint8_t red;
    uint8_t green;
    uint8_t blue;
}   ledStruct;

typedef struct knobStruct {
    uint8_t deviceID;
    const uint8_t packetType = 5;
    uint8_t knob[8];
}   knobStruct;

typedef struct actuatorStruct {
    uint8_t deviceID;
    const uint8_t packetType = 6;
    uint8_t function;
    uint8_t position;
    uint8_t command;
}   actuatorStruct;

typedef struct displayStruct {
    uint8_t deviceID;
    const uint8_t packetType = 7;
    uint8_t image;
    uint8_t x;
    uint8_t y;
    uint8_t brightness;
}   displayStruct;

typedef struct telemetryStruct {
    uint8_t deviceID;
    const uint8_t packetType = 8;
    uint8_t battery;
    uint8_t temperature;
    uint8_t macAddress;
    uint8_t error;
}   telemetryStruct;

typedef struct serialStruct {
    uint8_t deviceID;
    const uint8_t packetType = 9;
    uint8_t packet[8];
}   serialStruct;

// keyboardStruct  convertPacket2Keyboard(packetStruct packet);
// mouseStruct     convertPacket2Mouse(packetStruct packet);
// gamepadStruct   convertPacket2Gamepad(packetStruct packet);
// ledStruct       convertPacket2Led(packetStruct packet);
// knobStruct      convertPacket2Knob(packetStruct packet);
// actuatorStruct  convertPacket2Actuator(packetStruct packet);
// displayStruct   convertPacket2Display(packetStruct packet);
// telemetryStruct convertPacket2Telemetry(packetStruct packet);
// serialStruct    convertPacket2Serial(packetStruct packet);

packetStruct receivedPacket;

keyboardStruct keyboardPacket;
mouseStruct mousePacket;
gamepadStruct gamepadPacket;
ledStruct ledPacket;
knobStruct knobPacket;
actuatorStruct actuatorPacket;
displayStruct displayPacket;
telemetryStruct telemetryPacket;
serialStruct serialPacket;

keyboardStruct convertPacket2Keyboard(packetStruct packet)
{
    keyboardPacket.deviceID = packet.deviceID;
    keyboardPacket.key[0] = packet.data[0];
    keyboardPacket.key[1] = packet.data[1];
    keyboardPacket.key[2] = packet.data[2];
    keyboardPacket.key[3] = packet.data[3];
    keyboardPacket.key[4] = packet.data[4];
    keyboardPacket.key[5] = packet.data[5];
    keyboardPacket.key[6] = packet.data[6];
    keyboardPacket.key[7] = packet.data[7];
    return keyboardPacket;
}

mouseStruct convertPacket2Mouse(packetStruct packet)
{
    mousePacket.deviceID = packet.deviceID;
    mousePacket.x = packet.data[0];
    mousePacket.y = packet.data[1];
    mousePacket.w = packet.data[2];
    mousePacket.p = packet.data[3];
    mousePacket.k = packet.data[4];
    return mousePacket;
}

gamepadStruct convertPacket2Gamepad(packetStruct packet)
{
    gamepadPacket.deviceID = packet.deviceID;
    gamepadPacket.x = packet.data[0];
    gamepadPacket.y = packet.data[1];
    gamepadPacket.z = packet.data[2];
    gamepadPacket.rz = packet.data[3];
    gamepadPacket.rx = packet.data[4];
    gamepadPacket.ry = packet.data[5];
    gamepadPacket.hh = packet.data[6];

    for(uint8_t i = 0; i < 4; ++i)
    {
        gamepadPacket.buttons[i] = packet.data[7+i];
    }
    return gamepadPacket;
}

ledStruct convertPacket2Led(packetStruct packet)
{
    ledPacket.deviceID = packet.deviceID;
    ledPacket.function = packet.data[0];
    ledPacket.red = packet.data[1];
    ledPacket.green = packet.data[2];
    ledPacket.blue = packet.data[3];
    return ledPacket;
}

knobStruct convertPacket2Knob(packetStruct packet)
{
    knobPacket.deviceID = packet.deviceID;  
    for(uint8_t i = 0; i < 7; ++i)
    {
      knobPacket.knob[i] = packet.data[i];
    }
    return knobPacket;
}

actuatorStruct convertPacket2Actuator(packetStruct packet)
{
    actuatorPacket.deviceID = packet.deviceID;
    actuatorPacket.function = packet.data[0];
    actuatorPacket.position = packet.data[1];
    actuatorPacket.command = packet.data[2];
    return actuatorPacket;
}

displayStruct convertPacket2Display(packetStruct packet)
{
    displayPacket.deviceID = packet.deviceID;
    displayPacket.image = packet.data[0];
    displayPacket.x = packet.data[1];
    displayPacket.y = packet.data[2];
    displayPacket.brightness = packet.data[3];
    return displayPacket;
}

telemetryStruct convertPacket2Telemetry(packetStruct packet)
{
    telemetryPacket.deviceID = packet.deviceID;
    telemetryPacket.battery = packet.data[0];
    telemetryPacket.temperature = packet.data[1];
    telemetryPacket.macAddress = packet.data[2];
    telemetryPacket.error = packet.data[3];
    return telemetryPacket;
}   

serialStruct convertPacket2Serial(packetStruct packet)
{
    serialPacket.deviceID = packet.deviceID;
    for(uint8_t i = 0; i < 7; ++i)
    {
      serialPacket.packet[i] = packet.data[i];
    }
    return serialPacket;
}