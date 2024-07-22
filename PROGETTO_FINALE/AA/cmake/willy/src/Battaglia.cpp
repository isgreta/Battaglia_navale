//AUTORE:
#include "Battaglia.h"
#include "Helper.h"
#include "Radar.h"
#include <iostream>
#include <string>


//COSTRUTTORE
Battaglia::Battaglia()
{
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

//FUNZIONI CHE STAMPANO LA GRIGLIA DI ATTACCO E DIFESA
std::string Battaglia::print_att()
{
    char lettera = ASCII_A;
    std::string output = "";
    const int COLONNA = 2;
    for(int i = 0; i < DIM_G; i++)
    {
        if(lettera == ASCII_J)
            lettera = lettera+2;
        output += lettera;
        lettera++;
        for(int j = 0; j < DIM_G; j++)
        {
            //att = &attacco[0][0];
            //*att = attacco[i][j];
            int n = attacco[i][j];
            std::string str = Helper::convert_char(n);
            output += "| " + str;
            std::string col = "" + str;
            while (col.length() <COLONNA )
            {
                output += " ";
                col += " ";
            } 
        }
        output += "| ";
        output += "\n";
    }
    
    std::string spazio= "";
    for(int i = 0; i < COLONNA +1 ; i++)
    {
        spazio += " ";
    }
    std::string finale = spazio + "1" + spazio + "2" + spazio + "3" + spazio + "4" +spazio + "5" + spazio + "6" +spazio + "7" + spazio + "8" +spazio + "9" + "   " + "10" + "  " + "11" + "  " + "12"; 
    return output + finale;
}
std::string Battaglia::print_dif()
{
    char lettera = ASCII_A;
    std::string output;
    const int COLONNA = 2;  
    for(int i = 0; i < DIM_G; i++) //riga
    {
        if(lettera == ASCII_J)
            lettera = lettera+2;
        output += lettera;
        lettera++;
        for(int j = 0; j < DIM_G; j++) //colonne
        {
            //dif = &difesa[0][0];
            //*dif = difesa[i][j];
            int n = difesa[i][j];
            std::string str = Helper::convert_char(n);
            output += "| " + str;
           
            std::string col = ""+str; 
            while (col.length() <COLONNA)
            {
                output += " ";
                col += " ";
            } 
        }
        output += "| ";
        output += "\n";
    }
    std::string spazio= "";
    for(int i = 0; i < COLONNA +1 ; i++)
    {
        spazio += " ";
    }
    std::string finale = spazio + "1" + spazio + "2" + spazio + "3" + spazio + "4" +spazio + "5" + spazio + "6" +spazio + "7" + spazio + "8" +spazio + "9" + "   " + "10" + "  " + "11" + "  " + "12"; 
    return output + finale;
}

//AZIONI NAVI

//CORAZZATA
int Battaglia::get_pos_battleship(std::string xyOrigin)
{
    int riga = Helper::convert_lett(xyOrigin); //G
    int colonna = Helper::convert_num(xyOrigin); // 7
    if((difesa[riga-2][colonna] == 'C' || difesa[riga-1][colonna] == 'c') && (difesa[riga+2][colonna] == 'C' || difesa[riga+1][colonna] == 'c'))
        return 1;
    if((difesa[riga][colonna-2] == 'C' || difesa[riga][colonna-2] == 'c') && (difesa[riga][colonna+2] == 'C' || difesa[riga][colonna+2] == 'c'))
        return 0;
}
std::string Battaglia::get_battleshipCenter(std::string prua, std:: string poppa)
{
    int riga_prua = Helper::convert_lett(prua); //L
    int col_prua = Helper::convert_num(prua); //6
    int riga_poppa = Helper::convert_lett(poppa); //L
    int col_poppa= Helper::convert_num(poppa); // 10
    std::string centro;
    if(riga_prua == riga_poppa) //orizzontale
    {
        int col;
        if(col_prua > col_poppa)
            col = col_prua -2;
        else
            col = col_prua +2;
        std::string new_Col = Helper::convert_col(col);
        centro = Helper::convert_row(riga_prua) + new_Col;
    }
    else //verticale
    {
        int row;
        if(riga_prua > riga_poppa)
            row = riga_prua -2;
        else
            row = riga_prua +2;
        std::string new_Row = Helper::convert_row(row);
        centro = new_Row + Helper::convert_col(col_prua);
    }
    return centro;
}
bool Battaglia::find_battleship_center(std::string xyTarget, std::string centro, int pos_target, int pos_center) 
{
    if(centro == xyTarget) return false;

    int row_target = Helper::convert_lett(xyTarget); //B --> 1
    int col_target =  Helper::convert_num(xyTarget); // 2--> 1
    int row_center = Helper::convert_lett(centro); //A -->0
    int col_center = Helper::convert_num(centro); //2-->1
    bool valid = true;

    if(pos_target == 0)//Se orizzontale 
    {
        if(row_target == 0) //A 
        {
            for(int j = col_target - 3; j <= col_target +3; j++) // controlla tra 2 e 8 (3 e 9)
            {
                if((row_target+1 == row_center) && (j == col_center)) //ci troviamo nella cella che equivale al centro della nave di supporto da riparare
                    return true;
                else 
                    valid = false;
            }
        } 
        else if(row_target == 11) //N
        {
            for(int j = col_target -3; j <= col_target +3; j++) // controlla tra 2 e 8 (3 e 9)
            {
                if((row_target-1== row_center) && (j == col_center)) //ci troviamo nella cella che equivale al centro della nave di supporto da riparare
                    return true;
                else 
                    valid = false;
            }
        }
        else //tra B e M
        {
            for(int j = col_target -3; j <= col_target +3; j++) //1 e 3 (B e D)
            {
                for(int i = row_target-3; i <= row_target+3; i++) // controlla tra 2 e 8 (3 e 9)
                { 
                    if(i == row_center && j == col_center) //ci troviamo nella cella che equivale al centro della nave di supporto da riparare
                        return true;
                    else 
                        valid = false;
                }
            }
           
        }   
    }
    else //Se verticale
    {
        if(col_target == 0) //colonna 1
        {
            for(int i = row_target -3; i <= row_target +3; i++) // controlla tra 2 e 8 (3 e 9)
            {
                if((i == row_center) && (col_target+1== col_center)) //ci troviamo nella cella che equivale al centro della nave di supporto da riparare
                    return true;
                else 
                    valid = false;
            }
        }
        else if(col_target == 11) //colonna 12
        {
            for(int i = row_target -3; i <= row_target +3; i++) // controlla tra 2 e 8 (3 e 9)
            {
                if((i == row_center) && (col_target-1 == col_center)) //ci troviamo nella cella che equivale al centro della nave di supporto da riparare
                    return true;
                else 
                    valid = false;
            }
        }
        else
        {
            for(int j = col_target -3; j <= col_target +3; j++)//1 e 3 (B e D)
            {
                for(int i = row_target-3; i <= row_target+3; i++)  // controlla tra 2 e 8 (3 e 9)
                {
                    if(i == row_center && j == col_center) //ci troviamo nella cella che equivale al centro della nave di supporto da riparare
                        return true;
                    else 
                        valid = false;
                }
            }
        }
    }
    return valid;
}
bool Battaglia::check_battleship(char c)    //verifica che si tratti di una corazzata 
{
    if(c == 'C' || c == 'c') return true;
    else return false; 
}
char Battaglia::tolower_case(char c)    //rimpicciolisce la lettera quando una cella viene colpita dalla corazzata 
{
    if(c== 67 || c == 99) return 99; //C-->c
    else if(c == 83 || c == 115) return 115; //S-->s
    else if(c == 69) return 101; //E-->e
    else return 0;
}
void Battaglia::fire(std::string xyTarget) //azione di fuoco
{
    int riga = Helper::convert_lett(xyTarget);  //converte la riga con la corrispettiva lettera b->1
    int colonna = Helper::convert_num(xyTarget);//converte la colonna con la corrispettiva lettera 1->0
    if(get_cell(xyTarget) == 0) 
        difesa[riga][colonna] =0;
    else
    {
        char c = tolower_case(difesa[riga][colonna]);
        difesa[riga][colonna] = c;
    }
}
void Battaglia::hit(std::string xyTarget) //azione quando viene colpita una nave--> griglia attacco nemica appare una X
{
    int riga = Helper::convert_lett(xyTarget);
    int colonna = Helper::convert_num(xyTarget);
    attacco[riga][colonna] = 88; //X
}
void Battaglia::not_hit(std::string xyTarget) //azione quando non viene colpita una nave--> griglia attacco nemica appare una 0
{
    int riga = Helper::convert_lett(xyTarget);
    int colonna = Helper::convert_num(xyTarget);
    attacco[riga][colonna] = 79; //O
}

//SOTTOMARINO 
bool Battaglia::check_submarine(std::string xyOrigin) //controlla che nella cella si trovi un sottomarino
{
    if(get_cell(xyOrigin) == 'E') return true;
    else return false; 
}
bool Battaglia::space_submarine(std::string xyTarget) //verifico che la cella in cui voglio spostare il sottomarino sia libera 
{
    int riga = Helper::convert_lett(xyTarget);
    int colonna = Helper::convert_num(xyTarget);
    if(free_cell(riga, colonna))
        return true;
    else
        return false;
}
void Battaglia::move_submarine(std::string xyOrigin,std::string xyTarget)   //sposto sottomarino                           
{
    int riga1 = Helper::convert_lett(xyOrigin);
    int colonna2 = Helper::convert_num(xyOrigin);
    difesa[riga1][colonna2] = 0;
    int riga = Helper::convert_lett(xyTarget);
    int colonna = Helper::convert_num(xyTarget);
    set_submarine(xyTarget);
}
void Battaglia::radar(std::string xyTarget) //controllo il quadrato 5x5 della griglia nemica e salva le navi per l'azione radar
{
    int riga = Helper::convert_lett(xyTarget);
    int col = Helper::convert_num(xyTarget);
    int count = 0;  //count oer colonna
    int lim = 0;    //count per riga 

    if(riga != 0 && riga != 1 && riga != 10 && riga!=11) //tra C e L, E6 (E = 4)
    {
        for(int j = riga-2; j<= riga+2; j++) //j = C = 2 --> j = G = 6 ciclo che controlla da -2< riga >2
        {
            lim = 0;
            if(col != 0 && col != 1 && col!=10 && col!= 11) //tra 3 e 10
            {
                for(int i = col-2; i<= col+2; i++)  //-2< colonna >2
                {
                    radar_s[count][lim] = difesa[j][i];
                    lim++; 
                }        
            }
            else// tra colonne 1,2 e 11,12
            {
                if(col == 0)
                {
                    for(int i = col; i <= col+2; i++) //3 volte,col 0 ,1 , 2 
                    {
                        radar_s[count][lim+2] = difesa[j][i]; //F1 -> 2,2 
                        lim++;
                    }
                }
                else if (col == 11)
                {
                    for(int i = col-2; i <= col; i++)//3 volte, 11, 10, 9
                    {
                        radar_s[count][lim] = difesa[j][i];
                        lim++;
                    }
                }
                else if(col == 1)
                {
                    for(int i = col-1; i <= col+2; i++) //4 volte, 0,1,2,3
                    {
                        radar_s[count][lim+1] = difesa[j][i];
                        lim++;
                    }
                }
                else //10
                {
                    for(int i = col -2; i <= col+1; i++) //4 volte 
                    {
                        radar_s[count][lim] = difesa[j][i];
                        lim++;
                    }
                }
            }
            count++;
        }   
    }
    else //A,B, M,N, 0,1 e 10,11
    {
        if(col != 0 && col != 1 && col!=10 && col!= 11) //col va da 2 a 9, di A B M N 
        {
            for(int i = col-2; i <= col+2; i++) //4 volte
            {
                count = 0;
                if(riga == 0)
                {
                    for(int j=riga; j<=riga+2;j++) //3 volte
                    {    
                        radar_s[count+2][lim] = difesa[j][i];
                        count++;
                    }
                }
                else if(riga == 1)
                {
                    for(int j =riga-1; j<=riga+2; j++)
                    {
                        radar_s[count+1][lim] = difesa[j][i];
                        count++;
                    }
                }
                else if(riga == 10)
                {
                    for(int j=riga-2; j<=riga+1; j++) //4 volte
                    {
                        radar_s[count][lim] = difesa[j][i];
                        count++;
                    }
                }
                else //riga = 11
                {
                    for(int j = riga-2; j<=riga; j++)
                    {
                        radar_s[count][lim] = difesa[j][i];
                        count++;
                    }
                }
                lim++;
            }
        }
        else //col 0,1,10,11, A B M N
        {
            if(col == 0)//a1, b1,m1,n1
            {
               for(int i = col; i<=col +2; i++)
               {
                    count = 0;
                    if(riga==0) //A1
                    {
                        for(int j = riga; j <= riga+2; j++) //3 volte
                        {
                            radar_s[count+2][lim+2] = difesa[j][i];
                            count++;
                        }
                    }
                    else if(riga == 1) //B1
                    {
                        for(int j = riga -1; j <= riga+2; j++) //4 volte 
                        {
                            radar_s[count+1][lim+2] = difesa[j][i];
                            count++;
                        }
                    }
                    else if(riga == 10) //M1
                    {
                        for(int j = riga -2; j <= riga+1; j++)  //3 volte
                        {
                            radar_s[count][lim+2] = difesa[j][i];
                            count++;
                        }
                    }
                    else //N1
                    {
                        for(int j= riga-2; j<=riga; j++)    //4 volte
                        {
                            radar_s[count][lim+2] = difesa[j][i];
                            count++;
                        }
                    }
                    lim++;
               }
            }
            else if(col == 1)   //a2,b2,n2,m2
            {
                for(int i = col-1; i<=col +2; i++)
                {
                    count=0;
                    if(riga==0) //A2
                    {
                        for(int j = riga; j <= riga+2; j++) //3 volte
                        {
                            radar_s[count+2][lim+1] = difesa[j][i];
                            count++;
                        }
                    }
                    else if(riga == 1) //B2
                    {
                        for(int j = riga -1; j <= riga+2; j++) //4 volte
                        {
                            radar_s[count+1][lim+1] = difesa[j][i];
                            count++;
                        }
                    }
                    else if(riga == 10) //M2
                    {
                        for(int j = riga -2 ; j <= riga+1; j++)  //4 volte
                        {
                            radar_s[count][lim+1] = difesa[j][i];
                            count++;
                        }
                    }
                    else //N2
                    {
                        for(int j= riga-2; j<=riga; j++)    //3 volte
                        {
                            radar_s[count][lim+1] = difesa[j][i];
                            count++;
                        }
                    }
                    lim++;
                }
            }
            else if(col==10)
            {
                for(int i = col-2; i<=col+1; i++)
                {
                    count = 0;
                    if(riga==0) //A11
                    {
                        for(int j = riga; j <= riga+2; j++) //3 volte
                        {
                            radar_s[count+2][lim] = difesa[j][i];
                            count++;
                        }
                    }
                    else if(riga == 1) //B11
                    {
                        for(int j = riga -1; j <= riga+2; j++)
                        {
                            radar_s[count+1][lim] = difesa[j][i];
                            count++;
                        }
                    }
                    else if(riga == 10) //M11
                    {
                        for(int j = riga-2; j <= riga+1; j++)
                        {
                            radar_s[count][lim] = difesa[j][i];
                            count++;
                        }
                    }
                    else //N11
                    {
                        for(int j= riga-2; j<=riga; j++) 
                        {
                            radar_s[count][lim] = difesa[j][i];
                            count++;
                        }
                    }  
                    lim++;       
                }
            }
            else //12
            {
                for(int i=col-2; i<=col; i++)
                {
                    count = 0;
                    if(riga==0) //A12
                    {
                        for(int j = riga; j <= riga+2; j++)
                        {
                            radar_s[count+2][lim] = difesa[j][i];
                            count++;
                        }
                    }
                    else if(riga == 1) //B12
                    {
                        for(int j = riga -1; j <= riga+2; j++)
                        {
                            radar_s[count+1][lim] = difesa[j][i];
                            count++;
                        }
                    }
                    else if(riga == 10)//M12
                    {
                        for(int j = riga -2; j <= riga+1; j++)
                        {
                            radar_s[count][lim] = difesa[j][i];
                            count++;
                        }
                    }
                    else//N12
                    {
                        for(int j= riga-2; j<=riga; j++)
                        {
                            radar_s[count][lim] = difesa[j][i];
                            count++;
                        }
                    }
                    lim++;
                }

            }
        }
    }
}
char Battaglia::get_valueRadar(int riga, int colonna)
{
    return radar_s[riga][colonna];
}
void Battaglia::set_radar(std::string xyTarget, Radar r) 
{
    int riga = Helper::convert_lett(xyTarget); //F --> 5
    int colonna = Helper::convert_num(xyTarget);//6 -->5

    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j <5; j++)
        {
            if(i <= 2)
            {
                if(j <= 2) //0,1,2             
                    attacco[riga+i][colonna+j] = r.get_radarS(2+i,2+j); // L6 (2,2), L7 (2,3), L8 (2,4); M6 (3,2), M7 (3,3), M8 (3,4); N6 (4,2),N7 (4,3), N8 (4,4)
                else //j = 3,4; i = 0,1,2
                {
                    if(j == 3)
                        attacco[riga+i][colonna-j+2]= r.get_radarS(i+2,j-2);//L5 (2,1), M5 , N5
                    else
                        attacco[riga+i][colonna-j+2] = r.get_radarS(i+2,j-4); //j -4  L5 (2,1), L4 (2,2)
                }
            }
            else //i = 3,4; 
            {
                if(j <= 2) // j= 0,1,2
                {
                    if(i==3)
                        attacco[riga-i+2][colonna+j] = r.get_radarS(i-2,j+2);//I6 (1,2), I7(1,3), I8(1,4);
                    else //i ==4 e j = 0,1,2
                        attacco[riga-i+2][colonna+j] = r.get_radarS(i-4,j+2); //H6 (0,2), H7 (0,3), H8(0,4)
                }
                else if(j == 3)//j = 3 e i = 3,4
                {
                    if(i==3) 
                        attacco[riga-i+2][colonna-j+2] = r.get_radarS(i-2,j-2);//I5 (1,1)
                    else //i == 4 e j == 3
                        attacco[riga-i+2][colonna-j+2] = r.get_radarS(i-4,j-2); // H5(0,1)    
                }
                else //j == 4 e i = 3,4
                {
                    if(i == 3)
                        attacco[riga-i+2][colonna-j+2] = r.get_radarS(i-2,j-4);//I4 (1,0)        
                    else
                        attacco[riga-i+2][colonna-j+2] = r.get_radarS(i-4,j-4);// H4(0,0)
                }
            }
        }
    }
}
void Battaglia::reveal()
{
    for(int i = 0; i < 12; i++)
    {
        for(int j = 0; j< 12; j++)
        {
            if(attacco[i][j] == 'S' || attacco[i][j] == 'E' || attacco[i][j] == 'C')
            {
                attacco[i][j] = 'Y';
            }
            else if(attacco[i][j] == 's' || attacco[i][j] == 'c')
            {
                attacco[i][j]= 'X';
            }
        }
    }
}
void Battaglia::clear_Y()
{
    for(int i = 0; i < DIM_G; i++)
    {
        for(int j = 0; j < DIM_G; j++)
        {
            if(attacco[i][j]=='Y') 
            {
                attacco[i][j] = 0;
            }
        }
    }
}    


