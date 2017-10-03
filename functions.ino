
bool SrtToLvl(String st){
    if (st == "false" || st == "0" || st == "off"){
      return 0;
    } else {
      return 1;
    }
}
const char* pub(String st){
    if (st == "false" || st == "0" || st == "off"){
      return "false";
    } else{
      return "true";
    }
}


void callback_iobroker(String strTopic, String strPayload) {
  if (strTopic == "myhome/lighting/Switch_RGB") {
      Serial2.print(strPayload);
      Serial2.print('\r');
  }
//////////////////////////
  else if (strTopic == OUT_0) { //Спальня основной
      digitalWrite(out[0], SrtToLvl(strPayload));
      //delay(1000);
      client.publish(OUT_0, pub(strPayload));
  }
//////////////////////////
  else if (strTopic == OUT_1) { //Спальня доп
      digitalWrite(out[1], SrtToLvl(strPayload));
      //delay(pause);
      client.publish(OUT_1, pub(strPayload));
  }
//////////////////////////
  else if (strTopic == OUT_2) { //Зал основной
      digitalWrite(out[2], SrtToLvl(strPayload));
      //delay(pause);
      client.publish(OUT_2, pub(strPayload));
  }
//////////////////////////
  else if (strTopic == OUT_3) {//Зал основной 2
      digitalWrite(out[3], SrtToLvl(strPayload));
      //delay(pause);
      client.publish(OUT_3, pub(strPayload));
  }
//////////////////////////
  else if (strTopic == OUT_4) { //Зал доп
      digitalWrite(out[4], SrtToLvl(strPayload));
      //delay(pause);
      client.publish(OUT_4, pub(strPayload));
  }
//////////////////////////
  else if (strTopic == OUT_5) { //Кухня основной
      digitalWrite(out[5], SrtToLvl(strPayload));
      //delay(pause);
      client.publish(OUT_5, pub(strPayload));
  }
//////////////////////////
  else if (strTopic == OUT_6) { //Кухня доп
      digitalWrite(out[6], SrtToLvl(strPayload));
      //delay(pause);
      client.publish(OUT_6, pub(strPayload));
  }
//////////////////////////
  else if (strTopic == OUT_7) { //Ванна основной
      digitalWrite(out[7], SrtToLvl(strPayload));
      //delay(pause);
      client.publish(OUT_7, pub(strPayload));
  }
//////////////////////////
  else if (strTopic == OUT_8) { //Ванна доп
      digitalWrite(out[8], SrtToLvl(strPayload));
      //delay(pause);
      client.publish(OUT_8, pub(strPayload));
  }
//////////////////////////
  else if (strTopic == OUT_9) { //Коридор
      digitalWrite(out[9], SrtToLvl(strPayload));
      //delay(pause);
      client.publish(OUT_9, pub(strPayload));
  }
//////////////////////////
  else if (strTopic == "myhome/lighting/Cupboard") {
    if (pub(strPayload) == "false") {
      analogWrite(PWM_1, 255);
      client.publish("myhome/lighting/Cupboard", "false");
      flag_cupboard = false;
      cupboard = true;
      i_cup = 255;
      //cupboard_off();
    } else if (pub(strPayload) == "true") {
      cupboard = false;
      flag_cupboard = true;
      client.publish("myhome/lighting/Cupboard", pub(strPayload));
    }
  }
/////////////////////
  else if (strTopic == OUT_20) {
      digitalWrite(out[20], SrtToLvl(strPayload));
      //delay(pause);
      client.publish(OUT_20, pub(strPayload));
   }
///////////////////
  else if (strTopic == "myhome/lighting/All_OFF") {
    if (strPayload == "true") {
      for (int i = 0 ; i <= 20; i++) {
        if (i != 20){ //myhome/Bathroom/Ventilator
           digitalWrite (out[i], LOW);
        }
      }
      //PubTopic();
      client.publish("myhome/lighting/All_OFF", "true");
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
      posetitel = 0;
      bathswitch = 0;
    }
  }
//////////////////////
   else if (strTopic == "myhome/lighting/Lock") {
      if (pub(strPayload) == "true") {
         lock = true;
      } else {
         posetitel = 1;
         lock = false;
        }
      //delay(pause);
      client.publish("myhome/lighting/Lock", pub(strPayload));
    }
//////////////////////////
  else if (strTopic == "myhome/lighting/PWM_1") {
      int pwm = PWM(strPayload);
      analogWrite(PWM_1, pwm);
      client.publish("myhome/lighting/PWM_1", IntToChar(255 - pwm));
  }
//////////////////////////
  else if (strTopic == "myhome/lighting/PWM_2") {
      int pwm = PWM(strPayload);
      analogWrite(PWM_2, pwm);
      client.publish("myhome/lighting/PWM_2", IntToChar(255 - pwm));
  }
//////////////////////////
  else if (strTopic == "myhome/lighting/PWM_3") {
      int pwm = PWM(strPayload);
      analogWrite(PWM_3, pwm);
      client.publish("myhome/lighting/PWM_3", IntToChar(255 - pwm));
  }
//////////////////////////
  else if (strTopic == "myhome/lighting/PWM_4") {
      int pwm = PWM(strPayload);
      analogWrite(PWM_4, pwm);
      client.publish("myhome/lighting/PWM_4", IntToChar(255 - pwm));
  }
//////////////////////////
  else if (strTopic == "myhome/lighting/PWM_5") {
      int pwm = PWM(strPayload);
      analogWrite(PWM_5, pwm);
      client.publish("myhome/lighting/PWM_5", IntToChar(255 - pwm));
  }
//////////////////////////
  else if (strTopic == "myhome/lighting/PWM_6") {
      int pwm = PWM(strPayload);
      analogWrite(PWM_6, pwm);
      client.publish("myhome/lighting/PWM_6", IntToChar(255 - pwm));
  }
//////////////////////////
  else if (strTopic == "myhome/lighting/PWM_7") {
      int pwm = PWM(strPayload);
      analogWrite(PWM_7, pwm);
      client.publish("myhome/lighting/PWM_7", IntToChar(255 - pwm));
  }
//////////////////////////
  else if (strTopic == "myhome/lighting/PWM_8") {
      int pwm = PWM(strPayload);
      analogWrite(PWM_8, pwm);
      client.publish("myhome/lighting/PWM_8", IntToChar(255 - pwm));
  }
//////////////////////////
  else if (strTopic == "myhome/lighting/PWM_9") {
      int pwm = PWM(strPayload);
      analogWrite(PWM_9, pwm);
      client.publish("myhome/lighting/PWM_9", IntToChar(255 - pwm));
  }
//////////////////////////
  else if (strTopic == "myhome/lighting/RGB_1") {
      int R = strPayload.substring(1,strPayload.indexOf('G')).toInt();
      int G = strPayload.substring(strPayload.indexOf('G')+1, strPayload.lastIndexOf('B')).toInt();
      int B = strPayload.substring(strPayload.lastIndexOf('B')+1).toInt();
      analogWrite(PWM_1, 255 - R);
      analogWrite(PWM_2, 255 - G);
      analogWrite(PWM_3, 255 - B);
      client.publish("myhome/lighting/PWM_1", IntToChar(R));
      client.publish("myhome/lighting/PWM_2", IntToChar(G));
      client.publish("myhome/lighting/PWM_3", IntToChar(B));
      int len = strPayload.length()+1;
      char a[len+25];
      strPayload.toCharArray(a, len+1);
      client.publish("myhome/lighting/RGB_1", a);
  }
//////////////////////////
  else if (strTopic == "myhome/lighting/RGB_2") {
      int R = strPayload.substring(1,strPayload.indexOf('G')).toInt();
      int G = strPayload.substring(strPayload.indexOf('G')+1, strPayload.lastIndexOf('B')).toInt();
      int B = strPayload.substring(strPayload.lastIndexOf('B')+1).toInt();
      analogWrite(PWM_4, 255 - R);
      analogWrite(PWM_5, 255 - G);
      analogWrite(PWM_6, 255 - B);
      client.publish("myhome/lighting/PWM_4", IntToChar(R));
      client.publish("myhome/lighting/PWM_5", IntToChar(G));
      client.publish("myhome/lighting/PWM_6", IntToChar(B));
      int len = strPayload.length()+1;
      char a[len+25];
      strPayload.toCharArray(a, len+1);
      client.publish("myhome/lighting/RGB_2", a);
  }
//////////////////////////
  else if (strTopic == "myhome/lighting/RGB_3") {
      int R = strPayload.substring(1,strPayload.indexOf('G')).toInt();
      int G = strPayload.substring(strPayload.indexOf('G')+1, strPayload.lastIndexOf('B')).toInt();
      int B = strPayload.substring(strPayload.lastIndexOf('B')+1).toInt();
      analogWrite(PWM_7, 255 - R);
      analogWrite(PWM_8, 255 - G);
      analogWrite(PWM_9, 255 - B);
      client.publish("myhome/lighting/PWM_7", IntToChar(R));
      client.publish("myhome/lighting/PWM_8", IntToChar(G));
      client.publish("myhome/lighting/PWM_9", IntToChar(B));
      int len = strPayload.length()+1;
      char a[len+25];
      strPayload.toCharArray(a, len+1);
      client.publish("myhome/lighting/RGB_3", a);
  }
//////////////////////////
  else if (strTopic == "myhome/lighting/Reset") {
      if(strPayload == "true"){
        client.publish("myhome/lighting/Reset", "false");
        wdt_enable(WDTO_15MS);
        for(;;){}
      }
  }
}

