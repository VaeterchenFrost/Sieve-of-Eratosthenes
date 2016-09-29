/*> run this program using the console pauser or add your own getch, system("pause") or input loop */
/*> Autor: Martin Röbke, 29.09.2016

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
