/*
 * ICC Examin ist eine ICC Profil Betrachter
 * 
 * Copyright (C) 2005  Kai-Uwe Behrmann 
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
 * Die Kette von Profilen Klasse.
 * 
 */

#include "icc_kette.h"
#include "icc_examin.h"
#include "callback_simple.h"

bool
ICCkette::oeffnen (std::vector<std::string> dateinamen)
{ DBG_PROG_START
  bool erfolgreich = false;

  // Laden TODO: test auf Existenz der Datei (oyranos?)
  _profile.resize(dateinamen.size());
  for (unsigned int i = 0; i < dateinamen.size(); i++)
    _profile[i].load (dateinamen[i]);

  _profilnamen = dateinamen;
  _aktiv.resize(_profile.size());
  for(unsigned int i = 0; i < _aktiv.size(); i++)
    _aktiv[i] = true;

  if( _profile.size() )
    _aktuelles_profil = 0;

  if (dateinamen.size()) { DBG_PROG
    for (unsigned int i = 0; i < _profile.size(); i++) {
      //create_vrml ( dateiname.c_str(), "/usr/share/color/icc/sRGB.icm", &vrmlDatei[0]);

      icc_examin->fortschritt (0.8);

      std::vector<std::string> url;
      std::vector<std::string> param;
      //url.push_back (&vrmlDatei[0]);
      //browser->load_url(url, param);
        icc_examin->statlabel = dateinamen[i].c_str();
        icc_examin->statlabel.append (" ");
        icc_examin->statlabel.append (_("geladen"));
        status(icc_examin->statlabel.c_str());
    }
    icc_examin->fortschritt (1.0);
    icc_examin->fortschritt (1.1);
    DBG_PROG

    //Button a( make_callback((Callback1<Button*>*)0, icc_examin->icc_betrachter->tag_browser, &TagBrowser::reopen) );
    //icc_examin->icc_betrachter->tag_browser->reopen ();

    //icc_examin->icc_betrachter->measurement( _profile[_aktuelles_profil].hasMeasurement() );
    erfolgreich = true;
  } else {
    status(_("Datei nicht geladen!"));
  } DBG_PROG

  return erfolgreich;
  DBG_PROG_ENDE
}




