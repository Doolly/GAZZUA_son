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
  
}

void ChangeMode() {
  key = (encoderValue / encoder_gain) % number_of_modes;
  switch ( key % 4) {
    case -3 : rect_x_pos = 16; break;
    case -2 : rect_x_pos = 32; break;
    case -1 : rect_x_pos = 48; break;
    case 0 : rect_x_pos = 0; break;
    case 1 : rect_x_pos = 16; break;
    case 2 : rect_x_pos = 32; break;
    case 3 : rect_x_pos = 48; break;
  }
  if (key > 3) {
    page = 1;
  }
  else if ((key < 4 ) && (key > -1)) {
    page = 0;
  }
  else if ( (key < 0) && (key >= -4)) {
    page = 1;
  }
  else {
    page = 0;
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
