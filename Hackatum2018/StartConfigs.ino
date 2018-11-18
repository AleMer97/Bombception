void startConfig(int s){
  //2 configs, but doubled by explosiveLED
  //init noGoZone
  for (int x=0;x<8;x++){
    for (int y=0;y<8;y++){
      noGoZone[x][y]=0;
    }
  }
  if (s==0) Config1();
  if (s==1) Config2();
}

void Config1(){
  noGoZone[1][0]=1;
  noGoZone[1][1]=1;
  noGoZone[2][2]=1;
  noGoZone[3][3]=1;
  noGoZone[4][2]=1;
  noGoZone[4][4]=1;
  noGoZone[3][6]=1;
  noGoZone[5][5]=1;
  noGoZone[6][3]=1;
  noGoZone[3][7]=1;

  xsolution=2;
  ysolution=0;
}

void Config2(){
  noGoZone[4][0]=1;
  noGoZone[4][1]=1;
  noGoZone[4][2]=1;
  noGoZone[4][3]=1;
  noGoZone[3][3]=1;
  noGoZone[5][3]=1;
  noGoZone[3][4]=1;
  noGoZone[3][5]=1;
  noGoZone[4][5]=1;
  noGoZone[5][5]=1;

  xsolution=4;
  ysolution=4;
}
