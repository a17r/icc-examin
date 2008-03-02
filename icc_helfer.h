/*
 * ICC Examin ist eine ICC Profil Betrachter
 * 
 * Copyright (C) 2004-2007  Kai-Uwe Behrmann 
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
 * ICC helpers
 * 
 */

// Date:      Mai 2004

#ifndef ICC_HELFER_H
#define ICC_HELFER_H

#include "icc_utils.h"
#include "icc_icc.h"

#include <string>
#include <vector>
#include <stddef.h> // size_t

// file macros / partitialy from config.h
#ifdef WIN32
#define ICC_DIR_SEPARATOR_C '\\'
#define ICC_DIR_SEPARATOR "\\"
#define PATH_SHELLSTRING ""
#else
#define ICC_DIR_SEPARATOR_C '/'
#define ICC_DIR_SEPARATOR "/" 
#define PATH_SHELLSTRING "export PATH=$PATH:" PREFIX "/bin:~/bin; "
#endif


#if HAVE_FLTK
#include <FL/Fl_Widget.H>
// in icc_helfer_fltk.cpp
void        dbgFltkEvents  ( int           event);
std::string dbgFltkEvent   ( int           event);
void        setzeIcon      ( Fl_Window    *fenster,
                             char        **xpm_daten );
void        fl_delayed_redraw ( void *Fl_Widget);
#endif

// internal funktions

const char* cp_nchar (char* text, int n);


// helper functions
// ICC helpers defined in icc_helfer.cpp
icUInt16Number          icValue   (icUInt16Number val);
icUInt32Number          icValue   (icUInt32Number val);
long long               icValue   (icUInt64Number val);
double                  icSFValue (icS15Fixed16Number val);
double                  icUFValue (icU16Fixed16Number val);
double                  icUI16Value         (icUInt16Number val);
icS15Fixed16Number      icValueSF (double val);
icU16Fixed16Number      icValueUF (double val);
icUInt16Number          icValueUI16(double val);
icInt16Number                     icValue   (icInt16Number val);
icInt32Number                     icValue   (icInt32Number val);
int                     icValue   (icInt64Number val);
icColorSpaceSignature   icValue   (icColorSpaceSignature val);
icPlatformSignature     icValue   (icPlatformSignature val);
icProfileClassSignature icValue   (icProfileClassSignature val);
icTagSignature          icValue   (icTagSignature val);
icTagTypeSignature      icValue   (icTagTypeSignature val);
icTechnologySignature   icValue   (icTechnologySignature val);
icStandardObserver      icValue   (icStandardObserver val);
icMeasurementGeometry   icValue   (icMeasurementGeometry);
icMeasurementFlare      icValue   (icMeasurementFlare);
icIlluminant            icValue   (icIlluminant);
void                    icValueXYZ(icXYZNumber*, double X, double Y, double Z);

const double*           XYZto_xyY (double* XYZ);
void                    XYZto_xyY (std::vector<double> & XYZxyY);
void                    xyYto_XYZ (std::vector<double> & xyYXYZ);

std::string         renderingIntentName ( int intent);
int                 getColorSpaceChannels(icColorSpaceSignature color);
icColorSpaceSignature getColorSpaceGeneric( int channels );
std::string         getColorSpaceName   ( icColorSpaceSignature color);
std::vector<std::string> getChannelNamesShort( icColorSpaceSignature color);
std::vector<std::string> getChannelNames( icColorSpaceSignature color);
std::string         getDeviceClassName  ( icProfileClassSignature cl);
std::string         getPlatformName     ( icPlatformSignature platform);
std::string         getSigTagName( icTagSignature  sig );
std::string         getSigTagDescription( icTagSignature  sig );
std::string         getSigTypeName( icTagTypeSignature  sig );
std::string         getSigTechnology( icTechnologySignature sig );
std::string         getChromaticityColorantType( int type );
std::string         getIlluminant( icIlluminant illu );
std::string         getStandardObserver( icStandardObserver obsv );
std::string         getMeasurementGeometry( icMeasurementGeometry measgeo );
std::string         getMeasurementFlare( icMeasurementFlare flare );
std::string         printDatum( icDateTimeNumber date );

namespace icc_examin_ns {
  // Fl_Thread's lock / release
  void lock(const char *file, int line);
  void unlock(void *widget, const char *file, int line);
  double zeitSekunden();
  time_t zeit();
  time_t zeitProSekunde();
  void wait (double sekunden, int update_ui);
  extern int  (*waitFunc)(void);
#if APPLE
  std::string holeBundleResource (const char* Dateiname_ohne_Endung,
                                  const char* Endung);
#endif
}

#define doLocked_m( a, widget ) \
  icc_examin_ns::lock(__FILE__,__LINE__); \
  a; \
  icc_examin_ns::unlock( widget, __FILE__,__LINE__); 


// displaying
std::string         zeig_bits_bin      (const void* speicher, int groesse);

