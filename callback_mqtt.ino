void callback_mqtt(String top, String payload) {
  String cmd = top.substring(top.lastIndexOf("/") + 1);
  if (cmd.equals("Switch_RGB")) {
    Serial2.print(payload);
    Serial2.print('\r');
  }
  //////////////////////////
  else if (cmd.equals(OUT_0)) { //Спальня основной
    digitalWrite(out[0], SrtToLvl(payload));
    mqtt_publish(OUT_0, pub(payload));
  }
  //////////////////////////
  else if (cmd.equals(OUT_1)) { //Спальня доп
    digitalWrite(out[1], SrtToLvl(payload));
    mqtt_publish(OUT_1, pub(payload));
  }
  //////////////////////////
  else if (cmd.equals(OUT_2)) { //Зал основной
    digitalWrite(out[2], SrtToLvl(payload));
    mqtt_publish(OUT_2, pub(payload));
  }
  //////////////////////////
  else if (cmd.equals(OUT_3)) {//Зал основной 2
    digitalWrite(out[3], SrtToLvl(payload));
    mqtt_publish(OUT_3, pub(payload));
  }
  //////////////////////////
  else if (cmd.equals(OUT_4)) { //Зал доп
    digitalWrite(out[4], SrtToLvl(payload));
    mqtt_publish(OUT_4, pub(payload));
  }
  //////////////////////////
  else if (cmd.equals(OUT_5)) { //Кухня основной
    digitalWrite(out[5], SrtToLvl(payload));
    mqtt_publish(OUT_5, pub(payload));
  }
  //////////////////////////
  else if (cmd.equals(OUT_6)) { //Кухня доп
    digitalWrite(out[6], SrtToLvl(payload));
    mqtt_publish(OUT_6, pub(payload));
  }
  //////////////////////////
  else if (cmd.equals(OUT_7)) { //Ванна основной
    digitalWrite(out[7], SrtToLvl(payload));
    mqtt_publish(OUT_7, pub(payload));
  }
  //////////////////////////
  else if (cmd.equals(OUT_8)) { //Ванна доп
    digitalWrite(out[8], SrtToLvl(payload));
    mqtt_publish(OUT_8, pub(payload));
  }
  //////////////////////////
  else if (cmd.equals(OUT_9)) { //Коридор
    digitalWrite(out[9], SrtToLvl(payload));
    mqtt_publish(OUT_9, pub(payload));
  }
  //////////////////////////
  else if (cmd.equals("Cupboard")) {
    if (pub(payload) == "false") {
      analogWrite(PWM_1, 255);
      mqtt_publish("Cupboard", "false");
      flag_cupboard = false;
      cupboard = true;
      i_cup = 255;
      //cupboard_off();
    } else if (pub(payload) == "true") {
      cupboard = false;
      flag_cupboard = true;
      mqtt_publish("Cupboard", pub(payload));
    }
  }
  /////////////////////
  else if (top.equals(OUT_20)) {
    digitalWrite(out[20], SrtToLvl(payload));
    //mqtt_publish(OUT_20, pub(payload));
    mqtt.publish(OUT_20, pub(payload));
  }
  ///////////////////
  else if (cmd.equals("All_OFF")) {
    if (payload == "true") {
      for (int i = 0 ; i <= 20; i++) {
        if (i != 20) { //myhome/Bathroom/Ventilator
          digitalWrite (out[i], LOW);
        }
      }
      mqtt_publish("All_OFF", "true");
      mqtt_publish(OUT_0, state(0));
      mqtt_publish(OUT_1, state(1));
      mqtt_publish(OUT_2, state(2));
      mqtt_publish(OUT_3, state(3));
      mqtt_publish(OUT_4, state(4));
      mqtt_publish(OUT_5, state(5));
      mqtt_publish(OUT_6, state(6));
      mqtt_publish(OUT_7, state(7));
      mqtt_publish(OUT_8, state(8));
      mqtt_publish(OUT_9, state(9));
      mqtt_publish(OUT_10, state(10));
      mqtt_publish(OUT_11, state(11));
      mqtt_publish(OUT_12, state(12));
      mqtt_publish(OUT_13, state(13));
      mqtt_publish(OUT_14, state(14));
      mqtt_publish(OUT_15, state(15));
      mqtt_publish(OUT_16, state(16));
      mqtt_publish(OUT_17, state(17));
      mqtt_publish(OUT_18, state(18));
      mqtt_publish(OUT_19, state(19));
      //mqtt_publish(OUT_20, state(20));
      mqtt.publish(OUT_20, state(20));
      mqtt_publish("Cupboard", BoolToChar(cupboard));
      posetitel = 0;
      bathswitch = false;
    }
  }
  //////////////////////
  else if (cmd.equals("Lock")) {
    if (pub(payload) == "true") {
      lock = true;
    } else {
      posetitel = 1;
      lock = false;
    }
    mqtt_publish("Lock", pub(payload));
  }
  //////////////////////////
  else if (cmd.equals("PWM_1")) {
    byte pwm = PWM(payload);
    analogWrite(PWM_1, pwm);
    mqtt_publish("PWM_1", IntToChar(255 - pwm));
  }
  //////////////////////////
  else if (cmd.equals("PWM_2")) {
    byte pwm = PWM(payload);
    analogWrite(PWM_2, pwm);
    mqtt_publish("PWM_2", IntToChar(255 - pwm));
  }
  //////////////////////////
  else if (cmd.equals("PWM_3")) {
    byte pwm = PWM(payload);
    analogWrite(PWM_3, pwm);
    mqtt_publish("PWM_3", IntToChar(255 - pwm));
  }
  //////////////////////////
  else if (cmd.equals("PWM_4")) {
    byte pwm = PWM(payload);
    analogWrite(PWM_4, pwm);
    mqtt_publish("PWM_4", IntToChar(255 - pwm));
  }
  //////////////////////////
  else if (cmd.equals("PWM_5")) {
    byte pwm = PWM(payload);
    analogWrite(PWM_5, pwm);
    mqtt_publish("PWM_5", IntToChar(255 - pwm));
  }
  //////////////////////////
  else if (cmd.equals("PWM_6")) {
    byte pwm = PWM(payload);
    analogWrite(PWM_6, pwm);
    mqtt_publish("PWM_6", IntToChar(255 - pwm));
  }
  //////////////////////////
  else if (cmd.equals("PWM_7")) {
    byte pwm = PWM(payload);
    analogWrite(PWM_7, pwm);
    mqtt_publish("PWM_7", IntToChar(255 - pwm));
  }
  //////////////////////////
  else if (cmd.equals("PWM_8")) {
    byte pwm = PWM(payload);
    analogWrite(PWM_8, pwm);
    mqtt_publish("PWM_8", IntToChar(255 - pwm));
  }
  //////////////////////////
  else if (cmd.equals("PWM_9")) {
    byte pwm = PWM(payload);
    analogWrite(PWM_9, pwm);
    mqtt_publish("PWM_9", IntToChar(255 - pwm));
  }
  //////////////////////////
  else if (cmd.equals("BathRoom_posetitel")) {
    posetitel = payload.toInt();
    mqtt_publish("BathRoom_posetitel", IntToChar(posetitel));
  }
  //////////////////////////
  else if (cmd.equals("RGB_1")) {
    int R = payload.substring(1, payload.indexOf('G')).toInt();
    int G = payload.substring(payload.indexOf('G') + 1, payload.lastIndexOf('B')).toInt();
    int B = payload.substring(payload.lastIndexOf('B') + 1).toInt();
    analogWrite(PWM_1, 255 - R);
    analogWrite(PWM_2, 255 - G);
    analogWrite(PWM_3, 255 - B);
    mqtt_publish("PWM_1", IntToChar(R));
    mqtt_publish("PWM_2", IntToChar(G));
    mqtt_publish("PWM_3", IntToChar(B));
    int len = payload.length() + 1;
    char a[len + 25];
    payload.toCharArray(a, len + 1);
    mqtt_publish("RGB_1", a);
  }
  //////////////////////////
  else if (cmd.equals("RGB_2")) {
    int R = payload.substring(1, payload.indexOf('G')).toInt();
    int G = payload.substring(payload.indexOf('G') + 1, payload.lastIndexOf('B')).toInt();
    int B = payload.substring(payload.lastIndexOf('B') + 1).toInt();
    analogWrite(PWM_4, 255 - R);
    analogWrite(PWM_5, 255 - G);
    analogWrite(PWM_6, 255 - B);
    mqtt_publish("PWM_4", IntToChar(R));
    mqtt_publish("PWM_5", IntToChar(G));
    mqtt_publish("PWM_6", IntToChar(B));
    int len = payload.length() + 1;
    char a[len + 25];
    payload.toCharArray(a, len + 1);
    mqtt_publish("RGB_2", a);
  }
  //////////////////////////
  else if (cmd.equals("RGB_3")) {
    int R = payload.substring(1, payload.indexOf('G')).toInt();
    int G = payload.substring(payload.indexOf('G') + 1, payload.lastIndexOf('B')).toInt();
    int B = payload.substring(payload.lastIndexOf('B') + 1).toInt();
    analogWrite(PWM_7, 255 - R);
    analogWrite(PWM_8, 255 - G);
    analogWrite(PWM_9, 255 - B);
    mqtt_publish("PWM_7", IntToChar(R));
    mqtt_publish("PWM_8", IntToChar(G));
    mqtt_publish("PWM_9", IntToChar(B));
    int len = payload.length() + 1;
    char a[len + 25];
    payload.toCharArray(a, len + 1);
    mqtt_publish("RGB_3", a);
  }
  //////////////////////////
  else if (cmd.equals("Reset")) {
    if (payload == "true") {
      mqtt_publish("Reset", "false");
      //mqtt.publish(topic("Reset").c_str(), "false");
      wdt_enable(WDTO_15MS);
      for (;;) {}
    }
  }
}

