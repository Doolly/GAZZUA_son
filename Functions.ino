unsigned long current_time; //global variable
unsigned long previous_time; //global variable
void MillisDelay( int delay_time ) {
  current_time = millis();
  previous_time = current_time;
  while (current_time - previous_time < delay_time) {
    current_time = millis();
  }
}