void IRsens(){
  int left = analogRead(IR_1);
  int right = analogRead(IR_2);
  if (millis() - prevMillis4 > 5000){
    prevMillis4 = millis();
    client.publish("myhome/lighting/left_IR", IntToChar(left));
    client.publish("myhome/lighting/right_IR", IntToChar(right));
  }
  if ((left < 320 || right < 300) && left > 10 && right > 10 && flag_cupboard == false && cupboard == false){
    flag_cupboard = true;
  } else if ((left > 380 && right > 350) || (left < 10 && right < 10)){
    analogWrite(PWM_1, 255);
    if (cupboard == true){
      client.publish("myhome/lighting/Cupboard", "false");
    }
    i_cup = 255;
    flag_cupboard = false;
    cupboard = false;
  }
}

void Smooth_light(){
    if (millis() - prevMillis3 >= 20 && flag_cupboard == true && cupboard == false) {
      prevMillis3 = millis();
      if (cupboard == false){
         analogWrite(PWM_1, i_cup);
         i_cup--;
         if (i_cup < 1){
            client.publish("myhome/lighting/Cupboard", "true");
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
        InvertOut(2);
        client.publish(OUT_2, state(2));
      break;
    case 11:
        InvertOut(3);
        client.publish(OUT_3, state(3));
      break;
    case 12:
        InvertOut(4);
        client.publish(OUT_4, state(4));
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
  if (FirstStart){
    for(int i = 0; i <= 15; i++){
      btn_old[i] = mcp.digitalRead(bt[i]);
    }
    FirstStart = false;
  }
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
        digitalWrite(out[7], 1);//Включаем свет
        if (posetitel > 5) {
          posetitel = 5;
        }
        //delay(5);
        client.publish("myhome/lighting/BathRoom_main", "true");
      }
    }
    if (digitalRead(IN_UP8) == 1 && (millis() - prevMillis2 > 3000) && lock == false) { //Если кто то вышел из ванной то
      prevMillis2 = millis();
      posetitel--;
      if (posetitel <= 0) {
        posetitel = 0;
        //delay(50);
        digitalWrite(out[7], 0);//Выключаем свет
        //delay(5);
        client.publish("myhome/lighting/BathRoom_main", "false");
      }
    }
}

bool InvertOut(int n){
    digitalWrite(out[n], !digitalRead(out[n])); //инвертируем состояние пина
}

int PWM(String p){
    pwm = p.toInt();
    if (pwm > 254){
      pwm = 255;
    } else if (pwm < 1){
      pwm = 0;
    }
    pwm = 255 - pwm;
    return pwm;
}

const char* BoolToChar (bool r) {
    return r ? "true" : "false";
}

const char* IntToChar (unsigned int v) {
  sprintf(buf, "%d", v);
  return buf;
}
