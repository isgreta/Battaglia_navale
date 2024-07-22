//AUTORE
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

#include "Bot.h"
#include "Battaglia.h"
#include "Helper.h"
#include "Radar.h"


//COSTRUTTORE
Bot::Bot()
{
    srand((unsigned int)time(NULL));    //numero casuale
    for(int i = 0; i < DIM_G; i++)
    {
        for(int j = 0; j < DIM_G; j++)
        {
            attacco[i][j] = 0; //le celle di entrambe le griglie sono vuote
            difesa[i][j] = 0;
        }
    }
}

//FUNZIONI
//INSERISCONO LE NAVI NELLA GRIGLIA DI DIFESA
/* SETTO CORAZZATA 
separo la mia coordinata iniziale in lettera e numero e le trasformo in numero, successivamente "+2" e "-2" per trovare la poppa e la prua, 
richiamo void set_battleship(std::string xy1, std::string xy2);*/ 
void Bot::set_battleshipRand(std::string xy, int pos) //ti posiziona gia la corazzata nella griglia
{
    int row = Helper::convert_lett(xy); //Dalla coordinata xy ottengo la riga convertita già in un numero
    int col = Helper::convert_num(xy); //Dalla coordinata xy ottengo la colonna convertita nel numero corretto
    if(pos == 0) //orizzontale
    {
        std::string rowS = Helper::convert_row(row);
        std::string convCol1 = Helper::convert_col(col+2);     // coordinata del centro "+2", viene determinata la coordinata della prua
        std::string convCol2= Helper::convert_col(col-2);      // coordinata del centro "-2", viene determinata la coordinata della poppa
        std::string prow = rowS + convCol1;
        std::string stern = rowS + convCol2;
        set_battleship(prow, stern);                           // setto la corazzata usando poppa e prua
    }
    else //verticale
    {
        std::string colS = Helper::convert_col(col);
        std::string convrow1= Helper::convert_row(row +2);      // coordinata del centro "+2", viene determinata la coordinata della prua
        std::string convrow2= Helper::convert_row(row - 2);     // coordinata del centro "-2", viene determinata la coordinata della poppa
        std::string prow = convrow1 + colS;
        std::string stern = convrow2 + colS;
        set_battleship(prow, stern);
    }
}
/* SETTO NAVE DI SUPPORTO 
separo la mia coordinata iniziale in lettera e numero e le trasformo in numero, successivamente "+1" e "-1" per trovare la poppa e la prua, 
richiamo void set_naveS(std::string xy1, std::string xy2);*/ 
void Bot::set_supportRand(std::string xy, int pos)    
{
    int row = Helper::convert_lett(xy); //Dalla coordinata xy ottengo la riga convertita già in un numero
    int col = Helper::convert_num(xy); //Dalla coordinata xy ottengo la colonna convertita nel numero corretto
    if(pos== 0)//orizzontale
    {        
        std::string rowS = Helper::convert_row(row);
        std::string convCol1 = Helper::convert_col(col +1);    // coordinata del centro "+1", viene determinata la coordinata della prua
        std::string convCol2= Helper::convert_col(col-1);      // coordinata del centro "-1", viene determinata la coordinata della poppa
        std::string prow = rowS + convCol1;
        std::string stern = rowS + convCol2;
        set_support(prow, stern);                               // setto la nave di supporto usando poppa e prua
    }
    else //verticale
    {
        std::string colS = Helper::convert_col(col);
        std::string convrow1= Helper::convert_row(row+1);       // coordinata del centro "+1", viene determinata la coordinata della prua
        std::string convrow2= Helper::convert_row(row-1);       // coordinata del centro "-1", viene determinata la coordinata della prua
        std::string prow = convrow1 + colS;
        std::string stern = convrow2 + colS;
        set_support(prow, stern);                               
    }
}
void Bot::set_submarineRand(std::string xy)
{
    set_submarine(xy);
}

//CONTROLLA CHE LE COORDINATE GENERATE SIANO VALIDE
//xy centro dove piazzare la corazzata --> ci serve per il while per posizionare le corazzate
bool Bot::is_battleshipValid(std::string xy, int pos) 
{
    int row = Helper::convert_lett(xy); //Dalla coordinata xy ottengo la riga convertita già in un numero //10
    int col = Helper::convert_num(xy); //Dalla coordinata xy ottengo la colonna convertita nel numero corretto //8
    if(pos==0) //corazzata orizzontale
    {
        if(col != 0 && col !=1 && col !=10 && col !=11) //0,1,11,12 rappresentano le colonne dove la corazzata non può avere il suo centro 
            return true;
        else 
            return false;
    }
    else //corazzata verticale
    {
        if(row != 0 && row != 1 && row != 10 && row != 11)//A,B,M,N rappresentano le righe dove la corazzata non può avere il suo centro
            return true;
        else //riga = A,B,M,N
            return false;
    }
}
bool Bot::free_spot_bot(int row, int col) //varrebbe per sottomarino o celle libere singolarmente
{
    char* cell = &difesa[row][col];
    if (*cell != 0) return false; // C, S, E
    else return true;
}

//GENERA COORDINATE RANDOM PER IL PC (1x1)
std::string Bot::random_coord() //Restituisce coordinate random che verranno verificate nel set
{
    char letter = 'A' + rand()%14; //estrae lettera tra A e N-1
    if(letter == ASCII_J || letter == ASCII_K) //se estraggo una J o una K viene rifatto il sorteggio
    {
        while(letter == ASCII_J || letter == ASCII_K) 
            letter = 'A' + rand()%14;
    }
    int num = 1+ rand()%12; //estrae numero tra 0 e 11 
    std::string yy = std::to_string(num); //1 - 12
    char* p = &letter; 
    std::string uno = p;
    std::string output = uno + yy;
    return output;
}
