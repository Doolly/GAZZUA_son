void MotorInit() {
  Thumb_M.attach(M_THUMB);
  Index_M.attach(M_INDEX);
  Middle_M.attach(M_MIDDLE);
  Other_M.attach(M_OTHER);

  Thumb_M.write(ThumbMax);
  Index_M.write(IndexMax);
  Middle_M.write(MiddleMax);
  Other_M.write(OtherMax);
}

void MotorCtrl (int mode){
  switch(mode){
    case GRASP: break;
    case THREE: break;
    case PICK: break;
    case LED: break;
    case RCP: break;
    case FUCK: break;
    case OTHER: break;
    }
}


