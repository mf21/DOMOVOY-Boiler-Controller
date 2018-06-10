/*
 *  Строчный редактор stredit
 *    EditStr - редактируемая строка
 *    MinX - позиция X на экране дисплея
 *    Y - позиция Y на экране дисплея
 *    keypadGetKey() - функцию необходимо переписать под конкретный метод ввода
 *    'B' - символ BackSpace, заменить на свой код символа
 *    'E' - символ Enter, заменить на свой код символа
 */

void stredit(char* EditStr, byte MinX = 0, byte Y = 0) {

  boolean Enabled = true;
  boolean Changed = true;
  byte X = MinX;
  byte MaxX = MinX + strlen(EditStr) - 1;
 
  lcd.blink();
    
  while (Enabled) {

    char Key = kpd.getKey();
  
    if (Key != 0) {
      if (Key == '*') {
        X--;
        if (X < MinX) {X = MaxX;}
        Changed = true;
      } else if (Key == '#') {
        Enabled = false;
      } else {
        EditStr[X-MinX] = Key;
        X++;
        if (X > MaxX) {X = MinX;}
        if (X < MinX) {X = MinX;}
        Changed = true;
      }
    }
    
    if (Changed) {
      lcd.noBlink();
      lcd.setCursor(MinX, Y);
      lcd.print(EditStr);
      lcd.setCursor(X, Y);
      lcd.blink();
      Changed = false;
    }
    
  }

  lcd.noBlink();
  
}

