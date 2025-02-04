#pragma once

#define MAX_NUMBER_OF_DEEJ_KNOBS 8

#include "Arduino.h"
#include <vector>
#include <algorithm>

#include "Adafruit_TinyUSB.h"
#include "variables.h"
#include "config.h"

int8_t forceLayer = -1;

//#include "uartHandle.h"



#define PMK_DEVICE_ID_BYTE 0
#define PMK_PACKET_TYPE_BYTE 1
#define PMK_DATA_BYTE 2

#define LAYER_0 0xF0
#define LAYER_1 0xF1
#define LAYER_2 0xF2
#define LAYER_3 0xF3
#define LAYER_4 0xF4
#define LAYER_5 0xF5
#define LAYER_6 0xF6
#define LAYER_7 0xF7



uint8_t ledBrightness = 0;

uint8_t layerID = 0;

uint8_t keyboardDeviceID = 255;

uint8_t knobIDToDeej[MAX_NUMBER_OF_DEEJ_KNOBS] = {0};



typedef struct packetStruct {
    uint8_t deviceID;
    uint8_t packetType = 255;
    uint8_t data[16];
}   packetStruct;



typedef struct telemetryStruct {
    uint8_t deviceID;
    const uint8_t packetType = 0;
    uint8_t battery;
    uint8_t temperature;
    uint8_t macAddress[6];
    uint8_t error[5];
}   telemetryStruct;



typedef struct keyboardStruct {
    uint8_t deviceID;
    const uint8_t packetType = 1;
    uint8_t key[8] = {0};
}   keyboardStruct;



typedef struct mouseStruct {
    uint8_t deviceID;
    const uint8_t packetType = 2;
    int8_t x;
    int8_t y;
    int8_t w;
    int8_t p;
    uint8_t key;  //5 possible buttons, 8 bits be smart u dumbass, dont use an array. (I used an array before)
}   mouseStruct;



typedef struct gamepadStruct {
    uint8_t deviceID;
    const uint8_t packetType = 3;
    int8_t leftX;
    int8_t leftY;
    int8_t rightX;
    int8_t rightY;
    int8_t leftTrigger;
    int8_t rightTrigger;
    uint8_t dpad;   //0b000ldruc - Left - Down - Right - Up - Center
    uint8_t buttons[4];
}   gamepadStruct;



typedef struct ledStruct {
    uint8_t deviceID;
    const uint8_t packetType = 4;
    uint8_t function;
    uint8_t ledNumberStart;
    uint8_t ledNumberEnd;
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
    uint8_t function;   //Can be Torque, Speed, Position, Acceleration
    uint8_t command;    //Sent by Master
    uint8_t position;   //Returned by device
}   actuatorStruct;



typedef struct displayStruct {
    uint8_t deviceID;
    const uint8_t packetType = 7;
    uint8_t image;
    uint8_t x;
    uint8_t y;
    uint8_t brightness;
}   displayStruct;



typedef struct serialStruct {
    uint8_t deviceID;
    const uint8_t packetType = 8;
    uint8_t packet[8];
}   serialStruct;



typedef struct spaceMouseStruct {
    uint8_t deviceID;
    const uint8_t packetType = 9;
    int8_t trans[3];
    int8_t rot[3];
}   spaceMouseStruct;


enum errorID {
    none, 
    tooManyKeysPressed,
    overTemperature,
    lowBattery,
    invalidPacket,
    internalSensorFailure
};



keyboardStruct   keyboardPacket[8];
mouseStruct      mousePacket;
gamepadStruct    gamepadPacket[8];
ledStruct        ledPacket;
knobStruct       knobPacket[8];
actuatorStruct   actuatorPacket;
displayStruct    displayPacket;
telemetryStruct  telemetryPacket;
serialStruct     serialPacket;
spaceMouseStruct spaceMousePacket;



