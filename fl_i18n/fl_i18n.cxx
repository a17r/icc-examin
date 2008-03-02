/*
 * ICC Examin ist eine ICC Profil Betrachter
 * 
 * Copyright (C) 2004-2006  Kai-Uwe Behrmann 
 *
 * Autor: Kai-Uwe Behrmann <ku.b@gmx.de>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * -----------------------------------------------------------------------------
 *
 * Internationalisation functions
 * 
 */

#include "fl_i18n.H"

#include <locale.h>
#include <libintl.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

/* include pthread.h here for threads support */
#ifdef USE_THREADS
#include "threads.h"
#endif

#ifdef __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#endif


/* The following macros belong to Kai-Uwe's debug environment. */
#ifdef DEBUG
#include "icc_utils.h"
#else
/*extern int icc_debug;*/
#endif
#ifndef DBG_PROG_START
#define DBG_PROG_START
#endif
#ifndef DBG_PROG
#define DBG_PROG
#endif
#ifndef DBG_PROG_V
#define DBG_PROG_V(text)
#endif
#ifndef DBG_PROG_S
#define DBG_PROG_S(text)
#endif
#ifndef DBG_PROG_ENDE
#define DBG_PROG_ENDE
#endif


#define TEXTLEN 48

#ifdef USE_GETTEXT
void
fl_set_codeset_    ( const char* lang, const char* codeset_,
                     char* locale, char* codeset,
                     int set_zero_locale )
{
    if( strlen(locale) )
    {
      char* pos = strstr(locale, lang);
      if(pos != 0)
      {
        /* 1 a. select an appropriate charset (needed for non UTF-8 fltk/gtk1)*/
        sprintf (codeset, codeset_); DBG_PROG_V( locale <<" "<< strrchr(locale,'.'))
 
          /* merge charset with locale string */
        if((pos = strrchr(locale,'.')) != 0)
        {
          *pos = 0; DBG_PROG_V( locale )
        } else
          pos = & locale[strlen(locale)];
        snprintf(pos, TEXTLEN-strlen(locale), ".%s",codeset);

        DBG_PROG_V( locale )

        /* 1b. set correct environment variable LANG */
        {
          char settxt[64];
          snprintf( settxt, 63, "LANG=%s", locale );
          //TODO ? putenv( settxt );
        }
        /* setenv("LANG", locale, 1); *//* setenv is not standard C */

        /* 1c. set the locale info after LANG */
        if(set_zero_locale)
        {
          char *ptr = setlocale (LC_MESSAGES, "");
          if(ptr) snprintf( locale, TEXTLEN, ptr); DBG_PROG_V( locale )
        }
      }
    }
}
#endif

#ifdef WIN32
#define DIR_SEPARATOR "\\"
#else
#define DIR_SEPARATOR "/"
#endif

signed int
fl_search_locale_path (int n_places, const char **locale_paths,
                    const char *search_lang, const char *app_name)
{
  /* search in a given set of locale paths for a valid locale file */
  for (int i = 0; i < n_places; ++i)
  {
    if(locale_paths[i])
    {
      char test[1024];
      FILE *fp = 0;
      /* construct the full path to a possibly valid locale file */
      snprintf(test, 1024, "%s%s%s%sLC_MESSAGES%s%s.mo",
                           locale_paths[i], DIR_SEPARATOR,
                           search_lang, DIR_SEPARATOR, DIR_SEPARATOR, app_name);
      /* test the file for existence */
      fp = fopen(test, "r");
      if(fp)
      {
        fclose(fp);
        /* tell about the hit place */
        return i;
      }
    }
  }
  return -1;
}

