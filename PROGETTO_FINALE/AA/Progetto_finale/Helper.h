//AUTORE
#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <string>

class Helper
{
    public:
    static const int ASCII_A = 65;  //corrispettivi caratteri ASCII
    static const int ASCII_N = 78;
    static const int ASCII_J = 74;
    static const int ASCII_K = 75;
    static const int ASCII_ZERO = 48;

    //FUNZIONI
    static int convert_lett(std::string xy);        //trasforma lettera della coordinata nell'indice della griglia A-->0
    static int convert_num(std::string xy);         //trasforma numero della coordinata nell'indice della griglia 1-->0             
    static std::string convert_row(int row);        //trasforma riga della griglia nella lettera della coordinata 0-->A
    static std::string convert_col(int col);        //trasforma colonna della griglia nel numero della coordinata 0-->1
    static std::string convert_char(int n);         //trasforma int nel numero corrispondente alla tabella asci 

};

#endif