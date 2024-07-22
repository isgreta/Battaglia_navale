//AUTORE:
#include "Game.h"
#include "Helper.h"
#include "Radar.h"
#include <iostream>
#include <string>


//COSTRUTTORE
Game::Game()
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
std::string Game::print_att()//stampa griglia di attacco
{
    char letter = ASCII_A;
    std::string output = "";
    const int COLUMN = 2;
    for(int i = 0; i < DIM_G; i++)//stampa riga
    {
        if(letter == ASCII_J)//se lettera = a J salto alla L
            letter = letter+2;
        output += letter;
        letter++;
        for(int j = 0; j < DIM_G; j++)//stampa colonna
        {
            int n = attacco[i][j];
            std::string str = Helper::convert_char(n);
            output += "| " + str;
            std::string col = "" + str;
            while (col.length() <COLUMN )
            {
                output += " ";
                col += " ";
            } 
        }
        output += "| ";
        output += "\n";
    }
    
    std::string space= ""; //spazio tra i numeri 
    for(int i = 0; i < COLUMN +1 ; i++) 
    {
        space += " ";
    }
    std::string final = space+ "1" +space+ "2" +space+ "3" +space+ "4" +space+ "5" +space+ "6" +space+ "7" +space+ "8" +space+ "9" +"   "+ "10" +"  "+ "11" +"  "+ "12"; 
    return output + final;
}
std::string Game::print_dif()
{
    char letter = ASCII_A;
    std::string output;
    const int COLUMN = 2;  
    for(int i = 0; i < DIM_G; i++) // stampa riga
    {
        if(letter == ASCII_J)
            letter = letter+2;
        output += letter;
        letter++;
        for(int j = 0; j < DIM_G; j++) //stampa colonne
        {
            int n = difesa[i][j];
            std::string str = Helper::convert_char(n);
            output += "| " + str;
           
            std::string col = ""+str; 
            while (col.length() <COLUMN)
            {
                output += " ";
                col += " ";
            } 
        }
        output += "| ";
        output += "\n";
    }
    std::string space = "";
    for(int i = 0; i < COLUMN +1 ; i++)
    {
        space += " "; //spazio tra le colonne 
    }
    std::string final = space+ "1" +space+ "2" +space+ "3" +space+ "4" +space+ "5" +space+ "6" +space+ "7" +space+ "8" +space+ "9" +"   "+ "10" +"  "+ "11" +"  "+ "12"; 
    return output + final;
}

