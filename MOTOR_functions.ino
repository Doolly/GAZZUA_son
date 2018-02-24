void MotorInit() {
  Thumb_M.attach(M_THUMB);
  Index_M.attach(M_INDEX);
  Middle_M.attach(M_MIDDLE);
  Other_M.attach(M_OTHER);

  Thumb_M.write(ThumbOpen);
  Index_M.write(IndexOpen);
  Middle_M.write(MiddleOpen);
  Other_M.write(OtherOpen);
}

unsigned long last_mode_change_time;
int mode_init_delay = 1000;

void MotorCtrl () {
  temp_mode = mode;

  if (temp_mode != last_mode) {
    last_mode_change_time = millis();

    if ((millis() - last_mode_change_time ) > mode_init_delay) {
      mode = temp_mode;
    }
    else {
      mode = last_mode;
    }

    switch (mode) {
      case GRASP:
        Thumb_M.write(ThumbClose);
        Index_M.write(index_pos);
        Middle_M.write(middle_pos);
        Other_M.write(other_pos);
        Serial.println("grasp !!!!!!!!!!");
        break;
      case THREE:
        Thumb_M.write(ThumbClose);
        Index_M.write(index_pos);
        Middle_M.write(middle_pos);
        Other_M.write(OtherClose);
        Serial.println("threee !!!!!!!!!!");
        break;
      case PICK:
        Thumb_M.write(ThumbClose);
        Index_M.write(index_pos);
        Middle_M.write(MiddleClose);
        Other_M.write(OtherClose);
        break;
      case LED:
        Thumb_M.write(ThumbOpen);
        Index_M.write(IndexOpen);
        Middle_M.write(MiddleOpen);
        Other_M.write(OtherOpen);
        //digitalWrite(LED_EN, LOW);
        break;
      case RCP:
        break;
      case FUCK:
        Thumb_M.write(ThumbClose);
        Index_M.write(IndexClose);
        Middle_M.write(MiddleOpen);
        Other_M.write(OtherClose);
        break;
      case OTHER:
        break;
    }
  }
  
  else {
    mode = temp_mode;
    }
    last_mode = mode;
}


