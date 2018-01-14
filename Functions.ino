unsigned long current_time; //global variable
unsigned long previous_time; //global variable
void MillisDelay( int delay_time ) {
  current_time = millis();
  previous_time = current_time;
  while (current_time - previous_time < delay_time) {
    current_time = millis();
  }
}
unsigned long start_time; //global variable
bool current_state = false;
bool last_state = false;
int CheckExit(){
  if(digitalRead(ENCODER_BUTTON) == LOW){
        current_state = true;
  }
  else{
    current_state = false;
  }
  if((current_state == true)&&(last_state==false)){
    start_time = millis();
  }
  if((current_state == false) && (last_state == true)&& (millis() - start_time> 500)){
   // start_time = millis();
    return 1;
  } 
  last_state = current_state;
  
}
