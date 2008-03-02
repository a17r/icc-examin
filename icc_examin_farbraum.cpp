/*
 * ICC Examin ist eine ICC Profil Betrachter
 * 
 * Copyright (C) 2004-2005  Kai-Uwe Behrmann 
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
 * the central class. colour space parts
 * 
 */


#include "icc_examin.h"
#include "icc_betrachter.h"
#include "icc_gl.h"

using namespace icc_examin_ns;


//#define DEBUG_EXAMIN
#ifdef DEBUG_EXAMIN
#define DBG_EXAMIN_START DBG_PROG_START
#define DBG_EXAMIN_ENDE DBG_PROG_ENDE
#define DBG_EXAMIN_V( texte ) DBG_NUM_V( texte )
#define DBG_EXAMIN_S( texte ) DBG_NUM_S( texte )
#else
#define DBG_EXAMIN_START
#define DBG_EXAMIN_ENDE
#define DBG_EXAMIN_V( texte )
#define DBG_EXAMIN_S( texte )
#endif

#ifdef DEBUG_
#define MARK(x) DBG_S( #x ) x
#else
#define MARK(x) x
#endif


void
ICCexamin::messwertLese (int n,
                         std::vector<double> & p,
                         std::vector<float>  & f,
                         std::vector<std::string> & namen)
{
  DBG_PROG_START
  if(profile.size() > n &&
     profile.aktuell() == n &&
     profile[n]->hasMeasurement() )
    { DBG_NUM_S( "nutze Messdaten" )
      ICCmeasurement messung = profile[n]->getMeasurement();

      if(messung.valid() && profile[n]->size())
        icc_betrachter->DD_farbraum->zeig_punkte_als_paare = true;
      else
        icc_betrachter->DD_farbraum->zeig_punkte_als_paare = false;

        DBG_NUM_V( icc_betrachter->DD_farbraum->zeig_punkte_als_paare )
      icc_betrachter->DD_farbraum->zeig_punkte_als_messwerte = true;
        DBG_NUM_V( icc_betrachter->DD_farbraum->zeig_punkte_als_messwerte )

      if(profile.profil()->data_type == ICCprofile::ICCmeasurementDATA || 
         profile.profil()->hasTagName("ncl2") )
        icc_betrachter->DD_farbraum->zeig_punkte_als_messwerte = true;
      else
        icc_betrachter->DD_farbraum->zeig_punkte_als_messwerte = false;

        DBG_NUM_V( icc_betrachter->DD_farbraum->zeig_punkte_als_messwerte )

      unsigned int j;
      int n = messung.getPatchCount(); DBG_PROG_V( messung.getPatchCount() )

      if(messung.validHalf())
      {
        for (j = 0; j < (unsigned) n; ++j)
        { // first the measurments ...
          std::vector<double> daten;
          if(messung.hasXYZ() || messung.hasLab())
            daten = messung.getMessLab(j);
          else
            daten = messung.getCmmLab(j);
          for (unsigned i = 0; i < daten.size(); ++i)
            p.push_back(daten[i]);
          // ... then the calculated profile Lab values
          if (icc_betrachter->DD_farbraum->zeig_punkte_als_paare) {
            daten = messung.getCmmLab(j);
            for (unsigned i = 0; i < daten.size(); ++i)
              p.push_back(daten[i]);
          } 

          if(messung.hasXYZ() || messung.hasLab())
            daten = messung.getMessRGB(j);
          else
            daten = messung.getCmmRGB(j);
          for (unsigned i = 0; i < daten.size(); ++i) {
            f.push_back((float)daten[i]);
          }
          f.push_back(1.0);
          if (icc_betrachter->DD_farbraum->zeig_punkte_als_paare)
          { daten = messung.getCmmRGB(j);
            for (unsigned i = 0; i < daten.size(); ++i)
              f.push_back((float)daten[i]);
           f.push_back(1.0);
          } 
        }
      }
      namen = messung.getFeldNamen();
    }

  DBG_PROG_ENDE
}

