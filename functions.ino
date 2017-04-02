void callback_iobroker(String strTopic, String strPayload) {
  
  if (strTopic == "myhome/lighting2/BathRoom_main") { //Ванная основной
      digitalWrite(out[15], SrtToLvl(strPayload));
      //delay(pause);
      client.publish("myhome/lighting2/BathRoom_main", pub(strPayload));
  }
//////////////////////////
  else if (strTopic == "myhome/lighting2/BedRoom_main") { //Спальня основной
      digitalWrite(out[1], SrtToLvl(strPayload));
      //delay(pause);
      client.publish("myhome/lighting2/BedRoom_main", pub(strPayload));
  }
//////////////////////////
  else if (strTopic == "myhome/lighting2/BedRoom_sec") { //Спальня доп
      digitalWrite(out[2], SrtToLvl(strPayload));
      //delay(pause);
      client.publish("myhome/lighting2/BedRoom_sec", pub(strPayload));
  }
//////////////////////////
  else if (strTopic == "myhome/lighting2/Kitchen_main") {
      digitalWrite(out[3], SrtToLvl(strPayload));
      //delay(pause);
      client.publish("myhome/lighting2/Kitchen_main", pub(strPayload));
  }
//////////////////////////
  else if (strTopic == "myhome/lighting2/Kitchen_sec") {
      digitalWrite(out[4], SrtToLvl(strPayload));
      //delay(pause);
      client.publish("myhome/lighting2/Kitchen_sec", pub(strPayload));
  }
//////////////////////////
  else if (strTopic == "myhome/lighting2/Hall_main") {
      digitalWrite(out[5], SrtToLvl(strPayload));
      //delay(pause);
      client.publish("myhome/lighting2/Hall_main", pub(strPayload));
  }
//////////////////////////
  else if (strTopic == "myhome/lighting2/GuestRoom_main") {
      digitalWrite(out[6], SrtToLvl(strPayload));
      //delay(pause);
      client.publish("myhome/lighting2/GuestRoom_main", pub(strPayload));
  }
//////////////////////////
  else if (strTopic == "myhome/lighting2/GuestRoom_main2") {
      digitalWrite(out[7], SrtToLvl(strPayload));
      //delay(pause);
      client.publish("myhome/lighting2/GuestRoom_main2", pub(strPayload));
  }
//////////////////////////
  else if (strTopic == "myhome/lighting2/GuestRoom_sec") {
      digitalWrite(out[8], SrtToLvl(strPayload));
      //delay(pause);
      client.publish("myhome/lighting2/GuestRoom_sec", pub(strPayload));
  }
//////////////////////////
  else if (strTopic == "myhome/lighting2/Cupboard") {
    if (pub(strPayload) == "false") {
      analogWrite(PWM_1, 255);
      client.publish("myhome/lighting2/Cupboard", "false");
      flag_cupboard = false;
      cupboard = true;
      i_cup = 255;
      //cupboard_off();
    } else if (pub(strPayload) == "true") {
      cupboard = false;
      flag_cupboard = true;
      client.publish("myhome/lighting2/Cupboard", pub(strPayload));
    }
  }
/////////////////////
  else if (strTopic == "myhome/Bathroom/Ventilator") {
      digitalWrite(out[21], SrtToLvl(strPayload));
      //delay(pause);
      client.publish("myhome/Bathroom/Ventilator", pub(strPayload));
   }
///////////////////
  else if (strTopic == "myhome/lighting2/All_OFF") {
    if (strPayload == "true") {
      for (int i = 0 ; i <= 21; i++) {
        if (out[i] != 21){ //myhome/Bathroom/Ventilator
           digitalWrite (out[i], LOW);
        }
      }
      //PubTopic();
      client.publish("myhome/lighting2/All_OFF", "true");
      posetitel = 0;
      bathswitch = 0;
    }
  }
//////////////////////
   else if (strTopic == "myhome/lighting2/Lock") {
      if (pub(strPayload) == "true") {
         lock = true;
      } else {
         posetitel = 1;
         lock = false;
        }
      //delay(pause);
      client.publish("myhome/lighting2/Lock", pub(strPayload));
    }
//////////////////////////
  else if (strTopic == "myhome/lighting2/PWM_1") {
      int pwm = PWM(strPayload);
      analogWrite(PWM_1, pwm);
      client.publish("myhome/lighting2/PWM_1", IntToChar(255 - pwm));
  }
//////////////////////////
  else if (strTopic == "myhome/lighting2/PWM_2") {
      int pwm = PWM(strPayload);
      analogWrite(PWM_2, pwm);
      client.publish("myhome/lighting2/PWM_2", IntToChar(255 - pwm));
  }
//////////////////////////
  else if (strTopic == "myhome/lighting2/PWM_3") {
      int pwm = PWM(strPayload);
      analogWrite(PWM_3, pwm);
      client.publish("myhome/lighting2/PWM_3", IntToChar(255 - pwm));
  }
//////////////////////////
  else if (strTopic == "myhome/lighting2/PWM_4") {
      int pwm = PWM(strPayload);
      analogWrite(PWM_4, pwm);
      client.publish("myhome/lighting2/PWM_4", IntToChar(255 - pwm));
  }
//////////////////////////
  else if (strTopic == "myhome/lighting2/PWM_5") {
      int pwm = PWM(strPayload);
      analogWrite(PWM_5, pwm);
      client.publish("myhome/lighting2/PWM_5", IntToChar(255 - pwm));
  }
//////////////////////////
  else if (strTopic == "myhome/lighting2/PWM_6") {
      int pwm = PWM(strPayload);
      analogWrite(PWM_6, pwm);
      client.publish("myhome/lighting2/PWM_6", IntToChar(255 - pwm));
  }
//////////////////////////
  else if (strTopic == "myhome/lighting2/PWM_7") {
      int pwm = PWM(strPayload);
      analogWrite(PWM_7, pwm);
      client.publish("myhome/lighting2/PWM_7", IntToChar(255 - pwm));
  }
//////////////////////////
  else if (strTopic == "myhome/lighting2/PWM_8") {
      int pwm = PWM(strPayload);
      analogWrite(PWM_8, pwm);
      client.publish("myhome/lighting2/PWM_8", IntToChar(255 - pwm));
  }
//////////////////////////
  else if (strTopic == "myhome/lighting2/PWM_9") {
      int pwm = PWM(strPayload);
      analogWrite(PWM_9, pwm);
      client.publish("myhome/lighting2/PWM_9", IntToChar(255 - pwm));
  }
//////////////////////////
  else if (strTopic == "myhome/lighting2/RGB_1") {
      int R = strPayload.substring(1,strPayload.indexOf('G')).toInt();
      int G = strPayload.substring(strPayload.indexOf('G')+1, strPayload.lastIndexOf('B')).toInt();
      int B = strPayload.substring(strPayload.lastIndexOf('B')+1).toInt();
      analogWrite(PWM_1, 255 - R);
      analogWrite(PWM_2, 255 - G);
      analogWrite(PWM_3, 255 - B);
      client.publish("myhome/lighting2/PWM_1", IntToChar(R));
      client.publish("myhome/lighting2/PWM_2", IntToChar(G));
      client.publish("myhome/lighting2/PWM_3", IntToChar(B));
      client.publish("myhome/lighting2/RGB_1", RGBToChar(strPayload));
  }
//////////////////////////
  else if (strTopic == "myhome/lighting2/RGB_2") {
      int R = strPayload.substring(1,strPayload.indexOf('G')).toInt();
      int G = strPayload.substring(strPayload.indexOf('G')+1, strPayload.lastIndexOf('B')).toInt();
      int B = strPayload.substring(strPayload.lastIndexOf('B')+1).toInt();
      analogWrite(PWM_4, 255 - R);
      analogWrite(PWM_5, 255 - G);
      analogWrite(PWM_6, 255 - B);
      client.publish("myhome/lighting2/PWM_4", IntToChar(R));
      client.publish("myhome/lighting2/PWM_5", IntToChar(G));
      client.publish("myhome/lighting2/PWM_6", IntToChar(B));
      client.publish("myhome/lighting2/RGB_2", RGBToChar(strPayload));
  }
//////////////////////////
  else if (strTopic == "myhome/lighting2/RGB_3") {
      int R = strPayload.substring(1,strPayload.indexOf('G')).toInt();
      int G = strPayload.substring(strPayload.indexOf('G')+1, strPayload.lastIndexOf('B')).toInt();
      int B = strPayload.substring(strPayload.lastIndexOf('B')+1).toInt();
      analogWrite(PWM_7, 255 - R);
      analogWrite(PWM_8, 255 - G);
      analogWrite(PWM_9, 255 - B);
      client.publish("myhome/lighting2/PWM_7", IntToChar(R));
      client.publish("myhome/lighting2/PWM_8", IntToChar(G));
      client.publish("myhome/lighting2/PWM_9", IntToChar(B));
      client.publish("myhome/lighting2/RGB_3", RGBToChar(strPayload));
  }
//////////////////////////
  else if (strTopic == "myhome/lighting2/Switch_RGB") {
      Serial2.print(strPayload);
      Serial2.print('\r');
  }
}

