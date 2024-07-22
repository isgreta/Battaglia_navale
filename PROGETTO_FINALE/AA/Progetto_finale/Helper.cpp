
//AUTORE
#include "Helper.h"
#include <string>
#include <iostream>

//TRASFORMA LE COORDINATE INSERITE IN COORDINATE DEGLI ARRAY (NUMERI)
int Helper::convert_lett(std::string xy) //converte la prima parte della coordinata (x) in numero A12
{
    //controllo che le coordinate siano della lunghezza corretta
    int val_x = 0; //valore della lettera in numero
    //controllo sulle lettere
    char letter = xy[0]; //prendo il primo valore dell' array stringa all'indice 0
    char toupper_letter = toupper(letter);
    int xx = static_cast<int>(toupper_letter); // xx è il valore ascii di letter

    if(xx<ASCII_J)    //faccio corrispondere il valore della lettera al numero corrispondente es: A -> 0, B-> 1...
        val_x =xx -ASCII_A; 
    else
        val_x = xx - ASCII_A -2;

    return val_x;
     //C12 --> 211 attacco[2][11] 122 
}
int Helper::convert_num(std::string xy) //converte la seconda parte della coordinata in numero 
{
    int val_y = 0; //valore del numero
    if(xy.length() == 2) //caso tipo: B0 lunghezza 2
    {
        //controllo che il numero sia compreso tra 0 e 8 e sottraggo il numero inserito di 1 perchè l'array parte da 0
        char num = xy[1];  //prendo il secondo valore dell' array stringa all'indice 1 
        int yy = static_cast<int>(num); // yy è il valore in ascii di num
        val_y = yy - ASCII_ZERO - 1; 
    }
    else if(xy.length() == 3) //caso tipo: C12 lunghezza 3
    {
        std::string num = xy.substr(1,2); //10, 11, 12
        int y = stoi(num);                      
        if(y> 9  && y < 13 ) 
            val_y = y-1;
    }  
        
    return val_y;
}
std::string Helper::convert_row(int row) // converte il numero nell'indice della riga: converte A,B,C,D,E,F,G,H,I,L,M,N (indici delle righe) in 0,1,2,3,4,...,10,11  
{
    char letter = 65 + row; //65=A con uso dei caratteri ASCII
    if(letter >= ASCII_J ) 
        letter = letter + 2;//L,M,N
    char* p = &letter;
    std::string output = p;
    return output;
}
std::string Helper::convert_col(int col) // converte il numero nell'indice della colonna 1,2,3,4,...,11,12 in (indici delle colonne) 0,1,2,..,10,11
{
    col = col +1; 
    std::string output = std::to_string(col);
    return output;
}
std::string Helper::convert_char(int n) //converte l'intero in carattere ASCII 
{
    std::string s;
    if(n >= 65 && n <= 78) //range tra A e N
    {
        n = n- 65;
        s = convert_row(n);
    }
    else if(n == 83) //S
    {
        s = "S";
    }
    else if(n == 115)//s
    {
        s = "s";
    }
    else if(n==99)//c
    {
        s = "c";
    }
    else if(n == 101)//e
    {
        s = 'e';
    }
    else if (n == 88)//X
    {
        s = "X";
    }
    else if (n == 79)//o
    {
        s = "O";
    }
    else if(n == 89)//Y
    {
        s = "Y";
    }
    else
    {
        std::string s = std::to_string(n);
    }
    return s;
}