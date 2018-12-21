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

  
  tft.fillScreen(BLACK);

  //Draw white frame
  tft.drawRect(0,0,319,240,WHITE);
  
  //Print "Hello" Text
  tft.setCursor(100,30);
  tft.setTextColor(WHITE);
  tft.setTextSize(4);
  tft.print("Hello");
  
  //Print "YouTube!" text 
  tft.setCursor(80,100);
  tft.setTextColor(RED);
  tft.setTextSize(4);
  tft.print("YouTube!");
  
  //Create Red Button
  tft.fillRect(60,180, 200, 40, RED);
  tft.drawRect(60,180,200,40,WHITE);
  tft.setCursor(80,188);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("Subscribe!");

} 

// Main loop
void loop() 
{
  TSPoint p = ts.getPoint();  //Get touch point
  
  if (p.z > ts.pressureThreshhold) {

   Serial.print("X = "); Serial.print(p.x);
   Serial.print("\tY = "); Serial.print(p.y);
   Serial.print("\n");
   
   p.x = map(p.x, TS_MAXX, TS_MINX, 0, 320);
   p.y = map(p.y, TS_MAXY, TS_MINY, 0, 240);
       
   if(p.x>60 && p.x<260 && p.y>180 && p.y<220 && buttonEnabled)// The user has pressed inside the red rectangle
   {
    buttonEnabled = false; //Disable button
        
    //This is important, because the libraries are sharing pins
   pinMode(XM, OUTPUT);
   pinMode(YP, OUTPUT);
    
    //Erase the screen
    tft.fillScreen(BLACK);
    
    //Draw frame
    tft.drawRect(0,0,319,240,WHITE);
    
    tft.setCursor(50,50);
    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.print("Thank you for\n\n   subscribing!");
   }
   delay(10);  
  }
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
      Servo1();
      Servo2();
      Servo3();
      Servo4();
      credits = 0; 
  }

}
// Activate Servo 1
void Servo1(){
      servo1.attach(45);
      delay(3000);
      servo1.detach();  
}
// Activate Servo 2
void Servo2(){
      servo2.attach(46);
      delay(3000);
      servo2.detach();  
}
// Activate Servo 3
void Servo3(){
      servo3.attach(50);
      delay(3000);  
      servo3.detach();
}
// Activate Servo 4
void Servo4(){
      servo4.attach(52);
      delay(3000);
      servo4.detach();  
}
// Interrupt
void coinInterrupt(){
  
  // Each time a pulse is sent from the coin acceptor, interrupt main loop to add 1 cent and flip on the LED
  cents = cents + 1;
  
}
