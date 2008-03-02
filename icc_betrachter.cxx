// generated by Fast Light User Interface Designer (fluid) version 1.0104

#include "icc_betrachter.h"
static char *statlabel;
 std::vector<std::string> filenamen_alt;
 bool setTitleUrl = true;

 int px,py,pw,ph;
 int fullscreen;
  int inspekt_topline;
 int tag_nummer;
#include "icc_draw.h"
#include "icc_oyranos.h"
#include "fl_oyranos.h"
#include "agviewer.h"
#include "icc_gl.h"
#ifdef HAVE_FLU
static Flu_File_Chooser *dateiwahl;

static void dateiwahl_cb(const char *dateiname, int typ, void *arg) {
  DBG_PROG_START

  // kein Profile Dialog
  if (strstr( dateiwahl->pattern(), "*.ic*") == 0) { DBG_PROG
    DBG_PROG_ENDE
    return;
  }

    if (dateiname) {
      filenamen_alt.resize(1);
      filenamen_alt[0] = dateiname;

      DBG_NUM_V( filenamen_alt[0] )
      filenamen_alt[0] = dateiwahl->get_current_directory();
      filenamen_alt[0].append( dateiname );
      DBG_NUM_V( filenamen_alt[0] )

      open(false);
    }

  DBG_PROG_ENDE
}
#else
static Fl_File_Chooser *dateiwahl;

static void dateiwahl_cb(Fl_File_Chooser *f,void *data) {
  DBG_PROG_START


  const char *filename;

    Fl_File_Chooser* fl = (Fl_File_Chooser*)f;

    DBG_NUM_V( data )
    filename = fl->value();
  
    // kein Profile Dialog
    if (strstr(fl->filter(),
    #ifdef  HAVE_FLU
                        "*.ic*"
    #else
                        "*.{I,i}{C,c}"
    #endif
                                    ) == 0) {
      if (filename)
        DBG_PROG_V( filename )
      DBG_PROG_ENDE
      return;
    }

    if (filename && fl->count() && dateiwahl->preview()) {
      filenamen_alt.resize(fl->count());
      for (int i = 0; i < fl->count(); i++) {
        filenamen_alt[i] = fl->value(i);
      }
      DBG_NUM_V( filenamen_alt.size() << filename )
      open(false);
    }

  DBG_PROG_ENDE
}
#endif

Fl_Double_Window *ueber=(Fl_Double_Window *)0;

Fl_Help_View *ueber_html=(Fl_Help_View *)0;

Fl_Button *ja=(Fl_Button *)0;

static void cb_ja(Fl_Button*, void*) {
  ueber->hide();
}

Fl_Double_Window *details=(Fl_Double_Window *)0;

static void cb_ffnen(Fl_Menu_*, void*) {
  open(true);
}

static void cb_menueintrag_html_speichern(Fl_Menu_*, void*) {
  DBG_PROG_START
  std::string filename = filenamen_alt[0];  DBG_PROG_V( filename )

  std::string::size_type pos=0;
  if ((pos = filename.find_last_of(".", filename.size())) != std::string::npos) { DBG_PROG
    filename.replace (pos, 5, ".html"); DBG_NUM_S( ".html gesetzt" )
  } DBG_PROG_V( filename )
  DBG_PROG_V( dateiwahl->filter() )

  std::string muster = dateiwahl->filter(); DBG_PROG
  std::string datei;
  if (dateiwahl->value())
    datei = dateiwahl->value(); DBG_PROG
  std::string titel = dateiwahl->label(); DBG_PROG

  dateiwahl->filter(_("HTML Dokumente (*.htm*)")); DBG_PROG
  #ifdef HAVE_FLU
  dateiwahl->cd(".");
  #endif
  dateiwahl->label(_("Bericht Speichern")); DBG_PROG
  dateiwahl->value(filename.c_str()); DBG_PROG

  dateiwahl->show(); DBG_PROG
  while( dateiwahl->shown() )
    Fl::wait( 0.01 );

  DBG_PROG_V( dateiwahl->filter() )
  if (dateiwahl->value())
    filename = dateiwahl->value();
  else
    filename = "";
  DBG_PROG

  dateiwahl->filter(muster.c_str()); DBG_PROG
  dateiwahl->value(datei.c_str()); DBG_PROG
  dateiwahl->label(titel.c_str()); DBG_PROG
  DBG_PROG_V( dateiwahl->filter() )

  DBG_PROG_V( filename )

  if (dateiwahl->count() == 0 || filename != "" || filename == filenamen_alt[0]) {
    load_progress->hide ();
    return;
  }

  std::string bericht = profile[0].report();

  std::ofstream f ( filename.c_str(),  std::ios::out );
  f.write ( bericht.c_str(), bericht.size() );
  f.close();

  DBG_PROG_ENDE;
}

static void cb_Beenden(Fl_Menu_*, void*) {
  quit();
}

static void cb_Voreinstellungen(Fl_Menu_*, void*) {
  voreinstellungen();
}

static void cb_menueintrag_Voll(Fl_Menu_*, void*) {
  Fl_Window *w = (Fl_Window *)details;

  if (!fullscreen) {
    px = w->x();
    py = w->y();
    pw = w->w();
    ph = w->h();

    w->fullscreen();
    fullscreen = true;
  } else {
    w->fullscreen_off(px,py,pw,ph);
    fullscreen = false;
  };
}