void setupPMK()
{
    for(uint8_t deviceID = 0; deviceID < 8; deviceID++)
    {
        keyboardPacket[deviceID].deviceID = deviceID;

        for(uint8_t keyID = 0; keyID < 8; keyID++)
        {
            keyboardPacket[deviceID].key[keyID] = 0;
            knobPacket[deviceID].knob[keyID] = 0;   // not really a keyID but you get the idea
        }

        gamepadPacket[deviceID].rightX = -128;
        gamepadPacket[deviceID].rightY = -128;
        gamepadPacket[deviceID].leftX = -128;
        gamepadPacket[deviceID].leftY = -128;
        gamepadPacket[deviceID].leftTrigger = -128;
        gamepadPacket[deviceID].rightTrigger = -128;
    }
}



void convertPacket2Telemetry(packetStruct packet)
{
    telemetryPacket.deviceID = packet.deviceID;
    telemetryPacket.battery = packet.data[0];
    telemetryPacket.temperature = packet.data[1];
    telemetryPacket.macAddress[0] = packet.data[2]; //MAC address might not stay, maybe useless TODO
    telemetryPacket.macAddress[1] = packet.data[3];
    telemetryPacket.macAddress[2] = packet.data[4];
    telemetryPacket.macAddress[3] = packet.data[5];
    telemetryPacket.macAddress[4] = packet.data[6];
    telemetryPacket.macAddress[5] = packet.data[7];
    telemetryPacket.error[0] = packet.data[8];
    telemetryPacket.error[1] = packet.data[9];
    telemetryPacket.error[2] = packet.data[10];
    telemetryPacket.error[3] = packet.data[11];
    telemetryPacket.error[4] = packet.data[12];
}



void convertPacket2Keyboard(packetStruct packet)
{
    keyboardPacket[packet.deviceID].deviceID = packet.deviceID;
    keyboardPacket[packet.deviceID].key[0] = packet.data[0];
    keyboardPacket[packet.deviceID].key[1] = packet.data[1];
    keyboardPacket[packet.deviceID].key[2] = packet.data[2];
    keyboardPacket[packet.deviceID].key[3] = packet.data[3];
    keyboardPacket[packet.deviceID].key[4] = packet.data[4];
    keyboardPacket[packet.deviceID].key[5] = packet.data[5];
    keyboardPacket[packet.deviceID].key[6] = packet.data[6];
    keyboardPacket[packet.deviceID].key[7] = packet.data[7];

    #ifdef DEBUG
    if(debug2)
    {
        Serial.printf("Keyboard packet: ");
        for(uint8_t i = 0; i < 8; i++)
        {
            Serial.printf(" %02X", keyboardPacket[packet.deviceID].key[i]);
        }
        Serial.printf("\r\n");
    }
    #endif
    
}



void convertPacket2Mouse(packetStruct packet)
{
    mousePacket.deviceID = packet.deviceID;
    mousePacket.x = packet.data[0];
    mousePacket.y = packet.data[1];
    mousePacket.w = packet.data[2];
    mousePacket.p = packet.data[3];
    mousePacket.key = packet.data[4];
}



void convertPacket2Gamepad(packetStruct packet)
{
    gamepadPacket[packet.deviceID].deviceID = packet.deviceID;
    gamepadPacket[packet.deviceID].leftX = packet.data[0];
    gamepadPacket[packet.deviceID].leftY = packet.data[1];
    gamepadPacket[packet.deviceID].rightX = packet.data[2];
    gamepadPacket[packet.deviceID].rightY = packet.data[3];
    gamepadPacket[packet.deviceID].leftTrigger = packet.data[4];
    gamepadPacket[packet.deviceID].rightTrigger = packet.data[5];
    gamepadPacket[packet.deviceID].dpad = packet.data[6];

    for(uint8_t i = 0; i < 4; ++i)
    {
        gamepadPacket[packet.deviceID].buttons[i] = packet.data[7+i];
    }
}



