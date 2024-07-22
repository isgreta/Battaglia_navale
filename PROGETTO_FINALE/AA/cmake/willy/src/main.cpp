//AUTORE
#include "Battaglia.h"
#include "Bot.h"
#include "Helper.h"
#include "Radar.h"
#include <iostream>
#include <string>

using namespace std;

int main(void)
{
    Battaglia giocatore1 = Battaglia(); 
    Bot bot1 = Bot();
    Bot bot2 = Bot();
    bool continua;
    string risposta, prua, poppa;

    do
    {
        cout <<endl<<"a) Partita giocatore vs computer: premi \"1\"" <<endl 
            << "b) Partita computer vs computer: premi\"2\""<<endl
            << "c) Terminare: premi\"3\""<<endl;
             
        cin>>risposta;
        cout<<endl;
    }
    while(continua);

    if(risposta=="3")
    {
        cout<<"Programma terminato";
        continua = false;
    }
    else if(risposta == "1")
    {
        //GIOCATORE
        //INSERIMENTO NAVI
        //CORAZZATE
        cout<<"Inserisci prua e poppa della corazzata c1: " <<endl;
        //cin>>prua>>poppa;
        prua = "B6";
        poppa = "B10";
        giocatore1.set_battleship(prua, poppa);
        string b1_center= giocatore1.get_battleshipCenter(prua,poppa);
        int b1_position = giocatore1.get_pos_battleship(b1_center);
        
        
        cout<<"Inserisci prua e poppa della corazzata c2: "<<endl;
        //cin>>prua>>poppa;
        prua = "F8";
        poppa = "F12";
        giocatore1.set_battleship(prua, poppa);
        string b2_center = giocatore1.get_battleshipCenter(prua,poppa);
        int b2_position = giocatore1.get_pos_battleship(b2_center);

        cout<<"Inserisci prua e poppa della corazzata c3: "<<endl;
        //cin>>prua>>poppa;
        prua = "D2";
        poppa = "H2";
        giocatore1.set_battleship(prua, poppa);
        string b3_center = giocatore1.get_battleshipCenter(prua,poppa);
        int b3_position = giocatore1.get_pos_battleship(b3_center);
        //cout <<giocatore1.stampa_difesa() <<endl; 
        
        //NAVI DI SUPPORTO
        cout<<"Inserisci prua e poppa della nave di supporto n1: "<<endl;
        //cin>>prua>>poppa;
        prua = "A4";
        poppa = "C4";
        giocatore1.set_support(prua, poppa);
        string n1_center = giocatore1.get_supportCenter(prua, poppa);
        int n1_position = giocatore1.get_pos_support(n1_center);

        
        cout<<"Inserisci prua e poppa della nave di supporto n2: "<<endl;
        //cin>>prua>>poppa;
        prua = "D6";
        poppa = "D8";
        giocatore1.set_support(prua, poppa);
        string n2_center = giocatore1.get_supportCenter(prua, poppa);
        int n2_position=giocatore1.get_pos_support(n2_center);


        cout<<"Inserisci prua e poppa della nave di supporto n3: "<<endl;
        //cin>>prua>>poppa;
        prua = "A1";
        poppa = "A3";
        giocatore1.set_support(prua, poppa);
        string n3_center = giocatore1.get_supportCenter(prua,poppa);
        int n3_position = giocatore1.get_pos_support(n3_center);

        //cout <<giocatore1.stampa_difesa() <<endl;
        
        //SOTTOMARINO
        cout<<"Inserisci prua e poppa del sottomarino s1: "<<endl;
        //cin>>prua;
        string sub1_center = "H11";
        giocatore1.set_submarine(sub1_center);

        cout<<"Inserisci prua e poppa del sottomarino s2: "<<endl;
        //cin>>prua;
        string sub2_center = "L2";
        giocatore1.set_submarine(sub2_center);

        
        //cout <<giocatore1.stampa_difesa() <<endl;
        
        //BOT
        cout<<"INSERIMENTO NAVI BOT: ... ... "<<endl;  
        //CORAZZATE
        int b1_positionB = rand()%2; //0 = orizzontale o 1= verticale
        int b2_positionB = rand()%2;
        int b3_positionB = rand()%2;
        string b1_centerB, b2_centerB, b3_centerB;
        bool valid = true;
        while(valid)
        {
            b1_centerB = bot1.random_coord();//A1
            if(bot1.is_battleshipValid(b1_centerB,b1_positionB) && bot1.free_battles_space(b1_centerB,b1_positionB))
                valid = false;
        }
        bot1.set_battleshipRand(b1_centerB, b1_positionB);
        valid = true;
        
        while(valid)
        {
            b2_centerB = bot1.random_coord();
            if(bot1.is_battleshipValid(b2_centerB,b2_positionB) && bot1.free_battles_space(b2_centerB,b2_positionB))
                valid=false;   
        }
        bot1.set_battleshipRand(b2_centerB, b2_positionB);
        valid = true;

        while(valid)
        {
            b3_centerB = bot1.random_coord();
            if(bot1.is_battleshipValid(b3_centerB,b3_positionB) && bot1.free_battles_space(b3_centerB,b3_positionB))
                valid=false;  
        }
        bot1.set_battleshipRand(b3_centerB, b3_positionB);
        valid = true;

        //NAVI DI SUPPORTO
        int n1_positionB = rand()%2; //0 = orizzontale o 1= verticale
        int n2_positionB = rand()%2;
        int n3_positionB = rand()%2;
        string n1_centerB, n2_centerB, n3_centerB;
        
        while(valid)
        {
            n1_centerB = bot1.random_coord();//A1
            if(bot1.is_supportValid(n1_centerB,n1_positionB) && bot1.free_support_space(n1_centerB,n1_positionB))
                valid = false;
        }
        bot1.set_supportRand(n1_centerB,n1_positionB);
        valid = true;
        
        while(valid)
        {
            n2_centerB = bot1.random_coord();
            if(bot1.is_supportValid(n2_centerB,n2_positionB) && bot1.free_support_space(n2_centerB,n2_positionB))
                valid=false;   
        }
        bot1.set_supportRand(n2_centerB, n2_positionB);
        valid = true;

        while(valid)
        {
            n3_centerB = bot1.random_coord();
            if(bot1.is_supportValid(n3_centerB,n3_positionB) && bot1.free_support_space(n3_centerB,n3_positionB))
                valid=false;  
        }
        bot1.set_supportRand(n3_centerB, n3_positionB);
        valid = true;
        

        //SOTTOMARINO
        string sub1_centerB, sub2_centerB;
        while(valid)
        {
            sub1_centerB = bot1.random_coord();//A1
            if(bot1.free_cell(Helper::convert_lett(sub1_centerB), Helper::convert_num(sub1_centerB)))
                valid = false;
        }
        bot1.set_submarineRand(sub1_centerB);
        valid = true;
        
        while(valid)
        {
            sub2_centerB = bot1.random_coord();
            if(bot1.free_cell(Helper::convert_lett(sub2_centerB), Helper::convert_num(sub2_centerB)))
                valid=false;   
        }
        bot1.set_submarineRand(sub2_centerB);
        valid = true;
        
        //STAMPA GRIGLIE DI DIFESA AGGIORNATE
        //da togliere
        cout<< "BOT: " <<endl;
        cout << bot1.print_dif()<<endl;
        cout<< "GIOCATORE: " <<endl;
        cout << giocatore1.print_dif()<<endl;

        //INIZIO PARTITA
        int turni = 0;
        int start = rand()%2;
        string xyOrigin, xyTarget;
        
        while(turni < 60)
        {
            if (start == 0 || start == 2) //se inizia il giocatore 
            {
                try
                {
                
                    cout<<"Giocatore inserisci coordinate nel formato xyOrigin xyTarget: " <<endl;
                    cin>>xyOrigin>>xyTarget;
            
                    if(xyOrigin == "XX" && xyTarget == "XX")
                    {
                        cout<< giocatore1.print_dif() <<endl;
                        cout<<giocatore1.print_att() << endl;
                        cout<<"Inserisci coordinate nel formato xyOrigin xyTarget: " <<endl;
                        cin>>xyOrigin>>xyTarget;
                    }
                    else if (xyOrigin =="AA" && xyTarget=="AA")
                    {
                        giocatore1.clear_Y();
                        cout<< giocatore1.print_att() <<endl;
                        //comando che toglie le Y nella griglia di attacco
                        cout<<"Inserisci coordinate nel formato xyOrigin xyTarget: " <<endl;
                        cin>>xyOrigin>>xyTarget;
                    }
                }
                catch(Battaglia::Invalid_Coordinate& e)
                {
                    cout<<"Hai inserito una coordinata non valida, inserisci di nuovo" <<endl;
                    cin>>xyOrigin>>xyTarget;
                }
                catch(Helper::Invalid_Coordinate_H& e)
                {
                    cout<<"Hai inserito una coordinata non valida, inserisci di nuovo" <<endl;
                    cin>>xyOrigin>>xyTarget;
                }

                xyOrigin = Helper::convert_row(Helper::convert_lett(xyOrigin)) + Helper::convert_col(Helper::convert_num(xyOrigin));
                if(giocatore1.check_battleship(giocatore1.get_cell(xyOrigin))) //verifica che nella cella ci sia una corazzata, se c'è entra nell'if
                {
                    xyTarget = Helper::convert_row(Helper::convert_lett(xyTarget)) + Helper::convert_col(Helper::convert_num(xyTarget));
                    cout<<" -> Corazzata in " << xyOrigin << " fa fuoco su casella " << xyTarget << endl;
                    bot1.fire(xyTarget); //mette minuscolo la lettera
                    if(bot1.get_cell(xyTarget) == 0) //se la cella non è vuota fai apparire una X nella cella attacco del giocatore
                        giocatore1.not_hit(xyTarget);
                    else 
                        giocatore1.hit(xyTarget);
                }
                else if(giocatore1.check_submarine(xyOrigin) && giocatore1.space_submarine(xyTarget)) //controlla se c'e un sottomarino
                {
                    xyTarget = Helper::convert_row(Helper::convert_lett(xyTarget)) + Helper::convert_col(Helper::convert_num(xyTarget));
                    cout<<" -> Nave di supporto in " << xyOrigin << " si sposta in " << xyTarget << endl;
                    giocatore1.move_submarine(xyOrigin, xyTarget); 
                    Radar r = Radar();
                    bot1.radar(xyTarget); //ha salvato nell'array 5x5 del bot ciò che ha visto
                    for(int i = 0; i<5; i++)
                    {
                        for(int j = 0; j< 5; j++)
                        {
                            r.set_radarS(bot1.get_valueRadar(i,j),i,j);
                        }
                    }
                    giocatore1.set_radar(xyTarget, r); //set radar da rivdere
                    giocatore1.reveal();
                    for(int i = 0; i<5; i++)
                    {
                        for(int j = 0; j< 5; j++)
                        {
                            r.set_radarS(0,i,j);
                        }
                    }
                    //cout<<"Giocatore griglia attacco: \n"<< giocatore1.stampa_attacco()<<endl;
                }
                else if((giocatore1.space_support(xyTarget, giocatore1.get_pos_support(xyOrigin))) && (xyOrigin == n1_center || xyOrigin == n2_center || xyOrigin == n3_center)) //verifichiamo che ci sia una nave di supporto
                {
                    int n_pos = giocatore1.get_pos_support(xyOrigin);
                    int b_pos =  giocatore1.get_pos_battleship(xyOrigin);
                    giocatore1.move_support(xyOrigin, xyTarget, n_pos);

                    //Aggiorna il nuovo centro
                    xyTarget = Helper::convert_row(Helper::convert_lett(xyTarget)) + Helper::convert_col(Helper::convert_num(xyTarget)); 
                    if(xyOrigin == n1_center)       n1_center = xyTarget;
                    else if(xyOrigin == n2_center)  n2_center = xyTarget;
                    else if (xyOrigin == n3_center) n3_center = xyTarget;
                    else if(xyOrigin == b1_center)  b1_center = xyTarget;
                    else if(xyOrigin == b2_center)  b2_center = xyTarget;
                    else if(xyOrigin == b3_center)  b3_center = xyTarget;

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
                giocatore1.sunk_battleship(b1_center, b1_position);
                giocatore1.sunk_battleship(b2_center, b2_position);
                giocatore1.sunk_battleship(b3_center, b3_position);
                giocatore1.sunk_support(n1_center, n1_position);
                giocatore1.sunk_support(n2_center, n2_position);
                giocatore1.sunk_support(n3_center, n3_position);
                giocatore1.sunk_submarine(sub1_center);
                giocatore1.sunk_submarine(sub2_center);
            
                cout<<"Giocatore griglia difesa: \n" << giocatore1.print_dif()<<endl;
                cout<<"Giocatore griglia attacco: \n"<< giocatore1.print_att()<<endl;
                start = 2;
            }
            if(start == 1 || start == 2) //se inizia il bot
            {
                //BOT
                string origin = bot1.random_coord();
                int row = Helper::convert_lett(origin); 
                int col= Helper::convert_num(origin);
                while(bot1.free_cell(row,col))//se quella cella random è libera ti restituisce true, 
                {
                    origin = bot1.random_coord(); 
                    row = Helper::convert_lett(origin); 
                    col= Helper::convert_num(origin);
                }

                
                string target = bot1.random_coord(); //genera una coordinata random che serve per il
                row = Helper::convert_lett(target); 
                col = Helper::convert_num(target);
                while(!bot1.free_cell(row,col))//se quella cella random è libera ti restituisce true, 
                {
                    target = bot1.random_coord(); 
                    row = Helper::convert_lett(target); 
                    col = Helper::convert_num(target);
                }

                string xyTarget = bot1.random_coord(); 
                while (!bot1.space_support(xyTarget, bot1.get_pos_support(origin))) //restituisce true se la nave di supporto può essere messa li
                {
                    xyTarget = bot1.random_coord(); 
                }


                if(bot1.check_battleship(bot1.get_cell(origin))) //verifica che nella cella ci sia una corazzata, se c'è entra nell'if
                {
                    target = bot1.random_coord();
                    giocatore1.fire(target); //mette minuscolo la lettera
                    if(giocatore1.get_cell(target) == 0) //se la cella non è vuota fai apparire una X nella cella attacco del giocatore
                        bot1.not_hit(target);
                    else 
                        bot1.hit(target);
                }
                else if(bot1.check_submarine(origin) && bot1.space_submarine(target)) //controlla se c'e un sottomarino
                {
                    bot1.move_submarine(origin, target);
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
                    //cout<<"Giocatore griglia attacco: \n"<< giocatore1.stampa_attacco()<<endl;   
                }
                else if((bot1.space_support(xyTarget, bot1.get_pos_support(origin))) && (origin == n1_centerB || origin == n2_centerB || origin == n3_centerB)) //verifichiamo che ci sia una nave di supporto
                {
                    //centerS1 --> pos1S
                    //centerS2 --> pos2S
                    //centerS3 --> pos3S
                    //giocatore1.verifica_naveS(giocatore1.get_cell(xyOrigin)) da vedere se serve nell?ig
                    
                    int n_pos = bot1.get_pos_support(origin);
                    int b_pos =  bot1.get_pos_battleship(origin);
                    bot1.move_support(origin, xyTarget, n_pos);

                    //Aggiorna il nuovo centro
                    xyTarget = Helper::convert_row(Helper::convert_lett(xyTarget)) + Helper::convert_col(Helper::convert_num(xyTarget)); 
                    if(origin == n1_centerB)        n1_centerB = xyTarget;
                    else if(origin == n2_centerB)   n2_centerB = xyTarget;
                    else if(origin == n3_centerB)   n3_centerB = xyTarget;
                    else if(origin == b1_centerB)   b1_centerB = xyTarget;
                    else if(origin == b2_centerB)   b2_centerB = xyTarget;
                    else if(origin == b3_centerB)   b3_centerB = xyTarget;

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
            }
            bot1.sunk_battleship(b1_centerB, b1_positionB);
            bot1.sunk_battleship(b2_centerB, b2_positionB);
            bot1.sunk_battleship(b3_centerB, b3_positionB);
            bot1.sunk_support(n1_centerB, n1_positionB);
            bot1.sunk_support(n2_centerB, n2_positionB);
            bot1.sunk_support(n3_centerB, n3_positionB);
            bot1.sunk_submarine(sub1_centerB);
            bot1.sunk_submarine(sub2_centerB);
            cout<<"Bot griglia difesa: \n"<< bot1.print_dif()<<endl;
            cout<<"Bot griglia attacco: \n"<< bot1.print_att()<<endl;
            turni++;
            //start = 2;
        } 
    }
    else if(risposta == "2")
    {
        //computer vs computer 
        //BOT1 INSERIMENTO NAVI
        cout<<"INSERIMENTO NAVI BOT1: ... ... "<<endl;  
        
        //CORAZZATE
        int pos1C = rand()%2; //0 = orizzontale o 1= verticale
        int pos2C = rand()%2;
        int pos3C = rand()%2;
        bool valid = true;
        string xy1, xy2, xy3;
        while(valid)
        {
            xy1 = bot1.random_coord();//A1
            if(bot1.is_battleshipValid(xy1,pos1C) && bot1.free_battles_space(xy1,pos1C))
                valid = false;
        }
        bot1.set_battleshipRand(xy1, pos1C);
        valid = true;
        
        while(valid)
        {
            xy2 = bot1.random_coord();
            if(bot1.is_battleshipValid(xy2,pos2C) && bot1.free_battles_space(xy2,pos2C))
                valid=false;   
        }
        bot1.set_battleshipRand(xy2, pos2C);
        valid = true;

        while(valid)
        {
            xy3 = bot1.random_coord();
            if(bot1.is_battleshipValid(xy3,pos3C) && bot1.free_battles_space(xy3,pos3C))
                valid=false;  
        }
        bot1.set_battleshipRand(xy3, pos3C);
        valid = true;

        //NAVI DI SUPPORTO
        int pos1S = rand()%2; //0 = orizzontale o 1= verticale
        int pos2S = rand()%2;
        int pos3S = rand()%2;
        string centerS1, centerS2, centerS3;
        
        while(valid)
        {
            centerS1 = bot1.random_coord();//A1
            if(bot1.is_supportValid(centerS1,pos1S) && bot1.free_support_space(centerS1,pos1S))
                valid = false;
        }
        bot1.set_supportRand(centerS1,pos1S);
        valid = true;
        
        while(valid)
        {
            centerS2 = bot1.random_coord();
            if(bot1.is_supportValid(centerS2,pos2S) && bot1.free_support_space(centerS2,pos2S))
                valid=false;   
        }
        bot1.set_supportRand(centerS2, pos2S);
        valid = true;

        while(valid)
        {
            centerS3 = bot1.random_coord();
            if(bot1.is_supportValid(centerS3,pos3S) && bot1.free_support_space(centerS3,pos3S))
                valid=false;  
        }
        bot1.set_supportRand(centerS3, pos3S);
        valid = true;
        
        //SOTTOMARINO
        string submarine1, submarine2;
        while(valid)
        {
            submarine1 = bot1.random_coord();//A1
            if(bot1.free_cell(Helper::convert_lett(submarine1), Helper::convert_num(submarine1)))
                valid = false;
        }
        bot1.set_submarineRand(submarine1);
        valid = true;
        
        while(valid)
        {
            submarine2 = bot1.random_coord();
            if(bot1.free_cell(Helper::convert_lett(submarine2), Helper::convert_num(submarine2)))
                valid=false;   
        }
        bot1.set_submarineRand(submarine2);
        valid = true;
//=======================================================================================================================
//=======================================================================================================================
//=======================================================================================================================        
        //BOT 2
        cout<<"INSERIMENTO NAVI BOT2: ... ... "<<endl;  
        //CORAZZATE
        int pos1C_bot2 = rand()%2; //0 = orizzontale o 1= verticale
        int pos2C_bot2 = rand()%2;
        int pos3C_bot2 = rand()%2;
        bool valid_bot2 = true;
        string b1_centerBot2, b2_centerBot2, b3_centerBot2;
        while(valid_bot2)
        {
            b1_centerBot2 = bot2.random_coord();//A1
            if(bot2.is_battleshipValid(b1_centerBot2,pos1C_bot2) && bot2.free_battles_space(b1_centerBot2,pos1C_bot2))
                valid_bot2 = false;
        }
        bot2.set_battleshipRand(b1_centerBot2, pos1C_bot2);
        valid_bot2 = true;
        
        while(valid_bot2)
        {
            b2_centerBot2 = bot2.random_coord();
            if(bot2.is_battleshipValid(b2_centerBot2,pos2C_bot2) && bot2.free_battles_space(b2_centerBot2,pos2C_bot2))
                valid_bot2=false;   
        }
        bot2.set_battleshipRand(b2_centerBot2, pos2C_bot2);
        valid_bot2 = true;

        while(valid_bot2)
        {
            b3_centerBot2 = bot2.random_coord();
            if(bot2.is_battleshipValid(b3_centerBot2,pos3C_bot2) && bot2.free_battles_space(b3_centerBot2,pos3C_bot2))
                valid_bot2=false;  
        }
        bot2.set_battleshipRand(b3_centerBot2, pos3C_bot2);
        valid_bot2 = true;

        //NAVI DI SUPPORTO
        int pos1S_bot2 = rand()%2; //0 = orizzontale o 1= verticale
        int pos2S_bot2 = rand()%2;
        int pos3S_bot2 = rand()%2;
        string centerS1_bot2, centerS2_bot2, centerS3_bot2;
        
        while(valid_bot2)
        {
            centerS1_bot2 = bot2.random_coord();//A1
            if(bot2.is_supportValid(centerS1_bot2,pos1S_bot2) && bot2.free_support_space(centerS1_bot2,pos1S_bot2))
                valid_bot2 = false;
        }
        bot2.set_supportRand(centerS1_bot2,pos1S_bot2);
        valid_bot2 = true;
        
        while(valid_bot2)
        {
            centerS2_bot2 = bot2.random_coord();
            if(bot2.is_supportValid(centerS2_bot2,pos2S_bot2) && bot2.free_support_space(centerS2_bot2,pos2S_bot2))
                valid_bot2=false;   
        }
        bot2.set_supportRand(centerS2_bot2, pos2S_bot2);
        valid_bot2 = true;

        while(valid_bot2)
        {
            centerS3_bot2 = bot2.random_coord();
            if(bot2.is_supportValid(centerS3_bot2,pos3S_bot2) && bot2.free_support_space(centerS3_bot2,pos3S_bot2))
                valid_bot2=false;  
        }
        bot2.set_supportRand(centerS3_bot2, pos3S_bot2);
        valid_bot2 = true;
        
        //SOTTOMARINO
        string submarine1_bot2, submarine2_bot2;
        while(valid_bot2)
        {
            submarine1_bot2 = bot2.random_coord();//A1
            if(bot2.free_cell(Helper::convert_lett(submarine1_bot2), Helper::convert_num(submarine1_bot2)))
                valid_bot2 = false;
        }
        bot2.set_submarineRand(submarine1_bot2);
        valid_bot2 = true;
        
        while(valid_bot2)
        {
            submarine2_bot2 = bot2.random_coord();
            if(bot2.free_cell(Helper::convert_lett(submarine2_bot2), Helper::convert_num(submarine2_bot2)))
                valid_bot2=false;   
        }
        bot2.set_submarineRand(submarine2_bot2);
        valid_bot2 = true;

        cout<< "BOT 1: " <<endl;
        cout << bot1.print_dif()<<endl;
        cout<< "BOT 2: " <<endl;
        cout << bot2.print_dif()<<endl;

        //INIZIO PARTITA 
        
        int turni = 0;
        int start = rand()%2;
        string xyOrigin, xyTarget;
        
        while(turni < 60)
        {
            
            if (start == 0 || start == 2) //se inizia il bot2
            {
                //BOT2
                string origin_bot2 = bot2.random_coord();
                int row_bot2 = Helper::convert_lett(origin_bot2); 
                int col_bot2= Helper::convert_num(origin_bot2);
                while(bot2.free_cell(row_bot2,col_bot2))//se quella cella random è libera ti restituisce true, 
                {
                    origin_bot2 = bot2.random_coord(); 
                    row_bot2 = Helper::convert_lett(origin_bot2); 
                    col_bot2= Helper::convert_num(origin_bot2);
                }

                string target_bot2 = bot2.random_coord();
                row_bot2 = Helper::convert_lett(target_bot2); 
                col_bot2 = Helper::convert_num(target_bot2);
                while(!bot1.free_cell(row_bot2,col_bot2))//se quella cella random è libera ti restituisce true, 
                {
                    target_bot2 = bot2.random_coord(); 
                    row_bot2 = Helper::convert_lett(target_bot2); 
                    col_bot2 = Helper::convert_num(target_bot2);
                }
                target_bot2 = "A2";

                if(bot2.check_battleship(bot2.get_cell(origin_bot2))) //verifica che nella cella ci sia una corazzata, se c'è entra nell'if
                {
                    target_bot2 = bot2.random_coord();
                    bot1.fire(target_bot2); //mette minuscolo la lettera
                    if(bot1.get_cell(target_bot2) == 0) //se la cella non è vuota fai apparire una X nella cella attacco del giocatore
                        bot2.not_hit(target_bot2);
                    else 
                        bot2.hit(target_bot2);
                }
                else if(bot2.check_submarine(origin_bot2) && bot2.space_submarine(target_bot2)) //controlla se c'e un sottomarino
                {
                    bot2.move_submarine(origin_bot2, target_bot2);
                    Radar r_bot2 = Radar();
                    bot1.radar(target_bot2);
                    for(int i = 0; i<5; i++)
                    {
                        for(int j = 0; j< 5; j++)
                        {
                            r_bot2.set_radarS(bot1.get_valueRadar(i,j),i,j);
                        }
                    }
                    bot2.set_radar(target_bot2, r_bot2);
                    bot2.reveal();
                    //cout<<"Giocatore griglia attacco: \n"<< giocatore1.stampa_attacco()<<endl;   
                }
                else if((bot2.space_support(target_bot2, bot2.get_pos_support(origin_bot2))) && (origin_bot2 == centerS1_bot2 || origin_bot2 == centerS2_bot2 || origin_bot2 == centerS3_bot2)) //verifichiamo che ci sia una nave di supporto
                {
                    //centerS1 --> pos1S
                    //centerS2 --> pos2S
                    //centerS3 --> pos3S
                    //giocatore1.verifica_naveS(giocatore1.get_cell(xyOrigin)) da vedere se serve nell?ig
                    
                    int pos_bot2 = bot2.get_pos_support(origin_bot2);
                    bot2.move_support(origin_bot2, target_bot2, pos_bot2);

                    //Aggiorna il nuovo centro
                    target_bot2 = Helper::convert_row(Helper::convert_lett(target_bot2)) + Helper::convert_col(Helper::convert_num(target_bot2)); 
                    if(origin_bot2 == centerS1_bot2)      centerS1_bot2 = target_bot2;
                    else if(origin_bot2 == centerS2_bot2) centerS2_bot2 = target_bot2;
                    else        centerS3_bot2 = target_bot2;
                    //bot1.ripara_naveS(centerS1, pos1S);
                    //bot1.ripara_naveS(centerS2, pos2S);
                    //bot1.ripara_naveS(centerS3, pos3S);
                }
                    start = 2;
            }
            else if(start == 1 || start == 2) //se inizia il bot1
            {
                //BOT1
                string origin = bot1.random_coord();
                int row = Helper::convert_lett(origin); 
                int col= Helper::convert_num(origin);
                while(bot1.free_cell(row,col))//se quella cella random è libera ti restituisce true, 
                {
                    origin = bot1.random_coord(); 
                    row = Helper::convert_lett(origin); 
                    col= Helper::convert_num(origin);
                }

                string target = bot1.random_coord();
                row = Helper::convert_lett(target); 
                col = Helper::convert_num(target);
                while(!bot1.free_cell(row,col))//se quella cella random è libera ti restituisce true, 
                {
                    target = bot1.random_coord(); 
                    row = Helper::convert_lett(target); 
                    col = Helper::convert_num(target);
                }
                target = "A2";

                if(bot1.check_battleship(bot1.get_cell(origin))) //verifica che nella cella ci sia una corazzata, se c'è entra nell'if
                {
                    target = bot1.random_coord();
                    bot2.fire(target); //mette minuscolo la lettera
                    if(bot2.get_cell(target) == 0) //se la cella non è vuota fai apparire una X nella cella attacco del giocatore
                        bot1.not_hit(target);
                    else 
                        bot1.hit(target);
                }
                else if(bot1.check_submarine(origin) && bot1.space_submarine(target)) //controlla se c'e un sottomarino
                {
                    bot1.move_submarine(origin, target);
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
                    //cout<<"Giocatore griglia attacco: \n"<< giocatore1.stampa_attacco()<<endl;
                    
                }
                else if((bot1.space_support(target, bot1.get_pos_support(origin))) && (origin == centerS1 || origin == centerS2 || origin == centerS3)) //verifichiamo che ci sia una nave di supporto
                {
                    
                    //centerS1 --> pos1S
                    //centerS2 --> pos2S
                    //centerS3 --> pos3S
                    //giocatore1.verifica_naveS(giocatore1.get_cell(xyOrigin)) da vedere se serve nell?ig
                    
                    int pos = bot1.get_pos_support(origin);
                    bot1.move_support(origin, target, pos);

                    //Aggiorna il nuovo centro
                    target = Helper::convert_row(Helper::convert_lett(target)) + Helper::convert_col(Helper::convert_num(target)); 
                    if(origin == centerS1)      centerS1 = target;
                    else if(origin == centerS2) centerS2 = target;
                    else        centerS3 = target;
                    //bot1.ripara_naveS(centerS1, pos1S);
                    //bot1.ripara_naveS(centerS2, pos2S);
                    //bot1.ripara_naveS(centerS3, pos3S);
                }
                    start = 2;
            }
            cout<<"Bot griglia difesa: \n"<< bot1.print_dif()<<endl;
            cout<<"Bot griglia attacco: \n"<< bot1.print_att()<<endl;
            turni++;
        }
    }
    else
    {
        cout<<"Risposta non valida. ";
        continua = true; 
    }
}

//g++ Battaglia.cpp Helper.cpp Bot.cpp Radar.cpp main.cpp -o main;./main