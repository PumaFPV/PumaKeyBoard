#include "Arduino.h"

esp_now_peer_info_t peerInfo;

String success;

void handleReceivedPacket(packetStruct receivedPacket)
{
  switch(receivedPacket.packetType)
  {
  case 255: 
    //default packet
    break;
  case 0:
    Serial.println("Telem Packet");
    convertPacket2Telemetry(receivedPacket);
    break;
  case 1: //Keyboard
    convertPacket2Keyboard(receivedPacket);
    break;
  case 2: //Mouse
    convertPacket2Mouse(receivedPacket);
    break;
  case 3: //GamePad
    convertPacket2Gamepad(receivedPacket);
    break;
  case 4: //LED
    convertPacket2Led(receivedPacket);
    break;
  case 5: //Knob
    convertPacket2Knob(receivedPacket);
    break;
  case 6: //Actuator
    convertPacket2Actuator(receivedPacket);
    break;
  case 7: //Display
    convertPacket2Display(receivedPacket);
    break;
  case 8: //Serial
    convertPacket2Serial(receivedPacket);
    break;
  }
}

// Callback when data is sent
void OnEspNowDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) 
{
  //USBSerial.print("\r\nLast Packet Send Status:\t");
  //USBSerial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  if (status == 0)
  {
    success = "Delivery Success :)";
  }
  else
  {
    success = "Delivery Fail :(";
  }
}

// Callback when data is received
void OnEspNowDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) 
{
  memcpy(&receivedPacket, incomingData, sizeof(receivedPacket));
}

