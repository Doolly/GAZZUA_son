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
#define WINDOW_SIZE 50
#define NUMBER_OF_MODES 10
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
void CenterDisplay(String ment);
void DisplayValue(int variable);
void Change_Value_in_Serial();
void SerialMonitor();
void Calibration ();
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

String mode_s[NUMBER_OF_MODES] = {"grasp", "three", "pick", "LED", "rcp", "love", "Fxxx", "other"};
enum MODE {GRASP, THREE, PICK, LED, RCP, LOVE , FUCK, OTHER};
enum MODE mode = GRASP;

int pressure_val_raw = 0;
int pressure_val = 0;
int pressure_max;
int pressure_min;
int sensor_array[WINDOW_SIZE] = {0,};
int encoder_gain = 3;  //encoder sensitivity

int a;

void setup() {
  pinMode(LED_EN, OUTPUT);
  Serial.begin(115200);
  EncoderInit();
  OLEDInit ();
  MotorInit();

  // Calibration ();
}

void loop() {
  Change_Value_in_Serial();
  SerialMonitor();
  ChangeMode();
  MainDisplay();
  GetSensor();
 
}
