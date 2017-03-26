
#include <SPI.h>           // Ethernet shield
#include <Ethernet.h>      // Ethernet shield
#include <PubSubClient.h>  // MQTT 
#include <Wire.h>
#include <Adafruit_MCP23017.h>

Adafruit_MCP23017 mcp;

#define ledPin = 43

#define MCP_INTA 19
#define MCP_INTB 18
#define IN_UP1 56 //A2
#define IN_UP2 57 //A3
#define IN_UP3 58 //A4
#define IN_UP4 59 //A5
#define IN_UP5 60 //A6
#define IN_UP6 61 //A7
#define IN_UP7 15
#define IN_UP8 14

#define PWM_1 44
#define PWM_2 45
#define PWM_3 46
#define PWM_4 6
#define PWM_5 7
#define PWM_6 4
#define PWM_7 5
#define PWM_8 3
#define PWM_9 2

#define IR_1 55 //A1
#define IR_2 54 //A0
#define LED_1 10
#define LED_2 11

#define IN_DW1 21
#define IN_DW2 20
#define IN_DW3 12
#define IN_DW4 13
#define IN_DW5 48
#define IN_DW6 47
#define IN_DW7 49
#define IN_DW8 43



uint16_t mcp_oldstate = 0;
byte btn[15];
byte btn_old[15];

byte mac[]    = { 0x0C, 0x8E, 0xC0, 0x42, 0x19, 0x42 };
byte server[] = { 192, 168, 1, 190 }; //IP Брокера
byte ip[]     = { 192, 168, 1, 63 }; //IP Клиента (Arduino)

void callback(char* topic, byte* payload, unsigned int length) {
    payload[length] = '\0';
    String strTopic = String(topic);
    String strPayload = String((char*)payload);
    callback_iobroker(strTopic, strPayload);
}

EthernetClient ethClient;
PubSubClient client(server, 1883, callback, ethClient);
#define ID_CONNECT "Lighting2"
#define PREF "myhome/Lighting2/"

bool state_out;
byte out[] = {29, 30, 31, 32, 33, 34, 35, 22, 23, 24, 25, 26, 27, 28, 36, 37, 38, 39, 40, 41, 42};
byte bt[] = {15, 14, 13, 12, 11, 10, 9, 8, 0, 1, 2, 3, 4, 5, 6, 7};

void reconnect() {
  while (!client.connected()) {
    if (client.connect(ID_CONNECT)) {
      client.publish("myhome/Lighting2/connection", "true");
      PubTopic();
      client.subscribe("myhome/Lighting2/#");
    } else {
        delay(5000);  //TODO
    }
  }
}
void setup() {
  DDRA = 0xFF;
  DDRC = 0xFF;
  DDRG |= 0b00000111;
  DDRL |= 0b10000000;
  
  Serial2.begin(19200);
  mcp.begin();
  mcp.setupInterrupts(true, false, LOW);
  for(int i = 0; i <= 15; i++){
    mcp.pinMode(i, INPUT);
    mcp.setupInterruptPin(i, FALLING);
  }
  Ethernet.begin(mac, ip);
}

void loop() { 
  if (client.connected()){
    if (Serial2.available() > 0) {
      int inByte = Serial2.read();
      client.publish("myhome/Lighting2/UART", inByte);
    }
    client.loop();
    ReadButton();
  } else {
    reconnect();
  }
}

void PubTopic (){
    client.publish("myhome/Lighting2/All_OFF", "false");
    //client.publish("myhome/Bathroom2/Ventilator", "false");
    client.publish("myhome/Lighting2/BedRoom_Main", "false");
    client.publish("myhome/Lighting2/BedRoom_Additional", "false");
    client.publish("myhome/Lighting2/GuestRoom_Main", "false");
    client.publish("myhome/Lighting2/GuestRoom_Main2", "false");
    client.publish("myhome/Lighting2/GuestRoom_Additional", "false");
    client.publish("myhome/Lighting2/Kitchen_Main", "false");
    client.publish("myhome/Lighting2/Kitchen_Additional", "false");
    client.publish("myhome/Lighting2/BathRoom_Main", "false");
    client.publish("myhome/Lighting2/BathRoom_Additional", "false");
    client.publish("myhome/Lighting2/Hall_Main", "false");
    client.publish("myhome/Lighting2/Cupboard", "false");
    client.publish("myhome/Lighting2/Lock", "false");
    client.publish("myhome/Lighting2/PWM1", "false");
  }
