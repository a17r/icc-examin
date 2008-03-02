/*
   friend2.cpp

   �ber Freundschaften.

   Aufgabe:
   =======
    Die Klasse ICC besitze ein Element (Objekt) vom Typ Header:
   	class ICC {
	    //...
	    Header header;
        };
    Die Klasse Header besitze eine Funktion write() und eine Funktion show():
        class Header {
	    //...
	    void write ();
	    void show ();
	};
    Intern in ICC soll write() und show() aufrufbar sein, aber ein externer
    Anwender eines ICC-Objektes soll zwar Header::show(), aber nicht
    Header::write() aufrufen k�nnen. Also

   	ICC icc;

	icc.header.show();	// soll ok sein
	icc.header.write();	// Compiler soll Fehler melden!


    Es gibt (mindestens) zwei M�glichkeiten, dies zu erreichen:

    1.) Header deklariert show() als public und write() als private; damit
        k�nnen Externe zwar show(), aber nicht write() aufrufen. ICC als
	"besonderer" Header-Kunde mu� aber auch an private Header-Elemente ran.
        Deshalb erkl�rt Header die Klasse ICC als 'befreundet'.
        ICC legt nun sein Header-Element als public an, so da� ICC-Kunden
	direkt die �ffentlichen Header-Funktionen als
	    icc.header.show()
	aufrufen k�nnen.

    2.) ICC versteckt sein Element Header als privat vor jedem ICC-Kunden-
        Zugriff und reicht lediglich die Header-Funktionen, die ICC-Kunden
	nutzen k�nnen sollen, explizit nach au�en durch.
	Header, sodurch vor ICC-Kunden versteckt, kann nun alles, worauf ICC
	Zugriff braucht, public deklarieren. Das erspart ausdr�ckliche
	Freundschaftsbekundungen in Richtung ICC.
	
    Diese Datei hier f�hrt Variante 1 aus, die Datei "friend2.cpp" die zweite.

    Variante 1 hat den vielleicht Makel, da� ein ICC-Kunde explizit
    eine ICC-Interna, ein ICC-Element namens 'header' in die Hand nehmen mu�
    zum Aufruf
    	icc.header.show().
    M�glw. sollten ICC-Kunden syntakisch strikt auf der ersten Ebene bleiben
    k�nnen a'la
        icc.show_header().
    Aber das mag eine Geschmacksfrage sein.
*/

#include <cstdio>

#define HEAD_WAS 	printf ("Header::%s():\n",__func__);
#define ICC_WAS		printf ("ICC::%s():\n",__func__);



class ICC;		// Klasse, die Header als Freund nennen will/soll;
			// mu� deshalb vor Header *erw�hnt* werden;


class Header {		// Hier soll ICC auf Privates zugreifen k�nnen

    friend class ICC;	// Header erkl�rt: ICC ist mein Freund!

private:
    int privat_data;			// privates Datum von Header
    void write ()	{ HEAD_WAS }	// private Methode von Header

public:
    void show ()	{ HEAD_WAS }	// �ffentl. Methode von Header
};


class ICC {
public:
    Header header;

    void write ()
       { ICC_WAS
       header.write(); 		// ICC ruft private Header-Methode auf
       header.privat_data = 1;  // ICC beschreibt privates Header-Element
       }			// D�rfte normalerweise niemand au�er Header
};


void f ()
{
    ICC icc;			// 'ich' als f() bin ein Anwender von ICC

    icc.write ();		// ok, 'ich' als Nutzer von icc rufe �ffentl.
    				// icc-Funktion auf

    icc.header.show ();		// ok, Aufruf einer �ffentlichen Funktion
    				// eines �ffentlichen icc-Elementes

//  icc.header.write ();	// Fehler: Header::write() ist f�r 'mich',
    				// den Header nicht als friend erkl�rt hat,
				// privat.

//  icc.header.privat_data = 1; // Fehler, Header::privat_data ist f�r 'mich'
    				// privat.
}

int main ()
{
    f();
}

