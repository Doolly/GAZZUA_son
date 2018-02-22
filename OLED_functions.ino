/*
  y는 10 부터 됨
  x엔 12자리
  x 0~127 y 10~60  폰트크기가 10
*/
void OLEDInit () {
  delay(100);
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);  // Initialize display with the I2C address
  display.clearDisplay();  // Clear the buffer
  display.setTextColor(WHITE);  // Set color of the text (BLACK BLUE RED GREEN CYAN MAGENTA YELLOW WHITE)
  display.setRotation(0);  // Set orientation. Goes from 0, 1, 2 or 3 (회전 0도 90도 180도 270도)
  display.dim(0);  //Set brightness (0 is maximun and 1 is a little dim)
  display.setTextWrap(false);
  // By default, long lines of text are set to automatically “wrap” back to the leftmost column.
  // To override this behavior (so text will run off the right side of the display - useful for
  // scrolling marquee effects), use setTextWrap(false). The normal wrapping behavior is restored
  // with setTextWrap(true).
  display.setFont(&FreeMono9pt7b);  // Set a custom font
  display.setTextSize(0);  // Set text size. We are using a custom font so you should always use the text size of 0

  CenterDisplay("GAZZUA_son");
  delay(2000);
}
void MainDisplay() {
  display.drawRect(0, rect_x_pos, 70, 16, WHITE);  // Draw rectangle (x,y,width,height,color) 좌측상단부터 그림

  display.setCursor(5, 10);  
  display.println(mode_s[page*4]);
  display.setCursor(5, 27);  
  display.println(mode_s[page*4 + 1]);
  display.setCursor(5, 44);  
  display.println(mode_s[page*4 + 2]);
  display.setCursor(5, 60);  
  display.println(mode_s[page*4 + 3]);
  
  display.display();
  display.clearDisplay();
}
void CenterDisplay(String ment) {
  display.clearDisplay();
  display.setCursor(5, 32);
  display.println(ment);
  display.display();
}

void DisplayValue(int variable) {
  // Convert Variable1 into a string, so we can change the text alignment to the right AND It can be also used to add or remove decimal numbers.
  char string[10];  // Create a character array of 10 characters
  dtostrf(encoderValue, 3, 0, string);  // Convert float to a string: (<variable>,<amount of digits we are going to use>,<amount of decimal digits>,<string name>)
  display.setCursor(90, 10);  // (x,y)
  display.println(variable);  // Text or value to print (key)
  display.display();
  delay(2);
  display.clearDisplay();
}
