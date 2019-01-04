#include <SPI.h>           // Ethernet shield
#include <Ethernet.h>      // >= 2.0.0 Ethernet shield
#include <PubSubClient.h>  // MQTT 
#include <Adafruit_MCP23017.h>
#include <avr/wdt.h>
#include <utility/w5100.h>
#include <TextFinder.h>
#include <EEPROM.h>
#include <avr/pgmspace.h>

#define OUT_0  "BedRoom_main"
#define OUT_1  "BedRoom_sec"
#define OUT_2  "GuestRoom_main"
#define OUT_3  "GuestRoom_main2"
#define OUT_4  "GuestRoom_sec"
#define OUT_5  "Kitchen_main"
#define OUT_6  "Kitchen_sec"
#define OUT_7  "BathRoom_main"
#define OUT_8  "BathRoom_sec"
#define OUT_9  "Hall_main"
#define OUT_10 "reserv"
#define OUT_11 "reserv"
#define OUT_12 "reserv"
#define OUT_13 "reserv"
#define OUT_14 "reserv"
#define OUT_15 "reserv"
#define OUT_16 "reserv"
#define OUT_17 "reserv"
#define OUT_18 "reserv"
#define OUT_19 "reserv"
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
#define LED_1 10 //* транзисторный выход 100 mA
#define LED_2 11 //* транзисторный выход 100 mA

#define IN_DW1 21 //SCL
#define IN_DW2 20 //SDA
#define IN_DW3 12
#define IN_DW4 13
#define IN_DW5 48
#define IN_DW6 47
#define IN_DW7 49
#define IN_DW8 43

#define ID_CONNECT "lighting"
String TOPIC = "myhome/lighting/";

bool btn[16];
bool btn_old[16];
unsigned long prevMillis  = 0; // для reconnect
unsigned long prevMillis2 = 0; // для ванной
unsigned long prevMillis3 = 0; // для подсветки шкафа
unsigned long prevMillis4 = 0; // для теста подсветки шкафа
bool lock = false;
bool firststart = true;
bool bathswitch = false;
byte  posetitel = 0;
bool flag_cupboard = true;
byte  i_cup = 255;
bool cupboard = false;
bool mqtt_connect = false;
const byte ID = 0x91;
char buffer[100];
//char buf [50];
//String inputString = "";

const byte out[21] = {29, 30, 31, 32, 33, 34, 35, 22, 23, 24, 25, 26, 27, 28, 36, 37, 38, 39, 40, 41, 42};
const byte bt[16] = {15, 14, 13, 12, 11, 10, 9, 8, 0, 1, 2, 3, 4, 5, 6, 7};

byte mac[6]  = { 0x0C, 0x8E, 0xCE, 0x41, 0xEE, 0x11 }; //MAC адрес контроллера
byte mqtt_serv[] = {192, 168, 88, 190}; //IP MQTT брокера

void callback(char* topic, byte* payload, unsigned int length) {
  payload[length] = '\0';
  String strTopic = String(topic);
  String strPayload = String((char*)payload);
  callback_mqtt(strTopic, strPayload);
}
Adafruit_MCP23017 mcp;
EthernetClient ethClient;
EthernetServer http_server(80);
PubSubClient mqtt(ethClient);

void setup() {
  MCUSR = 0;
  wdt_disable();
  pinconfig();
  //Serial.begin(115200);
  Serial2.begin(19200);
  //inputString.reserve(20);
  mcp.begin();
  delay(1000);
  //mcp.setupInterrupts(true, false, LOW);
  for (int i = 0; i <= 15; i++) {
    mcp.pinMode(i, INPUT);
    //mcp.setupInterruptPin(i, FALLING);
  }
  httpSetup();
  mqttSetup();
  delay(1000);
  wdt_enable(WDTO_8S);
  prevMillis = 0;
}

boolean reconnect() {
  if (mqtt.connect(ID_CONNECT)) {
    mqtt_connect = true;
    wdt_reset();
    mqtt_publish("connection", "true");
    PubTopic();
    mqtt.subscribe(topic("#").c_str());
    mqtt.subscribe("myhome/Bathroom/#");
  }
  return mqtt.connected();
}

void loop() {
  wdt_reset();
  checkHttp();
  if (!mqtt.loop()) {
    mqtt_connect = false;
    if (millis() - prevMillis > 60000) {
      prevMillis = millis();
      if (reconnect()) {
        //prevMillis = 0;
      }
      if (Ethernet.linkStatus() == LinkON) { //Если есть линк
        if (Ethernet.begin(mac) == 0) {
          Reset();
        } else {

        }
      }
    }
  }
  ReadButton();
  Bath();
  IRsens();
  Smooth_light();
  //Bath();

  /*if (Serial2.available() > 0) {
    char inChar = (char)Serial2.read();
    inputString += inChar;
    if (inChar == '\n') {
      inputString.replace(" ", "");
      char charVar[20];
      inputString.toCharArray(charVar, 20);
      mqtt.publish("myhome/lighting/UART2", charVar);
      inputString = "";
    }
    }*/
}

void mqttSetup() {
  int idcheck = EEPROM.read(0);
  if (idcheck == ID) {
    for (int i = 0; i < 4; i++) {
      mqtt_serv[i] = EEPROM.read(i + 7);
    }
  }
  mqtt.setServer(mqtt_serv, 1883);
  mqtt.setCallback(callback);
  reconnect();
}

void httpSetup() {
  Ethernet.init(53); //Порт CS для W5100
  //Ethernet.setRetransmissionTimeout(0x01F4);
  //Ethernet.setRetransmissionCount(3);
  int idcheck = EEPROM.read(0);
  if (idcheck == ID) {
    for (int i = 0; i < 6; i++) {
      mac[i] = EEPROM.read(i + 1);
    }
  }
  Ethernet.begin(mac);
}
