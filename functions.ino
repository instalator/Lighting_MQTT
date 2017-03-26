void callback_iobroker(String strTopic, String strPayload) {
  
  if (strTopic == "myhome/Lighting2/BedRoom_Main") {
      digitalWrite(out[0], SrtToLvl(strPayload));
      //delay(pause);
      client.publish("myhome/Lighting2/BedRoom_Main", pub(strPayload));
  }
  //////////////////////////
  else if (strTopic == "myhome/Lighting2/PWM1") {
      int pwm = PWM(strPayload);
      analogWrite(PWM_1, pwm);
      client.publish("myhome/Lighting2/PWM1", IntToChar(255 - pwm));
  }
  //////////////////////////
  else if (strTopic == "myhome/Lighting2/RGB") {
      Serial.println(strPayload);
      client.publish("myhome/Lighting2/RGB", ToChar(strPayload));
  }
  /* else if (strTopic == "myhome/Lighting2/Lock") {
      if (strPayload == "1") {
          Lock = true;
      } else {
         posetitel = 1;
         Lock = false;
        }
      delay(pause);
      client.publish("myhome/Lighting/Lock", ToChar(strPayload));
    }*/
}

void RGB_Switch(int i, int color){
  Serial.print(i);
  Serial.println(color);
}

void Switch(int i){
   if (i == 0) { // Спальня 1
      InvertOut(out[i]);
      client.publish("myhome/Lighting2/BedRoom_Main", IntToBool(state_out));
   }
}

bool InvertOut(int pin){
    //delay(10);
    digitalWrite(pin, !digitalRead(pin)); //инвертируем состояние пина
    state_out = digitalRead(pin);
    return state_out;
}

int PWM(String p){
  int pwm = p.toInt();
    if (pwm > 255){
      pwm = 255;
    } else if (pwm < 0){
      pwm = 0;
    }
    return (255 - pwm);
}

void ReadButton (){
  for(int i = 0; i <= 15; i++){
    btn[i] = mcp.digitalRead(bt[i]);
    if (btn[i] != btn_old[i]){
      btn_old[i] = btn[i];
      Switch(i);
      //client.publish(topic[i],  IntToChar(btn[i]));
    }
  }
}

char* pub(String st){
    if (st == "false" || st == "0" || st == "off"){
      return "false";
    } else{
      return "true";
    }
}
bool SrtToLvl(String st){
    if (st == "false" || st == "0" || st == "off"){
      return HIGH;
    } else{
      return LOW;
    }
}

char* ToChar (String intstr){
    char b[2];
    intstr.toCharArray(b, 2);
    return b;
  }
char* IntToChar (int intV) {
  char b[5];
  String stringVar = String(intV, DEC);
  stringVar.toCharArray(b, 4);
  return b;
}
char* IntToBool (int r) {
    if (r > 0){
      return "false";
    } else{
      return "true";
    }
}
  /*
String InvertOut(int pin){
    delay(pause);
    digitalWrite(pin, !digitalRead(pin)); //инвертируем состояние пина
    out = String(digitalRead(pin), DEC);
    return out;
}
*/
