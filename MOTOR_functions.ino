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



void MotorCtrl () {
  if (mode == LED) {
    digitalWrite(LED_EN, HIGH);
  }
  else {
    digitalWrite(LED_EN, LOW);
  }
  switch (mode) {
    case GRASP:
      Thumb_M.write(ThumbClose);
      Index_M.write(index_pos);
      Middle_M.write(middle_pos);
      Other_M.write(other_pos);
      break;
    case THREE:
      Thumb_M.write(ThumbClose);
      Index_M.write(index_pos);
      Middle_M.write(middle_pos);
      Other_M.write(OtherOpen);
      break;
    case PICK:
      Thumb_M.write(ThumbClose);
      Index_M.write(index_pos);
      Middle_M.write(MiddleOpen);
      Other_M.write(OtherOpen);
      break;
    case LED:
      Thumb_M.write(ThumbOpen);
      Index_M.write(IndexOpen);
      Middle_M.write(MiddleOpen);
      Other_M.write(OtherOpen);
      break;
    case RCP:
//      if (pressure_rate > 90) {
//        int a = random(1, 4);
//        if (a == 1) { //묵
//          Thumb_M.write(ThumbClose);
//          Index_M.write(IndexClose);
//          Middle_M.write(MiddleClose);
//          Other_M.write(OtherClose);
//        }
//        if (a == 2) { //찌
//          Thumb_M.write(ThumbClose);
//          Index_M.write(IndexClose);
//          Middle_M.write(MiddleClose);
//          Other_M.write(OtherOpen);
//        }
//        if (a == 3) { //paper
//          Thumb_M.write(ThumbOpen);
//          Index_M.write(IndexOpen);
//          Middle_M.write(MiddleOpen);
//          Other_M.write(OtherOpen);
//        }
//      }
      break;
    case FUCK:
      Thumb_M.write(ThumbClose);
      Index_M.write(IndexClose);
      Middle_M.write(middle_pos);
      Other_M.write(OtherClose);
      break;
    case THUMBUP:
      Thumb_M.write(thumb_pos);
      Index_M.write(30);
      Middle_M.write(MiddleClose);
      Other_M.write(OtherClose);
      break;
    case POINT:
      Thumb_M.write(ThumbClose);
      Index_M.write(index_pos);
      Middle_M.write(MiddleClose);
      Other_M.write(OtherClose);
      break;
  }
}