//AZIONI NAVI
//CORAZZATA
bool Game::is_battleshipValid(std::string xy, int pos) 
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
int Game::get_pos_battleship(std::string xyOrigin)//ricevo posizione corazzata
{
    int row = Helper::convert_lett(xyOrigin); //G
    int col = Helper::convert_num(xyOrigin); // 7
    if((difesa[row-2][col] == 'C' || difesa[row-2][col] == 'c') && (difesa[row+2][col] == 'C' || difesa[row+2][col] == 'c'))// guardo riga da -2 a +2 i caratteri c e C se è posizionata in verticale
        return 1;        
    return 0;
}
std::string Game::get_battleshipCenter(std::string prow, std:: string stern)//ricevo centro corazzata
{
    int row_prow = Helper::convert_lett(prow); //L
    int col_prow = Helper::convert_num(prow); //6
    int row_stern = Helper::convert_lett(stern); //L
    int col_stern= Helper::convert_num(stern); // 10 
    std::string center;
    if(row_prow == row_stern) //orizzontale
    {
        int col; //colonna
        if(col_prow > col_stern) //colonna prua> colonna poppa
            col = col_prow -2; //guardo dalla colonna della poppa maggiore e tolgo -2, trovo il centro es. F5, F1-> F5-2= F3 centro 
        else
            col = col_prow +2;//guardo dalla colonna della poppa minore e aggiungo +2, trovo il centro es. F1,F5-> F1+2= F3 centro 
        std::string new_Col = Helper::convert_col(col);
        center = Helper::convert_row(row_prow) + new_Col;
    }
    else //verticale
    {
        int row;
        if(row_prow > row_stern)//guardo dalla riga della poppa maggiore e tolgo -2, trovo il centro es. L5, F5-> L5-2= H5 centro 
            row = row_prow -2;
        else
            row = row_prow +2;//guardo dalla colonna della poppa minore e aggiungo +2, trovo il centro es. F5,L5-> F5+2= H5 centro 
        std::string new_Row = Helper::convert_row(row);
        center = new_Row + Helper::convert_col(col_prow);
    }
    return center;
}
//xyTarget è il centro della nave di supporto
//quando sposti nave di supporto per riparare questa funzione cerca il centro della corazzata per ripararla
bool Game::find_battleship_center(std::string xyTarget, std::string center, int pos_target, int pos_center) //ricava centro dalla corazzata
{
    if(center == xyTarget) return false;

    int row_target = Helper::convert_lett(xyTarget); //B --> 1
    int col_target =  Helper::convert_num(xyTarget); // 2--> 1
    int row_center = Helper::convert_lett(center); //A -->0
    int col_center = Helper::convert_num(center); //2-->1
    bool valid = true;

    if(pos_target == 0)//Se orizzontale 
    {
        if(row_target == 0) //A 
        {
            if(pos_center == 0) //corazzata è orizzontale
            {
                for(int j = col_target - 3; j <= col_target +3; j++) // controlla tra 2 e 8 (3 e 9)
                {
                    if((row_target+1 == row_center) && (j == col_center)) //ci troviamo nella cella che equivale al centro della corazzata da riparare
                        return true;
                    else 
                        valid = false;
                }
            }
            else //corazzata in verticale
            {
                for(int j = col_target -1; j <= col_target +1; j++) 
                {
                    if((row_target +3 == row_center) && (j == col_center)) //ci troviamo nella cella che equivale al centro della corazzata da riparare
                        return true;
                    else 
                        valid = false;
                }
            }
        } 
        else if(row_target == 11) //N
        {
            if(pos_center == 0)//corazzata in orizzontale
            {
                for(int j = col_target - 3; j <= col_target +3; j++) // controlla tra 2 e 8 (3 e 9)
                {
                    if((row_target-1 == row_center) && (j == col_center)) //ci troviamo nella cella che equivale al centro della corazzata da riparare
                        return true;
                    else 
                        valid = false;
                }
            }
            else //corazzata in verticale
            {
                for(int j = col_target -1; j <= col_target +1; j++) 
                {
                    if((row_target-3 == row_center) && (j == col_center)) //ci troviamo nella cella che equivale al centro della corazzata da riparare
                        return true;
                    else 
                        valid = false;
                }

            }
        }
        else //tra B e M
        {
            if(pos_center == 0)
            {
                for(int j = col_target -3; j <= col_target +3; j++) //1 e 3 (B e D)
                {
                    for(int i = row_target-1; i <= row_target+1; i++) 
                    {
                        if(i == row_center && j == col_center) //ci troviamo nella cella che equivale al centro della corazzata da riparare
                            return true;
                        else 
                            valid = false;
                    }
                }
            }
            else //corazzata in verticale
            {
                for(int j = col_target -1; j <= col_target +1; j++) //1 e 3 (B e D)
                {
                    for(int i = row_target-3; i <= row_target+3; i++) 
                    {
                        if(i == row_center && j == col_center) //ci troviamo nella cella che equivale al centro della corazzata da riparare
                            return true;
                        else 
                            valid = false;
                    }
                }
            }
        }   
    }
    else //Se verticale
    {
        if(col_target == 0) //colonna 1
        {
            if(pos_center == 0)
            {
                for(int i = row_target -1; i <= row_target +1; i++) // controlla tra 2 e 8 (3 e 9)
                {
                    if((i == row_center) && (col_target +3 == col_center)) //ci troviamo nella cella che equivale al centro della nave di supporto da riparare
                        return true;
                    else 
                        valid = false;
                }
            }
            else //corazzata verticale
            {
                for(int i = row_target -3; i <= row_target +3; i++)
                {
                    if((i == row_center) && (col_target+1== col_center)) //ci troviamo nella cella che equivale al centro della nave di supporto da riparare
                        return true;
                    else 
                        valid = false;
                }
            }
        }
        else if(col_target == 11) //colonna 12
        {
            if(pos_center == 0)
            {
                for(int i = row_target -1; i <= row_target +1; i++) // controlla tra 2 e 8 (3 e 9)
                {
                    if((i == row_center) && (col_target - 3 == col_center)) //ci troviamo nella cella che equivale al centro della nave di supporto da riparare
                        return true;
                    else 
                        valid = false;
                }
            }
            else
            {
                for(int i = row_target -3; i <= row_target +3; i++) // controlla tra 2 e 8 (3 e 9)
                {
                    if((i == row_center) && (col_target-1 == col_center)) //ci troviamo nella cella che equivale al centro della nave di supporto da riparare
                        return true;
                    else 
                        valid = false;
                }
            }
        }
        else
        {
            if(pos_center == 0)
            {
                for(int j = col_target -3; j <= col_target +3; j++)//1 e 3 (B e D)
                {
                    for(int i = row_target-1; i <= row_target+1; i++)
                    {
                        if(i == row_center && j == col_center) //ci troviamo nella cella che equivale al centro della nave di supporto da riparare
                            return true;
                        else 
                            valid = false;
                    }
                }
            }
            else
            {
                for(int j = col_target -1; j <= col_target +1; j++)//1 e 3 (B e D)
                {
                    for(int i = row_target-3; i <= row_target+3; i++)
                    {
                        if(i == row_center && j == col_center) //ci troviamo nella cella che equivale al centro della nave di supporto da riparare
                            return true;
                        else 
                            valid = false;
                    }
                }
            }
        }
    }
    return valid;
}
bool Game::check_battleship(char c)    //verifica che si tratti di una corazzata 
{
    if(c == 'C' || c == 'c') return true;   //corazzata se trovo 'C' o/e 'c'
    else return false; 
}
char Game::tolower_case(char c)    //rendo minuscole la lettera quando una cella viene colpita dalla corazzata 
{
    if(c == 67 || c == 99) return 99; //C-->c
    else if(c == 83 || c == 115) return 115; //S-->s
    else if(c == 69) return 101; //E-->e
    else return 0; //altre lettere impostate a spazio vuoto
}
void Game::fire(std::string xyTarget) //azione di fuoco
{
    int row = Helper::convert_lett(xyTarget);  //converte la riga con la corrispettiva lettera b->1
    int col = Helper::convert_num(xyTarget);//converte la colonna con la corrispettiva lettera 1->0
    if(get_cell(xyTarget) == 0) //se cella è vuota non ritorna niente
        difesa[row][col] =0;
    else
    {
        char c = tolower_case(difesa[row][col]);//se una lettera maiuscola viene colpita, viene resa minuscola
        difesa[row][col] = c;
    }
}
void Game::hit(std::string xyTarget) //azione quando viene colpita una nave--> griglia attacco nemica appare una X
{
    int row = Helper::convert_lett(xyTarget);
    int col = Helper::convert_num(xyTarget);
    attacco[row][col] = 88;                     //X
}
void Game::not_hit(std::string xyTarget) //azione quando non viene colpita una nave--> griglia attacco nemica appare una 0
{
    int row = Helper::convert_lett(xyTarget);
    int col = Helper::convert_num(xyTarget);
    attacco[row][col] = 79;                     //O
}

