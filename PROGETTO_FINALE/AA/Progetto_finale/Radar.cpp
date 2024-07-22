//AUTORE
#include "Radar.h"

Radar::Radar()  //costruttore
{
    for(int i = 0; i < DIM_RS; i++) 
    {
        for(int j = 0; j < DIM_RS; j++)
        {
            radar_s[i][j] = 0;
        }
    }
}
void Radar::set_radarS(char c, int i, int j) 
{
    radar_s[i][j] = c;
}
char Radar::get_radarS(int i, int j) const  //ritorna caratteri nella griglia 
{
    char c = radar_s[i][j];
    return c;
}