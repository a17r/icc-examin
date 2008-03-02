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
 * Dateiwahl
 * 
 */

// Date:      Januar 2005

#ifndef ICC_FENSTER_H
#define ICC_FENSTER_H


#ifdef HAVE_FLTK
#ifdef HAVE_FLU
#include <FLU/Flu_File_Chooser.h> 
#endif
#include <FL/Fl_File_Chooser.H> 
#include <FL/Fl_Hold_Browser.H> 
#include <FL/Fl_File_Icon.H> 
#include <FL/Fl_Shared_Image.H> 
#include <FL/Fl_PNM_Image.H>
#include <FL/fl_ask.H>

#ifdef HAVE_FLU
  extern Flu_File_Chooser *dateiwahl;
  void dateiwahl_cb(const char *dateiname, int typ, void *arg);
#else
  extern Fl_File_Chooser  *dateiwahl;
  void dateiwahl_cb(Fl_File_Chooser *f,void *data);
#endif

Fl_Double_Window* nachricht(std::string text);

#endif

#endif //ICC_FENSTER_H