void
ICCexamin::netzLese (int n,
                     std::vector<ICCnetz> *netz)
{
  DBG_PROG_START
  if( profile.size() == 0 && farbraumModus()) {
    netz->resize(1);
    return;
  }

  ICCnetz & netz_temp = (*netz)[n];

  
  {
    int intent = intentGet(NULL);
    if(farbraumModus())
      intent = profile[n]->intent();

    icc_oyranos. netzVonProfil( *(profile[n]), intent, bpc(), netz_temp );
    if(netz_temp.punkte.size())
    {
      /*netz_temp[0].undurchsicht = (*netz)[n].undurchsicht;
      netz_temp[0].grau = (*netz)[n].grau;
      netz_temp[0].aktiv = (*netz)[n].aktiv;
      if(n >= (int)netz->size())
        netz->resize( n+1 );*/
      netz_temp.name = profile[n]->filename();
      // extract the file name
      std::string & dateiname = netz_temp.name;
      if( dateiname.find_last_of(ICC_DIR_SEPARATOR) != std::string::npos)
        dateiname = dateiname.substr( dateiname.find_last_of(ICC_DIR_SEPARATOR)+1,
                                    dateiname.size() );
      DBG_NUM_V( netz_temp.undurchsicht <<" "<< netz_temp.umriss.size() )
    }
# if 0  // should be checked on load time
    else {
      (*netz)[n].punkte.clear();
      (*netz)[n].indexe.clear();
      (*netz)[n].umriss.clear();
      (*netz)[n].name.clear();
    }
#endif
  }
  /*for(int i = 0; i < (int)netz->size(); ++i)
    DBG_PROG_V( (*netz)[n].aktiv <<" "<< (*netz)[i].undurchsicht <<" "<< (*netz)[i].umriss.size() );*/
  DBG_PROG_ENDE
}

/** 
   @param[in]  n       < 0 - single patch; >= 0 all patches from profile n
   @param[out] p       lab positions
   @param[out] f       colour
   @param[out] names   according names
   @return             nothing
 */