static void cb_menueintrag_inspekt(Fl_Menu_* o, void*) {
  Fl_Menu_* mw = (Fl_Menu_*)o;
  const Fl_Menu_Item* m = mw->mvalue();

  DBG_PROG_S (m->value())
  if (m->value()) {
    mft_gl->stop();
    inspekt->show();
    examin->hide();
    inspekt_html->value(profile[0].report().c_str());
    inspekt_html->topline(inspekt_topline);
  } else {
    inspekt->hide();
    examin->show();
    inspekt_topline = inspekt_html->topline();
  };
}

static void cb_menueintrag_3D(Fl_Menu_* o, void*) {
  Fl_Menu_* mw = (Fl_Menu_*)o;
  const Fl_Menu_Item* m = mw->mvalue();

  DBG_PROG_S (m->value())
  if (m->value()) {
    group_histogram->show();
    DD_histogram->show();
    inspekt->hide();
    examin->hide();
  } else {
    group_histogram->hide();
    inspekt->hide();
    examin->show();
    inspekt_topline = inspekt_html->topline();
  };
}

static void cb_ber(Fl_Menu_*, void*) {
  ueber->show();
ueber_html->value(getUeberHtml().c_str());
}

Fl_Menu_Item menu_[] = {
 {"Daten", 0,  0, 0, 64, 0, 0, 14, 56},
 {"\326""ffnen", 0x4006f,  (Fl_Callback*)cb_ffnen, 0, 0, 0, 0, 14, 56},
 {"Bericht Speichern", 0,  (Fl_Callback*)cb_menueintrag_html_speichern, 0, 129, 0, 0, 14, 56},
 {"Beenden", 0x40071,  (Fl_Callback*)cb_Beenden, 0, 0, 0, 0, 14, 56},
 {0},
 {"Bearbeiten", 0,  0, 0, 64, 0, 0, 14, 56},
 {"Voreinstellungen", 0,  (Fl_Callback*)cb_Voreinstellungen, 0, 0, 0, 0, 14, 56},
 {0},
 {"Ansicht", 0,  0, 0, 192, 0, 0, 14, 56},
 {"Ganzer Bildschirm an/aus", 0x40076,  (Fl_Callback*)cb_menueintrag_Voll, 0, 0, 0, 0, 14, 56},
 {"Pr\374""fansicht", 0x40062,  (Fl_Callback*)cb_menueintrag_inspekt, 0, 3, 0, 0, 14, 56},
 {"3D Ansicht", 0x40062,  (Fl_Callback*)cb_menueintrag_3D, 0, 130, 0, 0, 14, 56},
 {0},
 {"Hilfe", 0,  0, 0, 64, 0, 0, 14, 56},
 {"\334""ber", 0,  (Fl_Callback*)cb_ber, 0, 0, 0, 0, 14, 56},
 {0},
 {0}
};

Fl_Group *inspekt=(Fl_Group *)0;

Fl_Help_View *inspekt_html=(Fl_Help_View *)0;

Fl_Tile *examin=(Fl_Tile *)0;

TagBrowser *tag_browser=(TagBrowser *)0;

static void cb_tag_browser(TagBrowser* o, void*) {
  o->select_item( o->value() );
}

Fl_Group *ansichtsgruppe=(Fl_Group *)0;

Fl_Group *tabellengruppe=(Fl_Group *)0;

MftChoice *mft_choice=(MftChoice *)0;

static void cb_mft_choice(MftChoice* o, void*) {
  o->auswahl_cb();
}

TagDrawings *mft_viewer=(TagDrawings *)0;

TagTexts *mft_text=(TagTexts *)0;

GL_Ansicht *mft_gl=(GL_Ansicht *)0;

Fl_Group *tag_3D=(Fl_Group *)0;

TagDrawings *tag_viewer=(TagDrawings *)0;

TagTexts *tag_text=(TagTexts *)0;

Fl_Group *group_histogram=(Fl_Group *)0;

Fl_Box *DD_histogram=(Fl_Box *)0;

Fl_Box *box_stat=(Fl_Box *)0;

Fl_Progress *load_progress=(Fl_Progress *)0;