//SOTTOMARINO 
bool Game::check_submarine(std::string xyOrigin) //controlla che nella cella si trovi un sottomarino
{
    if(get_cell(xyOrigin) == 'E') return true; // E          se ho una e=> sottomarino affondato 
    else return false; 
}
bool Game::space_submarine(std::string xyTarget) //verifico che la cella in cui voglio spostare il sottomarino sia libera, ritorna una bool
{
    int row = Helper::convert_lett(xyTarget);
    int col = Helper::convert_num(xyTarget);
    if(free_cell(row, col)) //restituisce true se la  cella è libera
        return true;
    else
        return false;
}
void Game::move_submarine(std::string xyOrigin,std::string xyTarget)   //sposto sottomarino                           
{
    int row1 = Helper::convert_lett(xyOrigin);
    int col2 = Helper::convert_num(xyOrigin);
    difesa[row1][col2] = 0;
    set_submarine(xyTarget);
}
/* avendo una griglia di dimensione 5x5, prendiamo il centro e aggiungiamo -2 e +2 nelle quattro direzioni 
    studio la casistica della nostra griglia
    Punti critici colonne 1,2,11,12 e righe A,B,M,N
    controllo da casella centrale+2, a casella centrale -2 sia per le righe che per le colonne  
    nei punti critici il nostro radar costruirà una griglia (5x3 o 5x4 o 3x3) o (3x5 o 4x5 o 3x3) dove farà il controllo
*/
void Game::radar(std::string xyTarget) //controllo il quadrato 5x5 della griglia nemica e salva le navi per l'azione radar
{
    int row = Helper::convert_lett(xyTarget);
    int col = Helper::convert_num(xyTarget);
    int count = 0;  //count per colonna
    int lim = 0;    //count per riga 

    if(row != 0 && row != 1 && row != 10 && row!=11) //tra C e L, E6 (E = 4)
    {
        for(int j = row-2; j<= row+2; j++) //j = C = 2 --> j = G = 6 ciclo che controlla nelle righe da centro -2 a centro +2
        {
            lim = 0;
            if(col != 0 && col != 1 && col!=10 && col!= 11) //tra 3 e 10
            {
                for(int i = col-2; i<= col+2; i++)  //ciclo che controlla nelle colonne da centro -2 a centro +2
                {
                    radar_s[count][lim] = difesa[j][i];
                    lim++; 
                }        
            }
            else// tra colonne 1,2 e 11,12
            {
                if(col == 0)
                {
                    for(int i = col; i <= col+2; i++) //3 volte, colonne  0 ,1 , 2 
                    {
                        radar_s[count][lim+2] = difesa[j][i]; //F1 -> 2,2 
                        lim++;
                    }
                }
                else if (col == 11)
                {
                    for(int i = col-2; i <= col; i++)//3 volte,  colonne 11, 10, 9
                    {
                        radar_s[count][lim] = difesa[j][i];
                        lim++;
                    }
                }
                else if(col == 1)
                {
                    for(int i = col-1; i <= col+2; i++) //4 volte, colonne  0,1,2,3
                    {
                        radar_s[count][lim+1] = difesa[j][i];
                        lim++;
                    }
                }
                else //10
                {
                    for(int i = col -2; i <= col+1; i++) //4 volte colonne 11,10,9,8
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
                if(row == 0)
                {
                    for(int j=row; j<=row+2;j++) //3 volte righe 0,1,2
                    {    
                        radar_s[count+2][lim] = difesa[j][i];
                        count++;
                    }
                }
                else if(row == 1)
                {
                    for(int j =row-1; j<=row+2; j++)// 4 volte righe 0,1,2,3
                    {
                        radar_s[count+1][lim] = difesa[j][i];
                        count++;
                    }
                }
                else if(row == 10)
                {
                    for(int j=row-2; j<=row+1; j++) //4 volte righe 11,10,9,8
                    {
                        radar_s[count][lim] = difesa[j][i];
                        count++;
                    }
                }
                else //riga = 11
                {
                    for(int j = row-2; j<=row; j++) //3 volte righe 11,10,9
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
                    if(row==0) //A1
                    {
                        for(int j = row; j <= row+2; j++) //3 volte righe A1,B1,C1
                        {
                            radar_s[count+2][lim+2] = difesa[j][i];
                            count++;
                        }
                    }
                    else if(row == 1) //B1
                    {
                        for(int j = row -1; j <= row+2; j++) //4 volte righe A1,B1,C1,D1
                        {
                            radar_s[count+1][lim+2] = difesa[j][i];
                            count++;
                        }
                    }
                    else if(row == 10) //M1
                    {
                        for(int j = row -2; j <= row+1; j++)  //4 volte righe N1, M1,L1,I1
                        {
                            radar_s[count][lim+2] = difesa[j][i];
                            count++;
                        }
                    }
                    else //N1
                    {
                        for(int j= row-2; j<=row; j++)    //3 volte righe N1,M1,L1
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
                    if(row==0) //A2
                    {
                        for(int j = row; j <= row+2; j++) //3 volte righe A2,B2,C2
                        {
                            radar_s[count+2][lim+1] = difesa[j][i];
                            count++;
                        }
                    }
                    else if(row == 1) //B2
                    {
                        for(int j = row -1; j <= row+2; j++) //4 volte righe A2,B2,C2,D2
                        {
                            radar_s[count+1][lim+1] = difesa[j][i];
                            count++;
                        }
                    }
                    else if(row == 10) //M2
                    {
                        for(int j = row -2 ; j <= row+1; j++)  //4 volte righe N2,M2,L2,I2
                        {
                            radar_s[count][lim+1] = difesa[j][i];
                            count++;
                        }
                    }
                    else //N2
                    {
                        for(int j= row-2; j<=row; j++)    //3 volte righe N2,M2,L2
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
                    if(row==0) //A11
                    {
                        for(int j = row; j <= row+2; j++) //3 volte righe A11,B11,C11
                        {
                            radar_s[count+2][lim] = difesa[j][i];
                            count++;
                        }
                    }
                    else if(row == 1) //B11
                    {
                        for(int j = row -1; j <= row+2; j++) //4 volte righe A11,B11,C11,D11
                        {
                            radar_s[count+1][lim] = difesa[j][i];
                            count++;
                        }
                    }
                    else if(row == 10) //M11
                    {
                        for(int j = row-2; j <= row+1; j++) //4 volte righe N11,M11,L11,I11
                        {
                            radar_s[count][lim] = difesa[j][i];
                            count++;
                        }
                    }
                    else //N11
                    {
                        for(int j= row-2; j<=row; j++) //3 volte righe N11,M11,L11
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
                    if(row==0) //A12
                    {
                        for(int j = row; j <= row+2; j++) //3 volte righe A12,B12,C12
                        {
                            radar_s[count+2][lim] = difesa[j][i];
                            count++;
                        }
                    }
                    else if(row == 1) //B12
                    {
                        for(int j = row -1; j <= row+2; j++) //4 volte righe A12,B12,C12,D12
                        {
                            radar_s[count+1][lim] = difesa[j][i];
                            count++;
                        }
                    }
                    else if(row == 10)//M12
                    {
                        for(int j = row -2; j <= row+1; j++) //4 volte righe N12,M12,L12,I12
                        {
                            radar_s[count][lim] = difesa[j][i];
                            count++;
                        }
                    }
                    else//N12 
                    {
                        for(int j= row-2; j<=row; j++) //3 volte righe N12,M12,L12
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
char Game::get_valueRadar(int row, int col) //ritorna i valori nella griglia
{
    return radar_s[row][col];
}
void Game::set_radar(std::string xyTarget, Radar r) //copia i char nella griglia
/* costruisco il quadrato 5x5 (griglia attacco nemica) e riporto caratteri nella mia griglia di difesa */
{
    int row = Helper::convert_lett(xyTarget); //F --> 5
    int col = Helper::convert_num(xyTarget);//6 -->5

    for(int i = 0; i < DIM_RS; i++)
    {
        for(int j = 0; j <DIM_RS; j++)
        {
            if(i <= 2 )
            {
                if(j <= 2) //0,1,2            
                {
                    if(row+i < 0 || col +j <0)
                        j++;
                    else
                        attacco[row+i][col+j] = r.get_radarS(2+i,2+j); // L6 (2,2), L7 (2,3), L8 (2,4); M6 (3,2), M7 (3,3), M8 (3,4); N6 (4,2),N7 (4,3), N8 (4,4)
                } 
                else //j = 3,4; i = 0,1,2
                {
                    if(j == 3 )
                    {
                        if(row+i < 0 || col-j+2 < 0)
                            j++;
                        else
                            attacco[row+i][col-j+2]= r.get_radarS(i+2,j-2);//L5 (2,1), M5 , N5
                    }
                    else 
                    {
                        if(row+i < 0 || col-j+2 < 0)
                            j++;
                        else
                            attacco[row+i][col-j+2] = r.get_radarS(i+2,j-4); //j -4  L5 (2,1), L4 (2,2)
                    }
                }
            }
            else //i = 3,4; 
            {
                if(j <= 2) // j= 0,1,2
                {
                    if(i==3)
                    {
                        if(row-i+2< 0 || col+j < 0)
                            j++;
                        else
                            attacco[row-i+2][col+j] = r.get_radarS(i-2,j+2);//I6 (1,2), I7(1,3), I8(1,4);
                    }
                    else  //i ==4 e j = 0,1,2
                        if(row-i+2 < 0 || col+j <0)
                            j++;
                        else
                            attacco[row-i+2][col+j] = r.get_radarS(i-4,j+2); //H6 (0,2), H7 (0,3), H8(0,4)
                }
                else if(j == 3)//j = 3 e i = 3,4
                {
                    if(i==3 ) 
                    {
                        if(row-i+2 < 0 || col-j+2 < 0)
                            j++;
                        else
                            attacco[row-i+2][col-j+2] = r.get_radarS(i-2,j-2);//I5 (1,1)
                    }
                    else  //i == 4 e j == 3
                    {
                        if(row-i+2 < 0 || col-j+2 < 0)
                            j++;
                        else
                            attacco[row-i+2][col-j+2] = r.get_radarS(i-4,j-2); // H5(0,1)    
                    }
                }
                else //j == 4 e i = 3,4
                {
                    if(i == 3)
                    {
                        if(row-i+2 < 0 || col-j+2 < 0)
                            j++;
                        else
                            attacco[row-i+2][col-j+2] = r.get_radarS(i-2,j-4);//I4 (1,0)  
                    }      
                    else 
                    {
                        if(row-i+2 < 0 || col-j+2 < 0)
                            j++;
                        else
                            attacco[row-i+2][col-j+2] = r.get_radarS(i-4,j-4);// H4(0,0)
                    }
                }
            }
        }
    }
}
void Game::reveal()// rivela nella griglia di attacco i caratteri S, E; C e li trasforma in Y, per le navi già colpite tengo la X
{
    for(int i = 0; i < DIM_G; i++)
    {
        for(int j = 0; j< DIM_G; j++)
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
void Game::clear_Y() //comando AA AA, toglie le Y dalla griglia
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
bool Game::is_supportValid(std::string xy, int pos) //verifica che le coordianate della nave di supporto siano corrette
{
    int row = Helper::convert_lett(xy); //Dalla coordinata xy ottengo la riga convertita già in un numero
    int col = Helper::convert_num(xy); //Dalla coordinata xy ottengo la colonna convertita nel numero corretto
    if(pos==0) //nave orizzontale
    {
        if(col != 0 && col !=11) //0 e 11 rappresentano le colonne in cui la nave di supporto non può avere il suo centro 
            return true;
        else 
            return false;
    }
    else //nave verticale
    {
        if(row != 0 && row != 11) //A e N rappresentano le righe in cui la nave di supporto non può avere il suo centro 
            return true;
        else //riga = A,N
            return false;
    }
}
std::string Game::get_supportCenter(std::string prow, std::string stern) //ricava centro nave di supporto
{
    int row_prow = Helper::convert_lett(prow); //L
    int col_prow = Helper::convert_num(prow); //6
    int row_stern = Helper::convert_lett(stern); //L
    int col_stern= Helper::convert_num(stern); // 8
    std::string center;
    if(row_prow == row_stern) //orizzontale
    {
        int col;
        if(col_prow > col_stern) //guardo dalla colonna della poppa maggiore e tolgo -1, trovo il centro es. F5, D5-> F5-1= E5 centro 
            col = col_prow -1;
        else
            col = col_prow +1; //guardo dalla colonna della poppa minore e aggiungo +1, trovo il centro es. D5, F5-> D5+1= E5 centro
        std::string new_Col = Helper::convert_col(col);
        center = Helper::convert_row(row_prow) + new_Col;
    }
    else //verticale
    {
        int row;
        if(row_prow > row_stern)//guardo dalla riga della poppa maggiore e tolgo -1, trovo il centro es. F5, F3-> F5-1= F4 centro 
            row = row_prow -1;
        else
            row = row_prow +1;//guardo dalla riga della poppa minore e aggiungo +1, trovo il centro es. F3, F5-> F3+1= F4 centro
        std::string new_Row = Helper::convert_row(row);
        center = new_Row + Helper::convert_col(col_prow);
    }
    return center;
}
int Game::get_pos_support(std::string xyOrigin) //G7 mi restituisce l'orientamento della nave di supporto
{
    int row = Helper::convert_lett(xyOrigin); //G
    int col = Helper::convert_num(xyOrigin); // 7
    if((difesa[row-1][col] == 'S' || difesa[row-1][col] == 's') && (difesa[row+1][col] == 'S' || difesa[row+1][col] == 's'))//controlla riga centro +1 e riga centro -1 se sono presenti caratteri = a S e/o S
        return 1;
    return 0;
}
bool Game::space_support(std::string xyTarget, int pos) //verifica che lo spazio in cui deve posizionarsi la nave sia libero
{
    if(pos == 0 || pos == 1)   
    { 
        if(free_support_space(xyTarget, pos) && is_supportValid(xyTarget, pos)) return true;
        else return false;
    }
    else return false;    
}
void Game::move_support(std::string xyOrigin, std::string xyTarget, int pos)//sposta la nave di supporto
{
    int row = Helper::convert_lett(xyOrigin);        //riga della coordinata precedente
    int col = Helper::convert_num(xyOrigin);      //colonna della coordinata precedente
    int new_row = Helper::convert_lett(xyTarget);     //riga della nuova coordinata
    int new_col = Helper::convert_num(xyTarget);      //colonna della nuova coordinata
    std::string prow, stern;
    for(int j = -1; j <= 1; j++)
    {
        if(pos == 0)
        {
            difesa[new_row][new_col + j] = difesa[row][col + j]; //copi ciò che c'era prima
            difesa[row][col +j] = 0;
        }
        else
        {
            difesa[new_row + j][new_col] = difesa[row+j][col];
            difesa[row+j][col] = 0;
        }
    }
}
//xyTarget è il centro di dove sposti la nave di supporto, center è il centro della nave di supporto trovato da curare
bool Game::find_support_center(std::string xyTarget, std::string center, int pos_target, int pos_center) //ripara le navi 
{
    if(center == xyTarget) return false;

    int row_target = Helper::convert_lett(xyTarget); //B --> 1
    int col_target =  Helper::convert_num(xyTarget); // 2--> 1
    int row_center = Helper::convert_lett(center); //A -->0
    int col_center = Helper::convert_num(center); //2-->1
    bool valid = true;

    if(pos_target == 0)//Se orizzontale 
    {
        if(row_target == 0) //A 
        {
            if(pos_center == 0) //nave trova è orizzontale
            {
                for(int j = col_target-2; j <= col_target +2; j++) // controlla tra 2 e 8 (3 e 9)
                {
                    if((row_target+1 == row_center) && (j == col_center)) //ci troviamo nella cella che equivale al centro della nave di supporto da riparare
                        return true;
                    else    
                        valid = false;
                }
            }
            else //nave da curare è verticale
            {
                for(int j = col_target-1; j <= col_target+1; j++)
                {
                    if((row_target+2 == row_center) && (j == col_center))
                        return true;
                    else
                        valid = false;
                }
            }
        } 
        else if(row_target == 11)//N
        {
            if(pos_center == 0)//nave trovata è orizzontale
            {
                for(int j = col_target-2; j <= col_target +2; j++) // controlla tra 2 e 8 (3 e 9)
                {
                    if((row_target-1== row_center) && (j == col_center)) //ci troviamo nella cella che equivale al centro della nave di supporto da riparare
                        return true;
                    else 
                        valid = false;
                }
            }
            else // nave trovata è verticale
            {
                for(int j = col_target-1; j <= col_target+1; j++)
                {
                    if((row_target-2 == row_center) && (j == col_center))
                        return true;
                    else
                        valid = false;
                }
            }
        }
        else //tra B e M
        {
            if(pos_center == 0) //nave trovata è orizzontale
            {
                for(int j = col_target - 2; j <= col_target +2; j++) //1 e 3 (B e D)
                {
                    if(row_target+1 == row_center && j == col_center) return true;
                    else if(row_target-1 == row_center && j == col_center) //ci troviamo nella cella che equivale al centro della nave di supporto da riparare
                        return true;
                    else valid = false;
                }
            }
            else // nave trovata è verticale
            {
                for(int j = col_target - 1; j <= col_target +1; j++)
                {
                    if(row_target+2 == row_center && j == col_center) return true;
                    else if(row_target-2 == row_center && j == col_center) //ci troviamo nella cella che equivale al centro della nave di supporto da riparare
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
            if(pos_center == 0) //nave da curare è orizzontale
            {
                for(int i = row_target - 1; i <= row_target +1; i++) // controlla tra 2 e 8 (3 e 9)
                {
                    if(i == row_center && (col_target +2 == col_center)) //ci troviamo nella cella che equivale al centro della nave di supporto da riparare
                        return true;
                    else 
                        valid = false;
                }
            }
            else
            {
                for(int i = row_target - 2; i <= row_target +2; i++) // controlla tra 2 e 8 (3 e 9)
                {
                    if((i == row_center) && (col_target+1== col_center)) //ci troviamo nella cella che equivale al centro della nave di supporto da riparare
                        return true;
                    else 
                        valid = false;
                }
            }
        }
        else if(col_target == 11) //colonna 12
        {
            if(pos_center == 0)
            {
                for(int i = row_target -1; i <= row_target +1; i++)
                {
                    if((i == row_center) && (col_target-2 == col_center)) //ci troviamo nella cella che equivale al centro della nave di supporto da riparare
                        return true;
                    else 
                        valid = false;
                }
            }
            else
            {
                for(int i = row_target -2; i <= row_target +2; i++)
                {
                    if((i == row_center) && (col_target-1 == col_center)) //ci troviamo nella cella che equivale al centro della nave di supporto da riparare
                        return true;
                    else 
                        valid = false;
                }
            }
        }
        else //nel centro
        {
            if(pos_center == 0)
            {
                for(int i = row_target-1; i <= row_target+1; i++)
                {
                    if(i == row_center && col_target - 2 == col_center) //ci troviamo nella cella che equivale al centro della nave di supporto da riparare
                        return true;
                    else if(i == row_center && col_target + 2 == col_center) return true;
                    else 
                        valid = false;
                }
            }
            else
            {
                for(int i = row_target-2; i <= row_target+2; i++) 
                {
                    if(i == row_center &&  col_target - 1 == col_center) //ci troviamo nella cella che equivale al centro della nave di supporto da riparare
                        return true;
                    else if(i == row_center &&  col_target + 1 == col_center) return true;
                    else 
                        valid = false;
                }
            }
        }
    }
    return valid;
}
void Game::fix_support( std::string center, int pos_center) //ripara le navi di supporto
{
    int row_center = Helper::convert_lett(center);
    int col_center = Helper::convert_num(center); 
    if(pos_center == 0)
    {
        for(int i = -1; i < 2; i++)//guarda le colonne da centro +1 a centro -1 se ci siano navi di supporto da riparare
        {
            if(difesa[row_center][col_center+i] == 0) 
                difesa[row_center][col_center+i] = 0;
            else
                difesa[row_center][col_center+i] = 83; //S
        }
    }
    else
    {
        for(int i = -1; i < 2; i++) //guarda le righe da centro +1 a centro -1 se ci siano navi di supporto da riparare
        {
            if(difesa[row_center +i][col_center] == 0) 
                difesa[row_center +i][col_center] = 0;
            else
                difesa[row_center +i][col_center] =83; //S
        }
    } 
}
void Game::fix_battleship( std::string center, int pos_center) //ripara le corazzate
{
    int row_center = Helper::convert_lett(center);
    int col_center = Helper::convert_num(center); 
    if(pos_center == 0)
    {
        for(int i = -2; i < 3; i++)//guarda negli spazi da -2 a +2 se sono presenti delle corazzate
        {
            if( difesa[row_center][col_center+i] == 0)
                 difesa[row_center][col_center+i] = 0;
            else
                difesa[row_center][col_center+i] = 67; //C
        }
    }
    else
    {
        for(int i = -2; i < 3; i++ )
        {
            if( difesa[row_center +i][col_center] == 0)
                 difesa[row_center +i][col_center] = 0;
            else
                difesa[row_center +i][col_center] =67; //C
        }
    }
}

//SET COORDINATE INIZIALI
void Game::set_battleship(std::string xy1, std::string xy2) //setta la corazzata passandogli prua e poppa 
{
    int row_prow =Helper::convert_lett(xy1); // F=5  F3 B3 
    int row_stern = Helper::convert_lett(xy2);//  B= 1 
    int col_prow = Helper::convert_num(xy1); //  3 = 2   
    int col_stern = Helper::convert_num(xy2); //   3= 2
    if (row_prow == row_stern) 
    {
        // agisci in un modo controlla lunghezza guardando la colonna
        int lunghezza = col_stern - col_prow; 
        if (lunghezza == 4 || lunghezza == -4)      //faccio ls differenza tra le due coordinate, se è = a 4 o a -4 le coordinate sono corrette
        {
            for(int i = 0; i < 5; i++)//5 dimensione corazzata, ciclo per colonne
            {
                if(col_prow > col_stern)
                {
                    if(free_cell(row_prow, col_prow -i))
                        difesa[row_prow][col_prow-i] = 'C'; //setta le c
                        
                    else throw Invalid_Coordinate(); 
                }
                else
                {
                    if(free_cell(row_prow, col_prow+i))
                        difesa[row_prow][col_prow+i]= 'C';
                    else throw Invalid_Coordinate();
                }      
            }
        }
        else
            throw Invalid_Coordinate(); // se la lunghezza è diversa da 5
    }
    else if(col_prow == col_stern)
    {
        int lunghezza= row_prow-row_stern;
        if(lunghezza == 4 || lunghezza == -4)
        {
            for(int i = 0; i < 5; i++) //ciclo per righe
            {
                if(row_prow > row_stern)
                {
                    if(free_cell(row_prow-i,col_prow))
                        difesa[row_prow-i][col_prow] = 'C';
                    else throw Invalid_Coordinate();
                }
                else
                {
                    if(free_cell(row_prow+i,col_prow))
                        difesa[row_prow+i][col_prow]= 'C';
                    else throw Invalid_Coordinate();
                }    
            }
        }
        else
            throw Invalid_Coordinate(); //se la lunghezza è diversa da 5
    }
    else
        throw Invalid_Coordinate(); // corazzata non su stessa riga o colonna
}
void Game::set_support(std::string xy1, std::string xy2) //setta nave di supporto
{
    int row_prow = Helper::convert_lett(xy1); //B =1    
    int row_stern = Helper::convert_lett(xy2);//B = 1   
    int col_prow = Helper::convert_num(xy1); //6 = 5      
    int col_stern = Helper::convert_num(xy2); //10 = 10    
    //siamo gia sicure che c sia di dimensione 3
    if (row_prow == row_stern) //riga uguale 
    {
        // agisci in un modo controlla lunghezza guardando la colonna
        int lunghezza = col_stern - col_prow;
        if (lunghezza == 2 || lunghezza == -2) //faccio ls differenza tra le due coordinate, se è uguale a 2 o a -2 le coordinate sono corrette
        {
            for(int i = 0; i < 3; i++)// ciclo per colonne
            {
                if(col_prow > col_stern)
                {
                    if(free_cell(row_prow, col_prow -i))
                        difesa[row_prow][col_prow-i] = 'S';
                    else throw Invalid_Coordinate(); 
                }
                else
                {
                    if(free_cell(row_prow, col_prow +i))
                        difesa[row_prow][col_prow+i]= 'S';
                    else throw Invalid_Coordinate(); 
                }
            }
        }
        else
            throw Invalid_Coordinate(); // lunghezza diversa da 3
    }
    else if(col_prow == col_stern)
    {
        int lunghezza= row_prow-row_stern;
        if(lunghezza == 2 || lunghezza == -2)
        {
            for(int i = 0; i < 3; i++) //ciclo per righe
            {
                if(row_prow > row_stern)
                {
                    if(free_cell(row_prow-i,col_prow))
                        difesa[row_prow-i][col_prow] = 'S';
                    else throw Invalid_Coordinate();
                }
                else
                {
                    if(free_cell(row_prow+i,col_prow))
                        difesa[row_prow+i][col_prow]= 'S';
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
void Game::set_submarine(std::string xy) //setta coordinata sottomarino
{
    int row = Helper::convert_lett(xy);
    int col = Helper::convert_num(xy);
    if(!free_cell(row, col)) throw Invalid_Coordinate(); 
    difesa[row][col] = 'E'; //posiziona una e nella posizione indicata 
}

//CONTROLLANO CHE UNA CELLA O L'INTERO SPAZIO OCCUPATO DA UNA NAVE SIANO LIBERE O NO
bool Game::free_cell(int row, int col) //vale per sottomarino o celle libere singolarmente
{
    if(difesa[row][col] == 0) return true;
    else return false;
}
bool Game::free_battles_space(std::string xy,  int pos) //xy = centro, controlla che ci sia uno spazio pari a 5 celle per posizionare la corazzata 
{
    int row = Helper::convert_lett(xy); //G == 6
    int col = Helper::convert_num(xy); //8 == 7
    bool valid = true;
    if(pos==0) //orizzontale
    {
        for(int i=col-2; i<=col+2; i++) //controllo da colonna +2 a colonna -2  
        {
            if(free_cell(row, i)) //posiziona se le celle sono libere
                valid = true;
            else //vuol dire che la cella n è occupata
                return false;
        }
    }
    else //verticale
    {   
        for(int i=row-2; i<=row+2; i++) //controllo da riga +2 a riga -2 
        {
            if(free_cell (i, col)) //posiziona se le celle sono libere
                valid = true;
            else
                return false;
        }
    }   
    return valid;
}
bool Game::free_support_space(std::string xy, int pos) //controlla che ci sia uno spazio pari a 3 celle per posizionare la nave di supporto
{
    int row = Helper::convert_lett(xy); //G == 6
    int col = Helper::convert_num(xy); //8 == 7
    bool valid = true;
    if(pos==0) //orizzontale
    {
        for(int i=col-1; i<=col+1; i++) //controllo da colonna +1 a colonna -1
        {
            if(free_cell(row,i)) //posiziona se le celle sono libere
                valid = true;
            else 
                return false;
        }
    }
    else //verticale
    {   
        for(int i=row-1; i<=row+1; i++) //controllo da riga +1 a riga -1
        {
            if(free_cell(i, col)) 
                valid= true;
            else 
                return false;
        }
    }
    return valid;
}
char Game::get_cell(std::string xy)   //ritorna cella griglia difesa con il carattere corrispondente 
{
    int row = Helper::convert_lett(xy);
    int col = Helper::convert_num(xy);
    return difesa[row][col]; //C, S, E, 0, s, c, e
}
void Game::sunk_battleship(std::string center, int position) //rimozione sottomarino quando ho cinque c piccole (ccccc)
{
    int row_center = Helper::convert_lett(center);
    int col_center = Helper::convert_num(center);
    int count = 0;

    if(difesa[row_center][col_center] == 'c')
    {
        //Corazzata
        if(position == 0) //orizzontale
        {
            for(int i = col_center-2; i <= col_center+2; i++) //controllo da colonna centrale -2 a +2 
            {
                if(difesa[row_center][i] == 'c') //ogni volta che entro nell'if il mio contatore aumenta
                    count++;
            }
            if(count == 5) //corazzata con 5 c piccole 
            {
                for(int i = col_center-2; i <= col_center+2; i++)
                {
                   difesa[row_center][i] = 0; //le cinque c piccole vengono sostituite con degli spazi vuoti
                }
            }
        }
        else //verticale
        {
            for(int i = row_center-2; i <= row_center+2; i++) //controllo da riga centrale -2 a riga centrale +2 
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
void Game::sunk_support(std::string center, int position) //rimozione nave di supporto quando ho 3 s piccole (sss)
{
    int row_center = Helper::convert_lett(center);
    int col_center = Helper::convert_num(center);
    int count = 0;

    if(difesa[row_center][col_center] == 's')
    {
        //nave di supporto
        if(position == 0) //orizzontale
        {
            for(int i = col_center -1; i <= col_center+1; i++) //controllo da colonna centrale -1 a +1
            {
                if(difesa[row_center][i] == 's') //ogni volta che entro nell'if il mio contatore aumenta
                    count++; 
            }
            if(count == 3) //quando il contatore arriva a 3, situazione con 3 s piccole
            {
                for(int i = col_center -1; i <= col_center+1; i++)
                {
                    difesa[row_center][i] = 0; //le tre s piccole vengono sostituite con degli spazi vuoti
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
void Game::sunk_submarine(std::string center) //rimozione sottomarino 
{
    int row_center = Helper::convert_lett(center);
    int col_center = Helper::convert_num(center);
    if(difesa[row_center][col_center] == 'e') //quando viene colpito una volta la E viene rimossa
    {
        difesa[row_center][col_center] = 0;
    }
}

//VITTORIA
bool Game::is_battleship_sink(std::string center_b1, int pos_b1) //corazzata affondata 
{
    int row_center_b1 = Helper::convert_lett(center_b1);
    int col_center_b1 = Helper::convert_num(center_b1); 

    if(pos_b1 == 0) //ORIZZONTALE
    {
        for(int i = col_center_b1-2; i <= col_center_b1 +2; i++) //controllo colonna, da centro -2 a centro +2   
        {
            if(difesa[row_center_b1][i] == 0) //si tolgono i caratteri 
                return  true;
            else return false;
        }
    }
    else //VERTICALE
    {
        for(int i = row_center_b1-2; i <= row_center_b1 +2; i++) //controllo riga, da centro -2 a centro +2 
        {
            if(difesa[i][col_center_b1] == 0)//si tolgono i caratteri 
                return true;
            else return false;
        }
    }
    return false;
}
bool Game::is_submarine_sink(std::string center)    //sottomarino affondato
    {
        int row = Helper::convert_lett(center);
        int col = Helper::convert_num(center);
        if(difesa[row][col] == 0)       //si tolgono i caratteri 
            return true;
        else
            return false;
    }
bool Game::is_support_sink(std::string center, int pos) //nave di supporto affondato 
    {
        int row = Helper::convert_lett(center);
        int col = Helper::convert_num(center);
        if(pos == 0) //orizzontale
        {
            for(int i = col-1; i <= col +1; i++) //controlla colonna, da centro -1 a centro +1
            {
                if(difesa[row][i] == 0) //si tolgono i caratteri 
                    return true;
                else return false;
            }
        }
        else //verticale
        {
            for(int i = row-1; i <= row +1; i++) //controlla riga, da centro -1 a centro +1
            {
                if(difesa[i][col] == 0) 
                    return true;
                else return false;
            }
        }
        return false;
    }


//OVERLOADING OPERATORI
std::ostream& operator<<(std::ostream& os, Game& g) //operatore<<  
{
    os<<g.print_att()<< "\n"; //printa attacco
    os<<g.print_dif() << "\n"; //printa difesa
    return os;
}