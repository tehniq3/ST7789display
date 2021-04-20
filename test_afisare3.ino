/*
 * ST7789 TFT display test
 * by Nicu FLORICA (niq_ro)
 */
 
#include <Adafruit_GFX.h>     // Adafruit core graphics library
#include <Adafruit_ST7789.h>  // Adafruit hardware-specific library for ST7789

#define TFT_CS     6  // define chip select pin ST7789 TFT module
#define TFT_DC    10  // define data/command pin ST7789 TFT module
#define TFT_RST    9  // define reset pin, or set to -1 and connect to Arduino RESET pin
#define OLED_RESET 4  // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

char intro1[]      = "ST7789";
char intro2[]      = "test software";
char intro3[]      = "by niq_ro";
char intro4[]      = " arduinotehniq.com ";
char intro5[]      = " nicuflorica.blogspot.ro ";

float temperature = 0.;
int humidity = 0;

byte b, c, x, y, z, w;

int trvolt = 0;  // step 0..1023 (0..5V)
int proc = 100;
unsigned int sample = 0;
int proc0 = 0;  // battery voltage (mV)
float proc1 = 0.; // battery voltage (V)

void setup() {
  tft.init(240, 240, SPI_MODE3);
  tft.fillScreen(0x0000);  // clear the screen (ver.2)
  tft.setRotation(2);
  tft.setTextWrap(false);                        // turn off text wrap option

  tft.fillRect(0,0,240,240,0x0000);  // clear the screen (ver.2)
  tft.setTextColor(ST77XX_YELLOW, ST77XX_BLACK);
  tft.setTextSize(4);
  tft.setCursor(45,15);
  tft.print(intro1);
  delay(500);
  tft.setTextColor(ST77XX_RED, ST77XX_BLACK);
  tft.setTextSize(3);
  tft.setCursor(5,55);
  tft.print(intro2);
  delay(500);
  tft.setTextColor(ST77XX_GREEN, ST77XX_BLACK);
  tft.setTextSize(2);
  tft.setCursor(60,85);
  tft.print(intro3);
  delay(500);
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_BLUE, ST77XX_WHITE);
  tft.setCursor(10,110);
  tft.print(intro4);
  delay(500);
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
  tft.setCursor(50,135);
  tft.print(intro5);

  delay(5000);

  tft.fillScreen(0x0000);
}

void loop() {
tft.fillScreen(0x0000);  // clear the screen

x = 0;
y = 50;
   for (int i = -90; i <= 90; i++) {
   temperature = i/3.;
   showTemp (x, y, temperature);
   delay(50);
   }
delay(2000);

tft.fillScreen(0x0000);
z = 0;
w = 50;
   for (int i = 0; i <= 100; i++) {
   humidity = i;
   showHumy (z, w, humidity);
   delay(50);  
   }
delay(2000);

tft.fillScreen(0x0000);
b = 60;
c = 50;
   for (int i = 710; i <= 870; i++) {
   showBat(i);
   delay(100);  
   }
delay(2000);



tft.fillScreen(0x0000);
// full random
for (int i = 0; i <= 200; i++) {
x = 0;
y = 50;
   temperature = random (-300,300)/10.;
   showTemp (x, y, temperature);
z = 0;
w = 150;
   humidity = random (0,101);
   showHumy (z, w, humidity);
b = 80;
c = 120;
   trvolt = random(0,1024);
   showBat(trvolt);
  
delay(500);
}
delay(2000);
}  // end main loop


void showTemp (byte a, byte b, float c)
{
  if (c < -10.) tft.setTextColor(ST77XX_BLUE, ST77XX_BLACK);
   if ((c >= -10.) and (c < 0.)) tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
   if ((c >= 0.) and (c < 15.)) tft.setTextColor(ST77XX_YELLOW, ST77XX_BLACK);
   if ((c >= 15.) and (c < 27.)) tft.setTextColor(ST77XX_GREEN, ST77XX_BLACK);
   if (c >= 27.) tft.setTextColor(ST77XX_RED, ST77XX_BLACK);  
   tft.setTextSize(6);  
   tft.setCursor(a,b);
   //if (c < 100) tft.print(" ");
   if (abs(c) < 10) tft.print(" ");
   if (c < 0)
      tft.print("-");
   if (c > 0)
      tft.print("+");   
   if (c == 0)
      tft.print(" ");   
   c = abs(c);   
    tft.print(c,1);
    tft.setCursor(200+a,b);
    tft.print("C");
    tft.setCursor(183+a,b-7);
    tft.setTextSize(2);  
    tft.print("O");
}

void showHumy (byte a, byte b, int c)
{
   if (c < 20.) tft.setTextColor(ST77XX_BLUE, ST77XX_BLACK);
   if ((c >= 20.) and (c < 30.)) tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
   if ((c >= 30.) and (c < 40.)) tft.setTextColor(ST77XX_GREEN, ST77XX_BLACK);
   if ((c >= 40.) and (c < 50.)) tft.setTextColor(ST77XX_YELLOW, ST77XX_BLACK);
   if (c >= 50.) tft.setTextColor(ST77XX_RED, ST77XX_BLACK);  
   tft.setTextSize(6);  
   tft.setCursor(a,b);
   if (c < 100) tft.print(" ");
   if (c < 10) tft.print(" ");  
    tft.print(c);
    tft.print("%RH");
}