Fl_Double_Window* icc_betrachter(int argc, char** argv) {
  Fl_Double_Window* w;
  DBG_PROG_START
  statlabel = (char*)calloc (sizeof (char), 1024);
  fullscreen = false;
  inspekt_topline = 0;

  #ifdef HAVE_FLU
    Flu_File_Chooser::favoritesTxt = _("Lesezeichen");
    Flu_File_Chooser::myComputerTxt = _("Heimverzeichnis");
    Flu_File_Chooser::myDocumentsTxt = _("Dokumente");
    Flu_File_Chooser::desktopTxt = _("Desktop");

    Flu_File_Chooser::filenameTxt = _("Dateiname");
    Flu_File_Chooser::okTxt = _("Ja");
    Flu_File_Chooser::cancelTxt = _("Abbrechen");
    Flu_File_Chooser::locationTxt = _("Ordner");
    Flu_File_Chooser::showHiddenTxt = _("zeige versteckte Dateien");
    Flu_File_Chooser::fileTypesTxt = _("Datei Typen");
    Flu_File_Chooser::directoryTxt = _("Verzeichnis");
    Flu_File_Chooser::allFilesTxt = _("Alle Dateien (*)");
    Flu_File_Chooser::defaultFolderNameTxt = _("Neues Verzeichnis");

    Flu_File_Chooser::backTTxt = _("vorheriges Verzeichnis");
    Flu_File_Chooser::forwardTTxt = _("n�chstes Verzeichnis");
    Flu_File_Chooser::upTTxt = _("n�chsth�heres Verzeichnis");
    Flu_File_Chooser::reloadTTxt = _("Auffrischen");
    Flu_File_Chooser::trashTTxt = _("L�schen");
    Flu_File_Chooser::newDirTTxt = _("Verzeichnis erstellen");
    Flu_File_Chooser::addFavoriteTTxt = _("zu Lesezeichen");
    Flu_File_Chooser::previewTTxt = _("Vorschau");
    Flu_File_Chooser::listTTxt = _("Standard Anzeige");
    Flu_File_Chooser::wideListTTxt = _("weite Anzeige");
    Flu_File_Chooser::detailTTxt = _("detailierte Informationen");

    Flu_File_Chooser::detailTxt[0] = _("Name");
    Flu_File_Chooser::detailTxt[3] = _("Typ");
    Flu_File_Chooser::detailTxt[1] = _("Gr�sse");
    Flu_File_Chooser::detailTxt[2] = _("Datum");
    Flu_File_Chooser::contextMenuTxt[0] = _("contextMenuTxt 0");
    Flu_File_Chooser::contextMenuTxt[1] = _("Umbenennen");
    Flu_File_Chooser::contextMenuTxt[2] = _("L�schen");
    Flu_File_Chooser::diskTypesTxt[0] = _("Typ1");
    Flu_File_Chooser::diskTypesTxt[1] = _("Typ2");
    Flu_File_Chooser::diskTypesTxt[2] = _("Typ3");
    Flu_File_Chooser::diskTypesTxt[3] = _("Typ4");
    Flu_File_Chooser::diskTypesTxt[4] = _("Typ5");
    Flu_File_Chooser::diskTypesTxt[5] = _("Typ6");

    Flu_File_Chooser::createFolderErrTxt = _("Ordner konnte nicht erstellt werden");
    Flu_File_Chooser::deleteFileErrTxt = _("konnte Datei nicht l�schen");
    Flu_File_Chooser::fileExistsErrTxt = _("Datei existiert");
    Flu_File_Chooser::renameErrTxt = _("kontte nicht umbenennen");

/*    Flu_File_Chooser:: = _("");
    Flu_File_Chooser:: = _("");
    Flu_File_Chooser:: = _("");
    Flu_File_Chooser:: = _("");
    Flu_File_Chooser:: = _("");*/

    const char* ptr = NULL;
    if (filenamen_alt.size())
      ptr = filenamen_alt[0].c_str();
    dateiwahl = new Flu_File_Chooser(ptr, _("ICC Farbprofile (*.ic*)"), Flu_File_Chooser::SINGLE, _("Welches ICC Profil?"));
    dateiwahl->add_context_handler(Flu_File_Chooser::ENTRY_FILE, "icc", _("Profil �ffnen"), dateiwahl_cb, NULL);
    dateiwahl->add_context_handler(Flu_File_Chooser::ENTRY_FILE, "icm", _("Profil �ffnen"), dateiwahl_cb, NULL);
  #else
    const char* ptr = NULL;
    if (filenamen_alt.size())
      ptr = filenamen_alt[0].c_str();
    dateiwahl = new Fl_File_Chooser(ptr, _("ICC Farbprofile (*.{I,i}{C,c}{M,m,C,c})"), Fl_File_Chooser::SINGLE, _("Welches ICC Profil?"));
    dateiwahl->callback(dateiwahl_cb);
    dateiwahl->preview_label = _("Vorschau");
  #endif
  { Fl_Double_Window* o = ueber = new Fl_Double_Window(366, 241, "\334""ber ICC examin");
    w = o;
    { Fl_Group* o = new Fl_Group(0, 0, 365, 240);
      { Fl_Help_View* o = ueber_html = new Fl_Help_View(0, 0, 365, 205);
        Fl_Group::current()->resizable(o);
      }
      { Fl_Button* o = ja = new Fl_Button(130, 210, 110, 25, "Gut");
        o->callback((Fl_Callback*)cb_ja);
      }
      o->end();
    }
    o->hide();
    o->set_non_modal();
    o->end();
    o->resizable(o);
  }
  { Fl_Double_Window* o = details = new Fl_Double_Window(385, 520, "ICC Details");
    w = o;
    o->box(FL_NO_BOX);
    o->color((Fl_Color)53);
    { Fl_Group* o = new Fl_Group(0, 0, 385, 520);
      { Fl_Menu_Bar* o = new Fl_Menu_Bar(0, 0, 385, 25);
        o->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
        o->when(3);
        o->menu(menu_);
      }
      { Fl_Group* o = inspekt = new Fl_Group(0, 25, 385, 470);
        { Fl_Help_View* o = inspekt_html = new Fl_Help_View(0, 25, 385, 470, "Inspect");
          o->align(FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
        }
        o->hide();
        o->end();
      }
      { Fl_Tile* o = examin = new Fl_Tile(0, 25, 385, 470);
        { TagBrowser* o = tag_browser = new TagBrowser(0, 25, 385, 135, "Bitte w\344hlen Sie ein Profilmerkmal aus");
          o->box(FL_NO_BOX);
          o->color(FL_BACKGROUND_COLOR);
          o->selection_color(FL_SELECTION_COLOR);
          o->labeltype(FL_NORMAL_LABEL);
          o->labelfont(0);
          o->labelsize(14);
          o->labelcolor(FL_BLACK);
          o->textcolor(32);
          o->callback((Fl_Callback*)cb_tag_browser);
          o->align(FL_ALIGN_TOP|FL_ALIGN_INSIDE);
          o->when(FL_WHEN_RELEASE_ALWAYS);
          int lines = tag_browser->size();
          DBG_PROG_V( lines )
        }
        { Fl_Group* o = ansichtsgruppe = new Fl_Group(0, 160, 385, 335);
          { Fl_Group* o = tabellengruppe = new Fl_Group(0, 160, 385, 335);
            { MftChoice* o = mft_choice = new MftChoice(0, 160, 385, 25, "W\344hlen Sie ein Kettenmerkmal");
              o->box(FL_NO_BOX);
              o->down_box(FL_BORDER_BOX);
              o->color(FL_BACKGROUND_COLOR);
              o->selection_color(FL_SELECTION_COLOR);
              o->labeltype(FL_NORMAL_LABEL);
              o->labelfont(0);
              o->labelsize(14);
              o->labelcolor(FL_BLACK);
              o->callback((Fl_Callback*)cb_mft_choice);
              o->align(FL_ALIGN_LEFT);
              o->when(FL_WHEN_RELEASE);
              o->show();
            }
            { TagDrawings* o = mft_viewer = new TagDrawings(0, 185, 385, 310);
              o->box(FL_NO_BOX);
              o->color(FL_BACKGROUND_COLOR);
              o->selection_color(FL_BACKGROUND_COLOR);
              o->labeltype(FL_NORMAL_LABEL);
              o->labelfont(0);
              o->labelsize(14);
              o->labelcolor(FL_BLACK);
              o->align(FL_ALIGN_CENTER);
              o->when(FL_WHEN_RELEASE);
              o->show();
            }
            { TagTexts* o = mft_text = new TagTexts(0, 185, 385, 310, "Der Text");
              o->box(FL_NO_BOX);
              o->color((Fl_Color)48);
              o->selection_color(FL_SELECTION_COLOR);
              o->labeltype(FL_NORMAL_LABEL);
              o->labelfont(0);
              o->labelsize(14);
              o->labelcolor(FL_BLACK);
              o->textcolor(32);
              o->align(FL_ALIGN_BOTTOM|FL_ALIGN_INSIDE);
              o->when(FL_WHEN_RELEASE_ALWAYS);
              o->show();
            }
            { GL_Ansicht* o = mft_gl = new GL_Ansicht(0, 185, 385, 310);
              o->box(FL_NO_BOX);
              o->color(FL_BACKGROUND_COLOR);
              o->selection_color(FL_BACKGROUND_COLOR);
              o->labeltype(FL_NORMAL_LABEL);
              o->labelfont(0);
              o->labelsize(14);
              o->labelcolor(FL_BLACK);
              o->align(FL_ALIGN_BOTTOM|FL_ALIGN_INSIDE);
              o->when(FL_WHEN_RELEASE);
              o->first = true;
              o->hide();
            }
            o->show();
            o->end();
          }
          { Fl_Group* o = tag_3D = new Fl_Group(0, 160, 385, 335);
            o->hide();
            o->end();
          }
          { TagDrawings* o = tag_viewer = new TagDrawings(0, 160, 385, 335);
            o->box(FL_NO_BOX);
            o->color(FL_BACKGROUND_COLOR);
            o->selection_color(FL_BACKGROUND_COLOR);
            o->labeltype(FL_NORMAL_LABEL);
            o->labelfont(0);
            o->labelsize(14);
            o->labelcolor(FL_BLACK);
            o->align(FL_ALIGN_CENTER);
            o->when(FL_WHEN_RELEASE);
            o->hide();
          }
          { TagTexts* o = tag_text = new TagTexts(0, 160, 385, 335, "Der Text");
            o->box(FL_NO_BOX);
            o->color(FL_BACKGROUND_COLOR);
            o->selection_color(FL_SELECTION_COLOR);
            o->labeltype(FL_NORMAL_LABEL);
            o->labelfont(0);
            o->labelsize(14);
            o->labelcolor(FL_BLACK);
            o->textcolor(32);
            o->align(FL_ALIGN_BOTTOM|FL_ALIGN_INSIDE);
            o->when(FL_WHEN_RELEASE_ALWAYS);
            o->show();
          }
          o->end();
        }
        o->end();
        Fl_Group::current()->resizable(o);
      }
      { Fl_Group* o = group_histogram = new Fl_Group(0, 25, 385, 470);
        DD_histogram = new Fl_Box(0, 25, 385, 470);
        o->hide();
        o->end();
      }
      { Fl_Group* o = new Fl_Group(0, 495, 385, 25);
        { Fl_Box* o = box_stat = new Fl_Box(0, 495, 385, 25, "No wrl file loaded.");
          o->box(FL_THIN_DOWN_BOX);
          o->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
        }
        { Fl_Progress* o = load_progress = new Fl_Progress(0, 495, 385, 25, "Laden ..");
          o->hide();
          o->maximum(1.0);
          o->minimum(0.0);
        }
        o->end();
      }
      o->end();
    }
    DBG_PROG

    if (argc>1) {

      if (argc>1) {

        sprintf (statlabel, "%s geladen", argv[1]);
        box_stat->label(statlabel);
        filenamen_alt.resize(argc-1);
        for (int i = 1; i < argc; i++) {
          DBG_PROG_V( i ) filenamen_alt[i-1] = argv[i];
        }
      } else {
        status(_("Konnte Datei nicht laden!"));
      }
    }
    o->end();
  }
  w->resizable(tag_text);
  w->show();
  Fl::scheme(NULL);
  Fl_File_Icon::load_system_icons();

  if (argc > 1)
    open (false);
  DBG_PROG_ENDE
  Fl::run();
  return w;
}

void open(int interaktiv) {
  DBG_PROG_START
  #include "icc_vrml.h"

  std::vector<std::string> filenamen;
  filenamen = filenamen_alt;
  //Fl_File_Icon	*icon;	// New file icon
  DBG_PROG
  load_progress->show ();    load_progress->value (0.0);

  if (interaktiv) {
    const char* ptr = NULL;
    if (filenamen_alt.size()) {
      ptr = filenamen_alt[0].c_str();
      dateiwahl->value(ptr);
      //DBG_PROG_S( filenamen_alt[0])
    }
    dateiwahl->show(); //filename=fl_file_chooser("W�hle ICC Profil?", "ICC Farbprofile (*.{I,i}{C,c}{M,m,C,c})", filenamen_alt[0].c_str());

    


    while (dateiwahl->visible())
      Fl::wait();

    DBG_NUM_V( dateiwahl->count() )
    if (dateiwahl->count() && dateiwahl->value()) {
      DBG_NUM_V( dateiwahl->value() )
      filenamen.resize(dateiwahl->count());
      for (int i = 1; i <= dateiwahl->count(); i++)
        filenamen[i-1] = dateiwahl->value(i);
    }
  }

  if (filenamen.size() == 0) {
    load_progress->hide ();
    return;
  }

  // Laden
  profile.resize(filenamen.size());
  for (unsigned int i = 0; i < filenamen.size(); i++)
    profile[i].load (filenamen[i]);
  // Register the ICC type ...
  //Fl_Shared_Image::add_handler(icc_check);
  //Fl_Shared_Image::add_handler(ps_check);

  std::vector<std::string> url;
  std::vector<std::string> param;

  if (/*browser && */(filenamen.size())) { DBG_PROG
    for (unsigned int i = 0; i < profile.size(); i++) {
      //create_vrml ( filename.c_str(), "/usr/share/color/icc/sRGB.icm", &vrmlDatei[0]);

      load_progress->value (0.8);
      filenamen_alt = filenamen;
      //url.push_back (&vrmlDatei[0]);
      //browser->load_url(url, param);
      sprintf (statlabel, "%s geladen", filenamen[i].c_str());
      cout << statlabel << endl; DBG_PROG
      box_stat->label(statlabel);
    }
  } else {
    status(_("Datei nicht geladen!"));
  } DBG_PROG

  box_stat->hide();
  box_stat->show();
  load_progress->value (1.0);
  load_progress->value (0.0);
  load_progress->hide();
  DBG_PROG

  tag_browser->reopen ();

  if (profile[0].hasMeasurement()) {
    inspekt_topline = inspekt_html->topline();
    DBG_PROG_S(menueintrag_inspekt->value())
    if (menueintrag_inspekt->value()) {
      inspekt_html->value(profile[0].report().c_str());
      cout << inspekt_html->size() << " " << inspekt_topline; DBG_PROG
      if (inspekt_html->size() -75 < inspekt_topline)
        inspekt_html->topline (inspekt_html->size() - 75);
      else
        inspekt_html->topline (inspekt_topline);
      inspekt->show();
      examin->hide();
    }
    menueintrag_inspekt->activate();
    menueintrag_html_speichern->activate();
  } else {
    menueintrag_inspekt->deactivate();
    menueintrag_html_speichern->deactivate();
    inspekt->hide();
    examin->show();
    //menueintrag_inspekt->value( false );
  }

  return;
  DBG_PROG_ENDE
}

void quit(void) {
  DBG_PROG_START
  /*Fl::remove_timeout((void (*)(void *))timeIT, (void *)viewer);
  delete viewer;
  delete browser;
  delete canvas;*/
  details->hide();
  exit(0);
  DBG_PROG_ENDE
}

char* icc_read_info(char* filename) {
  DBG_PROG_START
  char systemBefehl[1024];
  char *textfile = "/tmp/icc_temp.txt";


  sprintf (systemBefehl, "iccdump \"%s\" > %s",
                                    filename, textfile);
  system (systemBefehl);

  return textfile;
  DBG_PROG_ENDE
}

TagBrowser::TagBrowser(int X,int Y,int W,int H,char* start_info) : Fl_Hold_Browser(X,Y,W,H,start_info), X(X), Y(Y), W(W), H(H) {
}

void TagBrowser::reopen() {
  DBG_PROG_START
  //open and preparing the first selected item
  std::stringstream s;
  std::string text;
  std::vector<std::string> tag_list = profile[0].printTags();

  #define add_s(stream) s << stream; add (s.str().c_str()); s.str("");
  #define add_          s << " ";

  clear();
  add_s ("@fDateiname:")
  add_s ("@b    " << profile[0].filename() )
  add_s ("")
  if (tag_list.size() == 0) {
    add_s ("keine Inhalte gefunden f�r \"" << profile[0].filename() << "\"")
    return;
  }
  add_s ("@B26@tNr. Bezeichner  Typ         Gr��e Beschreibung")
  add_s ("@t" << profile[0].printHeader() )
  DBG_PROG
  std::vector<std::string>::iterator it;
  for (it = tag_list.begin() ; it != tag_list.end(); ++it) {
    s << "@t";
    // Nummer
    int Nr = atoi((*it).c_str()) + 1;
    std::stringstream t; t << Nr;
    for (int i = t.str().size(); i < 3; i++) {s << " ";} s << Nr; *it++; s << " "; 
    // Name/Bezeichnung
    s << *it; for (int i = (*it++).size(); i < 12; i++) {s << " ";}
    // Typ
    s << *it; for (int i = (*it++).size(); i < 12; i++) {s << " ";}
    // Gr��e
    for (int i = (*it).size(); i < 5; i++) {s << " ";} s << *it++; s << " ";
    // Beschreibung
    add_s (*it)
  }
  DBG_PROG
  if (value())
    select_item (value()); // Anzeigen
  else
    select_item (1);

  if (profile[0].hasTagName (selectedTagName)) {
    int item = profile[0].getTagByName (selectedTagName) + 6;
    select_item (item);
    value(item);
  }

  std::string::size_type pos=0 , max = 0;
  std::string data = profile[0].filename(); DBG_NUM_S( data )
  while ((pos = data.find ("/", pos)) != std::string::npos) {
    if (pos > max) max = pos; pos++; max++;
  }
  data.erase (0, max); DBG_NUM_S( max << data )

  s.clear(); s << "ICC Details: " << data;
  details->label( (const char*) s.str().c_str() );
  DBG_PROG_ENDE
}

void TagBrowser::select_item(int item) {
  DBG_PROG_START
  //Auswahl aus tag_browser

  status("")

  std::string text = _("Leer");
  //tag_text->hinein(text);
  item -= 6;
  cout << item << ". Tag "; DBG_PROG
  std::vector<std::string> rgb_tags;
  rgb_tags.push_back("rXYZ");
  rgb_tags.push_back("gXYZ");
  rgb_tags.push_back("bXYZ");

  if (item < 0) {
    select(5);
    text = profile[0].printLongHeader(); DBG_PROG
    tag_text->hinein(text);    
  } else if (item >= 0) {
    std::vector<std::string> TagInfo = profile[0].printTagInfo(item);
    DBG_PROG_S( TagInfo.size() << " " << TagInfo[0] << " " << TagInfo[1] )

    if        ( TagInfo[1] == "text"
             || TagInfo[1] == "cprt?"
             || TagInfo[1] == "meas"
             || TagInfo[1] == "sig"
             || TagInfo[1] == "dtim") {
      tag_text->hinein ( (profile[0].getTagText (item))[0] ); DBG_PROG
    } else if ( TagInfo[1] == "desc" ) {
      tag_text->hinein( (profile[0].getTagDescription (item))[0] ); DBG_PROG
    } else if ( TagInfo[0] == "rXYZ" || TagInfo[0] == "gXYZ" || TagInfo[0] == "bXYZ" ) {
      std::vector<double> alle_punkte, punkte;
      std::vector<std::string> alle_texte;
      std::string TagName;
      for (unsigned int i_name = 0; i_name < rgb_tags.size(); i_name++) {
        if (profile[0].hasTagName (rgb_tags[i_name])) {
          punkte = profile[0].getTagCIEXYZ (profile[0].getTagByName(rgb_tags[i_name]));
          for (unsigned int i = 0; i < 3; i++)
            alle_punkte.push_back (punkte[i]);
          TagInfo = profile[0].printTagInfo (profile[0].getTagByName(rgb_tags[i_name]));
          for (unsigned int i = 0; i < 2; i++)
            alle_texte.push_back (TagInfo[i]);
        }
      }
      tag_viewer->hinein_punkt( alle_punkte, alle_texte );
    } else if ( TagInfo[1] == "curv"
             || TagInfo[1] == "bfd" ) {
      std::vector<std::vector<double> > kurven;
      std::vector<double> kurve;
      std::vector<std::string> texte;
      std::string TagName;
      for (int i_name = 0; i_name < profile[0].tagCount(); i_name++) {
        if ( (profile[0].printTagInfo(i_name))[1] == "curv"
          || (profile[0].printTagInfo(i_name))[1] == "bfd" ) {
          kurve = profile[0].getTagCurve (i_name);
          kurven.push_back (kurve);
          TagInfo = profile[0].printTagInfo (i_name);
          //for (unsigned int i = 0; i < 2; i++)
          texte.push_back (TagInfo[0]);
        }
      }
      texte.push_back ("curv");
      tag_viewer->hinein_kurven( kurven, texte );
    } else if ( TagInfo[1] == "chrm" ) {
      tag_viewer->hinein_punkt( profile[0].getTagCIEXYZ(item), profile[0].getTagText(item) );
    } else if ( TagInfo[1] == "XYZ" ) {
      tag_viewer->hinein_punkt( profile[0].getTagCIEXYZ(item), TagInfo );
    } else if ( TagInfo[1] == "mft2"
             || TagInfo[1] == "mft1" ) {
      mft_choice->profil_tag (item);
      //mft_text->hinein ( (profile[0].getTagText (item))[0] ); DBG_PROG
    } else if ( TagInfo[1] == "vcgt" ) { DBG_PROG
      tag_viewer->hinein_kurven ( profile[0].getTagCurves (item, ICCtag::CURVE_IN),
                                  profile[0].getTagText (item) ); cout << "vcgt "; DBG_PROG

    /*} else if ( TagInfo[1] == "chad" ) {
      std::vector<int> zahlen = profile[0].getTagNumbers (tag_nummer, ICCtag::MATRIX);
      cout << zahlen.size() << endl; DBG_PROG
      assert (9 == zahlen.size());
      s << endl <<
      "  " << zahlen[0] << ", " << zahlen[1] << ", " << zahlen[2] << ", " << endl <<
      "  " << zahlen[3] << ", " << zahlen[4] << ", " << zahlen[5] << ", " << endl <<
      "  " << zahlen[6] << ", " << zahlen[7] << ", " << zahlen[8] << ", " << endl;
      tag_text->hinein ( s.str() ); DBG_PROG
*/
    } else {
      tag_text->hinein ( (profile[0].getTagText (item))[0] ); DBG_PROG
    }
    selectedTagName = TagInfo[0];
  }DBG_PROG
  DBG_PROG_ENDE
}

TagTexts::TagTexts(int X,int Y,int W,int H,char* start_info) : Fl_Hold_Browser(X,Y,W,H,start_info), X(X), Y(Y), W(W), H(H) {
}

void TagTexts::hinein(std::string text) {
  DBG_PROG_START
  //Text aus tag_browser anzeigen

  zeig_mich(this); DBG_PROG

      this->clear();

      std::vector <std::string> texte = zeilenNachVector( text );
      for (unsigned int i = 0; i < texte.size(); i++)
        this->add( texte[i].c_str(), 0);


      this->topline(0);
      this->textfont(FL_COURIER);
      this->textsize(14);
  DBG_PROG_ENDE
}

TagDrawings::TagDrawings(int X,int Y,int W,int H) : Fl_Widget(X,Y,W,H), X(X), Y(Y), W(W), H(H) {
}

void TagDrawings::draw() {
  DBG_PROG_START
  // Kurven oder Punkte malen
  DBG_PROG_S( punkte.size() << "/" << kurven.size() <<" "<< texte.size() )

  //DBG_PROG_V( wiederholen )

  if (punkte.size() >= 3)
  {
    if (wiederholen)
    { draw_cie_shoe(x(),y(),w(),h(),texte,punkte,false);
      Fl::add_timeout( 1.2, (void(*)(void*))d_haendler ,(void*)this);
    } else {
      draw_cie_shoe(x(),y(),w(),h(),texte,punkte,true);
    }
    wiederholen = true;
  } else {
    wiederholen = false;
    draw_kurve   (x(),y(),w(),h(),texte,kurven);
  }
  DBG_PROG
  DBG_PROG_ENDE
}

void TagDrawings::hinein_punkt(std::vector<double> vect, std::vector<std::string> txt) {
  DBG_PROG_START
  //CIExyY aus tag_browser anzeigen
  punkte.clear();
  for (unsigned int i = 0; i < vect.size(); i++)
    punkte.push_back (vect[i]);
  texte.clear();
  for (unsigned int i = 0; i < txt.size(); i++)
    texte.push_back (txt[i]);
  kurven.clear();
  wiederholen = false;

  zeig_mich(this);
  DBG_PROG_ENDE
}

void TagDrawings::hinein_kurven(std::vector<std::vector<double> >vect, std::vector<std::string> txt) {
  DBG_PROG_START
  //Kurve aus tag_browser anzeigen
  kurven = vect;
  texte = txt;
  punkte.clear();
  wiederholen = false;

  zeig_mich(this);
  DBG_PROG
  DBG_PROG_ENDE
}

void TagDrawings::ruhig_neuzeichnen(void) {
  DBG_PROG_START
  draw_cie_shoe(x(),y(),w(),h(),texte,punkte,true);
  DBG_PROG_ENDE
}
#include <FL/fl_draw.H>

MftChoice::MftChoice(int X,int Y,int W,int H,char* start_info) : Fl_Choice(X,Y,W,H,start_info), X(X), Y(Y), W(W), H(H) {
  gewaehlter_eintrag = 0;
}

void MftChoice::profil_tag(int _tag) {
  DBG_PROG_START
  tag_nummer = _tag;

// = profile[0].printTagInfo(tag_nummer);
    sprintf (&typ[0], profile[0].printTagInfo(tag_nummer)[1].c_str());

    Info = zeilenNachVector (profile[0].getTagText (tag_nummer)[0]);

    if ( strstr (typ,"mft2") != 0 )
    {
      Fl_Menu_Item *mft_menue = (Fl_Menu_Item *)calloc (sizeof (Fl_Menu_Item), 6);

      mft_menue[0].text = Info[0].c_str();
      mft_menue[1].text = Info[4].c_str();
      mft_menue[2].text = Info[5].c_str();
      mft_menue[3].text = Info[6].c_str();
      mft_menue[4].text = Info[7].c_str();
      mft_menue[5].text = 0;
      mft_choice->menu(mft_menue);
    } else {
      Fl_Menu_Item *mft_menue = (Fl_Menu_Item *)calloc (sizeof (Fl_Menu_Item), 6);

      mft_menue[0].text = Info[0].c_str();
      mft_menue[1].text = Info[4].c_str();
      mft_menue[2].text = "lineare Eingangskurve mit 256 Stufungen";
      mft_menue[3].text = Info[5].c_str();
      mft_menue[4].text = "lineare Ausgangskurve mit 256 Stufungen";
      mft_menue[5].text = 0;
      mft_choice->menu(mft_menue);
    }

    mft_choice->value( gewaehlter_eintrag );

  //zeig_mich (this);
  auswahl_cb();
  DBG_PROG_ENDE
}

void MftChoice::auswahl_cb(void) {
  DBG_PROG_START
  //Auswahl aus mft_choice

  status("")

  Fl_Menu_* mw = (Fl_Menu_*)this;
  const Fl_Menu_Item* m = mw->mvalue();
  if (!m) {
    DBG_PROG_S("NULL \n")
  } else if (m->shortcut()) {
    DBG_PROG_S("%s - %s \n" << m->label() << fl_shortcut_label(m->shortcut()))
  } else {
    DBG_PROG_S("%s \n" << m->label())
  }

  std::stringstream s;
  std::vector<double> zahlen;

  switch (mw->value()) {
  case 0: // �berblick
    { for (unsigned int i = 1; i < Info.size(); i++) // erste Zeile weglassen
        s << Info [i] << endl;
      mft_text->hinein ( s.str() ); DBG_PROG // anzeigen
    } break;
  case 1: // Matriz
    zahlen = profile[0].getTagNumbers (tag_nummer, ICCtag::MATRIX);
    cout << zahlen.size() << endl; DBG_PROG
    assert (9 == zahlen.size());
    s << endl <<
    "  " << zahlen[0] << ", " << zahlen[1] << ", " << zahlen[2] << ", " << endl <<
    "  " << zahlen[3] << ", " << zahlen[4] << ", " << zahlen[5] << ", " << endl <<
    "  " << zahlen[6] << ", " << zahlen[7] << ", " << zahlen[8] << ", " << endl;
    mft_text->hinein ( s.str() ); DBG_PROG
    break;
  case 2: // Eingangskurven
    DBG_PROG
    mft_viewer->hinein_kurven (
                     profile[0].getTagCurves (tag_nummer, ICCtag::CURVE_IN),
                     profile[0].getTagChannelNames (tag_nummer, ICCtag::CURVE_IN) ); DBG_PROG
    break;
  case 3: // 3D Tabelle
    DBG_PROG
    mft_gl->hinein_tabelle (
                     profile[0].getTagTable (tag_nummer, ICCtag::TABLE),
                     profile[0].getTagChannelNames (tag_nummer, ICCtag::TABLE_IN),
                     profile[0].getTagChannelNames (tag_nummer, ICCtag::TABLE_OUT) ); DBG_PROG
    break;
  case 4: // Ausgangskurven
    mft_viewer->hinein_kurven (
                     profile[0].getTagCurves (tag_nummer, ICCtag::CURVE_OUT),
                     profile[0].getTagChannelNames (tag_nummer, ICCtag::CURVE_OUT) ); DBG_PROG
    break;
  }

  gewaehlter_eintrag = mw->value();
  DBG_PROG_ENDE
}

void d_haendler(void* o) {
  DBG_PROG_START
  Fl::remove_timeout( (void(*)(void*))d_haendler, 0 );

  if (!Fl::has_timeout( (void(*)(void*))d_haendler, 0 )
   && ((TagDrawings*)o)->active()
   && ((TagDrawings*)o)->visible_r()
   && ((TagDrawings*)o)->wiederholen)
  {
    ((TagDrawings*)o)->ruhig_neuzeichnen();

    #ifdef DEBUG
    DBG_PROG_V( ((TagDrawings*)o)->wiederholen )
    #endif
  }
  DBG_PROG_ENDE
}

void zeig_mich(void* widget) {
  DBG_PROG_START
  // zeigt das ausgew�hlte Fenster (widget)

  //tabellengruppe->hide();
  mft_viewer->hide();
  mft_text->hide();
  //mft_gl->hide();
  
  tag_viewer->hide(); DBG_PROG
  tag_viewer->clear_visible(); DBG_PROG
  tag_text->hide();
  if (widget != mft_gl) {
    mft_gl->verstecken();
    //((Fl_Widget*)widget)->parent()->show(); DBG_PROG
    ((Fl_Widget*)widget)->show(); DBG_PROG
  } else {
    DBG_PROG_S( "GL Fenster belassen." )
    mft_gl->zeigen();
  }
  DBG_PROG_ENDE
}

std::vector<std::string> zeilenNachVector(std::string text) {
  DBG_PROG_START
  // f�gt Zeilen aus einen Text in einen Vector
  std::vector <std::string> texte;

      int len = strlen(text.c_str());
      std::string text_line;
      char c;
      const char *chars = text.c_str();
      for (int zeichen = 0; zeichen < len; zeichen++) {
        c = chars[zeichen];
        if (c == '\n' || (int)c == 0) { // LF oder 0
          text_line += '\0';
          texte.push_back(text_line.c_str());
          text_line.clear();
        } else
          text_line += c;
      }
      if (text_line.size() > 0) // falls was �brig bleibt
        texte.push_back(text_line.c_str());

  DBG_PROG_ENDE
  return texte;
}