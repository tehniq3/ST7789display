/*
 * ST7789 TFT display test
 * by Nicu FLORICA (niq_ro)
 */
 
#include <Adafruit_ADS1015.h> // AD converter
#include <Adafruit_GFX.h>     // Adafruit core graphics library
#include <Adafruit_ST7789.h>  // Adafruit hardware-specific library for ST7789


#define TFT_CS    6  // define chip select pin ST7789 TFT module
#define TFT_DC     10  // define data/command pin ST7789 TFT module
#define TFT_RST    9  // define reset pin, or set to -1 and connect to Arduino RESET pin
#define OLED_RESET 4       // Reset pin # (or -1 if sharing Arduino reset pin)


Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

char ver1[]      = "ST7789 display";
char ver2[]      = "test software";
char warn1[]     = "This analyzer";
char warn2[]     = "has no brain!";
char warn3[]     = "Use your own!";

float temperature = 0.;
int humidity = 0;

byte x, y, z, w;

void setup() {
  tft.init(240, 240, SPI_MODE3);
  tft.fillScreen(0x0000);
  tft.setRotation(2);
  tft.setTextWrap(false);                        // turn off text wrap option

  tft.fillRect(0,32,240,240,0x0000);
 // tft.setTextColor(0xFFFF, 0x0000);
  tft.setTextColor(ST77XX_YELLOW, ST77XX_BLACK);
  tft.setTextSize(2);

  tft.setCursor(10,35);
  tft.print(ver1);
  tft.setCursor(10,55);
  tft.print(ver2);
  delay(250);

/*
  tft.fillRect(0,32,240,240,0x0000);
  tft.setTextSize(3);
  tft.setCursor(0,80);
  tft.println(warn1);
  tft.print(warn2);
  tft.setCursor(0,170);
  tft.print(warn3);
  */
  delay(3000);

  tft.fillScreen(0x0000);
}

void loop() {
x = 0;
y = 50;
   temperature = random (-300,300)/10.;
   if (temperature < -10.) tft.setTextColor(ST77XX_BLUE, ST77XX_BLACK);
   if ((temperature >= -10.) and (temperature < 0.)) tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
   if ((temperature >= 0.) and (temperature < 15.)) tft.setTextColor(ST77XX_YELLOW, ST77XX_BLACK);
   if ((temperature >= 15.) and (temperature < 27.)) tft.setTextColor(ST77XX_GREEN, ST77XX_BLACK);
   if (temperature >= 27.) tft.setTextColor(ST77XX_RED, ST77XX_BLACK);  
   tft.setTextSize(6);  
   tft.setCursor(x,y);
   //if (temperature < 100) tft.print(F(" "));
   if (abs(temperature) < 10) tft.print(F(" "));
   if (temperature < 0)
      tft.print(F("-"));
   if (temperature > 0)
      tft.print(F("+"));    
   temperature = abs(temperature);   
    tft.print(temperature,1);
    tft.setCursor(200+x,y);
    tft.print(F("C"));
    tft.setCursor(183+x,y-7);
    tft.setTextSize(2);  
    tft.print(F("O"));

z = 0;
w = 150;
   humidity = random (0,101);
   if (humidity < 20.) tft.setTextColor(ST77XX_BLUE, ST77XX_BLACK);
   if ((humidity >= 20.) and (humidity < 30.)) tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
   if ((humidity >= 30.) and (humidity < 40.)) tft.setTextColor(ST77XX_GREEN, ST77XX_BLACK);
   if ((humidity >= 40.) and (humidity < 50.)) tft.setTextColor(ST77XX_YELLOW, ST77XX_BLACK);
   if (humidity >= 50.) tft.setTextColor(ST77XX_RED, ST77XX_BLACK);  
   tft.setTextSize(6);  
   tft.setCursor(z,w);
  if (humidity < 100) tft.print(F(" "));
  if (humidity < 10) tft.print(F(" "));  
    tft.print(humidity);
    tft.print(F("%RH"));
    
delay(500);
}  // end main loop
