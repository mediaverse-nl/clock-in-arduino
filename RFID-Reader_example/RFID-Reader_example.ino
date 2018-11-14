#include <U8g2lib.h>
#include <U8x8lib.h>

#include <deprecated.h>
#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <require_cpp11.h>

#include <RestClient.h>

#include <Arduino.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif


//this has changed.

#define SS_PIN D8 //Pin on WeMos D1 Mini
#define RST_PIN 15 // RST-PIN for RC522 - RFID - SPI - Modul GPIO15
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
U8G2_SSD1327_MIDAS_128X128_F_HW_I2C u8g2(U8G2_R2, /* reset=*/ U8X8_PIN_NONE);//for the oled screen
byte buzzerPin = 16;//defines buzzerpin 16 equals D0 on the wemos

void setup(){
  Serial.begin(115200);//begins the serial monitor for testing purposes
  u8g2.begin();//begins the oled screen
  SPI.begin();//begins the spi 
  mfrc522.PCD_Init();   // Initiate the RFID Reader.
  
  pinMode(buzzerPin, INPUT);
}
void connectionSucces(){
 
  u8g2.clearBuffer(); // clear the internal memory from the screen. 
  u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
  u8g2.drawStr(0,10,"the connection"); //print a message using the oled screen
  u8g2.drawStr(0,25,"has succesfully"); //print a message using the oled screen
  u8g2.drawStr(0,40,"connected"); //print a message using the oled screen
  u8g2.sendBuffer(); // transfer internal memory to the display
  delay(1000);  
}


void error(){
  //the error sounds 
  //the error message.
}

void buzzerErrorTone(){
 //tone(buzzerPin, 600, 1000);
}

////unkown card
//void unknown(){
//  
//}


void normalScreen(){
  //the normal screen
  u8g2.clearBuffer(); // clear the internal memory from the screen. 
  u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
  u8g2.drawStr(30,25,"scan your chip"); //print a message using the oled screen
  u8g2.sendBuffer(); // transfer internal memory to the display
  delay(1000);
    
}

//this looks for a new card that wis presented at a rfid
void NFCcardReader(){    
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return ;
  }else if ( ! mfrc522.PICC_ReadCardSerial()) {
    return ;
  }
  String content = "";
  byte letter;
  
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  String response = "";
  int Status;
 
  Serial.println(response);//this is the oine thing we need to print the byte value from the card.
  buzzerErrorTone();
  Serial.println(content);
  connectionSucces();
}


void loop() {
  
NFCcardReader();
}
