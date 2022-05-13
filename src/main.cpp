/* Copyright (C) 2022 Jean Paul Bai
 * All rights reserved.
 *
 * Projet Stone de base
 * Ecole du Web
 * Cours Systèmes embarqués (c)2022
 *
    @file     main.cpp
    @author   Jean Paul Bai
    @version  1.1 22/04/15
    @description
      Démonstration comment utiliser le PORT SERIE pour accèder aux fonctionnalités
      de l'écran STONE en utilisant la classe MyStone et MySerial

    platform = ESP32
    OS : Arduino
    Langage : C++

    Historique des versions
        Version    Date       Auteur       Description
        1.1        22/08/15  Alain       Première version du logiciel

    Fonctionnalités implantées
        Lecture des evénements envoyés par l'écran
        Envoyer une commande à l'écran
          Optenir la version du Firmware de l'écran
 * */

#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include "DHT.h" //Librairie des capteurs DHT

#define DHT_SENSOR_PIN 17 // correspond au pin sur lequel le DHT22 est branché
#define DHT_SENSOR_TYPE DHT22

#define RXD2 18 // 16
#define TXD2 19 // 17
#define BAUD_RATE 115200

#include <iostream>
using namespace std;
#include "MyTemp.h"
MyTemp *myTemp = new MyTemp();

#include "MyStone.h"
MyStone *myStone;
// c'est le temps de sechege en secondes
int tempsSechage = 20;
// c'est la température obtenue par le senseur DHT22
float temperetureObtenue;
// nom du bouton de démmarage
int butonDemmarrage;
std::string intToHexa(int value)
{
  char buffer[10];
  sprintf(buffer, "0x%4X", value);
  return (buffer);
};

std::string charToString(char str, std::string formatStr)
{
  char buffer[10];
  sprintf(buffer, formatStr.c_str(), str);
  return (buffer);
};

std::string intToString(int value, std::string formatStr)
{
  char buffer[10];
  sprintf(buffer, formatStr.c_str(), value);
  return (buffer);
};

// Thread qui permet de LOOPER et lire le contenu du port serie
// avec l'aide du la fonction getValidsDatasIfExists
void readStoneData()
{
  datasRead rd = myStone->getValidsDatasIfExists();
  // std::cout << "GData : " << intToHexa(abs(rd.id)) << " " << rd.command << " " << rd.name << " " << rd.type << "\n";
  switch (rd.id)
  {
  case 0x1001:
  {
    // si le bouton de démarrage est appuyé ont compare le nom du bouton
    std::cout << "GData : " << intToHexa(abs(rd.id)) << " " << rd.command << " " << rd.name << " " << rd.type << "\n";

    char monBouton[] = "btndemarrage";
    int resultat = strcmp(rd.name, monBouton);
    if (resultat == 0 && rd.type == 2)
    {
      butonDemmarrage = 7;
    }

    break;
  }
  }

  if (rd.id < 0)
    std::cout << "Data received ( id: : " << intToHexa(abs(rd.id)) << "  Command: " << rd.command << " Type: " << rd.type << ")\n";
}

void setup()
{

  Serial.begin(9600);

  Serial.println("Stone serial Txd is on pin: " + String(TXD2));
  Serial.println("Stone serial Rxd is on pin: " + String(RXD2));
  myStone = new MyStone(115200, SERIAL_8N1, RXD2, TXD2);

  cout << std::string("Début de l'exemple Stone de base pour le ESP32") << "\n";

  myStone->setLabel("labelbois", "Érable");
  delay(200); // entre 0.2 seconde entre le remplissage des labal
  myStone->setLabel("labeltype", "dur");
  delay(200);
  myStone->setLabel("labelorigine", "US");
  delay(200);
  myStone->setLabel("labelsechage", "20 secondes");
  delay(200);
  myStone->setLabel("labeltempmin", "25 Celcius");
  myTemp->init();
}

void loop()
{
  readStoneData();
  // si le bouton démmarrage est appuyé
  if (butonDemmarrage == 7)
  {
    temperetureObtenue = myTemp->getTemperature();
    if (isnan(temperetureObtenue))
    {
      myStone->setLabel("labelaffichetemp", " ");
    }
    char stringTemperature[70];
    sprintf(stringTemperature, "%g Celcius", temperetureObtenue);
    myStone->setLabel("labelaffichetemp", stringTemperature);

    while (tempsSechage > 0)
    {
      if ((27.5 >= temperetureObtenue) && (temperetureObtenue >= 22.5))
      {
        delay(1000);
        tempsSechage--;
      }
      char stringSeconde[70];
      sprintf(stringSeconde, "%d", tempsSechage);
      myStone->setLabel("labelseconde", stringSeconde);
    }
    butonDemmarrage = 0;
    tempsSechage = 20;
  }
}