void nrfInit() {
  radio.begin();
  radio.openReadingPipe(0, nrfAddr);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  nrfState = millis();
}

void nrfLoop() {   

  if (radio.available()) {

    radio.read(&nrfBuf, sizeof(nrfBuf));
    TNormal = nrfBuf[0];
    HNormal = nrfBuf[1];

    if (TNormal != 0) {
      Serial.print("Sensor: Tn=");Serial.print(TNormal, DEC);  
      Serial.print(" Hn=");Serial.println(HNormal, DEC); 
      nrfState = millis(); 
      flgLostSensor = 0;
    }
    
  } else if (millis() - nrfState > 20000) {
      TNormal = 99;
      HNormal = 99;    
     
      if (flgLostSensor == 0) {
        Serial.println("Alert!");
        gsmSendSMS("Alert! Sensor disconnected!");
        flgLostSensor = 1;
      }
          
  }
 
}