void
fl_initialise_locale( const char *domain, const char *locale_path )
{

#ifdef USE_GETTEXT
  DBG_PROG_START
  char locale[TEXTLEN];
  int set_zero_locale = 1;

# ifdef __APPLE__
  // 1. get the locale info
  CFLocaleRef userLocaleRef = CFLocaleCopyCurrent();
  CFStringRef cfstring = CFLocaleGetIdentifier( userLocaleRef );

  CFShow( cfstring );
  DBG_PROG_V( CFStringGetLength(cfstring) )

    // copy to a C buffer
  CFIndex gr = 36;
  char text[36];
  Boolean fehler = CFStringGetCString( cfstring, text, gr, kCFStringEncodingISOLatin1 );

  if(fehler) {
      DBG_PROG_S( _("osX locale obtained: ") << text )
    snprintf(locale,TEXTLEN, text);
  } else {
      DBG_PROG_S( _("osX locale not obtained") )
  }
  DBG_PROG_V( locale )

  // set the locale info
  const char* tmp = 0;
  if(strlen(locale))
     setlocale (LC_MESSAGES, locale);
  if (tmp)
    snprintf(locale,TEXTLEN, tmp);
  set_zero_locale = 0;
# else
  DBG_PROG

  // 1. get default locale info ..
  const char *tmp = setlocale (LC_MESSAGES, "");
  if(tmp) {
    snprintf(locale,TEXTLEN, tmp);
    DBG_PROG_V( locale )
  }

    // .. or take locale info from environment
  if(getenv("LANG"))
    snprintf(locale,TEXTLEN, getenv("LANG"));
# endif

  char codeset[24] = "ISO-8859-1";


      // add more LINGUAS here
      // borrowed from http://czyborra.com/charsets/iso8859.html
    fl_set_codeset_( "af", "ISO-8859-1", locale, codeset, set_zero_locale ); // Afrikaans
    fl_set_codeset_( "ca", "ISO-8859-1", locale, codeset, set_zero_locale ); // Catalan
    fl_set_codeset_( "da", "ISO-8859-1", locale, codeset, set_zero_locale ); // Danish
    fl_set_codeset_( "de", "ISO-8859-1", locale, codeset, set_zero_locale ); // German
    fl_set_codeset_( "en", "ISO-8859-1", locale, codeset, set_zero_locale ); // English
    fl_set_codeset_( "es", "ISO-8859-1", locale, codeset, set_zero_locale ); // Spanish
    fl_set_codeset_( "eu", "ISO-8859-1", locale, codeset, set_zero_locale ); // Basque
    fl_set_codeset_( "fi", "ISO-8859-1", locale, codeset, set_zero_locale ); // Finnish
    fl_set_codeset_( "fo", "ISO-8859-1", locale, codeset, set_zero_locale ); // Faroese
    fl_set_codeset_( "fr", "ISO-8859-1", locale, codeset, set_zero_locale ); // French
    fl_set_codeset_( "ga", "ISO-8859-1", locale, codeset, set_zero_locale ); // Irish
    fl_set_codeset_( "gd", "ISO-8859-1", locale, codeset, set_zero_locale ); // Scottish
    fl_set_codeset_( "is", "ISO-8859-1", locale, codeset, set_zero_locale ); // Icelandic
    fl_set_codeset_( "it", "ISO-8859-1", locale, codeset, set_zero_locale ); // Italian
    fl_set_codeset_( "nl", "ISO-8859-1", locale, codeset, set_zero_locale ); // Dutch
    fl_set_codeset_( "no", "ISO-8859-1", locale, codeset, set_zero_locale ); // Norwegian
    fl_set_codeset_( "pt", "ISO-8859-1", locale, codeset, set_zero_locale ); // Portuguese
    fl_set_codeset_( "rm", "ISO-8859-1", locale, codeset, set_zero_locale ); // Rhaeto-Romanic
    fl_set_codeset_( "sq", "ISO-8859-1", locale, codeset, set_zero_locale ); // Albanian
    fl_set_codeset_( "sv", "ISO-8859-1", locale, codeset, set_zero_locale ); // Swedish
    fl_set_codeset_( "sw", "ISO-8859-1", locale, codeset, set_zero_locale ); // Swahili

    fl_set_codeset_( "cs", "ISO-8859-2", locale, codeset, set_zero_locale ); // Czech
    fl_set_codeset_( "hr", "ISO-8859-2", locale, codeset, set_zero_locale ); // Croatian
    fl_set_codeset_( "hu", "ISO-8859-2", locale, codeset, set_zero_locale ); // Hungarian
    fl_set_codeset_( "pl", "ISO-8859-2", locale, codeset, set_zero_locale ); // Polish
    fl_set_codeset_( "ro", "ISO-8859-2", locale, codeset, set_zero_locale ); // Romanian
    fl_set_codeset_( "sk", "ISO-8859-2", locale, codeset, set_zero_locale ); // Slovak
    fl_set_codeset_( "sl", "ISO-8859-2", locale, codeset, set_zero_locale ); // Slovenian

    fl_set_codeset_( "eo", "ISO-8859-3", locale, codeset, set_zero_locale ); // Esperanto
    fl_set_codeset_( "mt", "ISO-8859-3", locale, codeset, set_zero_locale ); // Maltese

    fl_set_codeset_( "et", "ISO-8859-4", locale, codeset, set_zero_locale ); // Estonian
    fl_set_codeset_( "lv", "ISO-8859-4", locale, codeset, set_zero_locale ); // Latvian
    fl_set_codeset_( "lt", "ISO-8859-4", locale, codeset, set_zero_locale ); // Lithuanian
    fl_set_codeset_( "kl", "ISO-8859-4", locale, codeset, set_zero_locale ); // Greenlandic

    fl_set_codeset_( "be", "ISO-8859-5", locale, codeset, set_zero_locale ); // Byelorussian
    fl_set_codeset_( "bg", "ISO-8859-5", locale, codeset, set_zero_locale ); // Bulgarian
    fl_set_codeset_( "mk", "ISO-8859-5", locale, codeset, set_zero_locale ); // Macedonian
    fl_set_codeset_( "ru", "ISO-8859-5", locale, codeset, set_zero_locale ); // Russian
    fl_set_codeset_( "sr", "ISO-8859-5", locale, codeset, set_zero_locale ); // Serbian
    fl_set_codeset_( "uk", "ISO-8859-5", locale, codeset, set_zero_locale ); // Ukrainian

    fl_set_codeset_( "ar", "ISO-8859-6", locale, codeset, set_zero_locale ); // Arabic
    fl_set_codeset_( "fa", "ISO-8859-6", locale, codeset, set_zero_locale ); // Persian
    fl_set_codeset_( "ur", "ISO-8859-6", locale, codeset, set_zero_locale ); // Pakistani Urdu

    fl_set_codeset_( "el", "ISO-8859-7", locale, codeset, set_zero_locale ); // Greek

    fl_set_codeset_( "iw", "ISO-8859-8", locale, codeset, set_zero_locale ); // Hebrew
    fl_set_codeset_( "ji", "ISO-8859-8", locale, codeset, set_zero_locale ); // Yiddish

    fl_set_codeset_( "tr", "ISO-8859-9", locale, codeset, set_zero_locale ); // Turkish

    fl_set_codeset_( "th", "ISO-8859-11", locale, codeset, set_zero_locale ); // Thai

    fl_set_codeset_( "zh", "ISO-8859-15", locale, codeset, set_zero_locale ); // Chinese

    fl_set_codeset_( "ja", "EUC", locale, codeset, set_zero_locale ); // Japan ; eucJP, ujis, EUC, PCK, jis7, SJIS

  if(strlen(locale))
    DBG_PROG_S( locale );


  // 2. for GNU gettext, the locale info is usually stored in the LANG variable
  const char *loc = getenv("LANG");

  if(loc) {

      // good
    DBG_PROG_V( loc )

  } else {

    DBG_PROG_S( _("try to set LANG") );

      // set LANG
#   ifdef __APPLE__
    if (strlen(locale))
      setenv("LANG", locale, 0);
#   endif

      // good?
    if(getenv("LANG"))
      DBG_PROG_S( getenv("LANG") );
  }

  DBG_PROG_V( system("set | grep LANG") )
  if(strlen(locale))
    DBG_PROG_S( locale );

  // 3. where to find the MO file? select an appropriate directory
  char* bdtd = 0;
  bdtd = bindtextdomain (domain, locale_path);
  DBG_PROG_S( _("try locale in ") << bdtd );

  // 4. set our charset
  char* cs = bind_textdomain_codeset(domain, codeset);

  // 5. our translations
  textdomain (domain);

  if(cs)
    DBG_PROG_S( _("set codeset for") << domain << " to " << cs );

  // gettext initialisation end

  DBG_PROG_ENDE
#endif
}