//NAVE DI SUPPORTO
bool Battaglia::is_supportValid(std::string xy, int pos)
{
    int riga = Helper::convert_lett(xy); //Dalla coordinata xy ottengo la riga convertita già in un numero
    int col = Helper::convert_num(xy); //Dalla coordinata xy ottengo la colonna convertita nel numero corretto
    if(pos==0) //nave orizzontale
    {
        if(col != 0 && col !=11) //0 e 11 rappresentano le colonne dove la nave di supporto non può avere il suo centro 
            return true;
        else 
            return false;
    }
    else //nave verticale
    {
        if(riga != 0 && riga != 11) //A e N rappresentano le righe dove la nave di supporto non può avere il suo centro 
            return true;
        else //riga = A,N
            return false;
    }
}
std::string Battaglia::get_supportCenter(std::string prua, std::string poppa)
{
    int riga_prua = Helper::convert_lett(prua); //L
    int col_prua = Helper::convert_num(prua); //6
    int riga_poppa = Helper::convert_lett(poppa); //L
    int col_poppa= Helper::convert_num(poppa); // 8
    std::string centro;
    if(riga_prua == riga_poppa) //orizzontale
    {
        int col;
        if(col_prua > col_poppa)
            col = col_prua -1;
        else
            col = col_prua +1;
        std::string new_Col = Helper::convert_col(col);
        centro = Helper::convert_row(riga_prua) + new_Col;
    }
    else //verticale
    {
        int row;
        if(riga_prua > riga_poppa)
            row = riga_prua -1;
        else
            row = riga_prua +1;
        std::string new_Row = Helper::convert_row(row);
        centro = new_Row + Helper::convert_col(col_prua);
    }
    return centro;
}
int Battaglia::get_pos_support(std::string xyOrigin) //G7
{
    int riga = Helper::convert_lett(xyOrigin); //G
    int colonna = Helper::convert_num(xyOrigin); // 7
    if((difesa[riga-1][colonna] == 'S' || difesa[riga-1][colonna] == 's') && (difesa[riga+1][colonna] == 'S' || difesa[riga+1][colonna] == 's'))
        return 1;
    if((difesa[riga][colonna-1] == 'S' || difesa[riga][colonna-1] == 's') && (difesa[riga][colonna+1] == 'S' || difesa[riga][colonna+1] == 's'))
        return 0;
}
bool Battaglia::space_support(std::string xyTarget, int pos) 
{
    int riga = Helper::convert_lett(xyTarget);
    int colonna = Helper::convert_num(xyTarget);
    if(pos == 0)
        if(free_support_space(xyTarget, pos) && is_supportValid(xyTarget, pos)) return true;
        else return false;
    if(pos == 1)
        if(free_support_space(xyTarget, pos) && is_supportValid(xyTarget, pos)) return true;
        else return false;
}
void Battaglia::move_support(std::string xyOrigin, std::string xyTarget, int pos)
{
    int riga = Helper::convert_lett(xyOrigin);        //riga della coordinata precedente
    int colonna = Helper::convert_num(xyOrigin);      //colonna della coordinata precedente
    int new_row = Helper::convert_lett(xyTarget);     //riga della nuova coordinata
    int new_col = Helper::convert_num(xyTarget);      //colonna della nuova coordinata
    std::string prua;
    std::string poppa;
    if(pos == 0)
    {
        for(int i = colonna-1 ; i<=colonna+1; i++)
        {
            difesa[riga][i] = 0;
        }
        
        prua = Helper::convert_row(new_row) + Helper::convert_col(new_col-1);
        poppa = Helper::convert_row(new_row) + Helper::convert_col(new_col+1);
        set_support(prua, poppa);
    }
    else
    {
        for(int i = riga -1 ; i<=riga+1; i++)
        {
            difesa[i][colonna] = 0;
        }
        prua = Helper::convert_row(new_row-1) +  Helper::convert_col(new_col);
        poppa = Helper::convert_row(new_row+1) +  Helper::convert_col(new_col);
        set_support(prua, poppa);
    }
    
}
bool Battaglia::find_support_center(std::string xyTarget, std::string centro, int pos_target, int pos_center) 
{
    if(centro == xyTarget) return false;

    int row_target = Helper::convert_lett(xyTarget); //B --> 1
    int col_target =  Helper::convert_num(xyTarget); // 2--> 1
    int row_center = Helper::convert_lett(centro); //A -->0
    int col_center = Helper::convert_num(centro); //2-->1
    bool valid = true;

    if(pos_target == 0)//Se orizzontale 
    {
        if(row_target == 0) //A 
        {
            for(int j = col_target - 2; j <= col_target +2; j++) // controlla tra 2 e 8 (3 e 9)
            {
                if((row_target+1 == row_center) && (j == col_center)) //ci troviamo nella cella che equivale al centro della nave di supporto da riparare
                    return true;
                else 
                    valid = false;
            }
        } 
        else if(row_target == 11)
        {
            for(int j = col_target -2; j <= col_target +2; j++) // controlla tra 2 e 8 (3 e 9)
            {
                if((row_target-1== row_center) && (j == col_center)) //ci troviamo nella cella che equivale al centro della nave di supporto da riparare
                    return true;
                else 
                    valid = false;
            }
        }
        else //tra B e M
        {
            for(int j = col_target - 2; j <= col_target +2; j++) //1 e 3 (B e D)
            {
                for(int i = row_target-2; i <= row_target+2; i++) // controlla tra 2 e 8 (3 e 9)
                { 
                    if(i == row_center && j == col_center) //ci troviamo nella cella che equivale al centro della nave di supporto da riparare
                        return true;
                    else 
                        valid = false;
                }
            }
           
        }   
    }
    else //Se verticale
    {
        if(col_target == 0) //colonna 1
        {
            for(int i = row_target - 2; i <= row_target +2; i++) // controlla tra 2 e 8 (3 e 9)
            {
                if((i == row_center) && (col_target+1== col_center)) //ci troviamo nella cella che equivale al centro della nave di supporto da riparare
                    return true;
                else 
                    valid = false;
            }
        }
        else if(col_target == 11) //colonna 12
        {
            for(int i = row_target -2; i <= row_target +2; i++) // controlla tra 2 e 8 (3 e 9)
            {
                if((i == row_center) && (col_target-1 == col_center)) //ci troviamo nella cella che equivale al centro della nave di supporto da riparare
                    return true;
                else 
                    valid = false;
            }
            
        }
        else
        {
            for(int j = col_target - 2; j <= col_target +2; j++)//1 e 3 (B e D)
            {
                for(int i = row_target-2; i <= row_target+2; i++)  // controlla tra 2 e 8 (3 e 9)
                {
                    if(i == row_center && j == col_center) //ci troviamo nella cella che equivale al centro della nave di supporto da riparare
                        return true;
                    else 
                        valid = false;
                }
            }
        }
    }
    return valid;
}
void Battaglia::fix_support( std::string centro, int pos_center) 
{
    int row_center = Helper::convert_lett(centro);
    int col_center = Helper::convert_num(centro); 
    if(pos_center == 0)
    {
        for(int i = -1; i < 2; i++)
        {
            difesa[row_center][col_center+i] = 83; //S
        }
    }
    else
    {
        for(int i = -1; i < 2; i++)
        {
            difesa[row_center +i][col_center] =83; //S
        }
    } 
}
void Battaglia::fix_battleship( std::string centro, int pos_center) 
{
    int row_center = Helper::convert_lett(centro);
    int col_center = Helper::convert_num(centro); 
    if(pos_center == 0)
    {
        for(int i = -2; i < 3; i++)
        {
            difesa[row_center][col_center+i] = 67; //C
        }
    }
    else
    {
        for(int i = -2; i < 3; i++ )
        {
            difesa[row_center +i][col_center] =67; //C
        }
    }
}

