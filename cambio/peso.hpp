#ifndef PESO_H
#define PESO_H
// #include <Arduino.h>
#include <Servo.h>

#include "HX711.h"

#include <string>

class Peso {
public:
  Peso(int doutPin, int sckPin, int servoPin);
  int lectura();
  void actuador();
private:
  int doutPin, sckPin, servoPin;

  HX711 escala;
  Servo compuerta;

  int measure = 0;
  bool open = false;
};

Peso::Peso(int doutPin, int sckPin, int servoPin) {
  Serial.println("--> Escala: Inicializada");

  this->doutPin = doutPin;
  this->sckPin = sckPin;
  this->servoPin = servoPin;

  this->compuerta.attach(this->servoPin);
  this->escala.begin(this->doutPin, this->sckPin);

  this->escala.set_scale(-7272.2);
  this->escala.tare();
}

int Peso::lectura() {
  this->measure = this->escala.get_units(10);
  this->escala.power_down();
  delay(50);
  this->escala.power_up();

  return this->measure;
}

// TODO: Modificar los angulos para ver que coincidan con los angulos
void Peso::actuador() {
  if (this->measure >= 4.5) {
    this->open = true;
  } else {
    this->open = false;
  }

  // depende del estado, se abre o cierra la compuerta
  if (this->open) {
    this->compuerta.write(180);
  } else {
    this->compuerta.write(0);
  }
  return;
}
#endif