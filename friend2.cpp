/*
   friend3.cpp

   siehe friend1.cpp

*/

#include <cstdio>

#define HEAD_WAS 	printf ("Header::%s():\n",__func__);
#define ICC_WAS		printf ("ICC::%s():\n",__func__);



class Header {
private:
    int privat_data;			// privates Datum von Header

public:
    void write ()	{ HEAD_WAS }	// �ffentl. Methode von Header
    void show ()	{ HEAD_WAS }	// �ffentl. Methode von Header
};


class ICC {
    Header header;			// ICC deklariert header als
    					// *privates* Element.
					// Damit ist es f�r ICC-*Anwender*
					// unzug�nglich
public:

    void write ()		// z.B schreibt ICC-Profil
       { ICC_WAS
       header.write(); 		// ok, ICC ruft �ffentl. Header-Methode auf
       // ...
//     header.privat_data = 1;  // Fehler: ICC kann als gew�hnl. Anwender von
       }			// Header auf private Header-Elemente nicht
				// zugreifen
    void show_header ()
       { ICC_WAS
       header.show();		// ICC reicht Header-Funktion an ICC-Anwender
       }			// durch, ver�ffentlicht diese
};


void f ()
{
    ICC icc;			// 'ich' als f() bin ein Anwender von ICC

    icc.write();		// ok, 'ich' als Nutzer von icc rufe �ffentl.
    				// icc-Funktion auf

    icc.show_header();		// ok, �ffentl. Funktion von icc

//  icc.header.show();		// Fehler: header ist privates icc-Element,
    				// f�r 'mich' als f() nicht zug�nglich
//  icc.header.write();		// dito
//  icc.header.privat_data = 1; // dito

}

int main ()
{
    f();
}

