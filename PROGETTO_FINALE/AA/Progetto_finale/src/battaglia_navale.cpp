//AUTORE
#include "Game.h"
#include "Bot.h"
#include "Helper.h"
#include "Radar.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <random>

using namespace std;

int main(void)
{
    std::random_device myRandomDevice;
    unsigned seed = myRandomDevice();
    std::default_random_engine myRandomEngine(seed);
    std::uniform_int_distribution<int> myUnifIntDist(0, 11);
    //CREO GLI OGGETTI GIOCATORE1, BOT1, BOT2
    Game giocatore1 = Game(); 
    Bot bot1 = Bot();
    Bot bot2 = Bot();
    vector<string> set_player1; //Questo vector serve per salvare le coordinate iniziali del bot1
    vector<int> set_position1;
    vector<string> set_player2; //Questo vector serve per salvare le coordinate iniziali del giocatore o bot2
    vector<int> set_position2;
    vector<string> player1; //Questo vector serve per salvare le coordinate durante i vari turni del bot1 
    vector<string> player2;//Questo vector serve per salvare le coordinate durante i vari turni del bot2 o il giocatore
    int start_replay;
    
    //BOT
    cout<<"... ... ... INSERIMENTO NAVI BOT1 ... ... ..."<<endl;  
    //INSERIMENTO CORAZZATE
    int b1_positionB = rand()%2; //0 = orizzontale o 1= verticale
    int b2_positionB = rand()%2;
    int b3_positionB = rand()%2;
    string b1_centerB, b2_centerB, b3_centerB;
    bool valid = true;
    while(valid)
    {
        b1_centerB = Helper::convert_row(myUnifIntDist(myRandomEngine)) + Helper::convert_col(myUnifIntDist(myRandomEngine));
        if(bot1.is_battleshipValid(b1_centerB,b1_positionB) && bot1.free_battles_space(b1_centerB,b1_positionB))
            valid = false;
    }
    bot1.set_battleshipRand(b1_centerB, b1_positionB);
    valid = true;
    set_player1.push_back(b1_centerB); //Coordinate B1 in indice 0 del vector
    set_position1.push_back(b1_positionB); //Orientamento B1 in indice 0 del vector
    while(valid)
    {
        b2_centerB = Helper::convert_row(myUnifIntDist(myRandomEngine)) + Helper::convert_col(myUnifIntDist(myRandomEngine));
        if(bot1.is_battleshipValid(b2_centerB,b2_positionB) && bot1.free_battles_space(b2_centerB,b2_positionB))
            valid=false;   
    }
    bot1.set_battleshipRand(b2_centerB, b2_positionB);
    valid = true;
    set_player1.push_back(b2_centerB); //Coordinate B2 in inice 1 del vector
    set_position1.push_back(b2_positionB);//Orientamento B2 in indice 1 del vector
    
    while(valid)
    {
        b3_centerB = Helper::convert_row(myUnifIntDist(myRandomEngine)) + Helper::convert_col(myUnifIntDist(myRandomEngine));
        if(bot1.is_battleshipValid(b3_centerB,b3_positionB) && bot1.free_battles_space(b3_centerB,b3_positionB))
            valid=false;  
    }
    bot1.set_battleshipRand(b3_centerB, b3_positionB);
    valid = true;
    set_player1.push_back(b3_centerB); //Coordinate B3 in inice 2 del vector
    set_position1.push_back(b3_positionB); //Orientamento B3 in indice 2 del vector

    //INSERIMENTO NAVI DI SUPPORTO
    int n1_positionB = rand()%2; //0 = orizzontale o 1= verticale
    int n2_positionB = rand()%2;
    int n3_positionB = rand()%2;
    string n1_centerB, n2_centerB, n3_centerB;
    
    while(valid)
    {
        n1_centerB = Helper::convert_row(myUnifIntDist(myRandomEngine)) + Helper::convert_col(myUnifIntDist(myRandomEngine));
        if(bot1.is_supportValid(n1_centerB,n1_positionB) && bot1.free_support_space(n1_centerB,n1_positionB))
            valid = false;
    }
    bot1.set_supportRand(n1_centerB,n1_positionB);
    valid = true;
    set_player1.push_back(n1_centerB); //Coordinate n1 in inice 3 del vector
    set_position1.push_back(n1_positionB); //Orientamento n1 in indice 3 del vector
    
    while(valid)
    {
        n2_centerB = Helper::convert_row(myUnifIntDist(myRandomEngine)) + Helper::convert_col(myUnifIntDist(myRandomEngine));
        if(bot1.is_supportValid(n2_centerB,n2_positionB) && bot1.free_support_space(n2_centerB,n2_positionB))
            valid=false;   
    }
    bot1.set_supportRand(n2_centerB, n2_positionB);
    valid = true;
    set_player1.push_back(n2_centerB); //Coordinate n2 in inice 4 del vector
    set_position1.push_back(n2_positionB); //Orientamento n2 in indice 4 del vector

    while(valid)
    {
        n3_centerB = Helper::convert_row(myUnifIntDist(myRandomEngine)) + Helper::convert_col(myUnifIntDist(myRandomEngine));
        if(bot1.is_supportValid(n3_centerB,n3_positionB) && bot1.free_support_space(n3_centerB,n3_positionB))
            valid=false;  
    }
    bot1.set_supportRand(n3_centerB, n3_positionB);
    valid = true;
    set_player1.push_back(n3_centerB); //Coordinate n3 in inice 5 del vector
    set_position1.push_back(n3_positionB); //Orientamento n3 in indice 5 del vector
        
    // INSERIMENTO SOTTOMARINO
    string sub1_centerB, sub2_centerB;
    while(valid)
    {
        sub1_centerB = Helper::convert_row(myUnifIntDist(myRandomEngine)) + Helper::convert_col(myUnifIntDist(myRandomEngine));//A1
        if(bot1.free_cell(Helper::convert_lett(sub1_centerB), Helper::convert_num(sub1_centerB)))
            valid = false;
    }
    bot1.set_submarineRand(sub1_centerB);
    valid = true;
    set_player1.push_back(sub1_centerB); //Coordinate sub1 in inice 6 del vector
    set_position1.push_back(-1); //Orientamento sub1 in indice 6 del vector

    while(valid)
    {
        sub2_centerB = Helper::convert_row(myUnifIntDist(myRandomEngine)) + Helper::convert_col(myUnifIntDist(myRandomEngine));
        if(bot1.free_cell(Helper::convert_lett(sub2_centerB), Helper::convert_num(sub2_centerB)))
            valid=false;   
    }
    bot1.set_submarineRand(sub2_centerB);
    valid = true;
    set_player1.push_back(sub2_centerB); //Coordinate sub2 in inice 7 del vector
    set_position1.push_back(-1); //Orientamento sub2 in indice 7 del vector

    bool continua = true;
    string answer;

    do
    {
        cout <<endl<<"a) Partita giocatore vs computer: premi \"1\"" <<endl 
            << "b) Partita computer vs computer: premi\"2\""<<endl
            << "c) Terminare: premi\"3\""<<endl;
        cin>>answer;
        cout<<endl;
  

    if(answer=="3")
    {
        cout<<"Programma terminato";
        continua = false;
    }
    else if(answer == "1")
    {
        //GIOCATORE INSERIMENTO NAVI
        //INSERIMENTO CORAZZATE
        cout<<"Inserisci prua e poppa della corazzata c1: " <<endl;
        string prow, stern; 
        string b1_center;
        int b1_position;
        try
        {
            cin>>prow>>stern;
            giocatore1.set_battleship(prow, stern);
            b1_center= giocatore1.get_battleshipCenter(prow,stern);
            b1_position = giocatore1.get_pos_battleship(b1_center);
        }
        catch(...)
        {
            cout<<"Errore! Un tentativo rimasto. Inserisci prua e poppa della corazzata c1: " <<endl;
            cin>>prow>>stern;
            giocatore1.set_battleship(prow, stern);
            b1_center= giocatore1.get_battleshipCenter(prow,stern);
            b1_position = giocatore1.get_pos_battleship(b1_center);
        }
        set_player2.push_back(b1_center); //Coordinate B1 in indice 0 del vector
        set_position2.push_back(b1_position); //Orientamento B1 in indice 0 del vector
        
        cout<<"Inserisci prua e poppa della corazzata c2: "<<endl;
        string b2_center;
        int b2_position;
        try
        {
            cin>>prow>>stern;
            giocatore1.set_battleship(prow, stern);
            b2_center = giocatore1.get_battleshipCenter(prow,stern);
            b2_position = giocatore1.get_pos_battleship(b2_center);
        }
        catch(...)
        {
            cout<<"Errore! Un tentativo rimasto. Inserisci prua e poppa della corazzata c3: "<<endl;
            cin>>prow>>stern;
            giocatore1.set_battleship(prow, stern);
            b2_center = giocatore1.get_battleshipCenter(prow,stern);
            b2_position = giocatore1.get_pos_battleship(b2_center);
        }
        set_player2.push_back(b2_center); //Coordinate B2 in indice 1 del vector
        set_position2.push_back(b2_position); //Orientamento b2 in indice 1 del vector

        cout<<"Inserisci prua e poppa della corazzata c3: "<<endl;
        string b3_center;
        int b3_position;
        try
        {
            cin>>prow>>stern;
            giocatore1.set_battleship(prow, stern);
            b3_center = giocatore1.get_battleshipCenter(prow,stern);
            b3_position = giocatore1.get_pos_battleship(b3_center);
        }
        catch(...)
        {
            cout<<"Errore! Un tentativo rimasto. Inserisci prua e poppa della corazzata c3: "<<endl;
            cin>>prow>>stern;
            giocatore1.set_battleship(prow, stern);
            b3_center = giocatore1.get_battleshipCenter(prow,stern);
            b3_position = giocatore1.get_pos_battleship(b3_center);
        }
        set_player2.push_back(b3_center); //Coordinate B3 in indice 2 del vector
        set_position2.push_back(b3_position); //Orientamento b3 in indice 2 del vector
        
        cout <<giocatore1.print_dif() <<endl; 

        // INSERIMENTO NAVI DI SUPPORTO
        cout<<"Inserisci prua e poppa della nave di supporto n1: "<<endl;
        string n1_center;
        int n1_position;
        try
        {
            cin>>prow>>stern;
            giocatore1.set_support(prow, stern);
            n1_center = giocatore1.get_supportCenter(prow, stern);
            n1_position = giocatore1.get_pos_support(n1_center);
        }
        catch(...)
        {
            cout<<"Errore! Un tentativo rimasto. Inserisci prua e poppa della nave di supporto n1: "<<endl;
            cin>>prow>>stern;
            giocatore1.set_support(prow, stern);
            n1_center = giocatore1.get_supportCenter(prow, stern);
            n1_position = giocatore1.get_pos_support(n1_center);
        }
        set_player2.push_back(n1_center); //Coordinate n1 in indice 3 del vector
        set_position2.push_back(n1_position); //Orientamento n1 in indice 3 del vector
        
        cout<<"Inserisci prua e poppa della nave di supporto n2: "<<endl;
        string n2_center;
        int n2_position;
        try
        {
            cin>>prow>>stern;
            giocatore1.set_support(prow, stern);
            n2_center = giocatore1.get_supportCenter(prow, stern);
            n2_position=giocatore1.get_pos_support(n2_center);
        }
        catch(...)
        {
            cout<<"Errore! Un tentativo rimasto. Inserisci prua e poppa della nave di supporto n2: "<<endl;
            cin>>prow>>stern;
            giocatore1.set_support(prow, stern);
            n2_center = giocatore1.get_supportCenter(prow, stern);
            n2_position=giocatore1.get_pos_support(n2_center);
        }
        set_player2.push_back(n2_center); //Coordinate n2 in indice 4 del vector
        set_position2.push_back(n2_position); //Orientamento n2 in indice 4 del vector
        
        cout<<"Inserisci prua e poppa della nave di supporto n3: "<<endl;
        string n3_center;
        int n3_position;
        try
        {
            cin>>prow>>stern;
            giocatore1.set_support(prow, stern);
            n3_center = giocatore1.get_supportCenter(prow,stern);
            n3_position = giocatore1.get_pos_support(n3_center);
        }
        catch(...)
        {
            cout<<"Errore! Un tentativo rimasto.Inserisci prua e poppa della nave di supporto n3: "<<endl;
            cin>>prow>>stern;
            giocatore1.set_support(prow, stern);
            n3_center = giocatore1.get_supportCenter(prow,stern);
            n3_position = giocatore1.get_pos_support(n3_center);
        }
        set_player2.push_back(n3_center); //Coordinate n3 in indice 5 del vector
        set_position2.push_back(n3_position); //Orientamento n3 in indice 5 del vector

        cout <<giocatore1.print_dif() <<endl;

        //INSERIMENTO SOTTOMARINO
        cout<<"Inserisci prua e poppa del sottomarino s1: "<<endl;
        string sub1_center;
        try
        {
            cin>>sub1_center;
            giocatore1.set_submarine(sub1_center);
        }
        catch(...)
        {
            cout<<"Errore! Un tentativo rimasto.Inserisci prua e poppa del sottomarino s1: "<<endl;
            cin>>sub1_center;
            giocatore1.set_submarine(sub1_center);
        }
        set_player2.push_back(sub1_center); //Coordinate sub1 in indice 6 del vector
        set_position2.push_back(0); //Orientamento sub1 in indice 6 del vector
        
        cout<<"Inserisci prua e poppa del sottomarino s2: "<<endl;
        string sub2_center;
        try
        {
            cin>>sub2_center;
            giocatore1.set_submarine(sub2_center);
        }
        catch(...)
        {
            cout<<"Errore! Un tentativo rimasto.Inserisci prua e poppa del sottomarino s2: "<<endl;
            cin>>sub2_center;
            giocatore1.set_submarine(sub2_center);
        }
        set_player2.push_back(sub2_center); //Coordinate sub2 in indice 7 del vector
        set_position2.push_back(0); //Orientamento sub2 in indice 7 del vector

        cout << "GIOCATORE: " << endl;
        cout <<giocatore1.print_dif() <<endl;

        //INIZIO PARTITA
        int turni = 0;
        int start = rand()%2;
        start_replay = start;

        if(start == 0)
            cout<<"... ...INIZIA IL GIOCATORE... ..." << endl;
        else 
            cout <<"... ...INIZIA IL BOT... ..." <<endl;
        
        while(turni < 200)
        {
            if (start == 0 || start == 2) //Se start = 0 inizia il giocatore, se start = 2 ha iniziato il bot
            {
                string xyOrigin, xyTarget;
                valid = true;
                cout<<"Giocatore inserisci coordinate nel formato xyOrigin xyTarget: " <<endl;
                cin>>xyOrigin>>xyTarget;

                while(valid)
                {
                    if(xyOrigin == "XX" && xyTarget == "XX" || xyOrigin == "xx" && xyTarget == "xx")
                    {
                        cout<< giocatore1.print_dif() <<endl;
                        cout<<giocatore1.print_att() << endl;
                        cout<<"Inserisci coordinate nel formato xyOrigin xyTarget: " <<endl;
                        cin>>xyOrigin>>xyTarget;
                    }
                    else if (xyOrigin =="AA" && xyTarget=="AA" || xyOrigin =="aa" && xyTarget=="aa")
                    {
                        giocatore1.clear_Y();
                        cout<< giocatore1.print_att() <<endl;
                        cout<<"Inserisci coordinate nel formato xyOrigin xyTarget: " <<endl;
                        cin>>xyOrigin>>xyTarget;
                    }
                    else if(xyOrigin.length() > 3 || xyTarget.length() > 3 ) 
                    {
                        cout<<"Errore! Un tentativo rimasto. Inserisci coordinate nel formato xyOrigin xyTarget: " <<endl;
                        cin>>xyOrigin>>xyTarget;
                    }
                    else if(!(Helper::convert_lett(xyOrigin) > -1 && Helper::convert_lett(xyOrigin) < 12) && !(Helper::convert_num(xyOrigin) > -1 && Helper::convert_num(xyOrigin) < 12))
                    {
                        cout<<"Errore! Un tentativo rimasto. Inserisci coordinate nel formato xyOrigin xyTarget: " <<endl;
                        cin>>xyOrigin>>xyTarget;
                    }
                    else if(!(Helper::convert_lett(xyTarget) > -1 && Helper::convert_lett(xyTarget) < 12) && !(Helper::convert_num(xyTarget) > -1 && Helper::convert_num(xyTarget) < 12))
                    {
                        cout<<"Errore! Un tentativo rimasto. Inserisci coordinate nel formato xyOrigin xyTarget: " <<endl;
                        cin>>xyOrigin>>xyTarget;
                    }
                    else
                        valid = false;
                }
                player2.push_back(xyOrigin); //Vengono salvate le coordinate inserite dal giocatore ad ogni turno, l'indice parte da 0
                player2.push_back(xyTarget); //L'indice aumenta di uno
                
                xyOrigin = Helper::convert_row(Helper::convert_lett(xyOrigin)) + Helper::convert_col(Helper::convert_num(xyOrigin)); //utilizziamo questi comandi per trasformare le coordinate in maiuscolo
                xyTarget = Helper::convert_row(Helper::convert_lett(xyTarget)) + Helper::convert_col(Helper::convert_num(xyTarget)); 
                if(giocatore1.check_battleship(giocatore1.get_cell(xyOrigin))) //verifica che nella cella ci sia una corazzata, se c'è entra nell'if
                {
                    cout<<"---> CORAZZATA IN " << xyOrigin << " FA FUOCO SU CASELLA " << xyTarget << endl;

                    bot1.fire(xyTarget); //Se il giocatore attacca una casella vuota non succede niente, altrimenti cambia la lettera della nave presa e la mette in minuscolo
                    if(bot1.get_cell(xyTarget) == 0) //se la cella è vuota fai apparire una O nella cella attacco corrispondente del giocatore
                        giocatore1.not_hit(xyTarget);
                    else        
                        giocatore1.hit(xyTarget); //se la casella è occupata da una nave segna una X nella cella di attacco del giocatore
                    //Se xyTarget è una cella occupata da un sottomarino, il sottomarino affonda 
                    if(xyTarget == sub1_centerB)
                        bot1.sunk_submarine(sub1_centerB);
                    else if(xyTarget == sub2_centerB)
                        bot1.sunk_submarine(sub2_centerB);
                }
                else if(giocatore1.check_submarine(xyOrigin) && giocatore1.space_submarine(xyTarget)) //controlla se c'e un sottomarino
                {
                    giocatore1.move_submarine(xyOrigin, xyTarget); //sposto il sottomarino
                    //AGGIORNA IL NUOVO CENTRO DEL SOTTOMARINO 
                    if(sub1_center == xyOrigin)
                        sub1_center = xyTarget;
                    else if(sub2_center == xyOrigin)
                        sub2_center = xyTarget;
                    Radar r = Radar(); //creo oggetto r che equivale ad un array 5x5
                    bot1.radar(xyTarget); //ha salvato nell'array radar_s del bot le corrispondenti celle della griglia di difesa, salvando le navi avvistate nel raggio 5x5
                    for(int i = 0; i<5; i++) //5 è la dimensione dell'array
                    {
                        for(int j = 0; j< 5; j++)
                        {
                            r.set_radarS(bot1.get_valueRadar(i,j),i,j); //Vengono salvate nell'oggetto r le celle dell'array radar_s
                        }
                    }
                    giocatore1.set_radar(xyTarget, r); //salva nell'array di attacco del giocatore ciò che l'oggeetto r ha salvato
                    giocatore1.reveal(); //trasforma le lettere delle navi in Y
                    for(int i = 0; i<5; i++)
                    {
                        for(int j = 0; j< 5; j++)
                        {
                            r.set_radarS(0,i,j);
                        }
                    }
                }
                else if((giocatore1.space_support(xyTarget, giocatore1.get_pos_support(xyOrigin))) && (xyOrigin == n1_center || xyOrigin == n2_center || xyOrigin == n3_center)) //verifichiamo che ci sia una nave di supporto
                {
                    cout<<" -> NAVE DI SUPPORTO IN " << xyOrigin << " SI SPOSTA IN " << xyTarget << endl;
                    
                    int n_pos = giocatore1.get_pos_support(xyOrigin);
                    int b_pos =  giocatore1.get_pos_battleship(xyOrigin);
                    giocatore1.move_support(xyOrigin, xyTarget, n_pos);
                    
                    //Aggiorna il nuovo centro
                    if(xyOrigin == n1_center)       n1_center = xyTarget;
                    else if(xyOrigin == n2_center)  n2_center = xyTarget;
                    else if (xyOrigin == n3_center) n3_center = xyTarget;

                    if(giocatore1.find_support_center(xyTarget, n1_center, n_pos, n1_position)) 
                        giocatore1.fix_support(n1_center, n1_position);
                    else if(giocatore1.find_support_center(xyTarget, n2_center, n_pos, n2_position))
                        giocatore1.fix_support(n2_center, n2_position);
                    else if(giocatore1.find_support_center(xyTarget, n3_center, n_pos, n3_position))
                        giocatore1.fix_support(n3_center, n3_position);
                    
                    if(giocatore1.find_battleship_center(xyTarget, b1_center, b_pos, b1_position))
                        giocatore1.fix_battleship(b1_center, b1_position);
                    else if(giocatore1.find_battleship_center(xyTarget, b2_center, b_pos, b2_position))
                        giocatore1.fix_battleship(b2_center, b2_position);
                    else if(giocatore1.find_battleship_center(xyTarget, b3_center, b_pos, b3_position))
                        giocatore1.fix_battleship(b3_center, b3_position);
                }
                //Se la corazzata è stata attaccata interamente e quindi ha le c minuscole, viene affondata
                bot1.sunk_battleship(b1_centerB, b1_positionB);
                bot1.sunk_battleship(b2_centerB, b2_positionB);
                bot1.sunk_battleship(b3_centerB, b3_positionB);
                //Se la nave di supporto è stata attaccata interamente e quindi ha le s minuscole, viene affondata
                bot1.sunk_support(n1_centerB, n1_positionB);
                bot1.sunk_support(n2_centerB, n2_positionB);
                bot1.sunk_support(n3_centerB, n3_positionB);
                bot1.sunk_submarine(sub1_centerB);
                bot1.sunk_submarine(sub2_centerB);
                start = 2;
            }//chiude if start 
            if(start == 1 || start == 2) //se inizia il bot
            {
                //BOT
                
                string origin = Helper::convert_row(myUnifIntDist(myRandomEngine)) + Helper::convert_col(myUnifIntDist(myRandomEngine));
                bool valid = false;

                while(!valid) //Sceglie delle cordinate giuste di origine
                {
                    if(origin == b1_centerB  && !bot1.is_battleship_sink(b1_centerB, b1_positionB)) //la coordinata estratta è il centro
                        valid = true;                        
                    else if(origin == b2_centerB && !bot1.is_battleship_sink(b2_centerB, b2_positionB))
                        valid = true; 
                    else if(origin == b3_centerB && !bot1.is_battleship_sink(b3_centerB, b3_positionB))
                        valid = true; 
                    else if((origin == sub1_centerB) && !bot1.is_submarine_sink(sub1_centerB)) 
                        valid = true;
                    else if ((origin == sub2_centerB) && !bot1.is_submarine_sink(sub2_centerB))
                        valid = true;
                    else if(origin == n1_centerB && !bot1.is_support_sink(n1_centerB, n1_positionB))
                        valid = true;
                    else if(origin == n2_centerB && !bot1.is_support_sink(n2_centerB, n2_positionB))
                        valid = true;
                    else if(origin == n3_centerB && !bot1.is_support_sink(n3_centerB, n3_positionB))
                        valid = true;
                    else
                        origin = Helper::convert_row(myUnifIntDist(myRandomEngine)) + Helper::convert_col(myUnifIntDist(myRandomEngine)); 
                }

                string target = Helper::convert_row(myUnifIntDist(myRandomEngine)) + Helper::convert_col(myUnifIntDist(myRandomEngine)); //genera una coordinata random che serve per il sottomarino
                int row = Helper::convert_lett(target); 
                int col = Helper::convert_num(target);
                while(!bot1.free_cell(row,col))//se quella cella random è libera ti restituisce true, 
                {
                    target = Helper::convert_row(myUnifIntDist(myRandomEngine)) + Helper::convert_col(myUnifIntDist(myRandomEngine)); 
                    row = Helper::convert_lett(target); 
                    col = Helper::convert_num(target);
                }
                string xyTarget;
                if((origin == n1_centerB) || (origin == n2_centerB) || (origin == n3_centerB)) //E' sicuramente una nave in vita
                {
                    xyTarget = Helper::convert_row(myUnifIntDist(myRandomEngine)) + Helper::convert_col(myUnifIntDist(myRandomEngine));
                    bool control = false;
                    while(!control)
                    {
                        if(bot1.free_support_space(xyTarget,bot1.get_pos_support(origin))) 
                            control = true;
                        else
                            xyTarget = Helper::convert_row(myUnifIntDist(myRandomEngine)) + Helper::convert_col(myUnifIntDist(myRandomEngine));
                    }
                }
                player1.push_back(origin); //Vengono salvate le coordinate inserite dal bot ad ogni turno, l'indice parte da 0
                if(origin != b1_centerB && origin != b2_centerB && origin != b3_centerB)
                {
                   if(origin != n1_centerB && origin != n2_centerB && origin != n3_centerB)
                   {
                        player1.push_back(target);
                   }
                   else
                   {
                        player1.push_back(xyTarget);
                   }
                }
                
                //player1.push_back(xyTarget); //L'indice aumenta di uno
                //IL BOT HA FINITO DI GENERARE LE COORDINATE E PUO' INIZIARE AD AGIRE
                if(bot1.check_battleship(bot1.get_cell(origin))) //verifica che nella cella ci sia una corazzata, se c'è entra nell'if
                {
                    target = Helper::convert_row(myUnifIntDist(myRandomEngine)) + Helper::convert_col(myUnifIntDist(myRandomEngine));
                    player1.push_back(target);
                    giocatore1.fire(target); //mette minuscolo la lettera
                    if(giocatore1.get_cell(target) == 0) //se la cella non è vuota fai apparire una X nella cella attacco del giocatore
                        bot1.not_hit(target);
                    else 
                        bot1.hit(target);
                    
                    if(target == sub1_center)
                        giocatore1.sunk_submarine(sub1_center);
                    else if(target == sub2_center)
                        giocatore1.sunk_submarine(sub2_center);
                }
                else if(bot1.check_submarine(origin) && bot1.space_submarine(target)) //controlla se c'e un sottomarino
                {
                    bot1.move_submarine(origin, target);
                    if(origin == sub1_centerB)
                        sub1_centerB = target;
                    else if(origin == sub2_centerB)
                        sub2_centerB = target;
                    
                    Radar r = Radar();
                    giocatore1.radar(target);
                    for(int i = 0; i<5; i++)
                    {
                        for(int j = 0; j< 5; j++)
                        {
                            r.set_radarS(giocatore1.get_valueRadar(i,j),i,j);
                        }
                    }
                    bot1.set_radar(target, r);
                    bot1.reveal();  
                }
                else if((bot1.space_support(xyTarget, bot1.get_pos_support(origin))) && (origin == n1_centerB || origin == n2_centerB || origin == n3_centerB)) //verifichiamo che ci sia una nave di supporto
                {
                    int n_pos = bot1.get_pos_support(origin);
                    int b_pos =  bot1.get_pos_battleship(origin);
                    bot1.move_support(origin, xyTarget, n_pos);
                    //Aggiorna il nuovo centro
                    if(origin == n1_centerB)        n1_centerB = xyTarget;
                    else if(origin == n2_centerB)   n2_centerB = xyTarget;
                    else if(origin == n3_centerB)   n3_centerB = xyTarget;

                    if(bot1.find_support_center(xyTarget, n1_centerB, n_pos, n1_positionB)) 
                        bot1.fix_support(n1_centerB, n1_positionB);
                    else if(bot1.find_support_center(xyTarget, n2_centerB, n_pos, n2_positionB))
                        bot1.fix_support(n2_centerB, n2_positionB);
                    else if(bot1.find_support_center(xyTarget, n3_centerB, n_pos, n3_positionB))
                        bot1.fix_support(n3_centerB, n3_positionB);
                    
                    if(bot1.find_battleship_center(xyTarget, b1_centerB, b_pos, b1_positionB))
                        bot1.fix_battleship(b1_centerB, b1_positionB);
                    else if(bot1.find_battleship_center(xyTarget, b2_centerB, b_pos, b2_positionB))
                        bot1.fix_battleship(b2_centerB, b2_positionB);
                    else if(bot1.find_battleship_center(xyTarget, b3_centerB, b_pos, b3_positionB))
                        bot1.fix_battleship(b3_centerB, b3_positionB);
                }
                start = 2;
                giocatore1.sunk_battleship(b1_center, b1_position);
                giocatore1.sunk_battleship(b2_center, b2_position);
                giocatore1.sunk_battleship(b3_center, b3_position);
                giocatore1.sunk_support(n1_center, n1_position);
                giocatore1.sunk_support(n2_center, n2_position);
                giocatore1.sunk_support(n3_center, n3_position);
                giocatore1.sunk_submarine(sub1_center);
                giocatore1.sunk_submarine(sub2_center);
            } //if del bot
            //VITTORIA
            if(giocatore1.is_battleship_sink(b1_center, b1_position) && giocatore1.is_battleship_sink(b2_center, b2_position) && giocatore1.is_battleship_sink(b3_center, b3_position))
            {
                cout<<"Il Bot ha vinto! GOOD JOB!" <<endl;
                break;
            }
            else if(bot1.is_battleship_sink(b1_centerB, b1_positionB) && bot1.is_battleship_sink(b2_centerB, b2_positionB) && bot1.is_battleship_sink(b3_centerB, b3_positionB))
            {
                cout<<"Il giocatore ha vinto! GOOD JOB!" <<endl;
                break;
            }
            else if(turni == 199)
            {
                cout<<"NESSUNO ha vinto" <<endl;
                break;
            }

            turni++;  
            start = 2;        
        }//chiude while turni
    }//chiudi answer == 1
    else if(answer == "2")
    {
        //BOT VS BOT        
        //BOT 2
        cout<<"INSERIMENTO NAVI BOT2: ... ... "<<endl;  
        //CORAZZATE
        int b1_positionB2 = rand()%2; //0 = orizzontale o 1= verticale
        int b2_positionB2 = rand()%2;
        int b3_positionB2 = rand()%2;
        bool valid_bot2 = true;
        string b1_centerB2, b2_centerB2, b3_centerB2;

        while(valid_bot2)
        {
            b1_centerB2 = Helper::convert_row(myUnifIntDist(myRandomEngine)) + Helper::convert_col(myUnifIntDist(myRandomEngine));//A1
            if(bot2.is_battleshipValid(b1_centerB2,b1_positionB2) && bot2.free_battles_space(b1_centerB2,b1_positionB2))
                valid_bot2 = false;
        }
        bot2.set_battleshipRand(b1_centerB2, b1_positionB2);
        valid_bot2 = true;
        set_player2.push_back(b1_centerB2); //Coordinata b1 parte indice 0
        set_position2.push_back(b1_positionB2);//Orientamento b1 parte indice 0
        
        while(valid_bot2)
        {
            b2_centerB2 = Helper::convert_row(myUnifIntDist(myRandomEngine)) + Helper::convert_col(myUnifIntDist(myRandomEngine));
            if(bot2.is_battleshipValid(b2_centerB2,b2_positionB2) && bot2.free_battles_space(b2_centerB2,b2_positionB2))
                valid_bot2=false;   
        }
        bot2.set_battleshipRand(b2_centerB2, b2_positionB2);
        valid_bot2 = true;
        set_player2.push_back(b2_centerB2); //Coordinata b2 parte indice 1
        set_position2.push_back(b2_positionB2);//Orientamento b2 parte indice 1
        
        while(valid_bot2)
        {
            b3_centerB2 = Helper::convert_row(myUnifIntDist(myRandomEngine)) + Helper::convert_col(myUnifIntDist(myRandomEngine));
            if(bot2.is_battleshipValid(b3_centerB2,b3_positionB2) && bot2.free_battles_space(b3_centerB2,b3_positionB2))
                valid_bot2=false;  
        }
        bot2.set_battleshipRand(b3_centerB2, b3_positionB2);
        valid_bot2 = true;
        set_player2.push_back(b3_centerB2); //Coordinata b3 parte indice 2
        set_position2.push_back(b3_positionB2);//Orientamento b3 parte indice 2

        //NAVI DI SUPPORTO
        int n1_positionB2 = rand()%2; //0 = orizzontale o 1= verticale
        int n2_positionB2 = rand()%2;
        int n3_positionB2 = rand()%2;
        string n1_centerB2, n2_centerB2, n3_centerB2;
        
        while(valid_bot2)
        {
            n1_centerB2 = Helper::convert_row(myUnifIntDist(myRandomEngine)) + Helper::convert_col(myUnifIntDist(myRandomEngine));//A1
            if(bot2.is_supportValid(n1_centerB2,n1_positionB2) && bot2.free_support_space(n1_centerB2,n1_positionB2))
                valid_bot2 = false;
        }
        bot2.set_supportRand(n1_centerB2,n1_positionB2);
        valid_bot2 = true;
        set_player2.push_back(n1_centerB2); //Coordinata n1 parte indice 3
        set_position2.push_back(n1_positionB2);//Orientamento n1 parte indice 3
        
        while(valid_bot2)
        {
            n2_centerB2 = Helper::convert_row(myUnifIntDist(myRandomEngine)) + Helper::convert_col(myUnifIntDist(myRandomEngine));
            if(bot2.is_supportValid(n2_centerB2,n2_positionB2) && bot2.free_support_space(n2_centerB2,n2_positionB2))
                valid_bot2=false;   
        }
        bot2.set_supportRand(n2_centerB2, n2_positionB2);
        valid_bot2 = true;
        set_player2.push_back(n2_centerB2); //Coordinata n2 parte indice 4
        set_position2.push_back(n2_positionB2);//Orientamento n2 parte indice 4

        while(valid_bot2)
        {
            n3_centerB2 = Helper::convert_row(myUnifIntDist(myRandomEngine)) + Helper::convert_col(myUnifIntDist(myRandomEngine));
            if(bot2.is_supportValid(n3_centerB2,n3_positionB2) && bot2.free_support_space(n3_centerB2,n3_positionB2))
                valid_bot2=false;  
        }
        bot2.set_supportRand(n3_centerB2, n3_positionB2);
        valid_bot2 = true;
        set_player2.push_back(n3_centerB2); //Coordinata n3 parte indice 5
        set_position2.push_back(n3_positionB2);//Orientamento n3 parte indice 5
        
        //SOTTOMARINO
        string sub1_centerB2, sub2_centerB2;
        while(valid_bot2)
        {
            sub1_centerB2 = Helper::convert_row(myUnifIntDist(myRandomEngine)) + Helper::convert_col(myUnifIntDist(myRandomEngine));//A1
            if(bot2.free_cell(Helper::convert_lett(sub1_centerB2), Helper::convert_num(sub1_centerB2)))
                valid_bot2 = false;
        }
        bot2.set_submarineRand(sub1_centerB2);
        valid_bot2 = true;
        set_player2.push_back(sub1_centerB2); //Coordinata sub1 parte indice 6
        set_position2.push_back(0);//Orientamento sub1 parte indice 6
        
        while(valid_bot2)
        {
            sub2_centerB2 = Helper::convert_row(myUnifIntDist(myRandomEngine)) + Helper::convert_col(myUnifIntDist(myRandomEngine));
            if(bot2.free_cell(Helper::convert_lett(sub2_centerB2), Helper::convert_num(sub2_centerB2)))
                valid_bot2=false;   
        }
        bot2.set_submarineRand(sub2_centerB2);
        valid_bot2 = true;
        set_player2.push_back(sub2_centerB2); //Coordinata sub1 parte indice 7
        set_position2.push_back(0);//Orientamento sub2 parte indice 7

        cout<< "BOT 1: " <<endl;
        cout << bot1.print_dif()<<endl<< bot2.print_att()<<endl;
        cout<< "BOT 2: " <<endl;
        cout << bot2.print_dif()<<endl<< bot2.print_att()<<endl;
        
        //INIZIO PARTITA 
        int turni = 0;
        int start = rand()%2;
        start_replay = start; //serve per il replay
        if(start == 0)
            cout<<"...INIZIA IL BOT2..." << endl;
        else
            cout<<"...INIZIA IL BOT1..." << endl;
        
        while(turni < 100)
        {
            if (start == 0 || start == 2) //se inizia il bot2
            {
                //BOT2
                string origin = Helper::convert_row(myUnifIntDist(myRandomEngine)) + Helper::convert_col(myUnifIntDist(myRandomEngine));
                bool valid = false;

                while(!valid) //Sceglie delle cordinate giuste di origine, origin è il centro della nave da cui parte l'azione
                {
                    //controllo che il centro sia di qualche nave e che la nave non sia affondata, altrimenti riestrae
                    if(origin == b1_centerB2  && !bot2.is_battleship_sink(b1_centerB2, b1_positionB2)) 
                        valid = true;                        
                    else if(origin == b2_centerB2 && !bot2.is_battleship_sink(b2_centerB2, b2_positionB2))
                        valid = true; 
                    else if(origin == b3_centerB2 && !bot2.is_battleship_sink(b3_centerB2, b3_positionB2))
                        valid = true; 
                    else if((origin == sub1_centerB2) && !bot2.is_submarine_sink(sub1_centerB2)) 
                        valid = true;
                    else if ((origin == sub2_centerB2) && !bot2.is_submarine_sink(sub2_centerB2))
                        valid = true;
                    else if(origin == n1_centerB2 && !bot2.is_support_sink(n1_centerB2, n1_positionB2))
                        valid = true;
                    else if(origin == n2_centerB2 && !bot2.is_support_sink(n2_centerB2, n2_positionB2))
                        valid = true;
                    else if(origin == n3_centerB2 && !bot2.is_support_sink(n3_centerB2, n3_positionB2))
                        valid = true;
                    else
                        origin = Helper::convert_row(myUnifIntDist(myRandomEngine)) + Helper::convert_col(myUnifIntDist(myRandomEngine)); 
                }
                //estrazione cella in cui devo spostare la nave (sempre il centro), vale per sottomarino
                string target = Helper::convert_row(myUnifIntDist(myRandomEngine)) + Helper::convert_col(myUnifIntDist(myRandomEngine)); //genera una coordinata random che serve per il sottomarino
                int row = Helper::convert_lett(target); 
                int col = Helper::convert_num(target);
                while(!bot2.free_cell(row,col))//se quella cella random è libera ti restituisce true, 
                {
                    target = Helper::convert_row(myUnifIntDist(myRandomEngine)) + Helper::convert_col(myUnifIntDist(myRandomEngine)); 
                    row = Helper::convert_lett(target); 
                    col = Helper::convert_num(target);
                }
                string xyTarget; //serve per la nave di supporto, è la cella dove dovrebbe spostarsi 
                if((origin == n1_centerB2) || (origin == n2_centerB2) || (origin == n3_centerB2))
                {
                    xyTarget = Helper::convert_row(myUnifIntDist(myRandomEngine)) + Helper::convert_col(myUnifIntDist(myRandomEngine));
                    bool control = false;
                    while(!control)
                    {
                        if(bot2.free_support_space(xyTarget, bot2.get_pos_support(origin)))
                            control = true;
                        else
                            xyTarget = Helper::convert_row(myUnifIntDist(myRandomEngine)) + Helper::convert_col(myUnifIntDist(myRandomEngine));
                    }
                }
                player2.push_back(origin); //Vengono salvate le coordinate inserite dal bot ad ogni turno, l'indice parte da 0
                if(origin != b1_centerB && origin != b2_centerB && origin != b3_centerB)
                {
                   if(origin != n1_centerB && origin != n2_centerB && origin != n3_centerB)
                        player2.push_back(target);
                   else
                        player2.push_back(xyTarget);
                }
                //se la nave è affondata la funzione restituisce true
                if(bot2.check_battleship(bot2.get_cell(origin))) //verifica che nella cella ci sia una corazzata, se c'è entra nell'if
                {
                    target = Helper::convert_row(myUnifIntDist(myRandomEngine)) + Helper::convert_col(myUnifIntDist(myRandomEngine));
                    player2.push_back(target);
                    cout<<"BOT 2---> CORAZZATA IN " << origin << " FA FUOCO SU CASELLA " << target << endl;
                    bot1.fire(target); //mette minuscolo la lettera
                    if(bot1.get_cell(target) == 0) //se la cella non è vuota fai apparire una X nella cella attacco del giocatore
                        bot2.not_hit(target); //altrimenti appare una O
                    else 
                        bot2.hit(target);
                    
                    if(target == sub1_centerB) //il sottomarino del bot1
                        bot1.sunk_submarine(sub1_centerB);
                    else if(target == sub2_centerB)
                        bot1.sunk_submarine(sub2_centerB);
                }                
                else if(bot2.check_submarine(origin) && bot2.space_submarine(target)) //controlla se c'e un sottomarino
                {
                    cout<<"BOT 2---> SOTTOMARINO IN " << origin << " SI SPOSTA IN CASELLA " << target << endl;
                    bot2.move_submarine(origin, target);
                    if(origin == sub1_centerB2)
                        sub1_centerB2 = target;
                    else if(origin == sub2_centerB2)
                        sub2_centerB2 = target;
                    Radar r = Radar();
                    bot1.radar(target);
                    for(int i = 0; i<5; i++)
                    {
                        for(int j = 0; j< 5; j++)
                        {
                            r.set_radarS(bot1.get_valueRadar(i,j),i,j);
                        }
                    }
                    bot2.set_radar(target, r);
                    bot2.reveal();  
                }
                else if((bot2.space_support(xyTarget, bot2.get_pos_support(origin))) && (origin == n1_centerB2 || origin == n2_centerB2 || origin == n3_centerB2)) //verifichiamo che ci sia una nave di supporto
                {
                    cout<<"BOT 2---> NAVE DI SUPPORTO IN " << origin << " SI SPOSTA IN  " << xyTarget << endl;
                    int n_pos = bot2.get_pos_support(origin);
                    int b_pos =  bot2.get_pos_battleship(origin);
                    bot2.move_support(origin, xyTarget, n_pos);
                    //Aggiorna il nuovo centro
                    if(origin == n1_centerB2)        n1_centerB2 = xyTarget;
                    else if(origin == n2_centerB2)   n2_centerB2 = xyTarget;
                    else if(origin == n3_centerB2)   n3_centerB2 = xyTarget;

                    if(bot2.find_support_center(xyTarget, n1_centerB2, n_pos, n1_positionB2)) 
                        bot2.fix_support(n1_centerB2, n1_positionB2);
                    else if(bot2.find_support_center(xyTarget, n2_centerB2, n_pos, n2_positionB2))
                        bot2.fix_support(n2_centerB2, n2_positionB2);
                    else if(bot2.find_support_center(xyTarget, n3_centerB2, n_pos, n3_positionB2))
                        bot2.fix_support(n3_centerB2, n3_positionB2);
                    
                    if(bot2.find_battleship_center(xyTarget, b1_centerB2, b_pos, b1_positionB2))
                        bot2.fix_battleship(b1_centerB2, b1_positionB2);
                    else if(bot2.find_battleship_center(xyTarget, b2_centerB2, b_pos, b2_positionB2))
                        bot2.fix_battleship(b2_centerB2, b2_positionB2);
                    else if(bot2.find_battleship_center(xyTarget, b3_centerB2, b_pos, b3_positionB2))
                        bot2.fix_battleship(b3_centerB2, b3_positionB2);
                }
                bot1.sunk_battleship(b1_centerB, b1_positionB);
                bot1.sunk_battleship(b2_centerB, b2_positionB);
                bot1.sunk_battleship(b3_centerB, b3_positionB);
                bot1.sunk_support(n1_centerB, n1_positionB);
                bot1.sunk_support(n2_centerB, n2_positionB);
                bot1.sunk_support(n3_centerB, n3_positionB);
                bot1.sunk_submarine(sub1_centerB);
                bot1.sunk_submarine(sub2_centerB);      
                start = 2;
            }
            if(start == 1 || start == 2) //se inizia il bot1
            {
                //BOT
                string origin = Helper::convert_row(myUnifIntDist(myRandomEngine)) + Helper::convert_col(myUnifIntDist(myRandomEngine));
                bool valid = false;

                while(!valid) //Sceglie delle cordinate giuste di origine
                {
                    if(origin == b1_centerB  && !bot1.is_battleship_sink(b1_centerB, b1_positionB)) //la coordinata estratta è il centro
                        valid = true;                        
                    else if(origin == b2_centerB && !bot1.is_battleship_sink(b2_centerB, b2_positionB))
                        valid = true; 
                    else if(origin == b3_centerB && !bot1.is_battleship_sink(b3_centerB, b3_positionB))
                        valid = true; 
                    else if((origin == sub1_centerB) && !bot1.is_submarine_sink(sub1_centerB)) 
                        valid = true;
                    else if ((origin == sub2_centerB) && !bot1.is_submarine_sink(sub2_centerB))
                        valid = true;
                    else if(origin == n1_centerB && !bot1.is_support_sink(n1_centerB, n1_positionB))
                        valid = true;
                    else if(origin == n2_centerB && !bot1.is_support_sink(n2_centerB, n2_positionB))
                        valid = true;
                    else if(origin == n3_centerB && !bot1.is_support_sink(n3_centerB, n3_positionB))
                        valid = true;
                    else
                        origin = Helper::convert_row(myUnifIntDist(myRandomEngine)) + Helper::convert_col(myUnifIntDist(myRandomEngine)); 
                }
                string target = Helper::convert_row(myUnifIntDist(myRandomEngine)) + Helper::convert_col(myUnifIntDist(myRandomEngine)); //genera una coordinata random che serve per il sottomarino
                int row = Helper::convert_lett(target); 
                int col = Helper::convert_num(target);
                while(!bot1.free_cell(row,col))//se quella cella random è libera ti restituisce true, 
                {
                    target = Helper::convert_row(myUnifIntDist(myRandomEngine)) + Helper::convert_col(myUnifIntDist(myRandomEngine)); 
                    row = Helper::convert_lett(target); 
                    col = Helper::convert_num(target);
                }
                string xyTarget;
                if((origin == n1_centerB) || (origin == n2_centerB) || (origin == n3_centerB)) //E' sicuramente una nave in vita
                {
                    xyTarget = Helper::convert_row(myUnifIntDist(myRandomEngine)) + Helper::convert_col(myUnifIntDist(myRandomEngine));
                    bool control = false;
                    while(!control)
                    {
                        if(bot1.free_support_space(xyTarget,bot1.get_pos_support(origin))) 
                            control = true;
                        else
                            xyTarget = Helper::convert_row(myUnifIntDist(myRandomEngine)) + Helper::convert_col(myUnifIntDist(myRandomEngine));
                    }
                }

                player1.push_back(origin); //Vengono salvate le coordinate inserite dal bot ad ogni turno, l'indice parte da 0
                if(origin != b1_centerB && origin != b2_centerB && origin != b3_centerB)
                {
                   if(origin != n1_centerB && origin != n2_centerB && origin != n3_centerB)
                   {
                        player1.push_back(target);
                   }
                   else
                   {
                        player1.push_back(xyTarget);
                   }
                }

                //IL BOT HA FINITO DI GENERARE LE COORDINATE E PUO' INIZIARE AD AGIRE
                if(bot1.check_battleship(bot1.get_cell(origin))) //verifica che nella cella ci sia una corazzata, se c'è entra nell'if
                {
                    target = Helper::convert_row(myUnifIntDist(myRandomEngine)) + Helper::convert_col(myUnifIntDist(myRandomEngine));
                    player1.push_back(target);
                    cout<<"BOT 1---> CORAZZATA IN " << origin << " FA FUOCO SU CASELLA " << target << endl;
                    bot2.fire(target); //mette minuscolo la lettera
                    if(bot2.get_cell(target) == 0) //se la cella non è vuota fai apparire una X nella cella attacco del giocatore
                        bot1.not_hit(target);
                    else 
                        bot1.hit(target);
                    
                    if(target == sub1_centerB2)
                        bot2.sunk_submarine(sub1_centerB2);
                    else if(target == sub2_centerB2)
                        bot2.sunk_submarine(sub2_centerB2);
                }
                else if(bot1.check_submarine(origin) && bot1.space_submarine(target)) //controlla se c'e un sottomarino
                {
                    cout<<"BOT 1---> SOTTOMARINO IN " << origin << " SI SPOSTA IN CASELLA " << target << endl;
                    bot1.move_submarine(origin, target);
                    if(origin == sub1_centerB)
                        sub1_centerB = target;
                    else if(origin == sub2_centerB)
                        sub2_centerB = target;
                    
                    Radar r = Radar();
                    bot2.radar(target);
                    for(int i = 0; i<5; i++)
                    {
                        for(int j = 0; j< 5; j++)
                        {
                            r.set_radarS(bot2.get_valueRadar(i,j),i,j);
                        }
                    }
                    bot1.set_radar(target, r);
                    bot1.reveal();  
                }
                else if((bot1.space_support(xyTarget, bot1.get_pos_support(origin))) && (origin == n1_centerB || origin == n2_centerB || origin == n3_centerB)) //verifichiamo che ci sia una nave di supporto
                {
                    cout<<"BOT 1---> NAVE DI SUPPORTO IN " << origin << " SI SPOSTA IN " << xyTarget << endl;
                    int n_pos = bot1.get_pos_support(origin);
                    int b_pos =  bot1.get_pos_battleship(origin);
                    bot1.move_support(origin, xyTarget, n_pos);
                    //Aggiorna il nuovo centro
                    if(origin == n1_centerB)        n1_centerB = xyTarget;
                    else if(origin == n2_centerB)   n2_centerB = xyTarget;
                    else if(origin == n3_centerB)   n3_centerB = xyTarget;

                    if(bot1.find_support_center(xyTarget, n1_centerB, n_pos, n1_positionB)) 
                        bot1.fix_support(n1_centerB, n1_positionB);
                    else if(bot1.find_support_center(xyTarget, n2_centerB, n_pos, n2_positionB))
                        bot1.fix_support(n2_centerB, n2_positionB);
                    else if(bot1.find_support_center(xyTarget, n3_centerB, n_pos, n3_positionB))
                        bot1.fix_support(n3_centerB, n3_positionB);
                    
                    if(bot1.find_battleship_center(xyTarget, b1_centerB, b_pos, b1_positionB))
                        bot1.fix_battleship(b1_centerB, b1_positionB);
                    else if(bot1.find_battleship_center(xyTarget, b2_centerB, b_pos, b2_positionB))
                        bot1.fix_battleship(b2_centerB, b2_positionB);
                    else if(bot1.find_battleship_center(xyTarget, b3_centerB, b_pos, b3_positionB))
                        bot1.fix_battleship(b3_centerB, b3_positionB);
                }
                start = 2;
                bot2.sunk_battleship(b1_centerB2, b1_positionB2);
                bot2.sunk_battleship(b2_centerB2, b2_positionB2);
                bot2.sunk_battleship(b3_centerB2, b3_positionB2);
                bot2.sunk_support(n1_centerB2, n1_positionB2);
                bot2.sunk_support(n2_centerB2, n2_positionB2);
                bot2.sunk_support(n3_centerB2, n3_positionB2);
                bot2.sunk_submarine(sub1_centerB2);
                bot2.sunk_submarine(sub2_centerB2);
            }
            //VITTORIA
            if(bot2.is_battleship_sink(b1_centerB2, b1_positionB2) && bot2.is_battleship_sink(b2_centerB2, b2_positionB2) && bot2.is_battleship_sink(b3_centerB2, b3_positionB2))
            {
                cout<<"Il Bot1 ha vinto! GOOD JOB!" <<endl;
                break;
            }
            else if(bot1.is_battleship_sink(b1_centerB, b1_positionB) && bot1.is_battleship_sink(b2_centerB, b2_positionB) && bot1.is_battleship_sink(b3_centerB, b3_positionB))
            {
                cout<<"Il Bot2 ha vinto! GOOD JOB!" <<endl;
                break;
            }
            else if(turni == 99)
            {
                cout<<"NESSUNO ha vinto" <<endl;
                break;
            }
            cout<< "BOT 1: " <<endl;
            cout << bot1.print_dif()<<endl<< bot2.print_att()<<endl;
            cout<< "BOT 2: " <<endl;
            cout << bot2.print_dif()<<endl<< bot2.print_att()<<endl;
            turni++; 
            cout<< "Turni " << turni << endl; 
            start = 2;         
        }
        
    }//answer
    else
    {
        cout<<"answer non valida. ";
        continua = true; 
    }

    ofstream myfile;
    myfile.open("replay.txt");

    if(myfile.is_open())
    {
        myfile << "Coordinate iniziali scelte dal giocatore 1"<<endl;
        for(int i = 0; i < 3; i++) //corazzata occupa 2, 2 , 2 (posizione ,centro)
        {
            myfile << "Centro corazzata " << i << ": " << set_player1[i] << " Posizione: " << set_position1[i]<<endl; 
        }
        for(int i = 3; i < 6; i++) //corazzata occupa 2, 2 , 2 (posizione ,centro)
        {
            myfile << "Centro nave di supporto  " << i-2 << ": " << set_player1[i] << " Posizione: " << set_position1[i]<<endl; 
        }
        for(int i = 6; i < 7; i++) //corazzata occupa 2, 2 , 2 (posizione ,centro)
        {
            myfile << "Sottomarino  " << i-5 << ": " << set_player1[i] << " Posizione: " << set_position1[i]<<endl; 
        }
    //.................GIOCATORE 2....................................
        myfile << "Coordinate iniziali scelte dal giocatore 2"<<endl;
        for(int i = 0; i < 3; i++) //corazzata occupa 2, 2 , 2 (posizione ,centro)
        {
            myfile << "Centro corazzata " << i << ": " << set_player2[i] << " Posizione: " << set_position2[i]<<endl; 
        }
        for(int i = 3; i < 6; i++) //corazzata occupa 2, 2 , 2 (posizione ,centro)
        {
            myfile << "Centro nave di supporto  " << i-2 << ": " << set_player2[i] << " Posizione: " << set_position2[i]<<endl; 
        }
        for(int i = 6; i < 7; i++) //corazzata occupa 2, 2 , 2 (posizione ,centro)
        {
            myfile << "Sottomarino  " << i-5 << ": " << set_player2[i] << " Posizione: " << set_position2[i]<<endl; 
        }

    //.................INIZIO PARTITA...............
        if(start_replay == 0) //Se inizia il giocatore 1 o il bot 2
        {
            myfile << "Inizia il giocatore 2 : " << endl;

            for(int i = 0; i < player2.size()-1; i++)
            {
                myfile << "Giocatore 2: xyOrigin: " << player2[i] << " xyTarget: " << player2[i+1] << endl;
                if(player1.size() != i)
                    myfile << "Giocatore 1: xyOrigin: "<< player1[i] << " xyTarget: " << player1[i+1] << endl;
            }
        }
        else if(start_replay == 1)
        {
            myfile << "Inizia il giocatore 1 : " << endl;

            for(int i = 0; i < player1.size() -1; i++)
            {
                myfile << "Giocatore 1: xyOrigin: " << player1[i] << " xyTarget: " << player1[i+1] << endl;
                if(player2.size() != i)
                    myfile <<"Giocatore 2: xyOrigin: "<< player2[i] <<" xyTarget: " << player2[i+1] << endl;
            }
        }
        set_player1.clear();
        set_player2.clear();
        player1.clear();
        player2.clear();
        set_position1.clear();
        set_position2.clear();
    }
    else cout<<"file non trovato";
    myfile.close();
    }
    while(continua);
}