void PubTopic () {
  if (mqtt_connect) {
    char s[16];
    sprintf(s, "%d.%d.%d.%d", Ethernet.localIP()[0], Ethernet.localIP()[1], Ethernet.localIP()[2], Ethernet.localIP()[3]);
    mqtt_publish("ip", s);
    //mqtt.publish(topic("ip").c_str(), s);
      mqtt_publish(OUT_0, state(0));
      mqtt_publish(OUT_1, state(1));
      mqtt_publish(OUT_2, state(2));
      mqtt_publish(OUT_3, state(3));
      mqtt_publish(OUT_4, state(4));
      mqtt_publish(OUT_5, state(5));
      mqtt_publish(OUT_6, state(6));
      mqtt_publish(OUT_7, state(7));
      mqtt_publish(OUT_8, state(8));
      mqtt_publish(OUT_9, state(9));
      mqtt_publish(OUT_10, state(10));
      mqtt_publish(OUT_11, state(11));
      mqtt_publish(OUT_12, state(12));
      mqtt_publish(OUT_13, state(13));
      mqtt_publish(OUT_14, state(14));
      mqtt_publish(OUT_15, state(15));
      mqtt_publish(OUT_16, state(16));
      mqtt_publish(OUT_17, state(17));
      mqtt_publish(OUT_18, state(18));
      mqtt_publish(OUT_19, state(19));
      //mqtt_publish(OUT_20, state(20)); //Вентилятор
      mqtt.publish(OUT_20, state(20));
    mqtt_publish("BathRoom_posetitel", IntToChar(posetitel));
    mqtt_publish("Cupboard", BoolToChar(cupboard));
    mqtt_publish("All_OFF", "false");
    mqtt_publish("Lock", BoolToChar(lock));

    mqtt_publish("Switch_RGB", "99R0G0B0");
    mqtt_publish("RGB_1", "R0G0B0");
    mqtt_publish("RGB_2", "R0G0B0");
    mqtt_publish("RGB_3", "R0G0B0");
    mqtt_publish("PWM_1", "0");
    mqtt_publish("PWM_2", "0");
    mqtt_publish("PWM_3", "0");
    mqtt_publish("PWM_4", "0");
    mqtt_publish("PWM_5", "0");
    mqtt_publish("PWM_6", "0");
    mqtt_publish("PWM_7", "0");
    mqtt_publish("PWM_8", "0");
    mqtt_publish("PWM_9", "0");
    mqtt_publish("Reset", "false");
  }
}
