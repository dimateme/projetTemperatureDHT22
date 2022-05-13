/* Copyright (C) 2022 Jean Paul Bai
 * All rights reserved.
 *
 * Projet Domotique
 * Ecole du Web
* Cours Systèmes embarqués (c)2022
 *
    @file     MyStone.h
    @author   Jean paul Bai
    @version  1.2 19/04/2022
    @description
      Démonstration comment utiliser l'écran STONE

    platform = ESP32
    OS = Arduino
    Langage : C++

    Historique des versions
        Version    Date       Auteur       Description
        1.1        22/08/15  Alain       Première version du logiciel

**/
#ifndef MYSTONE_H
#define MYSTONE_H

#include "MySerial.h"
using namespace std;
// Structure local utilisés pour garder les informations lues de l'écran
struct datasRead
{
    int id; // Si 0 alors il n'y a pas de données, <0 Numero commande non traitée, >1 Numero de la commande traité
    char command[80];
    char name[80];
    int type;
    char line[2048];
};
class MyStone
{
public:
    MyStone(int speed, uint32_t config, int rxd, int txd);
    ~MyStone();
    datasRead getValidsDatasIfExists();
    // Nouvelles mérthodes ajoutés dans la version 1.2
    void changePage(const char *pageName = "");
    void setLabel(const char *labelName, const char *value);
    void getVersion();

private:
    MySerial *mySerial;
    // transfert de ces deux methodes en privées depuis la version 1.2
    int writeIt(string cmdFrmat2);
    int readIt(char *data, int len);
};
#endif