void convertPacket2Led(packetStruct packet)
{
    ledPacket.deviceID = packet.deviceID;
    ledPacket.function = packet.data[0];
    ledPacket.red = packet.data[1];
    ledPacket.green = packet.data[2];
    ledPacket.blue = packet.data[3];
}



void convertPacket2Knob(packetStruct packet)
{
    knobPacket[packet.deviceID].deviceID = packet.deviceID;  
    for(uint8_t i = 0; i < 7; ++i)
    {
      knobPacket[packet.deviceID].knob[i] = packet.data[i];
    }
}



void convertPacket2Actuator(packetStruct packet)
{
    actuatorPacket.deviceID = packet.deviceID;
    actuatorPacket.function = packet.data[0];
    actuatorPacket.position = packet.data[1];
    actuatorPacket.command = packet.data[2];
}



void convertPacket2Display(packetStruct packet)
{
    displayPacket.deviceID = packet.deviceID;
    displayPacket.image = packet.data[0];
    displayPacket.x = packet.data[1];
    displayPacket.y = packet.data[2];
    displayPacket.brightness = packet.data[3];
} 



void convertPacket2Serial(packetStruct packet)
{
    serialPacket.deviceID = packet.deviceID;
    for(uint8_t i = 0; i < 8; i++)
    {
      serialPacket.packet[i] = packet.data[i];
    }
}



void convertPacket2SpaceMouse(packetStruct packet)
{
    spaceMousePacket.deviceID = packet.deviceID;
    for(uint8_t i = 0; i < 3; i++)
    {
        spaceMousePacket.trans[i] = packet.data[i];
        spaceMousePacket.rot[i] = packet.data[i + 3];
    }
}



uint8_t nonZeroSize(uint8_t arr[])
{
    uint8_t count = 0;

    for(uint8_t i = 0; i < 8; i++)
    {
        if(arr[i] == 0)
        {
            return i;
        }
    }
    return 255;
}



bool keycodeIsDifferent(uint8_t prevKeycode[6], uint8_t keycode[6])
{
    for(uint8_t i = 0; i < 6; i++)
    {
        if(keycode[i] != prevKeycode[i])
        {
            return 1;
        }
    }

    return 0;
}



