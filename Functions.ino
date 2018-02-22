unsigned long current_time; //global variable
unsigned long previous_time; //global variable
void MillisDelay( int delay_time ) {
  current_time = millis();
  previous_time = current_time;
  while (current_time - previous_time < delay_time) {
    current_time = millis();
  }
}

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

void Grasp(){
  MotorCtrl(0,2000, pressure_val);
  MotorCtrl(1,2000, pressure_val);
  MotorCtrl(2,2000, pressure_val);
  MotorCtrl(3,2000, pressure_val);
  MotorCtrl(4,2000, pressure_val);
}

void Point(){
  MotorCtrl(0,2000, pressure_val);
  MotorCtrl(1,2000, pressure_val);
  MotorCtrl(2,2000, pressure_val);
  MotorCtrl(3,100, pressure_val);
  MotorCtrl(4,2000, pressure_val);
}

void V_Pos(){
  MotorCtrl(0,2000, pressure_val);
  MotorCtrl(1,2000, pressure_val);
  MotorCtrl(2,100, pressure_val);
  MotorCtrl(3,100, pressure_val);
  MotorCtrl(4,2000, pressure_val);
}


