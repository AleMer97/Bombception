//timer for LED
int LedLast;
int LedCurrent;
//set to 0 to have it continuous
int Blinkyness=random(100,2000);

void ExtLED(){
  LedCurrent=millis();
  if (LedCurrent - LedLast >= Blinkyness){
    digitalWrite(ExtLed,HIGH);
    Blinkyness=random(100,700);
    LedLast=LedCurrent;
  }
  if((LedCurrent - LedLast)*2 >= Blinkyness){
    digitalWrite(ExtLed,LOW);
  }
}
