/*------ Headers to Include ------*/
#include <Servo.h>
#include <ClickEncoder.h>
#include <TimerOne.h>
/*------ Pin Define ------*/
#define M_THUMB 5
#define M_INDEX 6
#define M_MIDDLE 10
#define M_OTHER 13
#define LED_LIGHT 2
#define PRESS_SENSOR A0
#define ENCODER_1 3
#define ENCODER_2 12
#define ENCODER_BUTTON A1
/*------ Value Define ------*/
#define array_size 8
/*------ Objects ------*/
Servo Thumb_M;
Servo Index_M;
Servo Middle_M;
Servo Other_M;
ClickEncoder *encoder;
/*------ Functions ------*/
int DebounceRead(int button);
void Change_Value_in_Serial();
void LedBlink();
int GetPressureVal();
/*------ Global Variables ------*/
const int outThumbMax = 180;
const int outThumbMin = 85;
const int outIndexMax = 180;
const int outIndexMin = 50;
const int outOtherMax = 170;
const int outOtherMin = 110;

enum MODE {MENU = -1, FULL_GRASP,THREE_GRASP, PICK, V_POS, OK, LED, THUMB, INDEX, OTHER};   //grasp(5) ,grasp(3) , picking,  LED  랜덤가위바위보(grasp(5),pick,nutral, 뻐큐) 
enum MODE mode = MENU;

int pressure_val = 0;
int sensor_array[array_size] = {0,};
int last, value;

void setup() {
  pinMode (BUTTON, INPUT_PULLUP);
  pinMode(LED_LIGHT, OUTPUT);
  
  Thumb_M.attach(M_THUMB);
  Index_M.attach(M_INDEX);
  Middle_M.attach(M_MIDDLE);
  Other_M.attach(M_OTHER);

   encoder = new ClickEncoder(ENCODER_1, ENCODER_2, ENCODER_BUTTON);

  Timer1.initialize(1000);
  Timer1.attachInterrupt(timerIsr); 
  
  last = -1;

  Serial.begin(9600);
  
}
void loop() {
  Change_Value_in_Serial();
  digitalWrite(LED_PWM, LOW);


  while (mode == GRASP) {

  }
  while (mode == POINT) {
   
  }
  while (mode == V_POS) {
   
  }
  while (mode == OK) {
   
  }
  while (mode == LED) {
  
  }

}
