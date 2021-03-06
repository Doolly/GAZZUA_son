void MotorInit() {
  for (int i = 0; i < 5; i++) {
    pinMode(motor_en_array[i], OUTPUT);
    pinMode(motor_dir_array[i], OUTPUT);
    digitalWrite(motor_en_array[i], HIGH);
    digitalWrite(motor_dir_array[i], LOW);
    delay(1000);
  }
}



int last_pos[5] = {0,0,0,0,0};
void MotorCtrl (int moter_num, int range, int pos_in) {
  pos_in = constrain(pos_in, 0, range);

  int pos_to_move = pos_in - last_pos[moter_num];

  if (pos_to_move > 0) {
    digitalWrite(motor_en_array[moter_num], HIGH);
    digitalWrite(motor_dir_array[moter_num], EXTEND);
    MillisDelay(abs(pos_to_move));
    digitalWrite(motor_en_array[moter_num], LOW);
  }
  else if (pos_to_move < 0) {
    digitalWrite(motor_en_array[moter_num], HIGH);
    digitalWrite(motor_dir_array[moter_num], CONTRACT);
   MillisDelay(abs(pos_to_move));
    digitalWrite(motor_en_array[moter_num], LOW);
  }
  else {
    digitalWrite(motor_en_array[moter_num], LOW);
  }

  last_pos[moter_num] = last_pos[moter_num] + pos_to_move;
}

void Grasp() {
  MotorCtrl(0, 500, pressure_val);
}
