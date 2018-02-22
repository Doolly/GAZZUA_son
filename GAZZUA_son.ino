/*------ Headers to Include ------*/
#include <SoftwareSerial.h>
#include <Servo.h>
#include <Adafruit_GFX.h>  // Include core graphics library for the display
#include <Adafruit_SSD1306.h>  // Include Adafruit_SSD1306 library to drive the display
#include <Fonts/FreeMonoBold12pt7b.h>  // Add a custom font
#include <Fonts/FreeMono9pt7b.h>  // Add a custom font

/*------ Pin Define ------*/
#define ENCODER_1 0
#define ENCODER_2 1
#define I2C_SDA 2
#define I2C_SCL 3
#define ENCODER_BUTTON 4
#define LED_EN 7
#define M_THUMB 5
#define M_INDEX 6
#define M_MIDDLE 11
#define M_OTHER 13
#define PRESS_SEN A1

/*------ Value Define ------*/
#define OLED_ADDR 0x3C
#define array_size 8
/*------ Objects ------*/
Adafruit_SSD1306 display;
Servo Thumb_M;
Servo Index_M;
Servo Middle_M;
Servo Other_M;

/*------ Functions ------*/
void EncoderInit();
void UpdateEncoder();
void OLEDInit();
void MotorInit();
void ChangeMode();
int DebounceRead(int button);
void Change_Value_in_Serial();
void SerialMonitor();

/*------ Global Variables ------*/
volatile int lastEncoded = 0;
volatile long encoderValue = 0;

int rect_x_pos = 0;
int page = 0;
int key = 0;

const int ThumbMax = 100;
const int ThumbMin = 10;
const int IndexMax = 180;
const int IndexMin = 50;
const int MiddleMax = 180;
const int MiddleMin = 50;
const int OtherMax = 170;
const int OtherMin = 110;

enum MODE {MENU = -1, GRASP, THREE, PICK, LED, RCP, LOVE ,FUCK, OTHER};
enum MODE mode = MENU;

int pressure_val = 0;
int pressure_max;
int pressure_min;
int sensor_array[array_size] = {0,};
int encoder_gain = 30;
int number_of_modes = 8;

void setup() {
  EncoderInit();
  OLEDInit ();
  MotorInit();
  pinMode(LED_EN, OUTPUT);
  Serial.begin(9600);
  
}

void loop() {


  Change_Value_in_Serial();
  ChangeMode();

  display.clearDisplay();
  display.drawRect(0, rect_x_pos, 70, 16, WHITE);  // Draw rectangle (x,y,width,height,color) 좌측상단부터 그림
  if (page == 0) {
    display.setCursor(5, 10);  
    display.println("grasp");
    display.setCursor(5, 27);  
    display.println("three");
    display.setCursor(5, 44);  
    display.println("pick");
    display.setCursor(5, 60);  
    display.println("LED");
  }
  else {
    display.setCursor(5, 10); 
    display.println("rcp");
    display.setCursor(5, 27);  
    display.println("love");
    display.setCursor(5, 44);  
    display.println("Fxxx");
    display.setCursor(5, 60); 
    display.println("other");
  }
  display.display();
  
  
    if (key == 0) {
      mode = GRASP;
    }
    else if ((key == 1) || (key == -7)) {
      mode = THREE;
    }
    else if ((key == 2) || (key == -6)) {
      mode = PICK;
    }
    else if ((key == 3) || (key == -5)) {
      mode = LED;
    }
    else if ((key == 4) || (key == -4)) {
      mode = RCP;
    }
    else if ((key == 5) || (key == -3)) {
      mode = LOVE;
    }
    else if ((key == 6) || (key == -2)) {
      mode = FUCK;
    }
    else if ((key == 7) || (key == -1)) {
      mode = OTHER;
    }
  }


