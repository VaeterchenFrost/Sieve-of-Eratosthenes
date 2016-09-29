#include <math.h>
#include <vector> 
#include <windows.h> 
#include <iostream>
#include <tchar.h>
#include <time.h>
#include <sstream>
#include <string>
using namespace std;
/////////////////////////////////////////////////////////////////////////////////
///////////////////////4GB Patch!!!!!!!!!!!!! - Benötigt <~2.936.552 KB 
//   16 minuten für p=2!
//   ~35 min bis p=13
//
/////////////////////////////////////////////////////////////////////////////////
int main(void){
//    char path[]="C:\\Users\\Martin\\Documents\\Cpp\\PrimzahlenXXD.ini";
    int size = 2000000000; //Größe jedes Vectors
    //unsigned int 	4 Byte 	0 bis 4.294.967.295
    //cout << "Please insert upper limit.\n";
    //cin >> limit; 
       
                clock_t start, end1, end2; //ZEITMESSUNG
                start = clock();
    //Initialsisierung
    //v1 0-2*10^9-1
//    v1 2-4*10^9-1
//    v1 0-6*10^9-1
//    ...
//    v1 18-20*10^9-1
//    v1 20-22*10^9-1
//    v1 22-24*10^9-1    
    vector<bool> v1(size,false),v2(size,false),v3(size,false),v4(size,false),v5(size,false),v6(size,false),v7(size,false),v8(size,false),v9(size,false),v10(size,false),v11(size,false),v12(size,false);   

  //Zahlen 0 und 1 gestrichen
    v1[0]=true;
    v1[1]=true;
  //Nachricht
    cout << "Vectoren erstellt." <<endl;
    
//------------------------
  //unsigned char c1;
//     cin >> c1;
//    return 0;

//-------------------------------------------------------------------------

      for(int i=2; i<=154920; ++i){ //Für jeden in Frage kommenden Faktor (bis Wurzel 24*10^9 ~154919
              if(!v1[i]){ // nur den ersten zu prüfen, da alle diese Faktoren in diesem zu finden sind^^
                        cout<<i<<"| v";      
 // Durchlauf mit der Schrittweite i
 //für jeden Vektor - überspringen zum nächsten    
                    int k=i*i; 
                    //v1   
                    do{
                           v1[k]=true;
                           k+=i;
//                           if(k>2147483647)cout<<k;
                           }
                    while(k<v1.size());
                    cout<<1;
                    // 4 mrd. abziehen:
                         k-=v1.size();
                    //v2

                    do{
                           v2[k]=true;
                           k+=i;
                           }
                    while(k<v1.size());
                     cout<<2;
                    // 4 mrd. abziehen:
                         k-=v1.size();                         
                    //v3

                    do{
                           v3[k]=true;
                           k+=i;
                           }
                    while(k<v1.size());
                     cout<<3;
                    // 4 mrd. abziehen:
                         k-=v1.size();

                    //v4
                    do{
                           v4[k]=true;
                           k+=i;
                           }
                    while(k<v1.size());
                     cout<<4;
                    // 4 mrd. abziehen:
                         k-=v1.size();
                    //v5

                    do{
                           v5[k]=true;
                           k+=i;
                           }
                    while(k<v1.size());
                     cout<<5;
                    // 4 mrd. abziehen:
                         k-=v1.size();
                    //v6

                     do{
                           v6[k]=true;
                           k+=i;
                           }
                    while(k<v1.size());
                     cout<<6;
                    // 4 mrd. abziehen:
                         k-=v1.size();
                    //v7

                      do{
                           v7[k]=true;
                           k+=i;
                           }
                    while(k<v1.size());
                     cout<<7;
                    // 4 mrd. abziehen:
                         k-=v1.size();
                    //v8

                      do{
                           v8[k]=true;
                           k+=i;
                           }
                    while(k<v1.size());
                     cout<<8;
                    // 4 mrd. abziehen:
                         k-=v1.size();
                    //v9

                      do{
                           v9[k]=true;
                           k+=i;
                           }
                    while(k<v1.size());
                     cout<<9;
                    // 4 mrd. abziehen:
                         k-=v1.size();
                    //v10

                      do{
                           v10[k]=true;
                           k+=i;
                           }
                    while(k<v1.size());
                     cout<<10;
                    // 4 mrd. abziehen:
                         k-=v1.size();
                    //v11

                      do{
                           v11[k]=true;
                           k+=i;
                           }
                    while(k<v1.size());
                     cout<<11;
                    // 4 mrd. abziehen:
                         k-=v1.size();
                    //v12

                      do{
                           v12[k]=true;
                           k+=i;
                           }
                    while(k<v1.size());
                     cout<<12<<endl;
               
              }
      }
 //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::                               
      end1 = clock();                 
 
//    cout << "\nPrimes less or equal " << limit << " are:\n";
   // int zaehler=0;
//    for(long long i=0; i<=limit;++i) if(!v1[i]) ++zaehler;
//    cout << zaehler<<endl;
    
            end2 = clock(); //ZEITMESSUNG
            cout << (end1-start)/CLOCKS_PER_SEC <<" Sekunden"<< endl;
            cout << (end2-start)/CLOCKS_PER_SEC <<" Sekunden"<< endl;
    unsigned char c2;
    cin >> c2;
    return 0;
}
