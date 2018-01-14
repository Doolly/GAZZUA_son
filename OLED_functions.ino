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
  
  display.setCursor(63, 32);  // (x,y)
  display.println("GAZZUA_son");  // Text or value to print                           
  display.display();  // Print everything we set previously
}

