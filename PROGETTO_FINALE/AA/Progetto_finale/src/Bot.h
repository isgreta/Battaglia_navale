//AUTORE

#ifndef BOT_H
#define BOT_H

//file con definzioni funzioni
#include "Game.h"
#include "Helper.h"
#include "Radar.h"
#include <iostream>
#include <string>


class Bot: public Game
{
    char attacco[DIM_G][DIM_G];         //griglia di attacco
    char difesa[DIM_G][DIM_G];          //griglia di difesa
    
    public:
    //COSTRUTTORE
    Bot();

    //FUNZIONI
    //SET COORDINATE INIZIALI
    void set_battleshipRand(std::string xy, int pos);       //setta coordinate iniziali corazzta 
    void set_supportRand(std::string xy, int pos);          //setta coordinate inziali nave di supporto
    void set_submarineRand(std::string xy);                 //setta coordinate iniziali sottomarino

    //CONTROLLA CHE LE COORDINATE GENERATE SIANO VALIDE 
    bool is_battleshipValid(std::string xy, int pos);

    
};
#endif