#include <FL/Fl_Menu_Item.H>
void
fl_translate_menue( Fl_Menu_Item* menueleiste )
{
#ifdef USE_GETTEXT
  DBG_PROG_START
  int size = menueleiste->size();
  DBG_PROG_V( size )
  for(int i = 0; i < size ; ++i) {
    const char* text = menueleiste[i].label();
    menueleiste[i].label( _(text) );
    DBG_PROG_V( i )
    if(text)
      DBG_PROG_V( text <<" "<< _(text) );
  }
#endif
}

#include <FL/Fl.H>
const char*
threadGettext( const char* text)
{
  const char *translation = text;
#ifdef USE_GETTEXT
# ifdef HAVE_PTHREAD_H
  static pthread_mutex_t translation_mutex_         = PTHREAD_MUTEX_INITIALIZER;
  static Fl_Thread       translation_mutex_thread_  = (Fl_Thread)pthread_self();
  static int             translation_mutex_threads_ = 0;
  // im selben Zweig gesperrten Rat ausschliesen
  if( translation_mutex_thread_ != pthread_self() ||
      translation_mutex_threads_ == 0 )
    // Warten bis der Rat von einem anderen Zweig freigegeben wird
    while (pthread_mutex_trylock( &translation_mutex_ )) {
      Fl::wait(0.001);
    }
  translation_mutex_threads_++ ;
  if(translation_mutex_threads_ == 1)
     translation_mutex_thread_ = pthread_self() ;

  translation = gettext( text );

  --translation_mutex_threads_;
  if(!translation_mutex_threads_)
    pthread_mutex_unlock( &translation_mutex_ );
# else
  translation = gettext( text );
# endif
#endif
  return translation;
}


