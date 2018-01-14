void MotorInit() {
  for (int i = 0; i < 5; i++) {
    pinMode(motor_dir_array[i], OUTPUT);
    pinMode(motor_pwm_array[i], OUTPUT);
    digitalWrite(motor_dir_array[i], LOW);
    analogWrite(motor_pwm_array[i], 0);
  }
}

volatile int cnt = 0;
void MotorTest() {
  if (cnt < 5) {
    digitalWrite(M1_DIR, HIGH);
    digitalWrite(M2_DIR, HIGH);
    digitalWrite(M3_DIR, HIGH);
    digitalWrite(M4_DIR, HIGH);
    digitalWrite(M5_DIR, HIGH);
  }
  else {
    digitalWrite(M1_DIR, LOW);
    digitalWrite(M2_DIR, LOW);
    digitalWrite(M3_DIR, LOW);
    digitalWrite(M4_DIR, LOW);
    digitalWrite(M5_DIR, LOW);
    Serial.println("LOW");
    cnt = 0;
  }
  digitalWrite(M1_PWM, HIGH);
  analogWrite(M2_PWM, 1023);
  analogWrite(M3_PWM, 1023);
  analogWrite(M4_PWM, 1023);
  analogWrite(M5_PWM, 1023);
  delay(2000);
  digitalWrite(M1_PWM, LOW);
  analogWrite(M2_PWM, 0);
  analogWrite(M3_PWM, 0);
  analogWrite(M4_PWM, 0);
  analogWrite(M5_PWM, 0);
  delay(1000);
  cnt++;
}



