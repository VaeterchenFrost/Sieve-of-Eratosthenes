/*
	Name: Grundstruktur.cpp
	Copyright: -  
	Author: Martin Röbke
	Date: 01.03.16 17:14
	Description: 
	
	Grundlage in der Programmarchitektur der verbesserten
	Primzahlenberechnung; Sieb des Erastosthenes (SdE 1.-2.).
	
	Ziele: 
	1. Modularer Aufbau
	2. Skalierbarkeit
	3. Ressourcenschonend in RAM und HD.
	
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
==> Bisheriger Stand





	LAUFZEIT:
*/



