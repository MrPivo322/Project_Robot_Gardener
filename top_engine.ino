// Code for top stepper engine. Код для верхнего шагового моторчика.
#include <Stepper.h>
#define STEPS 200 
Stepper stepper(STEPS, 8, 9, 10, 11);
int pinButtons1[]={6,7};
int lastButtons1[]={0,0};
int currentButtons1[]={0,0};
int countButtons1=2;
void setup()
{
stepper.setSpeed(50);
}
void loop()
{
for(int i=0;i<countButtons1;i++)
{
currentButtons1[i] = debounce(lastButtons1[i],pinButtons1[i]);
if (lastButtons1[i] == 0 && currentButtons1[i] == 1)
{
if(i==0)
stepper.step(10*STEPS);
else
stepper.step(-10*STEPS);
}
lastButtons1[i] = currentButtons1[i];
}
}
int debounce(int last,int pin1)
{
int current = digitalRead(pin1);
if (last != current)
{
delay(5);
current = digitalRead(pin1);
return current;
}
}
