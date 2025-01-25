#include AccelStepper.h

 LDRs
const int LDR_TOP_LEFT = A0;
const int LDR_TOP_RIGHT = A1;
const int LDR_BOTTOM_LEFT = A2;
const int LDR_BOTTOM_RIGHT = A3;
const int LIGHT_THRESHOLD = 10;

 A4988 Stepper Motor Driver
const int STEP_PIN_VERTICAL = 12;  STEP pin for vertical stepper motor
const int DIR_PIN_VERTICAL = 11;   DIR pin for vertical stepper motor

const int STEP_PIN_HORIZONTAL = 7;  STEP pin for horizontal stepper motor
const int DIR_PIN_HORIZONTAL = 6;   DIR pin for horizontal stepper motor

AccelStepper stepperVertical(AccelStepperDRIVER, STEP_PIN_VERTICAL, DIR_PIN_VERTICAL);
AccelStepper stepperHorizontal(AccelStepperDRIVER, STEP_PIN_HORIZONTAL, DIR_PIN_HORIZONTAL);

const int UPPER_LIMIT_POS = 160;   Upper limit of stepper motors
const int LOWER_LIMIT_POS = 20;    Lower limit of stepper motors

void setup() {
  stepperVertical.setMaxSpeed(2000);
  stepperVertical.setAcceleration(500);

  stepperHorizontal.setMaxSpeed(2000);
  stepperHorizontal.setAcceleration(500);

  stepperVertical.moveTo(90);
  stepperHorizontal.moveTo(90);
}

void loop() {
  int ldr_tl_value = analogRead(LDR_TOP_LEFT);
  int ldr_tr_value = analogRead(LDR_TOP_RIGHT);
  int ldr_bl_value = analogRead(LDR_BOTTOM_LEFT);
  int ldr_br_value = analogRead(LDR_BOTTOM_RIGHT);

  int average_top = (ldr_tl_value + ldr_tr_value)  2;
  int average_bottom = (ldr_bl_value + ldr_br_value)  2;
  int average_left = (ldr_tl_value + ldr_bl_value)  2;
  int average_right = (ldr_tr_value + ldr_br_value)  2;

  moveSolarTracker(average_top, average_bottom, average_left, average_right);

  delay(30);
}

void moveSolarTracker(int average_top, int average_bottom, int average_left, int average_right) {
  if ((average_right - average_left)  LIGHT_THRESHOLD && stepperVertical.currentPosition()  UPPER_LIMIT_POS) {
    stepperVertical.move(1);
    stepperVertical.run();
  } else if ((average_left - average_right)  LIGHT_THRESHOLD && stepperVertical.currentPosition()  LOWER_LIMIT_POS) {
    stepperVertical.move(-1);
    stepperVertical.run();
  }

  if ((average_top - average_bottom)  LIGHT_THRESHOLD && stepperHorizontal.currentPosition()  UPPER_LIMIT_POS) {
    stepperHorizontal.move(1);
    stepperHorizontal.run();
  } else if ((average_bottom - average_top  )  LIGHT_THRESHOLD && stepperHorizontal.currentPosition()  LOWER_LIMIT_POS) {
    stepperHorizontal.move(-1);
    stepperHorizontal.run();
  }
}
