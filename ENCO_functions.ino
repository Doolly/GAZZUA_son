void EncoderInit() {
  pinMode(ENCODER_1, INPUT_PULLUP);
  pinMode(ENCODER_2, INPUT_PULLUP);
  pinMode(ENCODER_BUTTON, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ENCODER_1), UpdateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_2), UpdateEncoder, CHANGE);
}

void UpdateEncoder() {
  int MSB = digitalRead(ENCODER_1); //MSB = most significant bit
  int LSB = digitalRead(ENCODER_2); //LSB = least significant bit
  int encoded = (MSB << 1) | LSB; //converting the 2 pin value to single number
  int sum = (lastEncoded << 2) | encoded; //adding it to the previous encoded value
  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011)
    encoderValue ++;
  if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000)
    encoderValue --;
  lastEncoded = encoded; //store this value for next time

  if(encoderValue < 0)
    encoderValue = 999;
}
void PrintValue(int variable){
  // Convert Variable1 into a string, so we can change the text alignment to the right AND It can be also used to add or remove decimal numbers.
  char string[10];  // Create a character array of 10 characters
  dtostrf(encoderValue, 3, 0, string);  // Convert float to a string: (<variable>,<amount of digits we are going to use>,<amount of decimal digits>,<string name>)
  display.setCursor(90, 10);  // (x,y)
  display.println(variable);  // Text or value to print (key)
  display.display();
  delay(2);
  display.clearDisplay();
}
void ChangeMode() {
  key = (encoderValue * encoder_gain / 100) % NUMBER_OF_MODES;
  switch (key) {
    case 0 : mode = GRASP;break;
    case 1 : mode = THREE;break;
    case 2 : mode = PICK;break;
    case 3 : mode = LED;break;
    case 4 : mode = RCP;break;
    case 5 : mode = LOVE;break;
    case 6 : mode = FUCK;break;
    case 7 : mode = OTHER;break;
    }
  if (key > 3) {
    page = 1;
    rect_x_pos = (key-4)*16;
  }
  else {
    page = 0;
    rect_x_pos = key*16;
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
