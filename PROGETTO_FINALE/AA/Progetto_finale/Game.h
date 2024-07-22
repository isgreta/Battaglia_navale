//AUTORE: 
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include "Helper.h"
#include "Radar.h"

const int DIM_G = 12;   //dimensione griglie 
const int DIM_RN1 = 3;  //dimensione griglia azione nave di supporto


class Game
{
    //private
    char attacco[DIM_G][DIM_G];             //griglia di attacco
    char difesa[DIM_G][DIM_G];              //griglia di difesa
    char radar_s[DIM_RS][DIM_RS];           //griglia azione sottomarino 5x5
    
    public:
    //COSTANTI CHE SERVONO PER I CONTROLLI
    const int ASCII_A = 65;
    const int ASCII_N = 78;
    const int ASCII_J = 74;
    const int ASCII_K = 75;
    const int ASCII_ZERO = 48;

    //COSTRUTTORE
    Game();                //costruttore giocatore

    //FUNZIONI 
    std::string print_att();   //stampa la griglia di attacco 
    std::string print_dif();   //stampa la griglia di difesa 

    //AZIONI NAVI 
    //CORAZZATA 
    bool is_battleshipValid(std::string xy, int pos);       //verifica che le coordinate  della corazzata siano corrette
    bool is_battleship_setValid(std::string stern, std::string prow);
    int get_pos_set(std::string prow, std::string stern);
    int get_pos_battleship(std::string xyOrigin);           //ritorna la posizione della corazzata 
    std::string get_battleshipCenter(std::string prow, std:: string stern); //ritorna il centro della corazzata
    bool find_battleship_center(std::string xyTarget, std::string center, int pos_target, int pos_center); //ricava il centro della corazzata
    bool check_battleship(char c);            //verifica che sto chiamando la funzione su di una corazzata 
    char tolower_case(char c);                //trasforma le lettere maiuscole in minuscole quando cella viene attaccata
    void fire(std::string xyTarget);          //cambia i caratteri nella griglia di difesa del difensore, alla cella attaccata
    void hit(std::string xyTarget);           //segna una X nella griglia di attacco dell'attaccante, se il colpo è andato a segno              
    void not_hit(std::string xyTarget);       //segna una O nella griglia di attacco dell'attaccante, se il colpo è stato nullo 
   

    //SOTTOMARINO
    bool check_submarine(std::string xyOrigin);         //verifica che sto chiamando la funzione su un sottomarino
    bool space_submarine(std::string xyTarget);         //verifica che la posizione in cui voglio spostare il sottomarino sia libera
    void move_submarine(std::string xyOrigin,std::string xyTarget);      //sposta il sottomarino
    void radar(std::string xyTarget);                   //va nella griglia di difesa del difensore e copia in griglia 5x5 i char che trova il sottomarino 
    char get_valueRadar(int row, int col);              //ritorna valore in una cella dell'array 5x5
    void set_radar(std::string xyTarget, Radar r);      //nella griglia di attacco dell'attaccante copia i char che ci sono nell'array 5x5
    void reveal();                                      //nella griglia di attacco dell'attaccante mette le Y al posto dei char impostati dalla funzione precedente 
    void clear_Y();                                     //toglie le Y dalla griglia di attacco
  

    //NAVE DI SUPPORTO
    bool is_supportValid(std::string xy, int pos);                         //verifica che le coordinate  della nave di supporto siano corrette
    bool is_support_setValid(std::string prow,std::string stern);
    std::string get_supportCenter(std::string prow, std:: string stern);   //ricava il centro della nave di supporto
    int get_pos_support(std::string xyOrigin);                   //mi dice se la nave di supporto è orizzontale o verticale
    bool space_support(std::string xyTarget, int pos);           //verifica che lo spazio dove si sposta la nave sia effettivamente libero e le coordinate siano valide
    void move_support(std::string xyOrigin, std::string xyTarget, int pos);  //sposta la nave di supporto 
    bool find_support_center(std::string xyTarget, std::string center, int pos_target, int pos_center);   //se true ripara la nave
    void fix_support(std::string center, int pos_center);              //ripara le navi di supporto
    void fix_battleship(std::string center, int pos_center);           //ripara la corazzata
    

    //SET COORDINATE INIZIALI
    void set_battleship(std::string xy1, std::string xy2);      //setta coordinate iniziali corazzata  
    void set_support(std::string xy1, std::string xy2);         //setta coordinate iniziali nave di supporto 
    void set_submarine(std::string xy);                         //setta coordinate iniziali sottomarino
    
    //CONTROLLANO CHE UNA CELLA O L'INTERO SPAZIO OCCUPATO DA UNA NAVE SIANO LIBERE O No
    bool free_cell(int row, int col);                            //controlla che una cella sia libera
    bool free_battles_space(std::string center, int pos);        //controlla che un range di celle sia libero per la corazzata
    bool free_support_space(std::string center, int pos);        //controlla che un range di celle sia libero per la nave di supp.  
    char get_cell(std::string xyOrigin);                         //verifica presenza di una nave e ritorna il char corrispondente      
    void sunk_battleship(std::string center, int pos);           //affonda la corazzata 
    void sunk_support(std::string center, int pos);              //affonda la nave di supporto 
    void sunk_submarine(std::string center);                     //affonda il sottomarino

    //VITTORIA determina il vincitore della partita, mi dicono se le 3 navi sono affondate 
    bool is_battleship_sink(std::string center_b1, int pos_b1); 
    bool is_submarine_sink(std::string center);
    bool is_support_sink(std::string center, int pos);
};
    std::ostream& operator<<(std:: ostream& os, Game& g);  //overloading operatore << per stampare le griglie 
#endif