/*------ Headers to Include ------*/
#include <SoftwareSerial.h>
#include <Adafruit_GFX.h>  // Include core graphics library for the display
#include <Adafruit_SSD1306.h>  // Include Adafruit_SSD1306 library to drive the display
#include <Fonts/FreeMonoBold12pt7b.h>  // Add a custom font
#include <Fonts/FreeMono9pt7b.h>  // Add a custom font
/*------ Pin Define ------*/
#define ENCODER_1 0
#define ENCODER_2 1
#define I2C_SDA 2
#define I2C_SCL 3
#define M0_DIR 4
#define M0_EN 7
#define M1_DIR 5
#define M1_EN 8
#define M2_DIR 9
#define M2_EN 6
#define M3_DIR 13
#define M3_EN 10
#define M4_DIR 11
#define M4_EN A0
#define LED_PWM 12
#define PRESS_1 A1
#define PRESS_2 A2
#define BT_RX A3
#define BT_TX A4
#define ENCODER_BUTTON A5
/*------ Value Define ------*/
#define OLED_ADDR 0x3C
#define EXTEND 1
#define CONTRACT 0
/*------ Objects ------*/
Adafruit_SSD1306 display;
SoftwareSerial BTSerial(BT_RX, BT_TX);
/*------ Functions ------*/
void EncoderInit();
void UpdateEncoder();
void OLEDInit();
void MotorInit();
void MotorTest();
void ButtonTest();
int DebounceRead(int button);
int CheckExit();
void Change_Value_in_Serial();
/*------ Global Variables ------*/
volatile int lastEncoded = 0;
volatile long encoderValue = 0;
long lastencoderValue = 0;
int lastMSB = 0;
int lastLSB = 0;
int box_p = 0;
int page = 0;
int key = 0;

int motor_en_array[5] = {M0_EN, M1_EN, M2_EN, M3_EN, M4_EN};
int motor_dir_array[5] = {M0_DIR, M1_DIR, M2_DIR, M3_DIR, M4_DIR};
enum MODE {MENU = -1, GRASP, POINT, V_POS, OK, LED, BT, MOTION, SETSET};
enum MODE mode = MENU;

int pressure_val = 0;

void setup() {
  EncoderInit();
  OLEDInit ();
  MotorInit();
  BTSerial.begin(9600);
  Serial.begin(9600);
}

void loop() {
  Change_Value_in_Serial();
  Serial.println(pressure_val);
  
  changeMode();
  display.drawRect(0, box_p, 70, 16, WHITE);  // Draw rectangle (x,y,width,height,color) 좌측상단부터 그림
  if (page == 0) {
    display.setCursor(5, 10);  // (x,y)
    display.println("grasp");
    display.setCursor(5, 27);  // (x,y)
    display.println("point");
    display.setCursor(5, 44);  // (x,y)
    display.println("V pos");
    display.setCursor(5, 60);  // (x,y)
    display.println("O K");
  }
  else {
    display.setCursor(5, 10);  // (x,y)
    display.println("LED");
    display.setCursor(5, 27);  // (x,y)
    display.println("BT");
    display.setCursor(5, 44);  // (x,y)
    display.println("motion");
    display.setCursor(5, 60);  // (x,y)
    display.println("setset");
  }
  // Convert Variable1 into a string, so we can change the text alignment to the right:
  // It can be also used to add or remove decimal numbers.
  char string[10];  // Create a character array of 10 characters
  dtostrf(encoderValue, 3, 0, string);  // Convert float to a string: (<variable>,<amount of digits we are going to use>,<amount of decimal digits>,<string name>)
  display.setCursor(90, 10);  // (x,y)
  display.println(key);  // Text or value to print
  display.display();
  delay(2);
  display.clearDisplay();

  if (DebounceRead(ENCODER_BUTTON) == LOW) {
    display.fillRect(0, box_p, 70, 18, WHITE);
    delay(100);
    if (key == 0) {
      mode = GRASP;
    }
    else if ((key == 1) || (key == -7)) {
      mode = POINT;
    }
    else if ((key == 2) || (key == -6)) {
      mode = V_POS;
    }
    else if ((key == 3) || (key == -5)) {
      mode = OK;
    }
    else if ((key == 4) || (key == -4)) {
      mode = LED;
    }
    else if ((key == 5) || (key == -3)) {
      mode = BT;
    }
    else if ((key == 6) || (key == -2)) {
      mode = MOTION;
    }
    else if ((key == 7) || (key == -1)) {
      mode = SETSET;
    }
  }

  while (mode == GRASP) {
    display.clearDisplay();
    display.setCursor(5, 10);  // (x,y)
    display.println("grasp mode");
    display.display();
    Grasp();
    if (DebounceRead(ENCODER_BUTTON) == LOW) {
      delay(100);
      mode = MENU;
    }
  }
  while (mode == POINT) {
    display.clearDisplay();
    display.setCursor(5, 10);  // (x,y)
    display.println("point mode");
    display.display();
    if (DebounceRead(ENCODER_BUTTON) == LOW) {
      delay(100);
      mode = MENU;
    }
  }
  while (mode == V_POS) {
    display.clearDisplay();
    display.setCursor(5, 10);  // (x,y)
    display.println("V pos mode");
    display.display();
    if (DebounceRead(ENCODER_BUTTON) == LOW) {
      delay(100);
      mode = MENU;
    }
  }
  while (mode == OK) {
    display.clearDisplay();
    display.setCursor(5, 10);  // (x,y)
    display.println("OK mode");
    display.display();
    if (DebounceRead(ENCODER_BUTTON) == LOW) {
      delay(100);
      mode = MENU;
    }
  }
  while (mode == LED) {
    display.clearDisplay();
    display.setCursor(5, 10);  // (x,y)
    display.println("LED mode");
    display.display();
    if (DebounceRead(ENCODER_BUTTON) == LOW) {
      delay(100);
      mode = MENU;
    }
  }
  while (mode == BT) {
    display.clearDisplay();
    display.setCursor(5, 10);  // (x,y)
    display.println("BT mode");
    display.display();
    if (DebounceRead(ENCODER_BUTTON) == LOW) {
      delay(100);
      mode = MENU;
    }
  }
  while (mode == MOTION) {
    display.clearDisplay();
    display.setCursor(5, 10);  // (x,y)
    display.println("motion mode");
    display.display();
    if (DebounceRead(ENCODER_BUTTON) == LOW) {
      delay(100);
      mode = MENU;
    }
  }
  while (mode == SETSET) {
    display.clearDisplay();
    display.setCursor(5, 10);  // (x,y)
    display.println("setset mode");
    display.display();
    if (DebounceRead(ENCODER_BUTTON) == LOW) {
      delay(100);
      mode = MENU;
    }
  }
}
