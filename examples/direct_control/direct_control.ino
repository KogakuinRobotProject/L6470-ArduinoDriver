#include <L6470.h>
#include <L6470_dfs.h>

L6470 StepperMotor(11);

void setup() {
  // put your setup code here, to run once:
  while(L6470_OK != StepperMotor.begin()){
  }
  
  StepperMotor.Acc = 0x08A;       //IC default Parameter 0x08A
  StepperMotor.Dec = 0x08A;       //IC default Parameter 0x08A
  StepperMotor.MaxSpeed = 0x041;  //IC default Parameter 0x041
  StepperMotor.MinSpeed = 0x000;  //IC default Parameter 0x000
}

void loop() {
  // put your main code here, to run repeatedly:
  StepperMotor.Move(0,100);
  delay(1000);
  StepperMotor.Move(1,100);
  delay(1000);
}
