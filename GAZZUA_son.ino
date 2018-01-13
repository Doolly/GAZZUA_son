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
#define M1_PWM 7//// 둘이 바꾸고
#define M1_DIR 4////
#define M2_PWM 5//////// 이렇게 둘이
#define M2_DIR 8////////
#define M3_PWM 6
#define M3_DIR 9
#define M4_PWM 13
#define M4_DIR 10
#define M5_PWM 11 //얘네둘 바꾸기
#define M5_DIR AO //
#define LED_PWM   //이것도 vcc꼽은거 바꾸고
#define PRESS_1 A1
#define PRESS_2 A2
#define BT_RX A3
#define BT_TX A4
#define ENCODER_BUTTON A5
/*------ Value Define ------*/
#define OLED_ADDR 0x3C

/*------ Objects ------*/
Adafruit_SSD1306 display;
SoftwareSerial BTSerial(BT_RX, BT_TX);
/*------ Functions ------*/
void updateEncoder();
void OLED_init();
void Change_Value_in_Serial();
/*------ Global Variables ------*/
volatile int lastEncoded = 0;
volatile long encoderValue = 0;
long lastencoderValue = 0;
int lastMSB = 0;
int lastLSB = 0;

int mode;

String command; //debuging용

void setup() {
  Encoder_init();
  OLED_init ();

  BTSerial.begin(9600);


}

void loop() {
  //  display.drawRect(79, 0, 49, 27, WHITE);  // Draw rectangle (x,y,width,height,color) 우측 하단부터 그림
  //  display.display();
  //  //display.fillRect(79, 0, 49, 27, WHITE);
  //  display.display();
  //  delay(500);
  //  display.clearDisplay();
  //    delay(500);
  display.display();

  while (mode == 3) {
  }
  while (mode == 1) {
  }
  while (mode == 2) {
  }

}
