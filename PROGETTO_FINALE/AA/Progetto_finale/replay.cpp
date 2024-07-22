#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
 
  
int main(void)
{
    ofstream myfile;
    myfile.open("replay.txt");

    if(myfile.is_open())
    {
        /*myfile << "Benvenuti in Battaglia navale \n";

        myfile << "Coordinate iniziali scelte dal giocatore 1"<<endl;
        for(int i = 0; i < 3; i++) //corazzata occupa 2, 2 , 2 (posizione ,centro)
        {
            myfile << "Centro corazzata " << i << ": " << set_player1[i] << " Posizione: " << set_position1[i]; 
        }
        for(int i = 3; i < 6; i++) //corazzata occupa 2, 2 , 2 (posizione ,centro)
        {
            myfile << "Centro nave di supporto  " << i-2 << ": " << set_player1[i] << " Posizione: " << set_position1[i]; 
        }
        for(int i = 6; i < 7; i++) //corazzata occupa 2, 2 , 2 (posizione ,centro)
        {
            myfile << "Sottomarino  " << i-5 << ": " << set_player1[i] << " Posizione: " << set_position1[i]; 
        }*/

    }
    else cout<<"file non trovato";
    myfile.close();
    return 0;
}