// file I/O
char*     ladeDatei                  ( std::string dateiname,
                                       size_t     *size );
void      saveMemToFile              ( const char *filename,
                                       const char *block,
                                       size_t      size );
#include "icc_speicher.h"
Speicher  dateiNachSpeicher          ( const std::string & dateiname );
void      dateiNachSpeicher          ( Speicher & s,
                                       const std::string & dateiname );
void      speicherNachDatei          ( std::string & dateiname,
                                       Speicher & s );

double    holeDateiModifikationsZeit ( const char *fullFileName );
// file helpers
const char* dateiName(const char* name);
const char* dateiName(std::string name);
std::string tempFileName ();


// common
char* getExecPath               ( const char *filename );
void  setI18N                   ( const char *exename );

// text helper
namespace icc_parser {
  extern const char *alnum;
  extern const char *alpha;
  extern const char *numerisch;
  extern const char *ziffer;
  extern const char *leer_zeichen;

  int               suchenErsetzen    ( std::string            &text,
                                        std::string            &suchen,
                                        std::string            &ersetzen,
                                        std::string::size_type  pos );
  int               suchenErsetzen    ( std::string            &text,
                                        const char             *suchen,
                                        const char             *ersetzen,
                                        std::string::size_type  pos );
  std::vector<std::string> zeilenNachVector (std::string &text);
  std::string::size_type sucheWort    ( std::string            &text,
                                        std::string             wort,
                                        std::string::size_type  pos );

  struct ZifferWort {
    std::pair<bool,std::string> wort;
    std::pair<bool,double>      zahl;
    std::pair<bool,int>         ganz_zahl;
  };

  std::vector<ZifferWort>       unterscheideZiffernWorte ( std::string &zeile,
                                                 bool anfuehrungsstriche_setzen,
                                                 const char *trennzeichen );
}

// data structures
// partitial in icc_speicher.h
/** @brief list class template
 */
template <class T>
class ICClist {
  size_t     n_;          //!< the exposed number of elements
  size_t     reserve_;    //!< the allocated elements in list_
  T        * list_;       //!< the array of T
  void       init() {
    list_ = NULL;
    n_ = 0;
    reserve_ = 0;
    reserve_step = 10000/sizeof(T);
  }
public:
             ICClist () {
    init();
  }
             ICClist (int n) {
    init();
    reserve(n + reserve_step);
  }
  size_t reserve_step; //!< reserve of elements on some allocations
  ICClist&   copy    (const ICClist & l) {
    if(l.n_ > n_)
      list_ = (T*) calloc (sizeof(T), l.n_);
    if(l.n_)
      memcpy( list_, l.list_, l.n_ * sizeof(T*) );
    return *this;
  }
  void       clear   () {
    if(n_ && list_)
      free(list_);
    n_ = 0;
  }
  size_t     size() {
    return n_;
  }
  operator const size_t () const {
    return n_;
  }
  operator const size_t & () const {
    return n_;
  }
  ICClist& operator = (const ICClist& l) {
    return copy(l);
  }
  T &      operator [] (size_t i) {
    if(i < n_)
      return list_[i];
    else
      DBG_PROG_S("out of range");
    return list_[n_];
  }
  const T& operator [] (const size_t i) const {
    if(i < n_)
      return list_[i];
    else
      return 0.0;
  }
  void     push_back( T x ) {
    reserve( n_ + 1 + reserve_step );
    list_[n_] = x;
    ++n_;
  }
  T *      begin() {
    if(n_)
      return &list_[0];
    else
      return NULL;
  }
  T *      end() {
    if(n_)
      return &list_[n_ - 1];
    else
      return NULL;
  }
  void       reserve (size_t x) {
    if ( n_ == 0 ) {
      list_ = (T*) calloc (sizeof(T), x);
      reserve_ = x;
    } else if( n_ < x ) {
      T* tmp = (T*) calloc (sizeof(T), x);
      reserve_ = x;
      memcpy( tmp, list_, sizeof(T) * n_ );
      free(list_);
      list_ = tmp;
    }
}
  void     insert( T* start_, T* begin_, T* end_ ) {
    size_t news = (size_t)((intptr_t)(end_ - begin_)) + 1;
    size_t n = 0;
    if(&list_[n_] < start_)
      return;
    if(begin_ > end_ || !begin_)
      return;
    if(start_)
      n =(size_t)((intptr_t)(start_ - begin()));
    reserve( n + news + reserve_step );
    if(!start_)
      start_ = &list_[0];

    memcpy( start_, begin_, news );
    n_ = n + news;
  }
  void     resize( size_t n ) {
    if(n > reserve_)
      reserve (n + reserve_step);
    n_ = n;
  }
};



// Callback structure
/*typedef struct StructVoidInt
{
  void* data;
  int   wert;
};*/

#endif //ICC_HELFER_H
