void pinconfig() {
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
}