void IRsens(){
  left = analogRead(IR_1);
  right = analogRead(IR_2);
  if ((left < 10 || right < 10) && flag_cupboard == false && cupboard == false){
    flag_cupboard = true;
  } else if (left > 100 && right > 100){
    analogWrite(PWM_1, 255);
    client.publish("myhome/lighting2/Cupboard", "false");
    i_cup = 255;
    flag_cupboard = false;
    cupboard = false;
  }
}

void Smooth_light(){
    if (millis() - prevMillis3 >= 20 && flag_cupboard == true) {
      prevMillis3 = millis();
      if (cupboard == false){
         analogWrite(PWM_1, i_cup);
         i_cup--;
         if (i_cup < 1){
            client.publish("myhome/lighting2/Cupboard", "true");
            i_cup = 255;
            flag_cupboard = false;
            cupboard = true;
         }
      }
    }
}

void Switch(int i){
  switch (i){
    case 0:
        InvertOut(i);
        client.publish(OUT_0, state(i));
      break;
    case 1:
        InvertOut(i);
        client.publish(OUT_1, state(i));
      break;
    case 2:
        InvertOut(i);
        client.publish(OUT_2, state(i));
      break;
    case 3:
        InvertOut(i);
        client.publish(OUT_3, state(i));
      break;
    case 4:
        InvertOut(i);
        client.publish(OUT_4, state(i));
      break;
    case 5:
        InvertOut(i);
        client.publish(OUT_5, state(i));
      break;
    case 6:
        InvertOut(i);
        client.publish(OUT_6, state(i));
      break;
    case 7:
        InvertOut(i);
        client.publish(OUT_7, state(i));
      break;
    case 8:
        InvertOut(i);
        client.publish(OUT_8, state(i));
      break;
    case 9:
        InvertOut(i);
        client.publish(OUT_9, state(i));
      break;
    case 10:
        InvertOut(i);
        client.publish(OUT_10, state(i));
      break;
    case 11:
        InvertOut(i);
        client.publish(OUT_11, state(i));
      break;
    case 12:
        InvertOut(i);
        client.publish(OUT_12, state(i));
      break;
    case 13:
        InvertOut(i);
        client.publish(OUT_13, state(i));
      break;
    case 14:
        InvertOut(i);
        client.publish(OUT_14, state(i));
      break;
    case 15:
        InvertOut(i);
        client.publish(OUT_15, state(i));
        posetitel = digitalRead(out[i]);
        bathswitch = posetitel;
      break;
     case 16:
        InvertOut(i);
        client.publish(OUT_16, state(i));
      break;
     case 17:
        InvertOut(i);
        client.publish(OUT_17, state(i));
      break;
     case 18:
        InvertOut(i);
        client.publish(OUT_18, state(i));
      break;
     case 19:
        InvertOut(i);
        client.publish(OUT_19, state(i));
      break;
     case 20:
        InvertOut(i);
        client.publish(OUT_20, state(i));
      break;
    //default:
  }
}

