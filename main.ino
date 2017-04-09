#include <SPI.h>           // Ethernet shield
#include <Ethernet.h>      // Ethernet shield
#include <PubSubClient.h>  // MQTT 
#include <Wire.h>
#include <Adafruit_MCP23017.h>
//#include <EEPROM.h>
    
//C:\Users\instalator\AppData\Local\Temp
#define OUT_0  "myhome/lighting/BedRoom_main"
#define OUT_1  "myhome/lighting/BedRoom_sec"
#define OUT_2  "myhome/lighting/GuestRoom_main"
#define OUT_3  "myhome/lighting/GuestRoom_main2"
#define OUT_4  "myhome/lighting/GuestRoom_sec"
#define OUT_5  "myhome/lighting/Kitchen_main"
#define OUT_6  "myhome/lighting/Kitchen_sec"
#define OUT_7  "myhome/lighting/BathRoom_main"
#define OUT_8  "myhome/lighting/BathRoom_sec"
#define OUT_9  "myhome/lighting/Hall_main"
#define OUT_10 "myhome/lighting/reserv"
#define OUT_11 "myhome/lighting/reserv"
#define OUT_12 "myhome/lighting/reserv"
#define OUT_13 "myhome/lighting/reserv"
#define OUT_14 "myhome/lighting/reserv"
#define OUT_15 "myhome/lighting/reserv"
#define OUT_16 "myhome/lighting/reserv"
#define OUT_17 "myhome/lighting/reserv"
#define OUT_18 "myhome/lighting/reserv"
#define OUT_19 "myhome/lighting/reserv"
#define OUT_20 "myhome/Bathroom/Ventilator"


#define MCP_INTA 19
#define MCP_INTB 18
#define IN_UP1 56 //A2
#define IN_UP2 57 //A3
#define IN_UP3 58 //A4
#define IN_UP4 59 //A5
#define IN_UP5 60 //A6
#define IN_UP6 61 //A7
#define IN_UP7 15 //RXD3
#define IN_UP8 14 //TXD3

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

#define IN_DW1 21 //SCL
#define IN_DW2 20 //SDA
#define IN_DW3 12
#define IN_DW4 13
#define IN_DW5 48
#define IN_DW6 47
#define IN_DW7 49
#define IN_DW8 43

Adafruit_MCP23017 mcp;
uint16_t mcp_oldstate = 0;
byte btn[16];
byte btn_old[16] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
bool lock = false; 
long prevMillis = 0; //для reconnect
long prevMillis2 = 0; // для ванной
long prevMillis3 = 0; //для подсветки шкафа
int bathswitch = 0; 
int posetitel = 0; 
int left = 0;
int right = 0;
bool flag_cupboard = false;
int i_cup = 255;
bool cupboard = false;
bool All_OFF = false;
String inputString = "";

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
#define ID_CONNECT "lighting"
#define PREF "myhome/lighting/"

byte out[21] = {29, 30, 31, 32, 33, 34, 35, 22, 23, 24, 25, 26, 27, 28, 36, 37, 38, 39, 40, 41, 42};
byte bt[16] = {15, 14, 13, 12, 11, 10, 9, 8, 0, 1, 2, 3, 4, 5, 6, 7};


void reconnect() {
    if (client.connect(ID_CONNECT)) {
      client.publish("myhome/lighting/connection", "true");
      PubTopic();
      client.subscribe("myhome/lighting/#");
      client.subscribe("myhome/Bathroom/#");
    }
}
void setup() {
  
  DDRA = 0xFF;
  DDRC = 0xFF;
  DDRG |= 0b00000111;
  DDRL |= 0b10000000;
  DDRD |= 0b00001100;
  
  pinMode(IN_UP7, INPUT);
  pinMode(IN_UP8, INPUT);
  pinMode(IR_1, INPUT);
  pinMode(IR_2, INPUT);
  
  analogWrite(PWM_1, 255);
  analogWrite(PWM_2, 255);
  analogWrite(PWM_3, 255);
  analogWrite(PWM_4, 255);
  analogWrite(PWM_5, 255);
  analogWrite(PWM_6, 255);
  analogWrite(PWM_7, 255);
  analogWrite(PWM_8, 255);
  analogWrite(PWM_9, 255);
  
  Serial.begin(115200);
  Serial2.begin(19200);
  mcp.begin();
  delay(10);
  //mcp.setupInterrupts(true, false, LOW);
  for(int i = 0; i <= 15; i++){
    mcp.pinMode(i, INPUT);
    //mcp.setupInterruptPin(i, FALLING);
  }

  Ethernet.begin(mac, ip);
  delay(10);
}

void loop() { 
   client.loop();
    if (Serial2.available() > 0) {
      char inChar = (char)Serial2.read(); 
      inputString += inChar;
      if (inChar == '\n') {
        inputString.replace(" ", "");
        char charVar[20];
        inputString.toCharArray(charVar, 20);
        client.publish("myhome/lighting/UART2", charVar);
        inputString = "";
        //stringComplete = true;
      } 
    }
    ReadButton();
    Bath();
    IRsens();
    Smooth_light();
    if (!client.connected()){ 
     if (millis() - prevMillis > 10000){
        prevMillis = millis();
        reconnect();
     }
   }
}

char* state(int num){
  int s = digitalRead(out[num]);
    if (s > 0){
      return "true";
    } else {
      return "false";
    }
}

void PubTopic (){
    client.publish(OUT_0, state(0));
    client.publish(OUT_1, state(1));
    client.publish(OUT_2, state(2));
    client.publish(OUT_3, state(3));
    client.publish(OUT_4, state(4));
    client.publish(OUT_5, state(5));
    client.publish(OUT_6, state(6));
    client.publish(OUT_7, state(7));
    client.publish(OUT_8, state(8));
    client.publish(OUT_9, state(9));
    client.publish(OUT_10, state(10));
    client.publish(OUT_11, state(11));
    client.publish(OUT_12, state(12));
    client.publish(OUT_13, state(13));
    client.publish(OUT_14, state(14));
    client.publish(OUT_15, state(15));
    client.publish(OUT_16, state(16));
    client.publish(OUT_17, state(17));
    client.publish(OUT_18, state(18));
    client.publish(OUT_19, state(19));
    client.publish(OUT_20, state(20));
    client.publish("myhome/lighting/Cupboard", BoolToChar(cupboard));
    client.publish("myhome/lighting/All_OFF",  BoolToChar(All_OFF));
    client.publish("myhome/lighting/Lock", BoolToChar(lock));
    
    client.publish("myhome/lighting/Switch_RGB", "99R0G0B0");
    client.publish("myhome/lighting/RGB_1", "R0G0B0");
    client.publish("myhome/lighting/RGB_2", "R0G0B0");
    client.publish("myhome/lighting/RGB_3", "R0G0B0");
    client.publish("myhome/lighting/PWM_1", "0");
    client.publish("myhome/lighting/PWM_2", "0");
    client.publish("myhome/lighting/PWM_3", "0");
    client.publish("myhome/lighting/PWM_4", "0");
    client.publish("myhome/lighting/PWM_5", "0");
    client.publish("myhome/lighting/PWM_6", "0");
    client.publish("myhome/lighting/PWM_7", "0");
    client.publish("myhome/lighting/PWM_8", "0");
    client.publish("myhome/lighting/PWM_9", "0");
  }
