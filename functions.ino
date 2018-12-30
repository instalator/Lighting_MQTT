void IRsens() {
  int left = analogRead(IR_1);
  int right = analogRead(IR_2);
  if (millis() - prevMillis4 > 5000) {
    prevMillis4 = millis();
    if (mqtt_connect) {
      mqtt.publish("myhome/lighting/left_IR", IntToChar(left));
      mqtt.publish("myhome/lighting/right_IR", IntToChar(right));
    }
  }
  if ((left < 320 || right < 300) && left > 10 && right > 10 && !flag_cupboard && !cupboard) {
    flag_cupboard = true;
  } else if ((left > 380 && right > 350) || (left < 10 && right < 10)) {
    analogWrite(PWM_1, 255);
    if (cupboard) {
      if (mqtt_connect) {
        mqtt.publish("myhome/lighting/Cupboard", "false");
      }
    }
    i_cup = 255;
    flag_cupboard = false;
    cupboard = false;
  }
}

void Smooth_light() {
  if (millis() - prevMillis3 >= 20 && flag_cupboard && !cupboard) {
    prevMillis3 = millis();
    if (!cupboard) {
      analogWrite(PWM_1, i_cup);
      i_cup--;
      if (i_cup < 1) {
        if (mqtt_connect) {
          mqtt.publish("myhome/lighting/Cupboard", "true");
        }
        i_cup = 255;
        flag_cupboard = false;
        cupboard = true;
      }
    }
  }
}


void Switch(int i) { 
  switch (i) {
    case 0:
      InvertOut(i);
      if (mqtt_connect) {
        mqtt.publish(OUT_0, state(i));
      }
      break;
    case 1:
      InvertOut(i);
      if (mqtt_connect) {
        mqtt.publish(OUT_1, state(i));
      }
      break;
    case 2:
      InvertOut(i);
      if (mqtt_connect) {
        mqtt.publish(OUT_2, state(i));
      }
      break;
    case 3:
      InvertOut(i);
      if (mqtt_connect) {
        mqtt.publish(OUT_3, state(i));
      }
      break;
    case 4:
      InvertOut(i);
      if (mqtt_connect) {
        mqtt.publish(OUT_4, state(i));
      }
      break;
    case 5:
      InvertOut(i);
      if (mqtt_connect) {
        mqtt.publish(OUT_5, state(i));
      }
      break;
    case 6:
      InvertOut(i);
      if (mqtt_connect) {
        mqtt.publish(OUT_6, state(i));
      }
      break;
    case 7:
      InvertOut(i);
      if (mqtt_connect) {
        mqtt.publish(OUT_7, state(i));
      }
      posetitel = digitalRead(out[i]);
      bathswitch = posetitel;
      break;
    case 8:
      InvertOut(i);
      if (mqtt_connect) {
        mqtt.publish(OUT_8, state(i));
      }
      break;
    case 9:
      InvertOut(i);
      if (mqtt_connect) {
        mqtt.publish(OUT_9, state(i));
      }
      break;
    case 10:
      InvertOut(2);
      if (mqtt_connect) {
        mqtt.publish(OUT_2, state(2));
      }
      break;
    case 11:
      InvertOut(3);
      if (mqtt_connect) {
        mqtt.publish(OUT_3, state(3));
      }
      break;
    case 12:
      InvertOut(4);
      if (mqtt_connect) {
        mqtt.publish(OUT_4, state(4));
      }
      break;
    case 13:
      InvertOut(i);
      if (mqtt_connect) {
        mqtt.publish(OUT_13, state(i));
      }
      break;
    case 14:
      InvertOut(i);
      if (mqtt_connect) {
        mqtt.publish(OUT_14, state(i));
      }
      break;
    case 15:
      InvertOut(i);
      if (mqtt_connect) {
        mqtt.publish(OUT_15, state(i));
      }
      break;
    case 16:
      InvertOut(i);
      if (mqtt_connect) {
        mqtt.publish(OUT_16, state(i));
      }
      break;
    case 17:
      InvertOut(i);
      if (mqtt_connect) {
        mqtt.publish(OUT_17, state(i));
      }
      break;
    case 18:
      InvertOut(i);
      if (mqtt_connect) {
        mqtt.publish(OUT_18, state(i));
      }
      break;
    case 19:
      InvertOut(i);
      if (mqtt_connect) {
        mqtt.publish(OUT_19, state(i));
      }
      break;
    case 20:
      InvertOut(i);
      if (mqtt_connect) {
        mqtt.publish(OUT_20, state(i));
      }
      break;
      //default:
  }
}

void ReadButton () {
  if (firststart) {
    for (int i = 0; i <= 15; i++) {
      btn_old[i] = mcp.digitalRead(bt[i]);
    }
    firststart = false;
  }
  for (int i = 0; i <= 15; i++) {
    btn[i] = mcp.digitalRead(bt[i]);
    if (btn[i] != btn_old[i]) {
      btn_old[i] = btn[i];
      Switch(i);
    }
  }
}

void Bath() {
  //////////// Ванная //////////
  if (digitalRead(IN_UP7) == 1 && (millis() - prevMillis2 > 3000)) { //Если кто то зашел в ванную то
    prevMillis2 = millis();
    if (bathswitch) {
      posetitel = false;
      bathswitch = false;
    }
    posetitel++;
    if (mqtt_connect) {
      mqtt.publish("myhome/lighting/BathRoom_posetitel", IntToChar(posetitel));
    }
    if (posetitel > 0) {
      digitalWrite(out[7], HIGH);//Включаем свет
      if (posetitel > 5) {
        posetitel = 5;
      }
      if (mqtt_connect) {
        mqtt.publish("myhome/lighting/BathRoom_main", "true");
      }
    }
  }
  if (digitalRead(IN_UP8) == 1 && (millis() - prevMillis2 > 3000) && !lock) { //Если кто то вышел из ванной то
    prevMillis2 = millis();
    posetitel--;
    if (mqtt_connect) {
      mqtt.publish("myhome/lighting/BathRoom_posetitel", IntToChar(posetitel));
    }
    if (posetitel < 1) {
      posetitel = 0;
      digitalWrite(out[7], LOW);//Выключаем свет
      if (mqtt_connect) {
        mqtt.publish("myhome/lighting/BathRoom_main", "false");
      }
    }
  }
}

const char* state(int num) {
  if (digitalRead(out[num]) > 0) {
    return "true";
  } else {
    return "false";
  }
}


bool SrtToLvl(String st) {
  if (st == "false" || st == "0" || st == "off") {
    return 0;
  } else {
    return 1;
  }
}
const char* pub(String st) {
  if (st == "false" || st == "0" || st == "off") {
    return "false";
  } else {
    return "true";
  }
}

bool InvertOut(int n) {
  digitalWrite(out[n], !digitalRead(out[n])); //инвертируем состояние пина
}

byte PWM(String p) {
  byte pwm = p.toInt();
  if (pwm > 254) {
    pwm = 255;
  } else if (pwm < 1) {
    pwm = 0;
  }
  pwm = 255 - pwm;
  return pwm;
}

const char* BoolToChar (bool r) {
  return r ? "true" : "false";
}

const char* IntToChar (unsigned int v) {
  buf[0] = '\0';
  sprintf(buf, "%d", v);
  return buf;
}

void Reset() {
  for (;;) {}
}
