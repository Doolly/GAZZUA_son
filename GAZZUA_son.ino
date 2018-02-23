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
#define M_THUMB 13   //open100 close 10
#define M_INDEX 5  // close 150 open 0
#define M_MIDDLE 11 //
#define M_OTHER 6 // open10 close
#define PRESS_SEN A1

/*------ Value Define ------*/
#define OLED_ADDR 0x3C
#define WINDOW_SIZE 30
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
void MainDisplay();
void CenterDisplay(String ment);
void DisplayValue(int variable);
void MotorInit();
void MotorCtrl();
void ChangeMode();
int DebounceRead(int button);
void Change_Value_in_Serial();
void SerialMonitor(int how);
void Calibration ();

/*------ Global Variables ------*/
volatile int lastEncoded = 0;
volatile long encoderValue = 0;
int encoder_gain = 4;  //encoder sensitivity

const int ThumbOpen = 100;
const int ThumbClose = 10;
const int IndexOpen = 150;
const int IndexClose = 0;
const int MiddleOpen = 180;
const int MiddleClose = 50;
const int OtherOpen = 170;
const int OtherClose = 110;

String mode_s[NUMBER_OF_MODES] = {"grasp", "three", "pick", "LED", "rcp", "love", "Fxxx", "other"};
enum MODE {GRASP, THREE, PICK, LED, RCP, LOVE , FUCK, OTHER};
enum MODE mode = GRASP;
enum MODE pre_mode = GRASP;

bool is_change = false;

int pressure_val_raw = 0;
int pressure_val = 0;
int pressure_max;
int pressure_min;
int pressure_rate;
int sensor_array[WINDOW_SIZE] = {0,};

int thumb_pos;
int index_pos;
int middle_pos;
int other_pos;

int rect_x_pos = 0;
int page = 0;
int key = 0;

int mm; // monitoring method

void setup() {
  pinMode(LED_EN, OUTPUT);
  Serial.begin(9600);
  EncoderInit();
  OLEDInit ();
  MotorInit();

  // Calibration ();
}

void loop() {
  Change_Value_in_Serial();
  SerialMonitor(mm);
  ChangeMode();
  if (pre_mode != mode) {
    Thumb_M.write(ThumbOpen);
    Index_M.write(IndexOpen);
    Middle_M.write(MiddleOpen);
    Other_M.write(OtherOpen);
    digitalWrite(LED_EN, LOW);
    is_change = true;
  }
  MainDisplay();
  GetSensor();
  Sensor2Angle();
  if(is_change){
    MotorCtrl();
  }
  pre_mode = mode;
}
