
#include <SoftwareSerial.h>
#include "RoboClaw.h"

SoftwareSerial serial(5,6);
SoftwareSerial serial2(3,4);
RoboClaw roboclaw(&serial,10000);
RoboClaw roboclaw2(&serial2,10000);

int const JOYSTICK_AXIS_X = A0;
int const JOYSTICK_AXIS_Y = A1;

#define address 0x80
#define address2 0x81

void setup() {
 Serial.begin(9600);
 
 roboclaw.begin(38400);
 roboclaw2.begin(38400);
  
}

void loop() {
  unsigned long speedX=velX(analogRead(JOYSTICK_AXIS_X));
  unsigned long speedY=velY(analogRead(JOYSTICK_AXIS_Y));
  
  Serial.print("X="),Serial.println(speedX);
  Serial.print("Y="),Serial.println(speedY);
  
  if(speedX>64 && (speedY==61 || speedY==62))
    adelante(speedX);
  else if(speedX<63 && (speedY==61 || speedY==62))
    atras(speedX);
  else if((speedX==64 || speedX==63) && speedY>62 )
    rotacionDerecha(speedY+2);
  else if((speedX==64 || speedX==63) && speedY<62 )
    rotacionIzquierda(speedY+2);
  else if(speedX>64 && speedY>=62)
    giroDerechaF(speedX);
  else if(speedX>=64 && speedY<62)
    giroIzquierdaF(speedX);
  else if(speedX<64 && speedY<62)
    giroIzquierdaB(speedX); 
  else if(speedX<64 && speedY>62)
    giroDerechaB(speedY);   
  else{
    parar();
  }
}
unsigned long velX(float vel){
  unsigned long velocidadX = (vel*128)/1023;
  return velocidadX;
 }
unsigned long velY(float vel){
  unsigned long velocidadY = (vel*128)/1023;
  return velocidadY;
}
void parar(){
  roboclaw.BackwardM1(address,0);
  roboclaw.BackwardM2(address,0);
  roboclaw2.BackwardM1(address2,0);
  roboclaw2.BackwardM2(address2,0);
}
void adelante(float x){
  int xnew=(x-64)*2;
  if(xnew>=128)
    xnew=127;
  roboclaw.BackwardM1(address,xnew);
  roboclaw.BackwardM2(address,xnew);
  roboclaw2.BackwardM1(address2,xnew);
  roboclaw2.BackwardM2(address2,xnew);
}
void atras(float x){
  int xnew=((63-x)*2)+1;
  roboclaw.ForwardM1(address,xnew);
  roboclaw.ForwardM2(address,xnew);
  roboclaw2.ForwardM1(address2,xnew);
  roboclaw2.ForwardM2(address2,xnew);
}
void rotacionDerecha(float y){
  int ynew;
  ynew=(y-64)*2;
  if(ynew>=128)
    ynew=127;
  roboclaw.ForwardM1(address,ynew);
  roboclaw.BackwardM2(address,ynew);
  roboclaw2.ForwardM1(address2,ynew);
  roboclaw2.BackwardM2(address2,ynew);
}
void rotacionIzquierda(float y){
  int ynew=(64-y)*2-1;
  roboclaw.BackwardM1(address,ynew);
  roboclaw.ForwardM2(address,ynew);
  roboclaw2.BackwardM1(address2,ynew);
  roboclaw2.ForwardM2(address2,ynew);
}
void giroDerechaF(float x){
  x=(x-64)*2;
  if(x>=128)
    x=127.0;
  int lento=x*0.75;
  roboclaw.BackwardM1(address,lento);
  roboclaw.BackwardM2(address,x);
  roboclaw2.BackwardM1(address2,lento);
  roboclaw2.BackwardM2(address2,x);
}
void giroIzquierdaF(float x){
  x=(x-64)*2;
  if(x>=128)
    x=127.0;
  int lento=x*0.75;
  roboclaw.BackwardM1(address,x);
  roboclaw.BackwardM2(address,lento);
  roboclaw2.BackwardM1(address2,x);
  roboclaw2.BackwardM2(address2,lento);
}
void giroDerechaB(float y){
  y=abs(abs((64-y)*2)-1);
  int lento=y*0.75;
  roboclaw.ForwardM1(address,lento);
  roboclaw.ForwardM2(address,y);
  roboclaw2.ForwardM1(address2,lento);
  roboclaw2.ForwardM2(address2,y);
}
void giroIzquierdaB(float x){
  x=abs(abs((64-x)*2)-1);
  int lento=x*0.75;
  roboclaw.ForwardM1(address,x);
  roboclaw.ForwardM2(address,lento);
  roboclaw2.ForwardM1(address2,x);
  roboclaw2.ForwardM2(address2,lento);
}
