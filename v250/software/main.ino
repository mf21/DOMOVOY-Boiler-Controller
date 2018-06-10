void mainLoop() {
  
  if ((TNormal < defTAlert) && (flgAlert == 0)) {
    Serial.println("alert: TNormal < " + String(defTAlert));
    gsmSendSMS("Alert! TNormal < " + String(defTAlert));
    flgAlert = 1;
  }

  if ((TNormal > defTAlert) && (flgAlert == 1)) {
    Serial.println("info: TNormal > TAlert ");
    flgAlert = 0;
  }
  
  if (flgAlone == 0) {

    if ((TNormal < defTNormal) && (flgRelayOn == 0)) {
      PORTD |= 1 << 6; //digitalWrite(6, HIGH);
      Serial.println("info: Relay is on");
      flgRelayOn = 1;
    }

    if ((TNormal > defTNormal) && (flgRelayOn == 1)) {
      PORTD &= ~(1 << 6); //digitalWrite(6, LOW);
      Serial.println("info: Relay is off");
      flgRelayOn = 0;
    }

  } else {

    if ((TNormal < defTLow) && (flgRelayOn == 0)) {
      PORTD |= 1 << 6; //digitalWrite(6, HIGH);
      Serial.println("info: Relay is on");
      flgRelayOn = 1;
    }

    if ((TNormal > defTLow) && (flgRelayOn == 1)) {
      PORTD &= ~(1 << 6); //digitalWrite(6, LOW);
      
      Serial.println("info: Relay is off");
      flgRelayOn = 0;
    }

  }

}

