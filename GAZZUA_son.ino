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

int mode;
int motor_en_array[5] = {M0_EN, M1_EN, M2_EN, M3_EN, M4_EN};
int motor_dir_array[5] = {M0_DIR, M1_DIR, M2_DIR, M3_DIR, M4_DIR};

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

  if (DebounceRead(ENCODER_BUTTON) == 0) {
    display.fillRect(0, box_p, 70, 18, WHITE);
  }


  while (mode == 3) {
  }
  while (mode == 1) {
  }
  while (mode == 2) {
  }

}
