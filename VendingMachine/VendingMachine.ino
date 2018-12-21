#include <Servo.h> 
#include <Adafruit_TFTLCD.h> 
#include <Adafruit_GFX.h>    
#include <TouchScreen.h>

#define LCD_CS A3 
#define LCD_CD A2 
#define LCD_WR A1 
#define LCD_RD A0 
#define LCD_RESET A4 

#define TS_MINX 204
#define TS_MINY 195
#define TS_MAXX 948
#define TS_MAXY 910

#define YP A2  // must be an analog pin, use "An" notation!
#define XM A3  // must be an analog pin, use "An" notation!
#define YM 8   // can be a digital pin
#define XP 9   // can be a digital pin

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define CHOICE1   "A"
#define CHOICE2   "B"
#define CHOICE3   "C"
#define CHOICE4   "D"

#define SERVODELAY 5000

// Constants
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

const int coinpin = 21;
const int targetcents = 50;

// Variables
volatile int cents = 0;
int credits = 0;
boolean buttonEnabled = true;

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

void setup() 
{ 
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(coinpin), coinInterrupt, RISING);
  Serial.print("Starting...");
  
  tft.reset();
//  tft.begin(0x9325);
//  tft.setRotation(1);
  tft.begin(0x9341);
  tft.setRotation(3);

  clear_LCD();

  tft.setCursor(30,30);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("Vending Machine");
  
  tft.setCursor(20,90);
  tft.setTextColor(RED);
  tft.setTextSize(3);
  tft.print("@NickySlicksHaha");
  
  //Create Red Button
  tft.fillRect(40,180, 235, 40, RED);
  tft.drawRect(40,180,235,40,WHITE);
  tft.setCursor(55,188);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("Subscribe :)");

  delay(2000);
  waitingForCredit();
  updateCredits();

} 

// Main loop
void loop() 
{
  // If we've hit our target amount of coins, increment our credits and reset the cents counter
  if (cents >= targetcents) {
    credits = credits + 1;
    cents = cents - targetcents;
  }

  // If we haven't reached our target, keep waiting...
  else {
  }

  // Now, write your own cool code here that triggers an event when the player has credits!
  if (credits > 0) {
      drawChoices();
      findButton();
      reset(); 
  }
  delay(1000);
}

void reset(){
  credits=0;
  waitingForCredit();
  buttonEnabled=true;
  updateCredits();  
}
void findButton(){
  while(1){
    TSPoint p = ts.getPoint();  //Get touch point
    if (p.z > ts.pressureThreshhold) {
 
     p.x = map(p.x, TS_MAXX, TS_MINX, 0, 320);
     p.y = map(p.y, TS_MAXY, TS_MINY, 0, 240);
         
     if(p.x>10 && p.x<145 && p.y>80 && p.y<140 && buttonEnabled)// The user has pressed inside the red rectangle
     {
      buttonEnabled = false; //Disable button
          
      //This is important, because the libraries are sharing pins
      pinMode(XM, OUTPUT);
      pinMode(YP, OUTPUT);
      clear_LCD();      
      thanks();
      Servo1();
      break;
     }

     if(p.x>175 && p.x<310 && p.y>80 && p.y<140 && buttonEnabled)// The user has pressed inside the red rectangle
     {
      buttonEnabled = false; //Disable button
          
      //This is important, because the libraries are sharing pins
      pinMode(XM, OUTPUT);
      pinMode(YP, OUTPUT);
      
      clear_LCD();      
      thanks();
      Servo2();
      break;
     }

     if(p.x>10 && p.x<145 && p.y>160 && p.y<220 && buttonEnabled)// The user has pressed inside the red rectangle
     {
      buttonEnabled = false; //Disable button
          
      //This is important, because the libraries are sharing pins
      pinMode(XM, OUTPUT);
      pinMode(YP, OUTPUT);  
      clear_LCD();      
      thanks();
      Servo3();
      break;
     }

     if(p.x>175 && p.x<310 && p.y>160 && p.y<220 && buttonEnabled)// The user has pressed inside the red rectangle
     {
      buttonEnabled = false; //Disable button
          
      //This is important, because the libraries are sharing pins
      pinMode(XM, OUTPUT);
      pinMode(YP, OUTPUT);
      clear_LCD();      
      thanks();
      Servo4();
      break;
     }
     delay(10);  
    }
  }
}
void clear_LCD(){
    //Erase the screen
    tft.fillScreen(BLACK);      
    //Draw frame
    tft.drawRect(0,0,319,240,WHITE);
}
void thanks(){
    tft.setCursor(80,80);
    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.print("THANKS!");
}
// Activate Servo 1
void Servo1(){
      servo1.attach(45);
      delay(SERVODELAY);
      servo1.detach();  
}
// Activate Servo 2
void Servo2(){
      servo2.attach(46);
      delay(SERVODELAY);
      servo2.detach();  
}
// Activate Servo 3
void Servo3(){
      servo3.attach(50);
      delay(SERVODELAY);  
      servo3.detach();
}
// Activate Servo 4
void Servo4(){
      servo4.attach(52);
      delay(SERVODELAY);
      servo4.detach();  
}
// Interrupt
void coinInterrupt(){ 
  // Each time a pulse is sent from the coin acceptor, interrupt main loop to add 1 cent and flip on the LED
  cents = cents + 1;
  updateCredits(); 
}

void waitingForCredit(){
  clear_LCD();

  tft.setCursor(50,40);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("Insert $0.50");
  tft.setCursor(95,90);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("Credit:");
}

void updateCredits(){
  //Create Red Button
  tft.fillRect(70,140, 155, 40, RED);
  tft.drawRect(70,140,155,40,WHITE);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  if(cents == 0){
    tft.setCursor(105,148);
    tft.print("$0.00");
  }
  else{
    tft.setCursor(105,148);
    tft.print("$0.");
    tft.setCursor(160,148);
    tft.print(cents);
  }
}

void drawChoices(){
      clear_LCD();
    
      // Title
      tft.setCursor(60,20);
      tft.setTextColor(WHITE);
      tft.setTextSize(3);
      tft.print("Credits: 1");
      
      tft.fillRect(10,80,135, 60, RED);
      tft.drawRect(10,80,135,60,WHITE);
      tft.setTextColor(WHITE);
      tft.setTextSize(3);
      tft.setCursor(70,95);
      tft.print(CHOICE1);

      tft.fillRect(175,80,135, 60, RED);
      tft.drawRect(175,80,135,60,WHITE);
      tft.setTextColor(WHITE);
      tft.setTextSize(3);
      tft.setCursor(235,95);
      tft.print(CHOICE2);

      tft.fillRect(10,160,135, 60, RED);
      tft.drawRect(10,160,135,60,WHITE);
      tft.setTextColor(WHITE);
      tft.setTextSize(3);
      tft.setCursor(70,175);
      tft.print(CHOICE3);

      tft.fillRect(175,160,135, 60, RED);
      tft.drawRect(175,160,135,60,WHITE);
      tft.setTextColor(WHITE);
      tft.setTextSize(3);
      tft.setCursor(235,175);
      tft.print(CHOICE4);
}
