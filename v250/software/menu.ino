void menuInit() {
  lcd.init();
  lcd.backlight();
  lcd.createChar(1, degree);
}

void menuLogo() {
  lcd.setCursor(0, 0);
  lcd.print(" DOMOVOY BOYLER ");  
}

void menuMain() {

  char str1[16];

  menuLogo();
 
  sprintf(str1, "Tn: %02d\1C Hn: %02d%%", TNormal, HNormal);
  lcd.setCursor(0, 1); lcd.print(str1);

}

void menuSetTNormal() {

  lcd.noBlink();
  menuLogo();
  lcd.setCursor(0, 1);
  lcd.print(" Tnormal: ");
  lcd.setCursor(12, 1);
  lcd.print("\1C     ");

  char tmpStr[3] = "00";
  sprintf(tmpStr, "%.2d", defTNormal);
  
  byte tmpTNormal = defTNormal;
  
  stredit(tmpStr, 10, 1);

  defTNormal = atoi(tmpStr);

  if (defTNormal != tmpTNormal) {
    EEPROM.write(romTNormal, defTNormal);  
  }
  
  menuState++;

}

void menuSetTLow() {

  lcd.noBlink();
  menuLogo();
  lcd.setCursor(0, 1);
  lcd.print("   Tlow: ");
  lcd.setCursor(11, 1);
  lcd.print("\1C     ");

  char tmpStr[3] = "00";
  sprintf(tmpStr, "%.2d", defTLow);
  
  byte tmpTLow = defTLow;
  
  stredit(tmpStr, 9, 1);

  defTLow = atoi(tmpStr);

  if (defTLow != tmpTLow) {
    EEPROM.write(romTLow, defTLow);  
  }
  
  menuState++;

}

void menuSetTAlert() {

  lcd.noBlink();
  menuLogo();
  lcd.setCursor(0, 1);
  lcd.print("  Talert: ");
  lcd.setCursor(12, 1);
  lcd.print("\1C     ");

  char tmpStr[3] = "00";
  sprintf(tmpStr, "%.2d", defTAlert);
  
  byte tmpTAlert = defTAlert;
  
  stredit(tmpStr, 10, 1);

  defTAlert = atoi(tmpStr);

  if (defTAlert != tmpTAlert) {
    EEPROM.write(romTAlert, defTAlert);  
  }
  
  menuState++;

}

void menuSetAlone() {

  lcd.noBlink();
  menuLogo();
  lcd.setCursor(0, 1);
  lcd.print("   Alone: ");
  lcd.print(flgAlone);
  lcd.print("     ");
  
  char Key = kpd.getKey();  

  if (Key == '*') {
    flgAlone = (flgAlone - 1) * (-1);
    lcd.setCursor(10, 1);
    lcd.print(flgAlone);
  }

  if (Key == '0') {
    flgAlone = 0;
    lcd.setCursor(10, 1);
    lcd.print(flgAlone);
  }

  if (Key == '1') {
    flgAlone = 1;
    lcd.setCursor(10, 1);
    lcd.print(flgAlone);
  }

  if (Key == '#') {
      menuState++;
  }
  
}
void menuSetPhoneNum() {

  menuLogo();
  lcd.setCursor(0, 1);
  lcd.print("TEL:+");
  lcd.print(defPhone);
  lcd.setCursor(5, 1);

  char tmpPhone[12] = "00000000000";

  strcpy(tmpPhone, defPhone);

  stredit(defPhone, 5, 1);

  if (strcmp(defPhone, tmpPhone) != 0) {
    romWriteStr(defPhone, romPhone, 11);
  }
    
  menuState++;
  
}

void menuLoop() {

  char Key =   kpd.getKey();

  if (Key == '#') {
    menuState++;
  }

  if (menuState > 6) {
    menuState = 1;
  }

  if (menuState == 1) {
    menuMain();  
  }
  
  if (menuState == 2) {
    menuSetTNormal();  
  }

  if (menuState == 3) {
    menuSetTLow();  
  }
  
  if (menuState == 4) {
    menuSetTAlert();  
  }

  if (menuState == 5) {
    menuSetAlone();  
  }

  if (menuState == 6) {
    menuSetPhoneNum();  
  }

}
