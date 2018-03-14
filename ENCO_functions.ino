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

  if (encoderValue < 0)
    encoderValue = 999;

  ChangeMode();
}

void ChangeMode() {
  key = (encoderValue * encoder_gain / 100) % NUMBER_OF_MODES;
  switch (key) {
    case 0 : temp_mode = GRASP; break;
    case 1 : temp_mode = THREE; break;
    case 2 : temp_mode = PICK; break;
    case 3 : temp_mode = LED; break;
    case 4 : temp_mode = RCP; break;
    case 5 : temp_mode = FUCK; break;
    case 6 : temp_mode = THUMBUP; break;
    case 7 : temp_mode = POINT; break;
  }
  if (key > 3) {
    page = 1;
    rect_x_pos = (key - 4) * 16;
  }
  else {
    page = 0;
    rect_x_pos = key * 16;
  }

  if (key != last_key) {
    last_mode_change_time = millis();
  }
  last_key=key;
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
