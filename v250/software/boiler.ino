/*
  Memory mapping
  00     - TNormal preset
  01     - TLow preset
  02     - TAlert preset
  03..13 - defPhone preset
*/

#include <NeoSWSerial.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
#include <SPI.h>

#include <RF24.h>
#include <Keypad.h>

#define romTLow 1
#define romPhone 3
#define romTAlert 2
#define romTNormal 0

byte flgAlert = 0;
byte flgAlone = 0;
byte flgRelayOn = 0;
byte flgLostSensor = 0;

byte defTLow = 0;
byte defTAlert = 0;
byte defTNormal = 0;
char defPhone[12] = "00000000000";

char TNormal = 98;
char HNormal = 98;

const byte nrfAddr[6] = "KWL01";
byte nrfBuf[2] = "";
unsigned long nrfState;

byte menuState = 1;

byte degree[8] = {12, 18, 18, 18, 12, 0, 0, 0};

char keys[4][3] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}}; 

byte rowPins[4] = {A0, A1, A2, A3}; 
byte colPins[3] = {5, 4, 3}; 

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, 4, 3);
NeoSWSerial  gsmSerial(8, 7); 
LiquidCrystal_I2C lcd(0x3F, 16, 2);
RF24 radio(9, 10); // CE, CSN

void stredit(char *EditStr, byte MinX, byte Y);

void setup() {

  DDRD |= 1 << 6;

  Serial.begin(9600);
  Serial.println("DОМОВОЙ Бойлер ver. 2.5");
  Serial.println("");
  
  menuInit();
  romInit();
  gsmInit();
  nrfInit();
  
  Serial.println("OK");
  
}

void loop() {

  while(1) {
    gsmLoop();
    nrfLoop();
    menuLoop();
    mainLoop();
  }
  
}  
