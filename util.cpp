#include <cstdio>

class File_ptr {
    FILE* f;
public:
    File_ptr (const char* fname, const char* mode)
       {  if (! (f = fopen (fname, mode)))
             printf ("Kann \"%s\" nicht �ffnen\n", fname);
       }
   ~File_ptr () 	{ printf("Schlie�e\n"); if (f) fclose(f); }
   FILE* operator()() 	{ return f; }
};


int main ()
{
  {
    File_ptr fp ("datei", "ro");
  }
    printf ("danacb\n");
}

