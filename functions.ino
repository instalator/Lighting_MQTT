void callback_iobroker(String strTopic, String strPayload) {
  
  if (strTopic == "myhome/Lighting2/BedRoom_Main") {
      digitalWrite(out[0], SrtToLvl(strPayload));
      //delay(pause);
      client.publish("myhome/Lighting2/BedRoom_Main", pub(strPayload));
  }
  //////////////////////////
  else if (strTopic == "myhome/Lighting2/PWM1") {
      analogWrite(PWM_1, 256-strPayload.toInt());
      client.publish("myhome/Lighting2/PWM1", IntToChar(strPayload.toInt()));
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
void Switch(int i){
   if (i == 0) { // Спальня 1
      InvertOut(out[i]);
      client.publish("myhome/Lighting2/BedRoom_Main", IntToBool(state_out));
   }
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
bool InvertOut(int pin){
    //delay(10);
    digitalWrite(pin, !digitalRead(pin)); //инвертируем состояние пина
    state_out = digitalRead(pin);
    return state_out;
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
