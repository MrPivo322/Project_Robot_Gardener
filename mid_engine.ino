// Code for mid engine. Код для среднего шагового моторчика.
#include <Stepper.h>

const int stepsPerRevolution = 200; 
const int degreesPerStep = 360.0 / stepsPerRevolution; 

#define MOTOR_PIN1 8
#define MOTOR_PIN2 9
#define MOTOR_PIN3 10
#define MOTOR_PIN4 11

Stepper myStepper(stepsPerRevolution, MOTOR_PIN1, MOTOR_PIN2, MOTOR_PIN3, MOTOR_PIN4);

void setup() {
  myStepper.setSpeed(60);
  
  Serial.begin(9600);
  
  Serial.println("Программа запущена");
  Serial.print("Один шаг = ");
  Serial.print(degreesPerStep);
  Serial.println(" градусов");
}

void loop() {
  int stepsFor180Degrees = 180 / degreesPerStep;
  
  Serial.println("\n--- Начинаем движение вперед ---");
  
  for (int i = 0; i < stepsFor180Degrees; i++) {
    myStepper.step(1);
    
    Serial.print("Сделан шаг ");
    Serial.print(i + 1);
    Serial.print(" из ");
    Serial.println(stepsFor180Degrees);
    
    delay(2000);
  }
  
  Serial.println("Достигнуто 180 градусов");
  delay(1000);  
  
  Serial.println("--- Возврат в исходное положение ---");
  
  for (int i = 0; i < stepsFor180Degrees; i++) {
    myStepper.step(-1);
    
    Serial.print("Возврат: шаг ");
    Serial.print(i + 1);
    Serial.print(" из ");
    Serial.println(stepsFor180Degrees);
    
    delay(2000);
  }
  
  Serial.println("Возврат в исходное положение завершен");
  delay(3000); 
}