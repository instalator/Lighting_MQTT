#include <SPI.h>           // Ethernet shield
#include <Ethernet.h>      // Ethernet shield
#include <PubSubClient.h>  // MQTT 
#include <Adafruit_MCP23017.h>
#include <avr/wdt.h>
#include <utility/w5100.h>
#include <TextFinder.h>
#include <EEPROM.h>
#include <avr/pgmspace.h>
/**
   inline static void initSS()    { DDRB  |=  _BV(0); };
   inline static void setSS()     { PORTB &= ~_BV(0); };
   inline static void resetSS()   { PORTB |=  _BV(0); };
*/
//#define SPI_HAS_EXTENDED_CS_PIN_HANDLING

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
#define PREF "myhome/lighting/"

Adafruit_MCP23017 mcp;
bool btn[16];
bool btn_old[16];
bool lock = false;
bool FirstStart = true;
unsigned long prevMillis  = 0; // для reconnect
unsigned long prevMillis2 = 0; // для ванной
unsigned long prevMillis3 = 0; // для подсветки шкафа
unsigned long prevMillis4 = 0; // для теста подсветки шкафа
int count = 0;
byte  bathswitch = false;
byte  posetitel = false;
bool flag_cupboard = true;
byte  i_cup = 255;
bool cupboard = false;
bool All_OFF = false;
//String inputString = "";
char buf [50];
int pwm;
boolean mqtt_connect = false;
const byte ID = 0x91;
char buffer[100];

const byte out[21] = {29, 30, 31, 32, 33, 34, 35, 22, 23, 24, 25, 26, 27, 28, 36, 37, 38, 39, 40, 41, 42};
const byte bt[16] = {15, 14, 13, 12, 11, 10, 9, 8, 0, 1, 2, 3, 4, 5, 6, 7};

byte mac[6]  = { 0x0C, 0x8E, 0xCE, 0x41, 0xEE, 0x11 }; //MAC адрес контроллера
byte mqtt_serv[] = {192, 168, 1, 190}; //IP MQTT брокера

const char htmlx0[] PROGMEM = "<html><title>Controller IO setup Page</title><body marginwidth=\"0\" marginheight=\"0\" ";
const char htmlx1[] PROGMEM = "leftmargin=\"0\" \"><table bgcolor=\"#999999\" border";
const char htmlx2[] PROGMEM = "=\"0\" width=\"100%\" cellpadding=\"1\" ";
const char htmlx3[] PROGMEM = "\"><tr><td>&nbsp Controller IO setup Page</td></tr></table><br>";
const char* const string_table0[] PROGMEM = {htmlx0, htmlx1, htmlx2, htmlx3};

const char htmla0[] PROGMEM = "<script>function hex2num (s_hex) {eval(\"var n_num=0X\" + s_hex);return n_num;}";
const char htmla1[] PROGMEM = "</script><table><form><input type=\"hidden\" name=\"SBM\" value=\"1\"><tr><td>MAC:&nbsp&nbsp&nbsp";
const char htmla2[] PROGMEM = "<input id=\"T1\" type=\"text\" size=\"1\" maxlength=\"2\" name=\"DT1\" value=\"";
const char htmla3[] PROGMEM = "\">.<input id=\"T3\" type=\"text\" size=\"1\" maxlength=\"2\" name=\"DT2\" value=\"";
const char htmla4[] PROGMEM = "\">.<input id=\"T5\" type=\"text\" size=\"1\" maxlength=\"2\" name=\"DT3\" value=\"";
const char htmla5[] PROGMEM = "\">.<input id=\"T7\" type=\"text\" size=\"1\" maxlength=\"2\" name=\"DT4\" value=\"";
const char htmla6[] PROGMEM = "\">.<input id=\"T9\" type=\"text\" size=\"1\" maxlength=\"2\" name=\"DT5\" value=\"";
const char htmla7[] PROGMEM = "\">.<input id=\"T11\" type=\"text\" size=\"1\" maxlength=\"2\" name=\"DT6\" value=\"";
const char* const string_table1[] PROGMEM = {htmla0, htmla1, htmla2, htmla3, htmla4, htmla5, htmla6, htmla7};

