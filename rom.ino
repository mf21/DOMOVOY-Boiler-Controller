void romInit() {

  defTNormal = EEPROM.read(romTNormal);
  defTLow    = EEPROM.read(romTLow);
  defTAlert  = EEPROM.read(romTAlert);

  if (defTNormal == 255) {
    defTNormal = 0;
  }

  if (defTLow == 255) {
    defTLow = 0;
  }
  
  if (defTAlert == 255) {
    defTAlert = 0;
  }

//  Serial.print("rom: defTNormal=");
//  Serial.println(defTNormal);
//  Serial.print("rom: defTLow=");
//  Serial.println(defTLow);
//  Serial.print("rom: defTAlert=");
//  Serial.println(defTAlert);
  
  romReadStr(defPhone, romPhone, 11);

//  Serial.print("rom: defPhone=");
//  Serial.println(defPhone);
  
}

void romReadStr(char *romStr, int romOffset, int romCount) {

  for (int i=romOffset; i<=romCount+2; i++) {
    romStr[i-romOffset] = EEPROM.read(i);
    if (romStr[i-romOffset] == 255) {
      romStr[i-romOffset] = 0;
    }
  }

}

void romWriteStr(char *romStr, int romOffset, int romCount) {

  for (int i=romOffset; i<=romCount+2; i++) {
    EEPROM.write(i, romStr[i-romOffset]);
  }

}

