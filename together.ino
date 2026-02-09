
#include <stepper.h>

// ---------- Код проекта по созданию прототипа аграрного робота-манипулятора ----------

// Число шагов на оборот (360*) (например, для 28BYJ-48)
const int STEPS_PER_REV = 2048;

// Мотор N1 – двигает прототип по рельсе
Stepper motorN1(STEPS_PER_REV, 2, 4, 3, 5);

// Мотор N2 – Крутит прототип вокруг растения
Stepper motorN2(STEPS_PER_REV, 6, 8, 7, 9);

// На сколько двигается за раз (создать фиксированный промежуток)
const int MOVE_STEP = 50;

// Сколько шагов нужно, чтобы повернуться на 180 градусов
const int TURN_180 = STEPS_PER_REV / 2;

// Скорость вращения моторов
const int MOTOR_SPEED = 10;

// ------------------ ДАТЧИК HC-SR04 ------------------

const int TRIG_PIN = 10;
const int ECHO_PIN = 11;

// Если расстояние изменилось больше, чем на столько, считаем, что появилось растение
const int DELTA_DISTANCE = 5; // в сантиметрах

long lastDistance = 0;

// Создаем функцию для удр

long getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000); // ждём сигнал, но не дольше 5м
  long distance = duration / 60; // переводим в сантиметры

  return distance;
}

void setup() {
  motorN1.setSpeed(MOTOR_SPEED);
  motorN2.setSpeed(MOTOR_SPEED);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  delay(1000); // Ожинание 1 секунды (даём датчику успокоиться)
 
  lastDistance = getDistance();
}

void loop() {

  // 1. Чуть-чуть двигаем мотор N1 вперёд
  motorN1.step(MOVE_STEP);

  // 2. Меряем расстояние до объекта
  long currentDistance = getDistance();

  // 3. Смотрим, не появилось ли что-то новое (растение?)
  if (abs(currentDistance - lastDistance) &gt; DELTA_DISTANCE) {

    // Изменение в расстоянии до объекта (Появилось растение!)

    delay(300); // небольшая пауза

    // 4. Мотор N2 – поворачиваем инструмент на 180°
    motorN2.step(TURN_180);
    delay(300);

    // 5. Возвращаем обратно
    motorN2.step(-TURN_180);
    delay(300);

    // Запоминаем новое расстояние
    lastDistance = getDistance();
  }

  delay(100); // чтобы датчик лишний раз не срабатывал
}