//SET COORDINATE INIZIALI
void Battaglia::set_battleship(std::string xy1, std::string xy2) 
{
    int riga_prua =Helper::convert_lett(xy1); // F=5  F3 B3 
    int riga_poppa = Helper::convert_lett(xy2);//  B= 1 
    int col_prua = Helper::convert_num(xy1); //  3 = 2   
    int col_poppa = Helper::convert_num(xy2); //   3= 2
    if (riga_prua == riga_poppa) 
    {
        // agisci in un modo controlla lunghezza guardando la colonna
        int lunghezza = col_poppa - col_prua; 
        if (lunghezza == 4 || lunghezza == -4)      
        {
            for(int i = 0; i < 5; i++)
            {
                if(col_prua > col_poppa)
                {
                    if(free_cell(riga_prua, col_prua -i))
                        difesa[riga_prua][col_prua-i] = 'C';
                        
                    else throw Invalid_Coordinate(); 
                }
                else
                {
                    if(free_cell(riga_prua, col_prua+i))
                        difesa[riga_prua][col_prua+i]= 'C';
                    else throw Invalid_Coordinate();
                }      
            }
        }
        else
            throw Invalid_Coordinate(); // lunghezza non 5
    }
    else if(col_prua == col_poppa)
    {
        int lunghezza= riga_prua-riga_poppa;
        if(lunghezza == 4 || lunghezza == -4)
        {
            for(int i = 0; i < 5; i++)
            {
                if(riga_prua > riga_poppa)
                {
                    if(free_cell(riga_prua-i,col_prua))
                        difesa[riga_prua-i][col_prua] = 'C';
                    else throw Invalid_Coordinate();
                }
                else
                {
                    if(free_cell(riga_prua+i,col_prua))
                        difesa[riga_prua+i][col_prua]= 'C';
                    else throw Invalid_Coordinate();
                }    
            }
        }
        else
            throw Invalid_Coordinate(); //lunghezza non 5
    }
    else
        throw Invalid_Coordinate(); // corazzata non su stessa riga o colonna
    
}
void Battaglia::set_support(std::string xy1, std::string xy2)
{
    int riga_prua = Helper::convert_lett(xy1); //B =1    
    int riga_poppa = Helper::convert_lett(xy2);//B = 1   
    int col_prua = Helper::convert_num(xy1); //6 = 5      
    int col_poppa = Helper::convert_num(xy2); //10 = 10    
    //siamo gia sicure che c sia di dimensione 3
    if (riga_prua == riga_poppa) //
    {
        // agisci in un modo controlla lunghezza guardando la colonna
        int lunghezza = col_poppa - col_prua;
        if (lunghezza == 2 || lunghezza == -2)
        {
            for(int i = 0; i < 3; i++)
            {
                if(col_prua > col_poppa)
                {
                    if(free_cell(riga_prua, col_prua -i))
                        difesa[riga_prua][col_prua-i] = 'S';
                    else throw Invalid_Coordinate(); 
                }
                else
                {
                    if(free_cell(riga_prua, col_prua +i))
                        difesa[riga_prua][col_prua+i]= 'S';
                    else throw Invalid_Coordinate(); 
                }
            }
        }
        else
            throw Invalid_Coordinate(); // lunghezza non 3
    }
    else if(col_prua == col_poppa)
    {
        int lunghezza= riga_prua-riga_poppa;
        if(lunghezza == 2 || lunghezza == -2)
        {
            for(int i = 0; i < 3; i++)
            {
                if(riga_prua > riga_poppa)
                {
                    if(free_cell(riga_prua-i,col_prua))
                        difesa[riga_prua-i][col_prua] = 'S';
                    else throw Invalid_Coordinate();
                }
                else
                {
                    if(free_cell(riga_prua+i,col_prua))
                        difesa[riga_prua+i][col_prua]= 'S';
                    else throw Invalid_Coordinate();
                }       
            }
        }
        else
            throw Invalid_Coordinate(); //lunghezza non 3
    }
    else
        throw Invalid_Coordinate(); //naveS non su stessa riga o colonna
}  
void Battaglia::set_submarine(std::string xy)
{
    int riga = Helper::convert_lett(xy);
    int colonna = Helper::convert_num(xy);
    if(!free_cell(riga, colonna)) throw Invalid_Coordinate();
    difesa[riga][colonna] = 'E';
}

