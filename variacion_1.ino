//definicion de pins
const int motorPin1 = 13;    // 28BYJ48 In1
const int motorPin2 = 11;    // 28BYJ48 In2
const int motorPin3 = 12;   // 28BYJ48 In3
const int motorPin4 = 10;   // 28BYJ48 In4
#include <Stepper.h>
int valor = Serial.read();
//definitions for each command to be recieved via serial port
#define COMMAND_1 '1'
#define COMMAND_3 '3'
#define COMMAND_4 '4'
#define COMMAND_6 '6'
#define COMMAND_7 '7'
#define COMMAND_9 '9'
#define COMMAND_8 '8'
#define COMMAND_2 '2'

#define COMMAND_STOP ' '
                   
//definicion variables
int motorSpeed = 1200;   //variable para fijar la velocidad
int stepCounter = 0;     // contador para los pasos
int stepsPerRev = 4076;  // pasos para una vuelta completa
char lastCall = ' '; 
//tablas con la secuencia de encendido (descomentar la que necesiteis)
//secuencia 1-fase
//const int numSteps = 4;
//const int stepsLookup[4] = { B1000, B0100, B0010, B0001 };
 
//secuencia 2-fases
//const int numSteps = 4;
//const int stepsLookup[4] = { B1100, B0110, B0011, B1001 };
 
//secuencia media fase
const int numSteps = 8;
const int stepsLookup[8] = { B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001 };
 
 void allStop(){
  Serial.println("stop");
  // steppers stop
  PORTD = B00000000; //sets all of the pins 0 to 7 as LOW to power off stepper1
  PORTB = B00000000; //sets all of the pins 8 to 13 as LOW to power off stepper2
}   
void setup()
{
  Serial.begin(9600);
  //declarar pines como salida
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
}
 void clockwise()
{
  stepCounter++;
  if (stepCounter >= numSteps) stepCounter = 0;
  setOutput(stepCounter);
}
 
void anticlockwise()
{
  stepCounter--;
  if (stepCounter < 0) stepCounter = numSteps - 1;
  setOutput(stepCounter);
}
 
void setOutput(int step)
{
  digitalWrite(motorPin1, bitRead(stepsLookup[step], 0));
  digitalWrite(motorPin2, bitRead(stepsLookup[step], 1));
  digitalWrite(motorPin3, bitRead(stepsLookup[step], 2));
  digitalWrite(motorPin4, bitRead(stepsLookup[step], 3));
}
void loop()
{
lastCall = valor;
 if (Serial.available()>0) {
   valor = Serial.read();
lastCall = valor;
    if (lastCall=='1') {
 //if (valor=='1') {
  
  for (int i = 0; i < stepsPerRev * 2; i++)
  {
    clockwise();
    delayMicroseconds(motorSpeed);
  }
  } if (valor=='2'){
  
  for (int i = 0; i < stepsPerRev * 2; i++)
  {
    anticlockwise();
    delayMicroseconds(motorSpeed);
  }
 // delay(1000);
  }
}
  }


