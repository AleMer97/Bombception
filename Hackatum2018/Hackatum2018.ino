
//optional TODO: don't press button to end game, depending on, fake-no-go-zones

//INFORMATION:
//This Program does not work with MQTT beacause our ESP died and can't be flashed anymore

/*Dotmatrix*/
// 2-dimensional array of row pin numbers:
const int row[8] = {
  6,11,19,9,5,18,4,1  
};
// 2-dimensional array of column pin numbers:
const int col[8] = {
  10,3,2,7,0,8,12,13
};

/*Joystick*/
//x-axis;
const int xaxis = A0;
//y-axis:
const int yaxis = A1;

/*Button*/
const int button=A2;

/*External LED*/
const int ExtLed=A3;

/*Board init*/
int noGoZone[8][8];
//start position:
int x= 0;
int y= 0;
//winning position (currently unreachable):
int xsolution = 8;
int ysolution = 8;

/*refreshTimer:*/
int previousTime=0;
int currentTime=0;
int moveInterval=250;

/*blinking Pointer*/
int previousBlink=0;
int currentBlink=0;
int blinkInterval=moveInterval*2;
boolean isOn = true;

void setup() {  
  
  //choose start config of board
  randomSeed(analogRead(SCL));
  startConfig(random(0,2));
  x=0;
  y=0;
  
  // initialize the I/O pins as outputs iterate over the pins:
  for (int thisPin = 0; thisPin < 8; thisPin++) {
    // initialize the output pins:
    pinMode(col[thisPin], OUTPUT);
    pinMode(row[thisPin], OUTPUT);
    // take the col pins (i.e. the cathodes) high to ensure that the LEDS are off:
    digitalWrite(col[thisPin], HIGH);
    digitalWrite(row[thisPin], LOW);
  }
  
  pinMode(A2,INPUT);//button
  pinMode(A3,OUTPUT);//external LED
}

void loop() {
  //make cursor move;
  move();
  
  //make cursor blink;
  blink();

  //show no-go-zones
  noGoShow();

  //detect no-go-zones
  detect();
  
  //end game by pushbutton
  verify();

  //blinky LED
  ExtLED();
}

void move(){
  currentTime=millis();
  if(currentTime - previousTime >= moveInterval){
    int xval=1023-analogRead(xaxis);
    int yval=1023-analogRead(yaxis);

    //turn previous cursor off
    digitalWrite(col[x],HIGH);
    digitalWrite(row[y],LOW);
  
    if (xval>=1023-(512/2)){
      if (x!=7){
        x++;
      }
    }
    if (xval<=512/2){
      if(x!=0){
        x--;
      }
    }
  
    if (yval>=1023-(512/2)){
      if (y!=7){
        y++;
      }
    }
    if (yval<=512/2){
      if(y!=0){
        y--;
      }
    }  
    previousTime=currentTime;
  }
//cursor is shown by blink()
}

void blink(){
  currentBlink=millis();
  if(currentBlink - previousBlink >= blinkInterval){
    if(isOn){
      isOn=false;
    }else{
      isOn=true; 
    }
    previousBlink=currentBlink;
  }

  if(isOn) {            
    digitalWrite(row[y], HIGH);
    digitalWrite(col[x], LOW);
    digitalWrite(row[y], LOW);
    digitalWrite(col[x], HIGH);
  }
}

void noGoShow(){
  for (int x=0;x<8;x++){
    for (int y=0;y<8;y++){
      if(noGoZone[x][y]==1){
        digitalWrite(row[y],HIGH);
        digitalWrite(col[x],LOW);
        digitalWrite(row[y],LOW);
        digitalWrite(col[x],HIGH);
      }
    }
  }
}

void detect(){
  if(noGoZone[x][y]==1){
    lost();
  }
}