//CONTROLLANO CHE UNA CELLA O L'INTERO SPAZIO OCCUPATO DA UNA NAVE SIANO LIBERE O NO
bool Battaglia::free_cell(int riga, int colonna) //vale per sottomarino o celle libere singolarmente
{
    char* cella = &difesa[riga][colonna];
    if (*cella != 0) return false; // C, S, E
    else return true;
}
bool Battaglia::free_battles_space(std::string xy,  int pos) //xy = centro
{
    int riga = Helper::convert_lett(xy); //G == 6
    int col = Helper::convert_num(xy); //8 == 7
    bool valid = true;
    if(pos==0) //orizzontale
    {
        for(int i=col-2; i<=col+2; i++)
        {
            if(free_cell(riga, i)) //B2, B3 , B4 , B5 e
                valid = true;
            else //vuol dire che la cella n è occupata
                return false;
        }
    }
    else //verticale
    {   
        for(int i=riga-2; i<=riga+2; i++)
        {
            if(free_cell (i, col))
                valid = true;
            else
                return false;
        }
    }   
    return valid;
}
bool Battaglia::free_support_space(std::string xy, int pos)
{
    int riga = Helper::convert_lett(xy); //G == 6
    int col = Helper::convert_num(xy); //8 == 7
     bool valid = true;
    if(pos==0) //orizzontale
    {
        for(int i=col-1; i<=col+1; i++)
        {
            if(free_cell(riga,i)) 
                valid = true;
            else 
                return false;
        }
    }
    else //verticale
    {   
        for(int i=riga-1; i<=riga+1; i++) 
        {
            if(free_cell(i, col)) 
                valid= true;
            else 
                return false;
        }
    }
    return valid;
}
char Battaglia::get_cell(std::string xy)   //ritorna cella griglia difesa con il carattere corrispondente 
{
    int riga = Helper::convert_lett(xy);
    int colonna = Helper::convert_num(xy);
    return difesa[riga][colonna]; //C, S, E, 0, s, c, e
}
void Battaglia::sunk_battleship(std::string center, int position)
{
    int row_center = Helper::convert_lett(center);
    int col_center = Helper::convert_num(center);
    int count = 0;

    if(difesa[row_center][col_center] == 'c')
    {
        //Corazzata
        if(position == 0) //orizzontale
        {
            for(int i = col_center-2; i <= col_center+2; i++)
            {
                if(difesa[row_center][i] == 'c')
                    count++;
            }
            if(count == 5)
            {
                for(int i = col_center-2; i <= col_center+2; i++)
                {
                   difesa[row_center][i] = 0;
                }
            }
        }
        else //verticale
        {
            for(int i = row_center-2; i <= row_center+2; i++)
            {
                if(difesa[i][col_center] == 'c')
                    count++;
            }
            if(count == 5)
            {
                for(int i = row_center-2; i <= row_center+2; i++)
                {
                    difesa[i][col_center] = 0;
                }
            }
        }
    }
  
}
void Battaglia::sunk_support(std::string center, int position)
{
    int row_center = Helper::convert_lett(center);
    int col_center = Helper::convert_num(center);
    int count = 0;

    if(difesa[row_center][col_center] == 's')
    {
        //nave di supporto
        if(position == 0) //orizzontale
        {
            for(int i = col_center -1; i <= col_center+1; i++)
            {
                if(difesa[row_center][i] == 's')
                    count++; 
            }
            if(count = 3)
            {
                for(int i = col_center -1; i <= col_center+1; i++)
                {
                    difesa[row_center][i] = 0;
                }
            }
        }
        else //verticale
        {
           for(int i = row_center -1; i <= row_center+1; i++)
           {
                if(difesa[i][col_center] == 's')
                    count++;
           }
           if(count == 3)
           {
                for(int i = row_center -1; i <= row_center+1; i++)
                {
                    difesa[i][col_center] = 0;
                }
           }
        }
    }
}
void Battaglia::sunk_submarine(std::string center)
{
    int row_center = Helper::convert_lett(center);
    int col_center = Helper::convert_num(center);

    if(difesa[row_center][col_center] == 'e')
    {
        difesa[row_center][col_center] = 0;
    }

}

//VITTORIA
bool victory(std::string center_b1, int pos_b1, std::string center_b2, int pos_b2, std::string center_b3, int pos_b3)
{
    int row_center_b1 = Helper::convert_lett(center_b1);
    int col_center_b1 = Helper::convert_num(center_b1);   
    if(po)
}

//OVERLOADING OPERATORI
std::ostream& operator<<(std::ostream& os, Battaglia& g) 
{
    os<<g.print_att()<< "\n";
    os<<g.print_dif() << "\n";
    return os;
}