void
ICCexamin::farbenLese (int n,
                       std::vector<double> & p,
                       std::vector<float>  & f,
                       std::vector<std::string> & names)
{
  DBG_PROG_START
  // show named colours

  ICCprofile * pr = NULL;
  int single = (n < 0);
  int patch = single ? -n - 1 : -1;
  int s;

  if( single )
    pr = profile.profil();
  else
    pr = profile[n];

  if( (n >= 0 && profile.size() > n) ||
      single )
  {
    DBG_PROG

    int item = pr->getTagIDByName("ncl2");
    std::vector<double> p_neu = pr->getTagNumbers (item, ICCtag::MATRIX);
    int channels_n = pr->getColourChannelsCount();
    unsigned int n_farben = p_neu.size()/(3+channels_n);


    names = pr->getTag(item).getText("ncl2_names");

    int mult = 1;
    int neu = 0;

    if( !single )
    {
      icc_betrachter->DD_farbraum->zeig_punkte_als_messwerte = true;
      icc_betrachter->DD_farbraum->zeig_punkte_als_paare = true;
      if(icc_betrachter->DD_farbraum->zeig_punkte_als_paare)
        mult = 2;
    } else {
      if( patch > (int)p_neu.size() )
        WARN_S( "inadequate patch requested" << patch<<">"<< p_neu.size() )
      n_farben = 1;
    }

    if(n_farben != p.size() / 3 / mult)
    {
      DBG_PROG_S( "resize " << n_farben <<" "<<
              p_neu.size() / 3 <<" "<< p.size() / 3 / mult )
      p.resize( n_farben * 3 * mult );
      f.resize( n_farben * channels_n * mult );
      neu = 1;
    }

    if( single )
    {
      p[0] = p_neu[patch*3+0];
      p[1] = p_neu[patch*3+1];
      p[2] = p_neu[patch*3+2];

      names[0] = names[patch];
      names.resize(1);

    } else {

      for(size_t i = 0; i < n_farben; ++i)
      {
        s = i*mult*3;
        if(mult == 2 && !neu)
        {
          // copy old colours
          p[s+3] = p[s+0];
          p[s+4] = p[s+1];
          p[s+5] = p[s+2];
        }
        p[s+0] = p_neu[i*3+0];
        p[s+1] = p_neu[i*3+1];
        p[s+2] = p_neu[i*3+2];
        if(mult == 2 && neu)
        {
          // double of new colours
          p[s+3] = p[s+0];
          p[s+4] = p[s+1];
          p[s+5] = p[s+2];
        }
      }
    }

    DBG_NUM_V( f.size() )
    // ncl2 colours -> monitor colours
    /*double *lab = new double [n_farben*mult*3],
           *rgb=0;
    if(single) {
      for(unsigned i = 0; i < n_farben * 3; ++i)
        lab[i] = p_neu[patch*3 + i];
    } else 
      for(unsigned i = 0; i < n_farben * 3; ++i)
        lab[i] = p_neu[i];

    rgb = icc_oyranos. wandelLabNachBildschirmFarben(lab, n_farben*mult,
                                 intentGet(NULL),
                                 gamutwarn()?cmsFLAGS_GAMUTCHECK:0);
    DBG_NUM_V( n_farben )
    if(!rgb)  WARN_S( _("RGB result not available") ) */
    for(unsigned i = 0; i < n_farben; ++i)
    {
      s = i*mult*channels_n;
      if(mult == 2 && !neu)
      {
        for(int j = 0; j < channels_n; ++j)
          f[s+channels_n + j] = f[s + j];
/*        f[s+4] = f[s+0];
        f[s+5] = f[s+1];
        f[s+6] = f[s+2];
        f[s+7] = 0.;*/
      }
      for(int j = 0; j < channels_n; ++j)
        f[s + j] = p_neu[3*n_farben + i*channels_n + j];
/*      f[s+0] = rgb[i*3+0];
      f[s+1] = rgb[i*3+1];
      f[s+2] = rgb[i*3+2];
      f[s+3] = 1.0;*/
      if(mult == 2 && neu)
      {
        for(int j = 0; j < channels_n; ++j)
          f[s + channels_n + j] = f[i + j];
/*        f[s+4] = f[s+0];
        f[s+5] = f[s+1];
        f[s+6] = f[s+2];
        f[s+7] = f[s+3];*/
      }
    }
    /*if(lab) delete [] lab;
    if(rgb) delete [] rgb;*/
  }

  DBG_PROG_ENDE
}