void ReadButton (){
  for(int i = 0; i <= 15; i++){
    btn[i] = mcp.digitalRead(bt[i]);
    if (btn[i] != btn_old[i]){
      btn_old[i] = btn[i];
      Switch(i);
    }
  }
}

void Bath(){
  //////////// Ванная //////////
    if (digitalRead(IN_UP7) == 1 && (millis() - prevMillis2 > 3000)) { //Если кто то зашел в ванную то
      prevMillis2 = millis();
      if (bathswitch == 1) {
        posetitel = 0;
        bathswitch = 0;
      }
      posetitel++;
      if (posetitel > 0) {
        //delay(50);
        digitalWrite(out[15], 1);//Включаем свет
        if (posetitel > 5) {
          posetitel = 5;
        }
        //delay(5);
        client.publish("myhome/lighting2/BathRoom_main", "true");
      }
    }
    if (digitalRead(IN_UP8) == 1 && (millis() - prevMillis2 > 3000) && lock == false) { //Если кто то вышел из ванной то
      prevMillis2 = millis();
      posetitel--;
      if (posetitel <= 0) {
        posetitel = 0;
        //delay(50);
        digitalWrite(out[15], 0);//Выключаем свет
        //delay(5);
        client.publish("myhome/lighting2/BathRoom_main", "false");
      }
    }
}

bool InvertOut(int n){
    digitalWrite(out[n], !digitalRead(out[n])); //инвертируем состояние пина
}

int PWM(String p){
  int pwm = p.toInt();
    if (pwm > 254){
      pwm = 255;
    } else if (pwm < 1){
      pwm = 0;
    }
    pwm = 255 - pwm;
    return pwm;
}

char* pub(String st){
    if (st == "false" || st == "0" || st == "off"){
      return "false";
    } else{
      return "true";
    }
}

char* BoolToChar (bool r) {
    if (r == true){
      return "true";
    } else{
      return "false";
    }
}
bool SrtToLvl(String st){
    if (st == "false" || st == "0" || st == "off"){
      return LOW;
    } else{
      return HIGH;
    }
}

char* RGBToChar (String str){
    int len = str.length()+1;
    char a[len+25];
    str.toCharArray(a, len+1);
    return a;
}
 
char* IntToCh (int intV) {
  String str = String(intV, DEC);
  int len = str.length() + 1;
  char b[len+2];
  str.toCharArray(b, len);
  return b;
}

char* IntToChar (int intV) {
  String stringVar = String(intV, DEC);
  int len = stringVar.length() + 1;
  char b[len+1];
  stringVar.toCharArray(b, len);
  return b;
}


  