const char htmlb0[] PROGMEM = "\"><input id=\"T2\" type=\"hidden\" name=\"DT1\"><input id=\"T4\" type=\"hidden\" name=\"DT2";
const char htmlb1[] PROGMEM = "\"><input id=\"T6\" type=\"hidden\" name=\"DT3\"><input id=\"T8\" type=\"hidden\" name=\"DT4";
const char htmlb2[] PROGMEM = "\"><input id=\"T10\" type=\"hidden\" name=\"DT5\"><input id=\"T12\" type=\"hidden\" name=\"D";
const char htmlb3[] PROGMEM = "T6\"></td></tr><tr><td>MQTT: <input type=\"text\" size=\"1\" maxlength=\"3\" name=\"DT7\" value=\"";
const char htmlb4[] PROGMEM = "\">.<input type=\"text\" size=\"1\" maxlength=\"3\" name=\"DT8\" value=\"";
const char htmlb5[] PROGMEM = "\">.<input type=\"text\" size=\"1\" maxlength=\"3\" name=\"DT9\" value=\"";
const char htmlb6[] PROGMEM = "\">.<input type=\"text\" size=\"1\" maxlength=\"3\" name=\"DT10\" value=\"";
const char* const string_table2[] PROGMEM = {htmlb0, htmlb1, htmlb2, htmlb3, htmlb4, htmlb5, htmlb6};

const char htmlc0[] PROGMEM = "\"></td></tr><tr><td><br></td></tr><tr><td><input id=\"button1\"type=\"submit\" value=\"SAVE\" ";
const char htmlc1[] PROGMEM = "></td></tr></form></table></body></html>";
const char* const string_table3[] PROGMEM = {htmlc0, htmlc1};

const char htmld0[] PROGMEM = "Onclick=\"document.getElementById('T2').value ";
const char htmld1[] PROGMEM = "= hex2num(document.getElementById('T1').value);";
const char htmld2[] PROGMEM = "document.getElementById('T4').value = hex2num(document.getElementById('T3').value);";
const char htmld3[] PROGMEM = "document.getElementById('T6').value = hex2num(document.getElementById('T5').value);";
const char htmld4[] PROGMEM = "document.getElementById('T8').value = hex2num(document.getElementById('T7').value);";
const char htmld5[] PROGMEM = "document.getElementById('T10').value = hex2num(document.getElementById('T9').value);";
const char htmld6[] PROGMEM = "document.getElementById('T12').value = hex2num(document.getElementById('T11').value);\"";
const char* const string_table4[] PROGMEM = {htmld0, htmld1, htmld2, htmld3, htmld4, htmld5, htmld6};

void callback(char* topic, byte* payload, unsigned int length) {
  payload[length] = '\0';
  String strTopic = String(topic);
  String strPayload = String((char*)payload);
  callback_iobroker(strTopic, strPayload);
}

EthernetClient ethClient;
EthernetServer http_server(80);
PubSubClient mqtt(ethClient);


boolean reconnect() {
  if (mqtt.connect(ID_CONNECT)) {
    mqtt.publish("myhome/lighting/connection", "true");
    PubTopic();
    mqtt.subscribe("myhome/lighting/#");
    mqtt.subscribe("myhome/Bathroom/#");
    mqtt_connect = true;
  }
  return mqtt.connected();
}

/*void reconnect() {
    count++;
    wdt_reset();
    if (client.connect(ID_CONNECT)) {
      count = 0;
      wdt_reset();
      mqtt.publish("myhome/lighting/connection", "true");
      PubTopic();
      client.subscribe("myhome/lighting/#");
      client.subscribe("myhome/Bathroom/#");
    }
    for(int i = 0; i <= 15; i++){
      btn[i] = mcp.digitalRead(bt[i]);
      if (btn[i] == 1){
        count = 0;
      }
    }
    if (count > 50){
      wdt_enable(WDTO_15MS);
        for(;;){}
    }
  }*/

