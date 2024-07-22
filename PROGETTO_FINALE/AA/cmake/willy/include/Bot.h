//AUTORE

#ifndef BOT_H
#define BOT_H

//file con definzioni funzioni
#include "Battaglia.h"
#include "Helper.h"
#include "Radar.h"
#include <iostream>
#include <string>


class Bot: public Battaglia
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
    bool free_spot_bot(int riga, int col);  //verifica che la cella attaccata sia libera nella griglia di difesa del computer

    //GENERA COORDINATE RANDOM PER IL PC
    std::string random_coord(); 
    
};
#endif