/*
   file_ptr.cpp

*/

#ifndef ICC_UTILS_H
#define ICC_UTILS_H

#include <cstdio>		// printf()
#include <exception>		// class expeption
#include <new>			// bad_alloc()
#include <iostream>

#define DBG cout << __FILE__<<":"<<__LINE__ <<" "<< __func__ << "()" << endl;
#define DBG_S(txt) cout << __FILE__<<":"<<__LINE__ <<" "<< __func__ << "()" << txt << endl;

class Int {
public:
// TODO: byteswap + Groesse + Vorzeichen
#if BYTE_ORDER == BIG_ENDIAN
//  int             operator=(const int _n)     {return _n; }
  //icUInt32Number  operator=(const int _n)     {return _n; }
#endif
#if BYTE_ORDER == LITTLE_ENDIAN
  int             operator=(const int _n)     {return _n; }
  icUInt32Number  operator=(const int _n)     {return _n; }
#endif
};


// ============================================================
// Provisorische Ausnahme-Klasse; von std::exception abstammend:
// ============================================================
class Ausnahme : public std::exception {
public:
    virtual void report () const throw() {}  // oder = 0;
};


class ausn_file_io : public Ausnahme {
public:
    const char *fname;

    ausn_file_io (const char *fn) throw()	{ fname = fn; }
    virtual ~ausn_file_io () throw()		{ printf ("Destruktor von %s\n", __func__); }
    virtual const char* what() const throw()	{ return "Datei I/O"; }
    virtual void report () const throw() {
      printf ("Ausnahme-Report:\n");
      printf ("\tDatei \"%s\" war nicht zu �ffnen\n", fname);     // testweise
    };
};


/*void ausn_file_io::report () const throw()
{
    printf ("Ausnahme-Report:\n");
    printf ("\tDatei \"%s\" war nicht zu �ffnen\n", fname);	// testweise
}*/


// ==================
// Die FilePtr-Klasse:
// ==================
/*  Konstruktor wirft ausn_file_io bei Mi�erfolg.
*/
class FilePtr {
    FILE* f;
public:
    FilePtr (const char *fname, const char *mode)
      	{
	   if (!(f = fopen (fname, mode))) {
 	      printf ("%s(): Kann \"%s\" nicht �ffnen\n", __func__, fname);
	      throw ausn_file_io (fname);
           }
           printf ("%s(): �ffne \"%s\"\n", __func__, fname);
        }
    FilePtr (FILE* p)			{ f = p; }
    ~FilePtr ()				{ printf ("Schlie�e Datei...\n");
                                          if (f) fclose (f); }
    operator FILE*()			{ return f; }
};



// ==========================================================
// Beispiel einer doppelten Ressourcenanforderung im C++-Stil:
// ==========================================================
#if 0
void f ()
{
    // Datei �ffnen:
    FilePtr fp (__FILE__, "ro");	// wahrsch. erfolgreich
    //FilePtr fp ("gibs_nich", "ro");	// wirft wahrsch. ausn_file_io

    // Datei jetzt offen

    FILE* p = fp;		// Benutzung von fp wie gew�hnliches FILE*.

    // Speicher anfordern...
    // int* buf = new int [100];
    // Angenommen, geht schief und Ausnahme wird geworfen:
    throw std::bad_alloc();	// Ausnahmen-Mechanismus von C++ ruft Destr.
    				// der bis hierin fertigen Objekte auf:
				// --> ~FilePtr() schlie�t Datei fp

    // Daten aus Datei nach buf lesen...

    // Normalfall:
    // Blockende von fp --> Destruktor --> Datei fp wird geschlossen
}


// ======================================
// Zum Vergleich diese Funktion im C-Stil:
// ======================================
#include <cstdlib>	// malloc()

int f_C ()
{
    FILE* fp;
    int*  buf;

    if (! (fp = fopen ("datei","ro")))
       return -1;			// R�ckgabe-Kode f�r Mi�erfolg

    // Datei jetzt offen

    // Speicher anfordern...
    if (! (buf = (int*) malloc (100))) {
       fclose (fp);			// explizites Dateischlie�en n�tig
       return -1;			// R�ckgabe-Kode f�r Mi�erfolg
    }
    // Daten aus Datei nach buf lesen...

    // Normalfall:
    fclose (fp);			// explizites Dateischlie�en n�tig
    return 0;				// R�ckgabe-Kode f�r Erfolg
}


// ====================
// Fangen von Ausnahmen:
// ====================

int main ()
{
    try {
      f();
    }
    catch (Ausnahme & a) {	// f�ngt alles von Ausnahme Abstammende
        printf ("Ausnahme aufgetreten: %s\n", a.what());
        a.report();
    }
    catch (std::exception & e) { // f�ngt alles von exception Abstammende
        printf ("Std-Ausnahme aufgetreten: %s\n", e.what());
    }
    catch (...) {		// f�ngt alles �briggebliebene
        printf ("Huch, unbekannte Ausnahme\n");
    }
}
#endif

#endif //ICC_UTILS_H