void showBat(int sample)
{
proc0 = map(sample, 0, 1023, 0, 5000);  // voltage (mV)
proc1 = proc0/1000.;  // voltage (V)
proc = map(proc0, 3700, 4200, 0, 100); // voltage to percent
if (proc < 0) proc = 0;

if (proc <= 15)
{
  tft.drawLine(b, c, b+44, c, ST77XX_RED);
  tft.drawLine(b, c, b, c+13, ST77XX_RED);
  tft.drawLine(b, c+13, b+44, c+13, ST77XX_RED);
  tft.drawLine(b+44, c, b+44, c+4, ST77XX_RED);
  tft.drawLine(b+44, c+4, b+47, c+4, ST77XX_RED);
  tft.drawLine(b+47, c+4, b+47, c+8, ST77XX_RED);
  tft.drawLine(b+47, c+8, b+44, c+8, ST77XX_RED);
  tft.drawLine(b+44, c+8, b+44, c+12, ST77XX_RED);
  tft.fillRect(b+2, c+2, 7, 10, ST77XX_BLACK);
  tft.fillRect(b+12, c+2, 7, 10, ST77XX_BLACK);
  tft.fillRect(b+22, c+2, 7, 10, ST77XX_BLACK);
  tft.fillRect(b+32, c+2, 7, 10, ST77XX_BLACK);
  tft.setTextColor(ST77XX_YELLOW, ST77XX_BLACK);
  tft.setTextColor(ST77XX_RED, ST77XX_BLACK);
}
else
{
  tft.drawLine(b, c, b+44, c, ST77XX_WHITE);
  tft.drawLine(b, c, b, c+13, ST77XX_WHITE);
  tft.drawLine(b, c+13, b+44, c+13, ST77XX_WHITE);
  tft.drawLine(b+44, c, b+44, c+4, ST77XX_WHITE);
  tft.drawLine(b+44, c+4, b+47, c+4, ST77XX_WHITE);
  tft.drawLine(b+47, c+4, b+47, c+8, ST77XX_WHITE);
  tft.drawLine(b+47, c+8, b+44, c+8, ST77XX_WHITE);
  tft.drawLine(b+44, c+8, b+44, c+12, ST77XX_WHITE);
}
if ((proc > 15) and (proc <= 40))
{
  tft.fillRect(b+2, c+2, 7, 10, ST77XX_YELLOW);
  tft.fillRect(b+12, c+2, 7, 10, ST77XX_BLACK);
  tft.fillRect(b+22, c+2, 7, 10, ST77XX_BLACK);
  tft.fillRect(b+32, c+2, 7, 10, ST77XX_BLACK);
  tft.setTextColor(ST77XX_YELLOW, ST77XX_BLACK);
}
if ((proc > 40) and (proc <= 60))
{
  tft.fillRect(b+2, c+2, 7, 10, ST77XX_GREEN);
  tft.fillRect(b+12, c+2, 7, 10, ST77XX_GREEN);
  tft.fillRect(b+22, c+2, 7, 10, ST77XX_BLACK);
  tft.fillRect(b+32, c+2, 7, 10, ST77XX_BLACK);
  tft.setTextColor(ST77XX_GREEN, ST77XX_BLACK);
}
if ((proc > 60) and (proc <= 80))
{
  tft.fillRect(b+2, c+2, 7, 10, ST77XX_CYAN);
  tft.fillRect(b+12, c+2, 7, 10, ST77XX_CYAN);
  tft.fillRect(b+22, c+2, 7, 10, ST77XX_CYAN);
  tft.fillRect(b+32, c+2, 7, 10, ST77XX_BLACK);
  tft.setTextColor(ST77XX_CYAN, ST77XX_BLACK);
}
if ((proc > 80) and (proc <= 100))
{
  tft.fillRect(b+2, c+2, 7, 10, ST77XX_BLUE);
  tft.fillRect(b+12, c+2, 7, 10, ST77XX_BLUE);
  tft.fillRect(b+22, c+2, 7, 10, ST77XX_BLUE);
  tft.fillRect(b+32, c+2, 7, 10, ST77XX_BLUE);
  tft.setTextColor(ST77XX_BLUE, ST77XX_BLACK);
}
if (proc >100)
{
  tft.fillRect(b+2, c+2, 7, 10, ST77XX_MAGENTA);
  tft.fillRect(b+12, c+2, 7, 10, ST77XX_MAGENTA);
  tft.fillRect(b+22, c+2, 7, 10, ST77XX_MAGENTA);
  tft.fillRect(b+32, c+2, 7, 10, ST77XX_MAGENTA);
  tft.setTextColor(ST77XX_MAGENTA, ST77XX_BLACK);
}
 // tft.setCursor(0,0);
 // tft.print(F(" "));
  tft.setTextSize(2);
  tft.setCursor(b-55,c);
  if (proc < 100) tft.print(" ");
  if (proc < 10) tft.print(" ");
  tft.print(proc,1);
  tft.print("%");
  tft.setCursor(b+55,c);
  tft.print(proc1);
  tft.print("V");
}
