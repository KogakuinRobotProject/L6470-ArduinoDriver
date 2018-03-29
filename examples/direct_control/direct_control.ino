#include <L6470.h>
#include <L6470_dfs.h>

/*
 * ご使用の際には公式(ST)が出しているデータシートをみること。英語読めないとか泣き言言うな。
 * githubにデータシートを上げてあるけど、最新かどうかは必ず確認すること。
 * 細かい設定はデータシートを参照すること。
 * 
 * githubのwikiにAPIリファレンスを乗っける（予定）。
 */

L6470 StepperMotor(8);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.print("Init\n");
  while(L6470_OK != StepperMotor.begin()){
  }
  Serial.print("Parameter Init\n");
  StepperMotor.Acc = 0x08A;       //IC default Parameter 0x08A
  StepperMotor.Dec = 0x08A;       //IC default Parameter 0x08A
  StepperMotor.MaxSpeed = 0x041;  //IC default Parameter 0x041
  StepperMotor.MinSpeed = 0x000;  //IC default Parameter 0x000

//Vs が12Vで、回転時モータに掛ける最大の電圧を5Vに設定する場合
  StepperMotor.KvalHold = (5 / 12) * 255;
  StepperMotor.KvalRun = (5 / 12) * 255;
  StepperMotor.KvalAcc = (5 / 12) * 255;
  StepperMotor.KvalDec = (5 / 12) * 255;
}

void loop() {
  // put your main code here, to run repeatedly:
  StepperMotor.Move(1,(long)400 * 128);
  while(StepperMotor.isBusy()){
   delay(100);
  }
  StepperMotor.Move(0,(long)400 * 128);
  while(StepperMotor.isBusy()){
   delay(100);
  }
}
