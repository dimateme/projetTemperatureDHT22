/**
    Class MyButton : Gestion d'un bouton TOUCH sur ESP32
    @file MyButton.h
    @author Jean P
    @version 1.0 17/03/21

    Historique des versions
                            Versions  Date      Auteur      Description
                            1.0      17/03/21   Ald         Première version de la classe


    platform = espressif32
    board = esp32doit-devkit-v1
    framework = arduino
    lib_deps =
        Aucune
    Autres librairies (à copier dans le répertoire lib)
        Aucune
    GPIO qui peuvent être utilisés en TOUCH sur le ESP32
            T0:GPIO4 (default)  T1:GPIO0     T2:GPIO2   T3:GPI15    T4:GPI13
            T5:GPI12            T6:GPI14     T7:GPI27   T8:GPI32    T9:GPI33
    Exemple d'utilisation
        #include "MyButton.h"
        MyButton *myButton = new MyButton();
        myButton->init(T8);
        int sensibilisationButtonAction = myButton->autoSensibilisation(); //Trouve la sensibilité automatiquement


**/
//#include <Arduino.h>
//#include <Adafruit_Sensor.h>
#include "DHT.h"
#include "MyTemp.h"

MyTemp::MyTemp() {}
MyTemp::~MyTemp() {}
void MyTemp::init()
{
    dht_sensor = new DHT(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);
    dht_sensor->begin();
}

// Méthode qui permet d.obtenir la température
float MyTemp::getTemperature()
{
    dht_sensor = new DHT(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);
    float temperateure = dht_sensor->readTemperature();

    return temperateure;
}