void handleKeyboard()
{

    if(TinyUSBDevice.suspended())
    {
        TinyUSBDevice.remoteWakeup();
    }
    
    uint8_t keycode[6] = {0};
    uint8_t keycodeNumber = 0;
    uint8_t modifier = 0x00;
    std::vector<uint16_t> keyToPress{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,};

    if(forceLayer != -1)
    {
        layerID = forceLayer;
    }
    else
    {
        layerID = 0;  // Needed to have layer keys as press only and to toggle
        
        //Need to check for layer change key before going further
        for(uint8_t deviceID = 0; deviceID < 8; deviceID++)
        {
            for(uint8_t i = 0; i < 8; i++)
            {
                switch(keyIDtoHID(keyboardPacket[deviceID].key[i], layerID, deviceID))
                {
                    case LAYER_1:
                        layerID = 1;
                        break;
                    case LAYER_2:
                        layerID = 2;
                        break;
                }
            }
        }
    }
    //Serial.printf("Current layer is: %i\r\n", layerID);

    //Convert key[8] to HID[64]
    for(uint8_t deviceID = 0; deviceID < 8; deviceID++)
    {
        for(uint8_t i = 0; i < 8; i++)
        {
            keyToPress[i + deviceID*8] = keyIDtoHID(keyboardPacket[deviceID].key[i], layerID, deviceID);
        }
    }

    //Delete duplicate HID
    std::sort(keyToPress.begin(), keyToPress.end());
    keyToPress.erase(std::unique(keyToPress.begin(), keyToPress.end()), keyToPress.end());

    //Serial.printf("%02X %02X %02X %02X %02X %02X\r\n", keyToPress[0], keyToPress[1], keyToPress[2], keyToPress[3], keyToPress[4], keyToPress[5]);

    uint8_t numberOfKeyToPress = std::find(keyToPress.begin(), keyToPress.end(), 0xFFFF) - keyToPress.begin();
    //Serial.printf("Number of keys to press: %i\r\n", numberOfKeyToPress);

    for(uint8_t i = 0; i < numberOfKeyToPress; i++) //Add the final keyToPress to the report / deal with modifiers
    {
        uint16_t HIDKey = keyToPress[i];
        if(0xDF < HIDKey && HIDKey < 0xE8)
        {
            //We have a modifier
            modifier = modifier | (1 << (HIDKey - 0xE0));   //First modifier is 0xE0 Left control
            //Serial.printf("Modifier is: %02X\r\n", modifier);
        }
        //Serial.printf("Pressing: 0x%u, on layer: %i, Equivalent HID: %u\r\n", keyboardPacket.key[i], layerID, keyIDtoChar(keyboardPacket.key[i], layerID));

        if(HIDKey < 0xA5 )
        {
            //We have a non modifier key
            if(keycodeNumber < 6)
            {
                keycode[keycodeNumber] = HIDKey;
            }

            keycodeNumber++;
        }

        if(HIDKey < 0xA5 && keycodeNumber > 6)
        {
            //6KRO error
            for(uint8_t j = 0; j < 6; j++)
            {
                keycode[j] = 0x01;
            }
        }

        //Deal here with special keys (brightness, volume, etc...)
        //Consummer needs debounce
        static unsigned long previousConsumerControlTime = 0; 
        if((0x1000 <= HIDKey && HIDKey < 0x2000 && previousConsumerControlTime + 200 < millis())
            || (HIDKey == 0x10EA && previousConsumerControlTime + 20 < millis())
            || (HIDKey == 0x10E9 && previousConsumerControlTime + 20 < millis())
        )
        {
            HIDKey -= 0x1000;
            //Serial.printf("Consummer control: %04X\r\n", HIDKey);
            usb_hid.sendReport16(RID_CONSUMER_CONTROL, HIDKey);
            previousConsumerControlTime = millis();
        }

        //Mouse key
        static unsigned long previousMouseTime = 0;
        if(0x2000 <= HIDKey && HIDKey < 0x3000 && previousMouseTime + 200 < millis())
        {
            HIDKey -= 0x2000;
            HIDKey = 1 << HIDKey;
            usb_hid.mouseReport(RID_MOUSE, HIDKey, 0, 0, 0, 0);
            
            previousMouseTime = millis();
        }
    }

    #ifdef DEBUG
    if(debug3)
    {
        Serial.printf("Report: %02X %02X %02X %02X %02X %02X modifier: %02X\r\n", keycode[0], keycode[1], keycode[2], keycode[3], keycode[4], keycode[5], modifier);
    }
    #endif

    static uint8_t prevModifier;
    static uint8_t prevKeycode[6];

    //if(!usb_hid.ready())
    //{
    //    Serial.printf("not ready \r\n");
    //    return;
    //}
    //Serial.printf("usb ready\r\n");

    if((prevModifier != modifier) || keycodeIsDifferent(prevKeycode, keycode))
    {
        usb_hid.keyboardReport(RID_KEYBOARD, modifier, keycode);
    }

    prevModifier = modifier;
    memcpy(prevKeycode, keycode, 6);

}



void handleMouse()
{
    if(usb_hid.ready())
    {
        #ifdef DEBUG
        if(debug3)
        {
            Serial.printf("x: %i, y: %i, key: %u, wheel: %i, pan: %i", mousePacket.x, mousePacket.y, mousePacket.key,mousePacket.w, mousePacket.p);
        }
        #endif
        usb_hid.mouseReport(RID_MOUSE, mousePacket.key, mousePacket.x*dpi[mousePacket.deviceID][layerID], mousePacket.y*dpi[mousePacket.deviceID][layerID], mousePacket.w, mousePacket.p);
    }
}



