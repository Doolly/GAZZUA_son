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
#define M_THUMB 5
#define M_INDEX 6
#define M_MIDDLE 10
#define M_OTHER 13
#define LED_EN 4
#define PRESS_1 A1
#define ENCODER_BUTTON A5
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

void ButtonTest();
int DebounceRead(int button);
int CheckExit();
void Change_Value_in_Serial();
void Grasp();
void Point();
void V_Pos();
/*------ Global Variables ------*/
volatile int lastEncoded = 0;
volatile long encoderValue = 0;
long lastencoderValue = 0;
int lastMSB = 0;
int lastLSB = 0;
int box_p = 0;
int page = 0;
int key = 0;

const int outThumbMax = 180;
const int outThumbMin = 85;
const int outIndexMax = 180;
const int outIndexMin = 50;
const int outOtherMax = 170;
const int outOtherMin = 110;

enum MODE {MENU = -1, GRASP, POINT, V_POS, OK, LED, THUMB, INDEX, OTHER};   //grasp(5) ,grasp(3) , picking,  LED  랜덤가위바위보(grasp(5),pick,nutral, 뻐큐)
enum MODE mode = MENU;

int pressure_val = 0;
int sensor_array[array_size] = {0,};

void setup() {
  EncoderInit();
  OLEDInit ();


  Thumb_M.attach(M_THUMB);
  Index_M.attach(M_INDEX);
  Middle_M.attach(M_MIDDLE);
  Other_M.attach(M_OTHER);

  Serial.begin(9600);
  pinMode(LED_PWM, OUTPUT);
}

void loop() {
  Change_Value_in_Serial();
  changeMode();
  pressure_val = analogRead(PRESS_1);
  Serial.println(pressure_val);

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
    display.println("INDEX");
    display.setCursor(5, 60);  // (x,y)
    display.println("OTHER");
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
      mode = THUMB;
    }
    else if ((key == 6) || (key == -2)) {
      mode = INDEX;
    }
    else if ((key == 7) || (key == -1)) {
      mode = OTHER;
    }
  }

  while (mode == GRASP) {
    display.clearDisplay();
    display.setCursor(5, 10);  // (x,y)
    display.println("grasp mode");
    display.display();

    pressure_val = analogRead(PRESS_1);
    pressure_val = map(pressure_val, 0, 650, 0, 1000);


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

    pressure_val = analogRead(PRESS_1);
    pressure_val = map(pressure_val, 0, 650, 0, 1000);

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

    pressure_val = analogRead(PRESS_1);
    pressure_val = map(pressure_val, 0, 650, 0, 1000);


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

    pressure_val = analogRead(PRESS_1);
    pressure_val = map(pressure_val, 0, 650, 0, 1000);

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

    pressure_val = analogRead(PRESS_1);
    pressure_val = map(pressure_val, 0, 650, 0, 1000);

    if (pressure_val > 100) {
      digitalWrite(LED_PWM, HIGH);
    }
    else
      digitalWrite(LED_PWM, LOW);

    if (DebounceRead(ENCODER_BUTTON) == LOW) {
      delay(100);
      mode = MENU;
    }
  }
  while (mode == THUMB) {
    display.clearDisplay();
    display.setCursor(5, 10);  // (x,y)
    display.println("THUMB mode");
    display.display();
    if (DebounceRead(ENCODER_BUTTON) == LOW) {
      delay(100);
      mode = MENU;
    }
    pressure_val = analogRead(PRESS_1);
    pressure_val = map(pressure_val, 0, 650, outThumbMin, outThumbMax);
    Thumb_M.write(170);
  }
  while (mode == INDEX) {
    display.clearDisplay();
    display.setCursor(5, 10);  // (x,y)
    display.println("INDEX mode");
    display.display();
    if (DebounceRead(ENCODER_BUTTON) == LOW) {
      delay(100);
      mode = MENU;
    }
  }
  while (mode == OTHER) {
    display.clearDisplay();
    display.setCursor(5, 10);  // (x,y)
    display.println("OTHER mode");
    display.display();
    if (DebounceRead(ENCODER_BUTTON) == LOW) {
      delay(100);
      mode = MENU;
    }
  }
}
