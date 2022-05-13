/* Copyright (C) 2022 Jean Paul Bai
 * All rights reserved.
 *
 * Projet Système Atmosphérique Connectés
 * Ecole du Web
* Cours Systèmes embarqués (c)2022
 *
    @file     MyTemp.h
    @author   Jean paul Bai
    @version  1.0 19/04/2022
    @description
      Démonstration comment utiliser l'écran STONE
      Et un senseur DHT22
    platform = ESP32
    OS = Arduino
    Langage : C++
**/
#ifndef MYTEMP_H
#define MYTEMP_H
#include "DHT.h"
#define DHT_SENSOR_PIN 17 // ESP32 pin GIOP23 connected to DHT22 sensor
#define DHT_SENSOR_TYPE DHT22

using namespace std;

class MyTemp
{
private:
    DHT *dht_sensor;

public:
    MyTemp();
    ~MyTemp();
    void init();
    float getTemperature();
};
#endif
