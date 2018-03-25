#include <L6470.h>
#include <L6470_dfs.h>

L6470 StepperMotor(11);

void setup() {
  // put your setup code here, to run once:
  while(L6470_OK != StepperMotor.begin(){
  }
  
  StepperMotor.Acc.Set(100);
  StepperMotor.Dec.Set(100);
  StepperMotor.MaxSpeed.Set(100);
}

void loop() {
  // put your main code here, to run repeatedly:

}
