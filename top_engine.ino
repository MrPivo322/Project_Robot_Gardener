// Code for top stepper engine. Код для верхнего шагового моторчика.
#include <Srepper.h>
@define STEPS 100
Stepper stepper(STEPS, 8, 9, 10, 11);
void setup()
{
stepper.setSpeed(50);
}
void loop()
{


    
}