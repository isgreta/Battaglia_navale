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
        cout<<"INIZIO:"<<endl;
    }
    else cout<<"file non trovato";
    myfile.close();
    return 0;
}