//************************************************************
// Week 4 Assignment/Lab 4
// File: Lab4_CS328.ino
// Purpose: To learn how to program OLED display using Adafruit library
// Also learn how to use bluetooth
// Name: Audrey Saidel
//************************************************************
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // Width in px
#define SCREEN_HEIGHT 64 // Height in px
#define LOGO_WIDTH  32
#define LOGO_HEIGHT 32
// BLUETOOTH 38 400
#define OLED_RESET -1    
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
// LED
#define LEFT_LED 7
#define RIGHT_LED 6

// my Custom Sprite, 32x32px
const unsigned char logo_bmp [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x01, 0x00, 0x0e, 0x30, 
	0x06, 0xc0, 0x08, 0x18, 0x04, 0x40, 0x10, 0x08, 0x04, 0x20, 0x10, 0x18, 0x0c, 0x20, 0x11, 0x90, 
	0x08, 0x10, 0x22, 0x10, 0x04, 0x10, 0x22, 0x10, 0x04, 0x0b, 0xe0, 0x20, 0x04, 0x0c, 0x00, 0x20, 
	0x04, 0x00, 0x00, 0x20, 0x06, 0x00, 0x00, 0x20, 0x02, 0x00, 0x00, 0x40, 0x03, 0x00, 0x00, 0x40, 
	0x01, 0x80, 0x00, 0x40, 0x00, 0x88, 0x04, 0x40, 0x00, 0x80, 0x00, 0x40, 0x00, 0x80, 0x00, 0x40, 
	0x00, 0xc0, 0x00, 0x40, 0x00, 0x41, 0x40, 0x40, 0x00, 0x40, 0x80, 0x40, 0x00, 0x41, 0x40, 0x80, 
	0x00, 0x60, 0x03, 0x80, 0x00, 0x30, 0x4e, 0x00, 0x00, 0x1f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// left Blinker Sprite, 32x32px
const unsigned char left_arrow [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 
	0x01, 0xf0, 0x00, 0x00, 0x07, 0xf0, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xf8, 
	0x3f, 0xff, 0xff, 0xf8, 0x0f, 0xff, 0xfc, 0x00, 0x07, 0xf0, 0x00, 0x00, 0x01, 0xf0, 0x00, 0x00, 
	0x00, 0xf0, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// right Blinker Sprite, 32x32px
const unsigned char right_arrow [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x0f, 0x00, 
	0x00, 0x00, 0x0f, 0x80, 0x00, 0x00, 0x0f, 0xe0, 0x00, 0x00, 0x0f, 0xf0, 0x1f, 0xff, 0xff, 0xfc, 
	0x1f, 0xff, 0xff, 0xfc, 0x00, 0x3f, 0xff, 0xf0, 0x00, 0x00, 0x0f, 0xe0, 0x00, 0x00, 0x0f, 0x80, 
	0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

//************************************************************
// Method: setup
// Input: NONE
// Description: This is where you define constants and define
//    your configuration values.  This is run only once.
// pinMode options are INPUT, INPUT_PULLUP, OUTPUT
//************************************************************
void setup() {
  // Initialize OLED SCREEN
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)){
    for(;;);
  }
  // Initialize Bluetooth
  Serial.begin(9600);

  // Serial1 (pins 18 TX1, 19 RX1)
  Serial1.begin(38400);
  Serial.println("Serial1 initialized at 38400 baud.");

  // Initialize LEDS
  pinMode(LEFT_LED, OUTPUT);
  pinMode(RIGHT_LED, OUTPUT);

 // Finalize OLED
  display.display();
  delay(2000);
  display.clearDisplay();
  display.drawPixel(10,10, SSD1306_WHITE);
  display.display();

  // random seed for blinker function
  randomSeed(analogRead(A0));
}
//************************************************************
// Method: loop
// Input: NONE
// Description: Scroll through text, blink randomly, 
//  then bluetooth for the rest
//************************************************************
void loop() {
  scroll();
  blinker();
  while(true){ // this will loop endlessly
    bluetooth();
  }
}

//************************************************************
// Method: scroll
// Input: NONE
// Description: Scroll through lab title from right to left
//   Scroll custom sprite simutaneously from left to right
//************************************************************
void scroll(){
  // TEXT DISPLAY right - > left
  String text = "Lab 4 by: Audrey Saidel";  // text to display
  int16_t x = SCREEN_WIDTH;   // start just off the right edge
  int16_t textWidth = -text.length() * 6;  // ~6 px per char at size 1

  // SPRITE DISPLAY left - > right
  double spriteX = -LOGO_WIDTH;
  int16_t spriteY = SCREEN_HEIGHT - LOGO_HEIGHT;


  while (x > textWidth) {  // while text still visible on left side
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setTextWrap(false);
    display.setCursor(x, 0);
    display.println(text);


    display.drawBitmap(spriteX, spriteY, logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, SSD1306_WHITE); // custom sprite
    display.display();

    x -= 2;           // move text 2 pixels left
    spriteX += 1.5;    // move sprite one pixels right
    delay(20);      // speed adjust, the smaller the number faster text moves
}
}

//************************************************************
// Method: blinker
// Input: NONE
// Description: Blink left or right or display custom sprite
//   a random number of times
//************************************************************
void blinker(){
  unsigned long startTime = millis(); // start timer for how long function will occur
  while(millis() - startTime < 10000){ // this function will occur for around 10 seconds
    int ranNum = random(0, 3); // generates random int between 0, 1, and 2
    if (ranNum == 0){ // left Blinker
      digitalWrite(LEFT_LED, HIGH);
      digitalWrite(RIGHT_LED, LOW);
      display.drawBitmap(0, 16, left_arrow, LOGO_WIDTH, LOGO_HEIGHT, SSD1306_WHITE); // left arrow on left side of screen
    }
    else if (ranNum == 1){ // right  Blinker
      digitalWrite(LEFT_LED, LOW);
      digitalWrite(RIGHT_LED, HIGH);
      display.drawBitmap(90, 16, right_arrow, LOGO_WIDTH, LOGO_HEIGHT, SSD1306_WHITE); // right arrow on right side of screen
    }
    else { // custom Sprite
      digitalWrite(LEFT_LED, LOW);
      digitalWrite(RIGHT_LED, LOW);
      display.drawBitmap(48, 16, logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, SSD1306_WHITE); // custom sprite on center screen
    }
    // all displays will display for a second and then clear, next random number will be chosen
    display.display();
    delay(1000);
    display.clearDisplay();
  }
  // shut off LEDs and clear display
    digitalWrite(LEFT_LED, LOW);
    digitalWrite(RIGHT_LED, LOW);
    display.clearDisplay();
    display.display();
}

//************************************************************
// Method: bluetooth
// Input: NONE
// Description: Read byte in from serial port and control what
//   to do on OLED display and LEDS
//************************************************************
void bluetooth(void){
  // if data is availible from serial monitor
  if(Serial1.available()){
    char command = Serial1.read(); // read byte into char
    if(command == 'L'){ // if command is L (left) flash left blinker sprite and LED
      digitalWrite(LEFT_LED, HIGH);
      digitalWrite(RIGHT_LED, LOW);
      display.clearDisplay();
      display.drawBitmap(0, 16, left_arrow, LOGO_WIDTH, LOGO_HEIGHT, SSD1306_WHITE); // clear prior screen and display left arrow on left side of screen
      display.display();
    }
    else if(command == 'R'){ // if command is R (right), flash right blinker sprite and LED
      // deal with LEDS
      digitalWrite(LEFT_LED, LOW);
      digitalWrite(RIGHT_LED, HIGH);
      // deal with display
      display.clearDisplay();
      display.drawBitmap(90, 16, right_arrow, LOGO_WIDTH, LOGO_HEIGHT, SSD1306_WHITE); // clear prior screen and display right arrow on right side of screen
      display.display();
    }
    else{ // if neither left or right, display custom sprite and shut off LEDS
      // deal with LEDS
      digitalWrite(LEFT_LED, LOW);
      digitalWrite(RIGHT_LED, LOW);
      // deal with display
      display.clearDisplay();
      display.drawBitmap(48, 16, logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, SSD1306_WHITE); // clear prior screen and display custom sprite in center of screen
      display.display();
    }
  }
}


