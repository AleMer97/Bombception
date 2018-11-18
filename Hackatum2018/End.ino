void verify(){
    if (x==xsolution && y==ysolution){
      //Win
      won();
  }
}

int startAgain;

void won(){
  //good job, you won!
  startAgain=millis();
  digitalWrite(ExtLed,LOW);
  delay(1000);
  //reset after 6 seconds
  while (millis()-startAgain<=5000){
    for(int x=0;x<8;x++){
      for(int y=0;y<8;y++){
        digitalWrite(row[y],LOW);
        digitalWrite(col[x],HIGH);
        delay(60);
      }
    }
  }
  //reset
  setup();
}

void lost(){
  startAgain=millis();
  //reset after 6 seconds
  digitalWrite(ExtLed,HIGH);
  delay(1);
  while (millis()-startAgain<=6000){
    for(int x=0;x<8;x++){
      for(int y=0;y<8;y++){
        digitalWrite(row[y],HIGH);
        digitalWrite(col[x],LOW);
        delay(60);
      }
    }
  }
  //reset
  setup();
}
