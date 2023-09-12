#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>
//#include <RH_RF95.h>
// Singleton instance of the radio driver
RH_RF95 rf96;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using I2C
//#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
//#define SCREEN_ADDRESS 0x3C
//Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Declaration for SSD1306 display connected using software SPI:
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
Servo myservo;
int ir_s1 = 5;
int ir_s2 = 6;
int ir_s3 = 7;

int S1=0,S2=0,S3=0;

int ir_enter=2;
int ir_back=4;


int slot=3;

bool flag1 = 0;
bool flag2 = 0;


void setup()
{
  Serial.begin(9600);

  // while (!Serial) ; // Wait for serial port to be available
  // if (!rf96.init())
  //   Serial.println("init failed");
  
  pinMode(ir_s1, INPUT);
  pinMode(ir_s2, INPUT);
  pinMode(ir_s3, INPUT);
  pinMode(ir_enter, INPUT);
  pinMode(ir_back, INPUT);
  

  myservo.attach(3);
  myservo.write(90);

  Read_Sensor();

  int total = S1+S2+S3;
  slot = slot-total; 
  // initialize the OLED object
  //if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
   // Serial.println(F("SSD1306 allocation failed"));
   // for(;;); // Don't proceed, loop forever
 // }

  // Uncomment this if you are using SPI
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Clear the buffer.
  display.clearDisplay();

  // Display Text
  // display.setTextSize(1);
  // display.setTextColor(WHITE);
  // display.setCursor(0,28);
  // display.println("Hello world!");
  // display.display();
  // delay(2000);
  // display.clearDisplay();

  // // Display Inverted Text
  // display.setTextColor(BLACK, WHITE); // 'inverted' text
  // display.setCursor(0,28);
  // display.println("Hello world!");
  // display.display();
  // delay(2000);
  // display.clearDisplay();

  // // Changing Font Size
  // display.setTextColor(WHITE);
  // display.setCursor(0,24);
  // display.setTextSize(2);
  // display.println("Hello!");
  // display.display();
  // delay(2000);
  // display.clearDisplay();

  // // Display Numbers
  // display.setTextSize(1);
  // display.setCursor(0,28);
  // display.println(123456789);
  // display.display();
  // delay(2000);
  // display.clearDisplay();

  // // Specifying Base For Numbers
  // display.setCursor(0,28);
  // display.print("0x"); display.print(0xFF, HEX); 
  // display.print("(HEX) = ");
  // display.print(0xFF, DEC);
  // display.println("(DEC)"); 
  // display.display();
  // delay(2000);
  // display.clearDisplay();

  // // Display ASCII Characters
  // display.setCursor(0,24);
  // display.setTextSize(2);
  // display.write(3);
  // display.display();
  // delay(2000);
  // display.clearDisplay();

  // // Scroll full screen
  // display.setCursor(0,0);
  // display.setTextSize(1);
  // display.println("Full");
  // display.println("screen");
  // display.println("scrolling!");
  // display.display();
  // display.startscrollright(0x00, 0x07);
  // delay(2000);
  // display.stopscroll();
  // delay(1000);
  // display.startscrollleft(0x00, 0x07);
  // delay(2000);
  // display.stopscroll();
  // delay(1000);    
  // display.startscrolldiagright(0x00, 0x07);
  // delay(2000);
  // display.startscrolldiagleft(0x00, 0x07);
  // delay(2000);
  // display.stopscroll();
  // display.clearDisplay();

  // // Scroll part of the screen
  // display.setCursor(0,0);
  // display.setTextSize(1);
  // display.println("Scroll");
  // display.println("some part");
  // display.println("of the screen.");
  // display.display();
  // display.startscrollright(0x00, 0x00);

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("car parking ");
  display.setCursor(0,20);
  display.println("system ");
  display.display();
  delay(4000);
  display.clearDisplay();
}

void loop() {
   Read_Sensor();

display.setTextSize(1);
  display.setTextColor(WHITE);
display.setCursor(0,0);
  display.print("Have Slot: ");
  display.println(slot); 
   display.println("     ");
   display.display(); 

 display.setTextSize(1);
  display.setTextColor(WHITE);
 display.setCursor(0,15);
if(S1==1){display.println("S1:Fill "); display.display(); }
     else{display.println("S1:Empty"); display.display(); }

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,35);
if(S2==1){display.println("S2:Fill "); display.display(); }
     else{display.println("S2:Empty"); display.display(); }

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,55);
if(S3==1){display.println("S3:Fill "); display.display();}
     else{display.println("S3:Empty"); display.display(); }
  

if(digitalRead (ir_enter) == 0 && flag1==0){
if(slot>0){flag1=1;
if(flag2==0){myservo.write(180); slot = slot-1;}
}else{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
 display.println(" Sorry Parking Full ");
 display.display(); delay(2000);
}   
}

if(digitalRead (ir_back) == 0 && flag2==0){flag2=1;
if(flag1==0){myservo.write(180); if(slot<3)slot = slot+1;}
}

if(flag1==1 && flag2==1){
delay (1000);
myservo.write(90);
flag1=0, flag2=0;
}

delay(1000);   
display.clearDisplay();
///////////////////////////////////////////////////////
// Serial.println("Sending to rf96_server");
//   // Send a message to rf95_server
//   uint8_t data[] = "Hello I'm from lora!";
//   rf96.send(data, sizeof(data));
//   rf96.waitPacketSent();
//   // Now wait for a reply
//   uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
//   uint8_t len = sizeof(buf);
//   if (rf96.waitAvailableTimeout(3000))
//   {
//     // Should be a reply message for us now
//     if (rf96.recv(buf, &len))
//     {
//       Serial.print("got reply: ");
//       Serial.println((char*)buf);
//     }
//     else
//     {
//       Serial.println("recv failed");
//     }
//   }
//   else
//   {
//     Serial.println("No reply, is rf95_server running?");
//   }
//   delay(400);


}
void Read_Sensor(){
S1=0, S2=0, S3=0 ;

if(digitalRead(ir_s1) == 0){S1=1;}
if(digitalRead(ir_s2) == 0){S2=1;}
if(digitalRead(ir_s3) == 0){S3=1;}  
}
