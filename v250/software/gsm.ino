void gsmInit() {

  gsmSerial.begin(9600);
  lcd.setCursor(0, 0);
  lcd.print("    STARTING    ");

  while(gsmSerial.available() == 0);
  
  if (gsmResponse().indexOf("MODEM") > -1) {
    while(gsmSerial.available() == 0);
    gsmResponse();
  }

  gsmSerial.println("AT+CMEE=2");       // Extended ERROR report
  while(gsmSerial.available() == 0);
  gsmResponse();

  gsmSerial.println("AT+CLIP=1");       // Включить АОН
  while(gsmSerial.available() == 0);
  gsmResponse();
  
  gsmSerial.println("AT+CMGF=1");       // Текстовый режим sms
  while(gsmSerial.available() == 0);
  gsmResponse();
  
  gsmSerial.println("AT+CSCS=\"GSM\""); // ASCII кодировка
  while(gsmSerial.available() == 0);
  gsmResponse();
  
  gsmSerial.println("AT+CNMI=2,2");     // Отображать уведомления об sms
  while(gsmSerial.available() == 0);
  gsmResponse();

  delay(2000);
  
  gsmSerial.println("AT+CMGD=1,4");     // Удалить все сообщения
  while(gsmSerial.available() == 0);
  gsmResponse();

  gsmSerial.println("AT+CEER");     // Удалить все сообщения
  while(gsmSerial.available() == 0);
  gsmResponse();
      
}

String gsmResponse() {

  char gsmCh = ' ';
  String gsmResult = "";

  while (gsmSerial.available() > 0) {  
    gsmCh = gsmSerial.read();
    gsmResult += char(gsmCh); //собираем принятые символы в строку
    delay(3);
  }

  if (gsmResult != "") {
    Serial.print("Modem: ");
    Serial.println(gsmResult);
  }

  return gsmResult;
  
}

void gsmSendSMS(String gsmText) {
  
  gsmSerial.println("AT+COPS?");
  while(gsmSerial.available() == 0);
  gsmResponse();
  gsmSerial.println("AT+CMGS=\"+" + String(defPhone) + "\"");
  while(gsmSerial.available() == 0);
  gsmResponse();
  gsmSerial.print(gsmText);
  while(gsmSerial.available() == 0);
  gsmResponse();
  gsmSerial.print((char)26);
  while(gsmSerial.available() == 0);
  gsmResponse();
  Serial.println("SMS send OK");
}

void gsmCheckSMS() {

  String gsmCommand = gsmResponse();
  
  if (gsmCommand.indexOf("+CMT") == -1) {
    return;      
  }

  if (gsmCommand.indexOf("check") > -1) {  
    gsmSerial.println("AT");
    while(gsmSerial.available() == 0);
    gsmResponse();
    gsmSendSMS("Tcurrent=" + String((byte)TNormal) + "°C\n"+"Tn=" + String(defTNormal) + "°C\n"+"Tl=" + String(defTLow) + "°C\n"+"Ta=" + String(defTAlert) + "°C");      
    Serial.println("Tcurrent=" + String((byte)TNormal) + "°C\n"+"Tn=" + String(defTNormal) + "°C\n"+"Tl=" + String(defTLow) + "°C\n"+"Ta=" + String(defTAlert) + "°C");
  }

  if (gsmCommand.indexOf("settn=") > -1) {
    byte Pos = gsmCommand.indexOf("settn=") + 6;
    defTNormal = gsmCommand.substring(Pos).toInt();
    EEPROM.write(romTNormal, defTNormal);
    Serial.print("defTNormal=");Serial.println(defTNormal);
    
    gsmSendSMS("OK. TNormal=" + String(defTNormal) + "°C");      
  }

  if (gsmCommand.indexOf("settl=") > -1) {
    byte Pos = gsmCommand.indexOf("settl=") + 6;
    defTLow = gsmCommand.substring(Pos).toInt();
    EEPROM.write(romTLow, defTLow);
    Serial.print("defTLow=");Serial.println(defTLow);
    
    gsmSendSMS("OK. TLow=" + String(defTLow) + "°C");      
  }

  if (gsmCommand.indexOf("setta=") > -1) {
    byte Pos = gsmCommand.indexOf("setta=") + 6;
    defTAlert = gsmCommand.substring(Pos).toInt();
    EEPROM.write(romTAlert, defTAlert);
    Serial.print("defTAlert=");Serial.println(defTAlert);
    
    gsmSendSMS("OK. TAlert=" + String(defTAlert) + "°C");      
  }

  if (gsmCommand.indexOf("setmode=home") > -1) {
    flgAlone = 0;
    gsmSendSMS("OK. flgAlone=home");
    Serial.println("info: flgAlone=home");      
  }
    
  if (gsmCommand.indexOf("setmode=alone") > -1) {
    flgAlone = 1;
    gsmSendSMS("info: flgAlone=alone");      
    Serial.println("info: flgAlone=alone");      
  }

}

void gsmLoop() {

  gsmCheckSMS();
    
}