void handleGamepad()
{
    if(usb_hid.ready())
    {
        gp.hat = 0;
        gp.buttons = 0;
        gp.rx = 0;
        gp.ry = 0;
        gp.rz = 0;
        gp.x = 0;
        gp.y = 0;
        gp.z = 0;

        for(uint8_t deviceID = 0; deviceID < 8; deviceID++)
        {
            gp.hat |= gamepadPacket[deviceID].dpad;
            gp.buttons |= gamepadPacket[deviceID].buttons[0] | (gamepadPacket[deviceID].buttons[1] << 8) | (gamepadPacket[deviceID].buttons[2] << 16) | (gamepadPacket[deviceID].buttons[3] << 24);

            if(gamepadPacket[deviceID].rightX != -128)
            {
                gp.x = gamepadPacket[deviceID].rightX;
            }
            
            if(gamepadPacket[deviceID].rightY != -128)
            {
                gp.y = gamepadPacket[deviceID].rightY;
            }
            
            if(gamepadPacket[deviceID].leftX != -128)
            {
                gp.z = gamepadPacket[deviceID].leftX;
            }
            
            if(gamepadPacket[deviceID].leftY != -128)
            {
                gp.rx = gamepadPacket[deviceID].leftY;
            }
            
            if(gamepadPacket[deviceID].rightTrigger != -128)
            {
                gp.ry = gamepadPacket[deviceID].rightTrigger;
            }
            
            if(gamepadPacket[deviceID].leftTrigger != -128)
            {
                gp.rz = gamepadPacket[deviceID].leftTrigger;
            }
        }
        
        usb_hid.sendReport(RID_GAMEPAD, &gp, sizeof(gp));
    }
}



void handleDeej(uint8_t volume[MAX_NUMBER_OF_DEEJ_KNOBS])
{
    if(deejToggle)
    {
        String builtString = String("");

        for (int i = 0; i < MAX_NUMBER_OF_DEEJ_KNOBS; i++) 
        {
            builtString += String((int)volume[i]*4);

            if (i < MAX_NUMBER_OF_DEEJ_KNOBS - 1)
            {
                builtString += String("|");
            }
        }
    
        Serial.println(builtString);  // TODO only send when different
    }
}



void handleKnob()
{
    uint8_t aggregatedKnobs[8*MAX_NUMBER_OF_DEVICES];

    for(uint8_t deviceID = 0; deviceID < MAX_NUMBER_OF_DEVICES; deviceID++)
    {
        for(uint8_t knobID = 0; knobID < 8; knobID++)
        {
            aggregatedKnobs[deviceID * 8 + knobID] = knobPacket[deviceID+1].knob[knobID];
        }
    }

    uint8_t volume[MAX_NUMBER_OF_DEEJ_KNOBS];
    for(uint8_t knobID = 0; knobID < MAX_NUMBER_OF_DEEJ_KNOBS; knobID++)
    {
        volume[knobID] = aggregatedKnobs[knobIDToDeej[knobID]]; // deej json contains the knobID from aggreagatedKnobs to use for volume
    }

    handleDeej(volume);
}



void handleSpaceMouse()
{
    int16_t trans_report[3];
    int16_t rot_report[3];

    for(uint8_t i = 0; i < 3; i++)
    {
        trans_report[i] = map(spaceMousePacket.trans[i], -128, 127, -1400, 1400);
        rot_report[i] =   map(spaceMousePacket.rot[i],   -128, 127, -1400, 1400);
    }

    if(usb_hid.ready())
    {
        usb_hid.sendReport(1, trans_report, 6);
        delay(10);  // TODO FIX THIS DELAY
    }
    
    if(usb_hid.ready())
    {
        usb_hid.sendReport(2, rot_report, 6);
        delay(10);  // TODO FIX THIS DELAY
    }
}