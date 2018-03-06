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
#define M_THUMB 12
#define M_INDEX 5
#define M_MIDDLE 11
#define M_OTHER 6
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
void GetSensor();
/*------ Global Variables ------*/
volatile int lastEncoded = 0;
volatile long encoderValue = 0;
int encoder_gain = 4;  //encoder sensitivity

//const int ThumbOpen = 100;
//const int ThumbClose = 5;
//const int IndexOpen = 120;
//const int IndexClose = 0;
//const int MiddleOpen = 50;
//const int MiddleClose = 0;
//const int OtherOpen = 170;
//const int OtherClose = 80;


const int ThumbOpen = 90;
const int ThumbClose = 5;
const int IndexOpen = 110;
const int IndexClose = 0;
const int MiddleOpen = 40;
const int MiddleClose = 0;
const int OtherOpen = 160;
const int OtherClose = 80;

String mode_s[NUMBER_OF_MODES] = {"grasp", "three", "pick", "LED", "rcp", "love", "Fxxx", "other"};
enum MODE {GRASP, THREE, PICK, LED, RCP, LOVE , FUCK, OTHER};
enum MODE mode = GRASP;
enum MODE last_mode = GRASP;
enum MODE temp_mode = GRASP;
unsigned long last_mode_change_time;
int mode_init_delay = 2000;

int pressure_val_raw = 0;
int pressure_val = 0;
int pressure_max = 500;
int pressure_min = 0;
int pressure_rate;
int sensor_array[WINDOW_SIZE] = {0,};

int thumb_pos;
int index_pos;
int middle_pos;
int other_pos;

int thumb_pos_rate;
int index_pos_rate;
int middle_pos_rate;
int other_pos_rate ;

int rect_x_pos = 0;
int page = 0;
int key = 0;
int last_key = 0;

int mm = 1; // monitoring method

void setup() {
  pinMode(LED_EN, OUTPUT);
  digitalWrite(LED_EN, HIGH);

  Serial.begin(9600);
  EncoderInit();
  OLEDInit ();
  //MotorInit();

  //Calibration ();
}

void loop() {
  Change_Value_in_Serial();
  SerialMonitor(mm);
  MainDisplay();
  GetSensor();
  Sensor2Angle();
  MotorCtrl ();

  if (temp_mode != last_mode) {
    while (1) {
      if ((millis() - last_mode_change_time ) > mode_init_delay) {
        mode = temp_mode;
        last_mode = mode;
        break;
      }
      else {
        MainDisplay();
        SerialMonitor(mm);
        mode = last_mode;
      }
    }
  }
}
