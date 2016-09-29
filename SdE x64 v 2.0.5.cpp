
/*> run this program using the console pauser or add your own getch, system("pause") or input loop */
/*> Autor: Martin Röbke, “11.11.2013”

	Berechnung von Primzahlen beginnend mit 5.
	
	Es wird mit der Methode des Siebes des Eratosthenes gearbeitet, 
	kombiniert mit 6k+-1 Methode, die alle Primzahlen außer 2, 3 erfasst.
	
	Dabei ist der RAM-Verbrauch:
		1 Byte =(erfasst)= 24 fortlaufende Zahlen
		4 KB = Buffer-Größe während des Ausschreibens.
		
	Z.B. 	15 GB ~= Zahlenbereich bis 386.547.056.640
			 1 GB ~= Zahlenbereich bis  25.769.803.776
			 
	Ausgeschrieben wird in .pri Dateien innerhalb des Programmordners.
	Dabei wird im Dateinamen die gezählten Primzahlen vermerkt.

	Letzte Datei: 'Index= 983040 Min= 15077097176 SiebErgebnis'
	________________________________________________________________
	///////////////////V2: 15-30GB
		Bisher letzte Zahl: 386.547.056.640 = 360* 2^30 = 15*3*8* 2^30
		1. Erstellung Buffer char[] - enthält benötigte Primzahlen in altem bit Format- kein Wurzelabbruch nötig
		2. Verschiebung Startwert
		3. Verschiebung Limit
		Wurzel 30GB : 879257,70
	/// v 2.0.3::
		Einlesen : Zusammensetzung in char[] *buffer -> 
		Dabei jeweils Zeiger auf erste FREIE Position setzen
		
		Größe: Hält Sqrt als bits und drittel -> /8/3
LAUFZEIT:

<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
#include <windows.h> //FindFile
#include <math.h>   //WURZEL
#include <vector>   //VECTOR
#include <basetsd.h>//64 bit INT
#include <iostream> //stream für cout, cin
#include <time.h>	//Laufzeitmessung
#include <fstream>  //Dateistreams
#include <string.h> //Stringbearbeitung
#include <boost/lexical_cast.hpp> //Typumwandlung

using namespace std;

//GLOBALS PREPROCESSOR__________________________________
#define GB 15																	//Angabe der bereitgestellten GigaByte
//////////////////////__________________________________
#define SIZEG GB * 3 * 8 * pow(2,30)											//Angabe der resultierenden Zahlenmenge
//Hinweis: die Operation x*x wird etwas schneller ausgeführt als pow(x,2). 
//Man sollte daher für Quadrierung das x*x wählen, für alle anderen Potenzen aber pow.
#define MING (SIZEG + 1)														//Start der Berechnung
#define MAXG (2*SIZEG)															//Ende der Berechnung
#define DATSIZE (16*1024)														//Groesse der existierenden Dateien
#define _PATH "C:\\Users\\Martin\\Documents\\Cpp\\Primzahlen 15GB\\"			//Pfad der bereitgestellten .pri
//______________________________________________________
//Test Auf 64 BIT - Sonst Abbruch

//==================================================================
//FUNKTION: zahl 6k+-1 --> index im vector
inline UINT64 _index(UINT64 zahl){
	int rest = zahl%6;
	UINT64 index = (rest==5) + (zahl-rest)/3;
	return index;
}
void _buftest(char* buffer, int size){
	cout<<endl<<"BUFFERTEST"<<endl;
	cout<<"buffer[0] "<<(unsigned int) buffer[0] <<endl;
	cout<<"buffer[1] "<<(unsigned int) buffer[1] <<endl;
	cout<<"buffer[2] "<<(unsigned int) buffer[2] <<endl;
	cout<<"buffer[size-1] "<<(unsigned int) buffer[size-1] <<endl;
}
//-------------------------------------------------------------------------

int main(int argc, char *argv[])
{
	clock_t start, zwischenzeit, end1, end2; //ZEITMESSUNG
	
	string dateiname = "SiebErgebnis.pri";
	
	UINT64 SQRT_LIMIT=UINT64(sqrt(MAXG)+0.5); //Vordefinition der Wurzel als Grenze  
	
	cout << "RAM [GiB]= " << GB <<endl;
    cout << "Limit= " << MAXG <<endl<<endl;
    cout << "SQRT_LIMIT= " << SQRT_LIMIT <<endl<<endl;

	UINT64 primvor;
    UINT64 buffer_size_klein = SQRT_LIMIT / 3 / 8 + 2; //bits-> dritteln -> + Sicherheit
    //noch aufrunden auf ganze Dateien:
    UINT64 buffer_size = buffer_size_klein;
    if(buffer_size_klein % DATSIZE) UINT64 buffer_size = DATSIZE * (buffer_size_klein / DATSIZE +1); 

    //buffer_size in byte und als ganze DATSIZE
    char* buffer = new char[buffer_size];					//Speichert Zuordnungseinheiten zusammen
	cout<<"buffer_size" <<buffer_size<<endl;
	  //--SCHREIBEN-----------------------------------------------
	
	UINT64 anzahldat = buffer_size / DATSIZE;
	cout << "anzahldat= " << anzahldat <<endl<<endl;

	unsigned int datei_i, vorher = 0;
	for(datei_i=1; datei_i<=anzahldat; datei_i++ ){//Dateien beschreiben, jede mit .pri

		//Dateinamen erstellen. Aufteilbar durch Leerzeichen
		string datei = _PATH;
		datei.append("Index= "); //Beginn des Filename
		datei.append(boost::lexical_cast<std::string>(datei_i));//Weiter mit Laufzahl
		datei.append(" Min= *"); //2. Parameter
		//
		HANDLE hFind;								//---Dateiname komplettieren
			WIN32_FIND_DATA FindFileData;
			hFind = FindFirstFile(datei.c_str(), &FindFileData);
			if (hFind == INVALID_HANDLE_VALUE) 
			   {
			      cout<< "FindFirstFile failed "<< GetLastError();
			      return 0;
			   } 
	
			datei = FindFileData.cFileName; //NAME GEFUNDEN
		FindClose(hFind);
		
		//Schneidet Pfad und Name zusammen:
		string dateipfad_name = _PATH;
		dateipfad_name.append(datei); 
	
			//Dateiname erstellt.	
		ifstream myfile (dateipfad_name.c_str(),ifstream::binary);
			//FileStream geöffnet, voller Dateiname als Char übergeben.
			//Hochsetzen des Zeigers durch Addition:
		myfile.read (buffer + vorher*DATSIZE, DATSIZE);					//>>>>>>>>>>>>>>>>>>einlesen<<<<<<<<<<<<<<<<<<<<<<
		cout<<vorher*DATSIZE<<endl;
		if (myfile)
      	cout << "all characters read successfully."<<endl;
   		else
     	cout << "error: only " << myfile.gcount() << " could be read";
			//File wird geschlossen
		myfile.close();	
		vorher++;		
	}//FOR// Datei gelesen, 
	
	_buftest(buffer, buffer_size) ;	
	cout << "Vector erstellt.  Berechnung beginnt..." <<endl;
    cout << "Buffer:"<<buffer_size<<endl;
    
//    start = clock(); //BEGINN ZEIT

	// release dynamically-allocated memory
	delete[] buffer; 
	cout <<"_Sde_";
  return 0;
} //MAIN

