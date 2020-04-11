
#include <Wire.h>
#include "rgb_lcd.h"
rgb_lcd lcd;
int numRGB = 0;
int nRGB;
//后电机引脚
int right_go   = 9; 
int right_back = 10;
int left_go    = 5;
int left_back  = 6;
//前电机
int Mright_go   = 11;
int Mright_back = 13;
int Mleft_go    = 3;
int Mleft_back  = 1;
//循迹模块引脚
int left_1  = 2;
int left_2  = 4;
int central = 12;
int right_3  = 7;
int right_4  = 8;

//循迹数组
int redReturn[5] = {0,0,0,0,0};

void setup() {
  lcd.begin(16, 2);
  pinMode(right_go  ,OUTPUT);
  pinMode(right_back,OUTPUT);
  pinMode(left_go   ,OUTPUT);
  pinMode(left_back ,OUTPUT);

  pinMode(Mright_go  ,OUTPUT);
  pinMode(Mright_back,OUTPUT);
  pinMode(Mleft_go   ,OUTPUT);
  pinMode(Mleft_back ,OUTPUT);
  lcd.begin(16, 2);
  lcd.setRGB(255, 255, 255);//白
  lcd.print("BIG DATE");
  lcd.setCursor(0, 1);
  lcd.print("      Laboratory");

}
 //RGB切换无延迟
void huanRGB(){
  if(nRGB==6000){
    lcd.setRGB(random(0,255),random(0,255),random(0,255));
    nRGB=0;
    }
  else{
    nRGB++;
    }
  }

//红外
void redValues(){
  redReturn[0] = digitalRead(left_1);
  redReturn[1] = digitalRead(left_2);
  redReturn[2] = digitalRead(central);
  redReturn[3] = digitalRead(right_3);
  redReturn[4] = digitalRead(right_4);
  }
void rrun(){
  
  digitalWrite(Mleft_back, LOW); 
  digitalWrite(Mright_back,LOW); 
  analogWrite(left_back,   0);   
  analogWrite(right_back,  0);   
  
  analogWrite(left_go,   255);   //左前进
  analogWrite(right_go,  255);   //右前进
  analogWrite(Mleft_go,  255);   //左前进
  analogWrite(Mright_go, 255);   //右前进  
  }
void maeRun(int sp){
  digitalWrite(Mleft_back, LOW); 
  digitalWrite(Mright_back,LOW); 
  analogWrite(left_go,   0);   
  analogWrite(right_go,  0);   
  
  analogWrite(left_go,   sp-10);   //左前进
  analogWrite(right_go,  sp);   //右前进
  analogWrite(Mleft_go,  sp);   //左前进
  analogWrite(Mright_go, sp);   //右前进  
  }
 //左转
void hitariRun(int sp){
  analogWrite(right_go,  sp);   //右前进
  analogWrite(right_back, 0);     //右后退 禁止
  
  analogWrite(left_back, sp);   //左后退
  analogWrite(left_go,    0);     //左前进 禁止

  digitalWrite(Mright_back,LOW); 
  analogWrite(Mright_go,  255);   //右前进

  digitalWrite(Mleft_back, LOW);   //左后退
  analogWrite(Mleft_go,   0); 
  }

  //右转
void migiRun(int sp){
  analogWrite(left_go,  sp);   //右前进
  analogWrite(left_back, 0);     //右后退 禁止
  
  analogWrite(right_back, sp);   //左后退
  analogWrite(right_go,    0);     //左前进 禁止
  
  digitalWrite(Mright_back, LOW);
  analogWrite(Mleft_go,    255);   //左前进
  
  digitalWrite(Mleft_back,  LOW);
  analogWrite(Mright_go,   0);   //右后退
  
  }
 void stopp(){
  digitalWrite(left_back,LOW);
  digitalWrite(left_go,LOW);
  digitalWrite(right_back,LOW);
  digitalWrite(right_go,LOW);

  digitalWrite(Mleft_back,LOW);
  digitalWrite(Mleft_go,LOW);
  digitalWrite(Mright_back,LOW);
  digitalWrite(Mright_go,LOW);
  }

void run(){
  //0检测到，1没测到
  //直行
  //11 0 11
  if((redReturn[0] == 1) && (redReturn[1] == 1) && (redReturn[2] == 0) 
  &&( redReturn[3] == 1) && (redReturn[4] == 1)){
      maeRun(255);
    }
  //左转四种
  // 10 1 11
  else if((redReturn[0] == 1) && (redReturn[1] == 0) && (redReturn[2] == 1) 
  &&( redReturn[3] == 1) && (redReturn[4] == 1)){
      hitariRun(140);
      migiRun(40);
  }
  //01 1 11
  else if((redReturn[0] == 0) && (redReturn[1] == 1) && (redReturn[2] == 1) 
  &&( redReturn[3] == 1) && (redReturn[4] == 1)){
     hitariRun(200);
  }
  //00 1 11
  else if((redReturn[0] == 0) && (redReturn[1] == 0) && (redReturn[2] == 1) 
  &&( redReturn[3] == 1) && (redReturn[4] == 1)){
      hitariRun(200);
  }
  //00 0 11
  else if((redReturn[0] == 0) && (redReturn[1] == 0) && (redReturn[2] == 0) 
  &&( redReturn[3] == 1) && (redReturn[4] == 1)){
      hitariRun(200);
  }
  //大左转
  //00 0 01
  else if((redReturn[0] == 0) && (redReturn[1] == 0) && (redReturn[2] == 0) 
  &&( redReturn[3] == 0) && (redReturn[4] == 1)){
      hitariRun(200);
  }
  //右转四种
  //11 1 01
  else if((redReturn[0] == 1) && (redReturn[1] == 1) && (redReturn[2] == 1) 
  &&( redReturn[3] == 0) && (redReturn[4] == 1)){

      migiRun(140);
      hitariRun(40);
  }
  
  //11 1 10
  else if((redReturn[0] == 1) && (redReturn[1] == 1) && (redReturn[2] == 1) 
  &&( redReturn[3] == 1) && (redReturn[4] == 0)){
      migiRun(200);
  }
  //11 1 00
  else if((redReturn[0] == 1) && (redReturn[1] == 1) && (redReturn[2] == 1) 
  &&( redReturn[3] == 0) && (redReturn[4] == 0)){
      migiRun(200);
  }
  //11 0 00
  else if((redReturn[0] == 1) && (redReturn[1] == 1) && (redReturn[2] == 0) 
  &&( redReturn[3] == 0) && (redReturn[4] == 0)){
      migiRun(200);
  }
  //10 0 00
  else if((redReturn[0] == 1) && (redReturn[1] == 0) && (redReturn[2] == 0) 
  &&( redReturn[3] == 0) && (redReturn[4] == 0)){
      migiRun(200);
  }
  //00 0 00
   else if((redReturn[0] == 0) && (redReturn[1] == 0) && (redReturn[2] == 0) 
  &&( redReturn[3] == 0) && (redReturn[4] == 0)){
      stopp();
  }
  else{
    maeRun(240);
    }
}
void loop() {
  huanRGB();
  redValues();
  if(millis()>=800){
    run();
    }
  else{
    rrun();
    }
  
}