void setup() {
  MCUSR = 0;
  wdt_disable();
  DDRA = 0xFF;
  DDRC = 0xFF;
  DDRG |= 0b00000111;
  DDRL |= 0b10000000;
  DDRD |= 0b10000000;
  DDRB |= 0b00110000;

  pinMode(IN_UP7, INPUT);
  pinMode(IN_UP8, INPUT);
  pinMode(IR_1, INPUT);
  pinMode(IR_2, INPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
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
  W5100.setRetransmissionTime(0x01F4);
  W5100.setRetransmissionCount(3);
  wdt_enable(WDTO_8S);
  //Serial.print("START");
  prevMillis = 0;
}

void loop() {
  wdt_reset();
  checkHttp();
  if (!mqtt.connected()) {
    mqtt_connect = false;
    //unsigned long now = millis();
    if (millis() - prevMillis > 60000) {
      prevMillis = millis();
      if (Ethernet.begin(mac) == 0) {
        Reset();
      } else {
        if (reconnect()) {
          prevMillis = 0;
        }
      }
    }
  } else {
    mqtt.loop();
  }
  ReadButton();
  Bath();
  IRsens();
  Smooth_light();
  //Bath();

  /*if (!client.connected()) {
    if (millis() - prevMillis > 10000) {
      prevMillis = millis();
      reconnect();
    }
    }*/

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

void PubTopic () {
  if (mqtt_connect) {
    char s[16];
    sprintf(s, "%d.%d.%d.%d", Ethernet.localIP()[0], Ethernet.localIP()[1], Ethernet.localIP()[2], Ethernet.localIP()[3]);
    mqtt.publish("myhome/lighting/ip", s);
    mqtt.publish(OUT_0, state(0));
    mqtt.publish(OUT_1, state(1));
    mqtt.publish(OUT_2, state(2));
    mqtt.publish(OUT_3, state(3));
    mqtt.publish(OUT_4, state(4));
    mqtt.publish(OUT_5, state(5));
    mqtt.publish(OUT_6, state(6));
    mqtt.publish(OUT_7, state(7));
    mqtt.publish(OUT_8, state(8));
    mqtt.publish(OUT_9, state(9));
    mqtt.publish(OUT_10, state(10));
    mqtt.publish(OUT_11, state(11));
    mqtt.publish(OUT_12, state(12));
    mqtt.publish(OUT_13, state(13));
    mqtt.publish(OUT_14, state(14));
    mqtt.publish(OUT_15, state(15));
    mqtt.publish(OUT_16, state(16));
    mqtt.publish(OUT_17, state(17));
    mqtt.publish(OUT_18, state(18));
    mqtt.publish(OUT_19, state(19));
    mqtt.publish(OUT_20, state(20));
    mqtt.publish("myhome/lighting/Cupboard", BoolToChar(cupboard));
    mqtt.publish("myhome/lighting/All_OFF",  BoolToChar(All_OFF));
    mqtt.publish("myhome/lighting/Lock", BoolToChar(lock));

    mqtt.publish("myhome/lighting/Switch_RGB", "99R0G0B0");
    mqtt.publish("myhome/lighting/RGB_1", "R0G0B0");
    mqtt.publish("myhome/lighting/RGB_2", "R0G0B0");
    mqtt.publish("myhome/lighting/RGB_3", "R0G0B0");
    mqtt.publish("myhome/lighting/PWM_1", "0");
    mqtt.publish("myhome/lighting/PWM_2", "0");
    mqtt.publish("myhome/lighting/PWM_3", "0");
    mqtt.publish("myhome/lighting/PWM_4", "0");
    mqtt.publish("myhome/lighting/PWM_5", "0");
    mqtt.publish("myhome/lighting/PWM_6", "0");
    mqtt.publish("myhome/lighting/PWM_7", "0");
    mqtt.publish("myhome/lighting/PWM_8", "0");
    mqtt.publish("myhome/lighting/PWM_9", "0");
    mqtt.publish("myhome/lighting/Reset", "false");
  }
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
}

void httpSetup() {
  int idcheck = EEPROM.read(0);
  if (idcheck == ID) {
    for (int i = 0; i < 6; i++) {
      mac[i] = EEPROM.read(i + 1);
    }
  }
  Ethernet.begin(mac);
}

void checkHttp() {
  EthernetClient http = http_server.available();
  if (http) {
    TextFinder  finder(http );
    while (http.connected()) {
      if (http.available()) {
        if ( finder.find("GET /") ) {
          if (finder.findUntil("setup", "\n\r")) {
            if (finder.findUntil("SBM", "\n\r")) {
              byte SET = finder.getValue();
              while (finder.findUntil("DT", "\n\r")) {
                int val = finder.getValue();
                if (val >= 1 && val <= 6) {
                  mac[val - 1] = finder.getValue();
                }
                if (val >= 7 && val <= 10) {
                  mqtt_serv[val - 7] = finder.getValue();
                }
              }
              for (int i = 0 ; i < 6; i++) {
                EEPROM.write(i + 1, mac[i]);
              }
              for (int i = 0 ; i < 4; i++) {
                EEPROM.write(i + 7, mqtt_serv[i]);
              }
              EEPROM.write(0, ID);
              http.println("HTTP/1.1 200 OK");
              http.println("Content-Type: text/html");
              http.println();
              for (int i = 0; i < 4; i++) {
                strcpy_P(buffer, (char*)pgm_read_word(&(string_table0[i])));
                http.print( buffer );
              }
              http.println();
              http.print("Saved!");
              http.println();
              http.print("Restart");
              for (int i = 1; i < 10; i++) {
                http.print(".");
                delay(500);
              }
              http.println("OK");
              Reset(); // ребутим с новыми параметрами
            }
            http.println("HTTP/1.1 200 OK");
            http.println("Content-Type: text/html");
            http.println();
            for (int i = 0; i < 4; i++) {
              strcpy_P(buffer, (char*)pgm_read_word(&(string_table0[i])));
              http.print( buffer );
            }
            for (int i = 0; i < 3; i++) {
              strcpy_P(buffer, (char*)pgm_read_word(&(string_table1[i])));
              http.print( buffer );
            }
            http.print(mac[0], HEX);
            strcpy_P(buffer, (char*)pgm_read_word(&(string_table1[3])));
            http.print( buffer );
            http.print(mac[1], HEX);
            strcpy_P(buffer, (char*)pgm_read_word(&(string_table1[4])));
            http.print( buffer );
            http.print(mac[2], HEX);
            strcpy_P(buffer, (char*)pgm_read_word(&(string_table1[5])));
            http.print( buffer );
            http.print(mac[3], HEX);
            strcpy_P(buffer, (char*)pgm_read_word(&(string_table1[6])));
            http.print( buffer );
            http.print(mac[4], HEX);
            strcpy_P(buffer, (char*)pgm_read_word(&(string_table1[7])));
            http.print( buffer );
            http.print(mac[5], HEX);
            for (int i = 0; i < 4; i++) {
              strcpy_P(buffer, (char*)pgm_read_word(&(string_table2[i])));
              http.print( buffer );
            }
            http.print(mqtt_serv[0], DEC);
            strcpy_P(buffer, (char*)pgm_read_word(&(string_table2[4])));
            http.print( buffer );
            http.print(mqtt_serv[1], DEC);
            strcpy_P(buffer, (char*)pgm_read_word(&(string_table2[5])));
            http.print( buffer );
            http.print(mqtt_serv[2], DEC);
            strcpy_P(buffer, (char*)pgm_read_word(&(string_table2[6])));
            http.print( buffer );
            http.print(mqtt_serv[3], DEC);
            strcpy_P(buffer, (char*)pgm_read_word(&(string_table3[0])));
            http.print( buffer );
            for (int i = 0; i < 7; i++) {
              strcpy_P(buffer, (char*)pgm_read_word(&(string_table4[i])));
              http.print( buffer );
            }
            strcpy_P(buffer, (char*)pgm_read_word(&(string_table3[1])));
            http.print( buffer );
            break;
          }
        }
        http.println("HTTP/1.1 200 OK");
        http.println("Content-Type: text/html");
        http.println();
        http.print("IOT controller [");
        http.print(ID_CONNECT);
        http.print("]: go to <a href=\"/setup\"> setup</a>");
        break;
      }
    }
    delay(1);
    http.stop();
  } else {
    return;
  }
}

void Reset() {
  for (;;) {}
}