void
ICCexamin::farbraum (int n)
{
  DBG_PROG_START

  std::vector<std::string> texte, namen;

  texte.push_back(_("CIE *L"));
  texte.push_back(_("CIE *a"));
  texte.push_back(_("CIE *b"));

  std::vector<double> p;
  std::vector<float>  f;
  std::vector<std::string> names;
  icc_betrachter->DD_farbraum->herausNormalPunkte( p, f );

  DBG_PROG_V( n <<" "<< profile.size()<<" "<<profile.aktuell() )
  DBG_PROG_V( profile[n]->filename() )

  // measurements
  int messwerte=false;
  bool has_mess = profile[n]->hasMeasurement();
  MARK( frei(false); )
  if(profile.size() > n &&
     profile.aktuell() == n &&
     has_mess )
    {
      DBG_PROG
      messwertLese(n, p,f,namen);
      messwerte = true;
    }
  MARK( frei(true); )

  int ncl2_profil = profile[n]->hasTagName("ncl2");

  // open
  if(lade())
    farbraumModus( profile.aktuell() );

  // show named colours
  if( profile.size() > n && ncl2_profil )
  {
    DBG_PROG
    farbenLese(n, p,f,names);
  }

  bool neues_netz = false;
  if( n >= (int)icc_betrachter->DD_farbraum->dreiecks_netze.size() )
    neues_netz = true;

  if(n == 0)
    icc_betrachter->DD_farbraum->hineinPunkte( p, f, namen, texte );

  do {
    icc_examin_ns::sleep(0.05);
  } while(!icc_betrachter->DD_farbraum->frei());

  {
  MARK( icc_betrachter->DD_farbraum->frei(false); )

    if((int)icc_betrachter->DD_farbraum->dreiecks_netze .size() <= n)
      icc_betrachter->DD_farbraum->dreiecks_netze .resize( n + 1 );

    std::vector<ICCnetz> *netze = &icc_betrachter->DD_farbraum->dreiecks_netze;
    DBG_PROG_V( icc_betrachter->DD_farbraum->dreiecks_netze.size() <<" "<< n )


    if( profile.size() > n && !ncl2_profil )
    {
      icc_betrachter->DD_farbraum->frei(false);
      netzLese(n, netze);
      icc_betrachter->DD_farbraum->frei(true);
      icc_betrachter->DD_farbraum->hineinNetze(
          icc_betrachter->DD_farbraum->dreiecks_netze );
    }

    DBG_PROG_V( n <<" "<< netze->size() <<" "<< ncl2_profil )

    // set some standard values
    if(netze->size() && neues_netz)
    {
      if((n == 0 && ncl2_profil) &&
         !messwerte )
      {
        (*netze)[n].undurchsicht = 0.15;
        (*netze)[n].grau = false;
      }
      else
      if ( farbraumModus() && !messwerte )
      {
        if(n == 1)
          (*netze)[n].undurchsicht = 0.15;
        else
          (*netze)[n].undurchsicht = 0.10;
        (*netze)[n].grau = true;
      }
      else
      if ( profile.size() == 1 )
      {
        (*netze)[n].undurchsicht = 0.25;
        (*netze)[n].grau = false;
      }
      else
      {
        (*netze)[n].undurchsicht = 0.3;
        (*netze)[n].grau = true;
      }

      icc_betrachter->DD_farbraum->achsNamen( texte );

      // as the including is not that exactly a passive is more appropriate
      if(profile[n]->filename() == moniName())
        profile.passiv(n);
      DBG_PROG_V( n <<" "<< profile.aktiv(n) )
    }
    if(icc_betrachter->DD_farbraum->dreiecks_netze[n].name == "")
    {
      icc_betrachter->DD_farbraum->dreiecks_netze[n].name =
                                                         profile[n]->filename();
      // extract file name
      std::string & dateiname = icc_betrachter->DD_farbraum->dreiecks_netze[n].name;
      if( dateiname.find_last_of("/") != std::string::npos)
        dateiname = dateiname.substr( dateiname.find_last_of("/")+1,
                                    dateiname.size() );
      DBG_PROG_V( icc_betrachter->DD_farbraum->dreiecks_netze[n].name )
    }

  MARK( icc_betrachter->DD_farbraum->frei(true); )
  }

  DBG_PROG_ENDE
}

void
ICCexamin::farbraum ()
{
  DBG_PROG_START
  MARK( frei(false); )

  if((int)icc_betrachter->DD_farbraum->dreiecks_netze.size() > profile.size())
  {
    MARK( icc_betrachter->DD_farbraum->frei(false); )
    icc_betrachter->DD_farbraum->dreiecks_netze.resize(profile.size());
    MARK( icc_betrachter->DD_farbraum->frei(true); )
  }
  DBG_PROG_V( icc_betrachter->DD_farbraum->dreiecks_netze.size() )
  MARK( frei(true); )

  for(int i = 0; i < profile.size(); ++i)
  {
    while(!profile[i] || profile[i]->changing())
      icc_examin_ns::sleep(0.05);
    farbraum(i);
  }

  /*if(icc_betrachter->DD_farbraum -> dreiecks_netze.size())
    icc_betrachter->DD_farbraum ->
      dreiecks_netze [icc_betrachter->DD_farbraum->dreiecks_netze.size()-1]
        . undurchsicht = 0.7;*/

  DBG_PROG_V( profile.size() )

  DBG_PROG_ENDE
}

void
ICCexamin::farbraumModus (int profil)
{
  DBG_PROG_START
  MARK( frei(false); )

  farbraum_modus_ = false;
  if(profile.size() && profile.profil()->hasTagName("ncl2")) {
    farbraum_modus_ = true;
    intent( -1 );
    DBG_PROG_S( "set colour space mode" )
  } else if(!profile.size()) {
    WARN_S( "too early with " << profile.size() << " profiles" )
  }

  DBG_PROG_V( farbraum_modus_ )

  MARK( frei(true); )
  DBG_PROG_ENDE
}


