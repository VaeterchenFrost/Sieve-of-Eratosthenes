/* run this program using the console pauser or add your own getch, system("pause") or input loop */
/* Autor: Martin Röbke, 11.11.2013
	Berechnung von Primzahlen beginnend mit 5.
	Es wird mit der Methode des Siebes des Eratosthenes gearbeitet, 
	kombiniert mit 6k+-1 Methode, die alle Primzahlen außer 2, 3 erfasst.
	Dabei ist der RAM-Verbrauch:
		1 Byte =(erfasst)= 24 fortlaufende Zahlen
		4 KB = Buffer-Größe während des Ausschreibens.
	Z.B. 	15 GB ~= Zahlenbereich bis 386.547.056.640
			 1 GB ~= Zahlenbereich bis  25.769.803.776
	Ausgeschrieben wird in .txt Dateien innerhalb des Programmordners.
	Dabei wird im Dateinamen die gezählten Primzahlen vermerkt.
	Geschwindigkeit TEST: 0.96 GB in 6 Minuten mit 2 ZE pro Datei. ~21053 dat/min
	Letzte Datei: 'Index= 983040 Min= 15077097176 SiebErgebnis'
//////////////LAUFZEIT:
45-58 		s für 50MB Ram 
1023-1309 	s für 1GB Ram: 39.7s/Mrd
12375s -16(500)s für 15GB Ram: 825s/GB rechnen

*/
#include <math.h>   //WURZEL
#include <vector>   //VECTOR
#include <basetsd.h>//64 bit INT
#include <iostream> //stream für cout, cin
#include <time.h>	//Laufzeitmessung
#include <fstream>  //Dateistreams
#include <string.h> //Stringbearbeitung
#include <boost/lexical_cast.hpp> //Typumwandlung

using namespace std;

//FUNKTION: zahl 6k+-1 --> index im vector
inline UINT64 _index(UINT64 zahl){
	int rest= zahl%6;
//	int zuschlag = 0;
//	if(rest==5) zuschlag+=1;
	UINT64 index= (rest==5) + (zahl-rest)/3;
	return index;
}

int main(int argc, char *argv[]) {
	clock_t start, zwischenzeit, end1, end2; //ZEITMESSUNG
	string dateiname = "SiebErgebnis.pri";
	int gb = 15;
	UINT64 bits = pow(2,30); //1024^3
//	UINT64 bits = pow(2,20); //1024^2
    UINT64 limit=3*8*bits*gb;
    UINT64 feldgroesse = limit/3;
    cout << "RAM= " << gb <<endl;
    cout << "limit= " << limit <<endl<<endl;
    vector<bool> v(feldgroesse,false); //ZU 3
    v[0]=true; // Zahlen beginnen bei [1], hier mit 5
    cout << "Vector erstellt.  Berechnung beginnt..." <<endl;
    UINT64 SQRT_LIMIT=UINT64(sqrt(limit)+0.5); //Vordefinition der Wurzel als Grenze    
    start = clock(); //BEGINN ZEIT
    
//--RECHNEN---------------------------------
	UINT64 q, x; //q=Echtzahlposition, x=Zwischenspeicher
    UINT64 i = 5; //BEGINN PRÜFUNG
    while(i<SQRT_LIMIT){
    	UINT64 iindex = _index(i);
            if(!v[iindex]){//STREICHEN
				//QUADRAT           	
				q = i*i;
				v[_index(q)] = true;
				if(iindex%2){//6k-1
					while(true){
						x = q + 2*i;
						if(x<limit){
							q = x;
							v[_index(q)] = true;
						}
						else break;
						x = q + 4*i;
						if(x<limit){
							q = x;
							v[_index(q)] = true;
						}
						else break;
					}//-SPRUNGSCHLEIFE
				}//- 6k-1
				else{
					while(true){
						x = q + 4*i;
						if(x<limit){
							q = x;
							v[_index(q)] = true;
						}
						else break;
						x = q + 2*i;
						if(x<limit){
							q = x;
							v[_index(q)] = true;
						}
						else break;
					}//-SPRUNGSCHLEIFE
				}//- 6k+1				
			}//-STREICHEN
			i+=2;
			if(!(i%3)) i+=2; //wenn durch drei teilbar nochmals erhöhen
    }
//--NACHBEARBEITUNG-------------------------   
    cout << endl; //Absatz zu Berechnung
    //--Zeit für Berechnung---
    end1 = clock(); 
    cout <<"Zeit bisher: " << (end1-start)/CLOCKS_PER_SEC <<" Sekunden"<< endl;
    cout << "Primzahlen bis " << limit << " werden in "<<dateiname<<" geschrieben."<<endl;
    //--SCHREIBEN-----------------------------------------------
	//---------------ofstream myfile (dateiname,ofstream::binary);
	//Anzahl Dateien: 1024^2
	int anzahldat = pow(2,10)*960; //------------ 983040 Dateien!!
	cout << "Das sind " << anzahldat << "Dateien" << endl;
	UINT64 primvor = 2;
	int size = 4096; 	//Zuordnungsgröße
	UINT64 pos  = 0;	//aktuelle Position in Bit
	int sprung = size*8; //BIT pro Zuordnungseinheit	
	char* buffer = new char[size];//Speichert Zuordnungseinheit REVERS!
	for(int datei_i=1;datei_i<=anzahldat; datei_i++){//Dateien beschreiben, jede mit .pri
		//Dateinamen erstellen. Aufteilbar durch Leerzeichen
		string datei = "Index= "; //Beginn des Filename
		datei.append(boost::lexical_cast<std::string>(datei_i));//Weiter mit Laufzahl
		datei.append(" Min= "); //2. Parameter
		datei.append(boost::lexical_cast<std::string>(primvor));//Primzahlen zuvor
		datei.append(" "); //Leerzeichen zu Trennung des Namen
		datei.append(dateiname); //Name mit Endung 
		//Dateiname erstellt.
		ofstream myfile (datei.c_str(),ofstream::binary);
		//FileStream geöffnet, voller Dateiname als Char übergeben.
//		feldgroesse/sprung/anzahldat ergibt hier 4, also 4 ZE pro Datei.
		for(UINT64 i=feldgroesse/sprung/anzahldat;i>0; i--){//Zuordnungseinheit schreiben
			for(int j=size-1;j>=0; j--){//buffer mit Bytes füllen und 0 zählen
				//in Vector an Stelle pos
				//ZÄHLEN: 8 addieren und alle 1 en abziehen, sodass die anzahl nullen berechnet wird
					primvor+=8 -(v[pos]+v[pos+1]+v[pos+2]+v[pos+3]+v[pos+4]+v[pos+5]
					+v[pos+6]+v[pos+7]);
				//Buffer füllen
					buffer[size-1-j] = v[pos]+2*v[pos+1]+4*v[pos+2]+8*v[pos+3]
					+16*v[pos+4]+32*v[pos+5]+64*v[pos+6]+128*v[pos+7];
				pos+=8; //Position um 1 Byte weiter
			}//Buffer gefüllt
			myfile.write (buffer,size);		
		}//Datei geschrieben
		//File wird geschlossen
		myfile.close();
	}//Ergebnis gespeichert/geschrieben
	// release dynamically-allocated memory
    delete[] buffer;
//--AUSGABE---------------------------------
   	end2 = clock(); //GESAMTZEITMESSUNG
    cout << (end1-start)/CLOCKS_PER_SEC <<" Sekunden"<< endl;
    cout << (end2-start)/CLOCKS_PER_SEC <<" Sekunden"<< endl;
    system("pause");
    
    return 0;    
}



