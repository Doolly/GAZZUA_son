
int A_variable;
int B_variable;
int C_variable;
String command; //global variable
void Change_Value_in_Serial() { //new line   ex) A_variable 124
  if (Serial.available()) {
    char c = Serial.read();

    if (c == '\n') {
      String part1;
      String part2;

      part1 = command.substring(0, command.indexOf(" "));
      part2 = command.substring(command.indexOf(" ") + 1);

      if (part1.equalsIgnoreCase("mm"))
        mm = part2.toInt();

      else if (part1.equalsIgnoreCase("B_variable"))
        B_variable = part2.toInt();

      command = "";
    }

    else
      command += c;
  }
}

void SerialMonitor(int how) {
  if  (how == 0) { //for plot
    Serial.print(pressure_rate);
    Serial.print(" ");
    Serial.println(pressure_val_raw);
  }
  else if (how == 1) { //for value print
        Serial.print("pressure_val = " + String(pressure_val) + "\n");
        Serial.print("pressure_max = " + String(pressure_max) + "\n");
        Serial.print("middle_pos = " + String(middle_pos) + "\n");
//    Serial.print("mode = " + String(mode) + "\n");
//    Serial.print("temp_mode = " + String(temp_mode) + "\n");
//    Serial.print("last_mode = " + String(last_mode) + "\n");
//    Serial.print("last_mode_change_time = " + String(last_mode_change_time) + "\n");

    Serial.print("\n");
  }
}

void Calibration () {
  CenterDisplay("Calibration");
  delay(1500);
  pressure_max = pressure_val + 5;
  pressure_min = pressure_val;
  unsigned long now = millis();
  while ( millis() < now + 4000 ) {
    GetSensor();
    if ( pressure_val < pressure_min ) {
      pressure_min = pressure_val;
    }
    else if ( pressure_val > pressure_max ) {
      pressure_max = pressure_val;
    }
  }
  Serial.print("pressure_max = " + String(pressure_max) + "\n");
  Serial.print("pressure_min = " + String(pressure_min) + "\n");
  CenterDisplay("done");
  delay(1000);
}

void GetSensor() {
  int i;
  int sum = 0;
  for (i = 0; i < WINDOW_SIZE; i++) {
    pressure_val_raw = analogRead(PRESS_SEN);
    sensor_array[i] = pressure_val_raw;
    sum += sensor_array[i];
  }
  pressure_val = sum / WINDOW_SIZE;
}

void Sensor2Angle() {
  pressure_val = constrain(pressure_val, pressure_min, pressure_max);
  pressure_rate = map(pressure_val, pressure_min, pressure_max, 0, 100);

  thumb_pos = map(pressure_rate, 0, 100, ThumbOpen, ThumbClose);
  index_pos = map(pressure_rate, 0, 100, IndexOpen, IndexClose);
  middle_pos = map(pressure_rate, 0, 100, MiddleOpen, MiddleClose);
  other_pos = map(pressure_rate, 0, 100, OtherOpen, OtherClose);
}





