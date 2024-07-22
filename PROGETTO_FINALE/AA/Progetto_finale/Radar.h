//AUTORE
#ifndef RADAR_H
#define RADAR_H

#include <iostream>

const int DIM_RS = 5;// dimensione griglia radar 5x5

class Radar
{
    char radar_s[DIM_RS][DIM_RS]; //griglia radar 5x5

    public:

    // COSTRUTTORE 
    Radar();

    //FUNZIONI 
    void set_radarS(char c, int i, int j);    //settiamo il radar
    char get_radarS(int i, int j) const;      //ritorna avvistamenti radar 

};

#endif