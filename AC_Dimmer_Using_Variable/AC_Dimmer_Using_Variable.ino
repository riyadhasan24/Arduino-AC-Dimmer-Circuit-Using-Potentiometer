/* The source Code from : https://github.com/riyadhasan24
 * By Md. Riyad Hasan
 */

#include <TimerOne.h>

int Dim = 0;
int Input_Value;                            // Value from Potentiometer
int Freq_Step = 75;                         // This Freq_Step for 50Hz AC Power
volatile int ZC = 0;
volatile boolean Zero_Cross = 0;

#define Traic_Pin 9
#define Input_Pin A0

void setup()
{
  pinMode(Input_Pin, INPUT);
  pinMode(Traic_Pin, OUTPUT);

  Timer1.initialize(Freq_Step);
  Timer1.attachInterrupt(Dim_Check, Freq_Step);

  attachInterrupt(0, Zero_Cross_Detect, RISING);
}

void Zero_Cross_Detect()
{
  Zero_Cross = true;
  ZC = 0;
  digitalWrite(Traic_Pin, LOW);
}

void Dim_Check()
{
  if(Zero_Cross == true)
  {
    if(ZC >= Dim)
    {
      digitalWrite(Traic_Pin, HIGH);
      ZC = 0;
      Zero_Cross = false;
    }
    else
    {
      ZC++;
    }
  }
}

void loop()
{
  Input_Value = analogRead(Input_Pin);
  Dim = map(Input_Value, 0, 1023, 0, 128);
}