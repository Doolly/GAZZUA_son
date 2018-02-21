
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
 
int button_state;
int last_button_state = 0; //pull down circit
unsigned long last_debounce_time = 0;
unsigned long debounce_delay = 50;

int DebounceRead(int button) {
  int reading = digitalRead(button);

  if (reading != last_button_state)
    last_debounce_time = millis();

  if ((millis() - last_debounce_time) > debounce_delay) {
    if (reading != button_state) {
      button_state = reading;

      if (button_state == 1)
        return 1;
      else
        return 0;
    }
  }
  last_button_state = reading;
}


void timerIsr() {
  encoder->service();
}

int GetPressureVal () {
  
  
  }
