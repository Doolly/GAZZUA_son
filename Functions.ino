
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

      if (part1.equalsIgnoreCase("pressure_val"))
        pressure_val = part2.toInt();

      else if (part1.equalsIgnoreCase("B_variable"))
        B_variable = part2.toInt();

      command = "";
    }

    else
      command += c;
  }

}

void SerialMonitor() {
  Serial.print("pressure_val = " + String(pressure_val) + "\n");
  Serial.print("pressure_max = " + String(pressure_max) + "\n");
  Serial.print("pressure_min = " + String(pressure_min) + "\n");
}

void Calibration () {
  CenterDisplay("Calibration");

  pressure_max = GetSensor();
  pressure_min = pressure_max - 50;
  unsigned long now = millis();
  while ( millis() < now + 4000 ) {
    pressure_val = GetSensor();
    delay(25);
    if ( pressure_val < pressure_min ) {
      pressure_min = pressure_val;
    }
    else if ( pressure_val > pressure_max ) {
      pressure_max = pressure_val;
    }
  }
  CenterDisplay("done");
  delay(1000);
}
int GetSensor() {
  pressure_val = analogRead(PRESS_SEN);
  //Serial.print("pressure_val = " + String(pressure_val) + "\n");


}


