// generated by Fast Light User Interface Designer (fluid) version 1.0104

#include "icc_examin.h"
static char *statlabel;
 std::string filename_alt;
 bool setTitleUrl = true;

 int px,py,pw,ph;
 int fullscreen;
  int inspekt_topline;
 int tag_nummer;
#include "icc_draw.h"
ICCprofile profile;

Fl_Double_Window *details=(Fl_Double_Window *)0;

static void cb_ffnen(Fl_Menu_*, void*) {
  open(true);
}

static void cb_menueintrag_html_speichern(Fl_Menu_*, void*) {
  std::string bericht = profile.report();
  std::string filename = filename_alt;
  filename=fl_file_chooser("Bericht Speichern", "HTML Dokumente (*.[H,h][T,t][M,m,]*)", filename_alt.c_str());
  DBG

  if (filename == "" || filename == filename_alt) {
    load_progress->hide ();
    return;
  }

  std::ofstream f ( filename.c_str(),  std::ios::out );
  f.write ( bericht.c_str(), bericht.size() );
  f.close();
}

static void cb_Beenden(Fl_Menu_*, void*) {
  quit();
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

static void cb_MatrixTestprofil(Fl_Menu_*, void*) {
  Profilierer p;
//profile.removeTag(0); //Test
p.load (profile);
ICCprofile matrix (p.matrix());
matrix.saveProfileToFile("/tmp/icc_examin_test.icc");
}

static void cb_menueintrag_inspekt(Fl_Menu_* o, void*) {
  Fl_Menu_* mw = (Fl_Menu_*)o;
  const Fl_Menu_Item* m = mw->mvalue();

  DBG_S (m->value())
  if (m->value()) {
    inspekt->show();
    examin->hide();
    inspekt_html->value(profile.report().c_str());
    inspekt_html->topline(inspekt_topline);
  } else {
    inspekt->hide();
    examin->show();
    inspekt_topline = inspekt_html->topline();
  };
}

Fl_Menu_Item menu_[] = {
 {"Daten", 0,  0, 0, 64, 0, 0, 14, 56},
 {"\326""ffnen", 0x4006f,  (Fl_Callback*)cb_ffnen, 0, 0, 0, 0, 14, 56},
 {"Bericht Speichern", 0,  (Fl_Callback*)cb_menueintrag_html_speichern, 0, 128, 0, 0, 14, 56},
 {"Beenden", 0x40071,  (Fl_Callback*)cb_Beenden, 0, 0, 0, 0, 14, 56},
 {0},
 {"Ansicht", 0,  0, 0, 64, 0, 0, 14, 56},
 {"Ganzer Bildschirm an/aus", 0x40076,  (Fl_Callback*)cb_menueintrag_Voll, 0, 0, 0, 0, 14, 56},
 {"MatrixTestprofil schreiben", 0,  (Fl_Callback*)cb_MatrixTestprofil, 0, 0, 0, 0, 14, 56},
 {0},
 {"Pr\374""fansicht", 0x40062,  (Fl_Callback*)cb_menueintrag_inspekt, 0, 3, 0, 0, 14, 56},
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

Fl_Group *tag_3D=(Fl_Group *)0;

Fl_Group *tabellengruppe=(Fl_Group *)0;

MftChoice *mft_choice=(MftChoice *)0;

static void cb_mft_choice(MftChoice* o, void*) {
  o->auswahl_cb();
}

TagDrawings *mft_viewer=(TagDrawings *)0;

TagTexts *mft_text=(TagTexts *)0;

Fl_Box *mft_gl=(Fl_Box *)0;

TagDrawings *tag_viewer=(TagDrawings *)0;

TagTexts *tag_text=(TagTexts *)0;

Fl_Box *stat=(Fl_Box *)0;

Fl_Progress *load_progress=(Fl_Progress *)0;

int main(int argc, char **argv) {
  Fl_Double_Window* w;
  statlabel = (char*)calloc (sizeof (char), 1024);
  fullscreen = false;
  inspekt_topline = 0;
  { Fl_Double_Window* o = details = new Fl_Double_Window(385, 515, "ICC Details");
    w = o;
    o->box(FL_NO_BOX);
    o->color((Fl_Color)53);
    { Fl_Group* o = new Fl_Group(0, 0, 385, 520);
      { Fl_Menu_Bar* o = new Fl_Menu_Bar(0, 0, 385, 25);
        o->color((Fl_Color)53);
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
          o->color((Fl_Color)53);
          o->selection_color(FL_SELECTION_COLOR);
          o->labeltype(FL_NORMAL_LABEL);
          o->labelfont(0);
          o->labelsize(14);
          o->labelcolor(FL_BLACK);
          o->callback((Fl_Callback*)cb_tag_browser);
          o->align(FL_ALIGN_TOP|FL_ALIGN_INSIDE);
          o->when(FL_WHEN_RELEASE_ALWAYS);
          int lines = tag_browser->size();
          cout << lines << endl; DBG
        }
        { Fl_Group* o = ansichtsgruppe = new Fl_Group(0, 160, 385, 335);
          { Fl_Group* o = tag_3D = new Fl_Group(0, 160, 385, 335);
            o->hide();
            o->end();
          }
          { Fl_Group* o = tabellengruppe = new Fl_Group(0, 160, 385, 335);
            { MftChoice* o = mft_choice = new MftChoice(0, 160, 385, 25, "W\344hlen Sie ein Kettenmerkmal");
              o->box(FL_NO_BOX);
              o->down_box(FL_BORDER_BOX);
              o->color(FL_BACKGROUND2_COLOR);
              o->selection_color(FL_SELECTION_COLOR);
              o->labeltype(FL_NORMAL_LABEL);
              o->labelfont(0);
              o->labelsize(14);
              o->labelcolor(FL_BLACK);
              o->callback((Fl_Callback*)cb_mft_choice);
              o->align(FL_ALIGN_LEFT);
              o->when(FL_WHEN_RELEASE);
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
            }
            { TagTexts* o = mft_text = new TagTexts(0, 185, 385, 310, "Der Text");
              o->box(FL_NO_BOX);
              o->color((Fl_Color)53);
              o->selection_color(FL_SELECTION_COLOR);
              o->labeltype(FL_NORMAL_LABEL);
              o->labelfont(0);
              o->labelsize(14);
              o->labelcolor(FL_BLACK);
              o->align(FL_ALIGN_BOTTOM|FL_ALIGN_INSIDE);
              o->when(FL_WHEN_RELEASE_ALWAYS);
            }
            mft_gl = new Fl_Box(0, 185, 385, 310);
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
            o->color((Fl_Color)53);
            o->selection_color(FL_SELECTION_COLOR);
            o->labeltype(FL_NORMAL_LABEL);
            o->labelfont(0);
            o->labelsize(14);
            o->labelcolor(FL_BLACK);
            o->align(FL_ALIGN_BOTTOM|FL_ALIGN_INSIDE);
            o->when(FL_WHEN_RELEASE_ALWAYS);
          }
          o->end();
        }
        o->end();
        Fl_Group::current()->resizable(o);
      }
      { Fl_Group* o = new Fl_Group(0, 494, 385, 25);
        { Fl_Box* o = stat = new Fl_Box(0, 494, 385, 25, "No wrl file loaded.");
          o->box(FL_THIN_DOWN_BOX);
          o->color((Fl_Color)53);
          o->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
        }
        { Fl_Progress* o = load_progress = new Fl_Progress(0, 494, 385, 25, "Laden ..");
          o->color((Fl_Color)53);
          o->hide();
          o->maximum(1.0);
          o->minimum(0.0);
        }
        o->end();
      }
      o->end();
    }
    DBG
    if (argc>1) {

      if (argc>1) {

        sprintf (statlabel, "%s geladen", argv[1]);
        stat->label(statlabel);
        filename_alt = argv[1];
      } else {
        stat->label("Error loading file!");
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
  w->show(argc, argv);
  return Fl::run();
}

std::string open(int interaktiv) {
  #include "icc_vrml.h"

  std::string filename = filename_alt;
  //Fl_File_Icon	*icon;	// New file icon
  DBG
  load_progress->show ();    load_progress->value (0.0);

  if (interaktiv)
    filename=fl_file_chooser("W�hle ICC Profil?", "ICC Farbprofile (*.[I,i][C,c][M,m,C,c])", filename_alt.c_str());
  DBG cout << filename_alt << "|" << filename << endl;

  if (filename == "") {
    load_progress->hide ();
    return "";
  }

  // Laden
  profile.load (filename);
  // Register the ICC type ...
  //Fl_Shared_Image::add_handler(icc_check);
  //Fl_Shared_Image::add_handler(ps_check);

  std::vector<std::string> url;
  std::vector<std::string> param;

  if (/*browser && */(filename != "")) { DBG

    //create_vrml ( filename.c_str(), "/usr/share/color/icc/sRGB.icm", &vrmlDatei[0]);

    load_progress->value (0.8);
    filename_alt = filename;
    //url.push_back (&vrmlDatei[0]);
    //browser->load_url(url, param);
    sprintf (statlabel, "%s geladen", filename.c_str());
    cout << statlabel << endl; DBG
    stat->label(statlabel);
  } else {
    stat->label("Error loading file!");
  } DBG

  stat->hide();
  stat->show();
  load_progress->value (1.0);
  load_progress->value (0.0);
  load_progress->hide();
  DBG

  tag_browser->reopen ();

  if (profile.hasMeasurement()) {
    inspekt_topline = inspekt_html->topline();
    DBG_S(menueintrag_inspekt->value())
    if (menueintrag_inspekt->value()) {
      inspekt_html->value(profile.report().c_str());
      cout << inspekt_html->size() << " " << inspekt_topline; DBG
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

  return filename;
}

void quit(void) {
  /*Fl::remove_timeout((void (*)(void *))timeIT, (void *)viewer);
  delete viewer;
  delete browser;
  delete canvas;*/
  details->hide();
  exit(0);
}

char* icc_read_info(char* filename) {
  char systemBefehl[1024];
  char *textfile = "/tmp/icc_temp.txt";


  sprintf (systemBefehl, "iccdump \"%s\" > %s",
                                    filename, textfile);
  system (systemBefehl);

  return textfile;
}

TagBrowser::TagBrowser(int X,int Y,int W,int H,char* start_info) : Fl_Hold_Browser(X,Y,W,H,start_info), X(X), Y(Y), W(W), H(H) {
}

void TagBrowser::reopen() {
  //open and preparing the first selected item
  std::stringstream s;
  std::string text;
  std::vector<std::string> tag_list = profile.printTags();

  #define add_s(stream) s << stream; add (s.str().c_str()); s.str("");
  #define add_          s << " ";

  clear();
  add_s ("@fDateiname:")
  add_s ("@b    " << profile.filename() )
  add_s ("")
  if (tag_list.size() == 0) {
    add_s ("keine Inhalte gefunden f�r \"" << profile.filename() << "\"")
    return;
  }
  add_s ("@B26@tNr. Bezeichner  Typ         Gr��e Beschreibung")
  add_s ("@t" << profile.printHeader() )
  DBG
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
  DBG
  if (value())
    select_item (value()); // Anzeigen
  else
    select_item (1);

  if (profile.hasTagName (selectedTagName)) {
    int item = profile.getTagByName (selectedTagName) + 6;
    select_item (item);
    value(item);
  }

  s.clear(); s << "ICC Details: " << profile.filename();
  details->label( (const char*) s.str().c_str() );
}

void TagBrowser::select_item(int item) {
  //Auswahl aus tag_browser
  std::string text = _("Leer");
  tag_text->hinein(text);
  item -= 6;
  cout << item << ". Tag "; DBG
  std::vector<std::string> rgb_tags;
  rgb_tags.push_back("rXYZ");
  rgb_tags.push_back("gXYZ");
  rgb_tags.push_back("bXYZ");

  if (item < 0) {
    select(5);
    text = profile.printLongHeader(); DBG
    tag_text->hinein(text);    
  } else if (item >= 0) {
    std::vector<std::string> TagInfo = profile.printTagInfo(item);
    cout << TagInfo.size() << " " << TagInfo[0] << " " << TagInfo[1] << " "; DBG

    if        ( TagInfo[1] == "text"
             || TagInfo[1] == "cprt?"
             || TagInfo[1] == "meas"
             || TagInfo[1] == "sig"
             || TagInfo[1] == "dtim") {
      tag_text->hinein ( (profile.getTagText (item))[0] ); DBG
    } else if ( TagInfo[1] == "desc" ) {
      tag_text->hinein( (profile.getTagDescription (item))[0] ); DBG
    } else if ( TagInfo[0] == "rXYZ" || TagInfo[0] == "gXYZ" || TagInfo[0] == "bXYZ" ) {
      std::vector<double> alle_punkte, punkte;
      std::vector<std::string> alle_texte;
      std::string TagName;
      for (unsigned int i_name = 0; i_name < rgb_tags.size(); i_name++) {
        if (profile.hasTagName (rgb_tags[i_name])) {
          punkte = profile.getTagCIEXYZ (profile.getTagByName(rgb_tags[i_name]));
          for (unsigned int i = 0; i < 3; i++)
            alle_punkte.push_back (punkte[i]);
          TagInfo = profile.printTagInfo (profile.getTagByName(rgb_tags[i_name]));
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
      for (int i_name = 0; i_name < profile.tagCount(); i_name++) {
        if ( (profile.printTagInfo(i_name))[1] == "curv"
          || (profile.printTagInfo(i_name))[1] == "bfd" ) {
          kurve = profile.getTagCurve (i_name);
          kurven.push_back (kurve);
          TagInfo = profile.printTagInfo (i_name);
          //for (unsigned int i = 0; i < 2; i++)
          texte.push_back (TagInfo[0]);
        }
      }
      texte.push_back ("curv");
      tag_viewer->hinein_kurven( kurven, texte );
    } else if ( TagInfo[1] == "chrm") {
      tag_viewer->hinein_punkt( profile.getTagCIEXYZ(item), profile.getTagText(item) );
    } else if ( TagInfo[1] == "XYZ" ) {
      tag_viewer->hinein_punkt( profile.getTagCIEXYZ(item), TagInfo );
    } else if ( TagInfo[1] == "mft2"
             || TagInfo[1] == "mft1" ) {
      mft_choice->profil_tag (item);
      //mft_text->hinein ( (profile.getTagText (item))[0] ); DBG
    } else if ( TagInfo[1] == "vcgt" ) { DBG
      tag_viewer->hinein_kurven ( profile.getTagCurves (item, ICCtag::CURVE_IN),
                                  profile.getTagText (item) ); cout << "vcgt "; DBG
    }
    selectedTagName = TagInfo[0];
  }DBG
}

TagTexts::TagTexts(int X,int Y,int W,int H,char* start_info) : Fl_Hold_Browser(X,Y,W,H,start_info), X(X), Y(Y), W(W), H(H) {
}

void TagTexts::hinein(std::string text) {
  //Text aus tag_browser anzeigen

  zeig_mich(this); DBG

      this->clear();

      std::vector <std::string> texte = zeilenNachVector( text );
      for (unsigned int i = 0; i < texte.size(); i++)
        this->add( texte[i].c_str(), 0);


      this->topline(0);
      this->textfont(FL_COURIER);
      this->textsize(14);
}

TagDrawings::TagDrawings(int X,int Y,int W,int H) : Fl_Widget(X,Y,W,H), X(X), Y(Y), W(W), H(H) {
}

void TagDrawings::draw() {
  // Kurven oder Punkte malen
  cout << punkte.size() << "/" << kurven.size() <<" "<< texte.size() <<" "; DBG

  if (punkte.size() >= 3) {
    wiederholen = true;
    draw_cie_shoe(x(),y(),w(),h(),texte,punkte,false);
    Fl::add_timeout( 1.2, (void(*)(void*))d_haendler ,(void*)this);

  } else {
    wiederholen = false;
    draw_kurve   (x(),y(),w(),h(),texte,kurven);
  }
  DBG
}

void TagDrawings::hinein_punkt(std::vector<double> vect, std::vector<std::string> txt) {
  //CIExyY aus tag_browser anzeigen
  punkte.clear();
  for (unsigned int i = 0; i < vect.size(); i++)
    punkte.push_back (vect[i]);
  texte.clear();
  for (unsigned int i = 0; i < txt.size(); i++)
    texte.push_back (txt[i]);
  kurven.clear();

  zeig_mich(this);
}

void TagDrawings::hinein_kurven(std::vector<std::vector<double> >vect, std::vector<std::string> txt) {
  //Kurve aus tag_browser anzeigen
  kurven = vect;
  texte = txt;
  punkte.clear();

  zeig_mich(this);
  DBG
}

void TagDrawings::ruhig_neuzeichnen(void) {
  draw_cie_shoe(x(),y(),w(),h(),texte,punkte,true);
}
#include <FL/fl_draw.H>

MftChoice::MftChoice(int X,int Y,int W,int H,char* start_info) : Fl_Choice(X,Y,W,H,start_info), X(X), Y(Y), W(W), H(H) {
}

void MftChoice::profil_tag(int _tag) {
  tag_nummer = _tag;

// = profile.printTagInfo(tag_nummer);
    sprintf (&typ[0], profile.printTagInfo(tag_nummer)[1].c_str());

    Info = zeilenNachVector (profile.getTagText (tag_nummer)[0]);

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

  zeig_mich (this);
  auswahl_cb();
}

void MftChoice::auswahl_cb(void) {
  //Auswahl aus mft_choice

  Fl_Menu_* mw = (Fl_Menu_*)this;
  const Fl_Menu_Item* m = mw->mvalue();
  if (!m) {
    printf("NULL \n"); DBG
  } else if (m->shortcut()) {
    printf("%s - %s \n", m->label(), fl_shortcut_label(m->shortcut())); DBG
  } else {
    printf("%s \n", m->label()); DBG
  }

  std::stringstream s;
  std::vector<double> zahlen;

  switch (mw->value()) {
  case 0: // �berblick
    { for (unsigned int i = 1; i < Info.size(); i++) // erste Zeile weglassen
        s << Info [i] << endl;
      mft_text->hinein ( s.str() ); DBG // anzeigen
    } break;
  case 1: // Matriz
    zahlen = profile.getTagNumbers (tag_nummer, ICCtag::MATRIX);
    cout << zahlen.size() << endl; DBG
    assert (9 == zahlen.size());
    s << endl <<
    "  " << zahlen[0] << ", " << zahlen[1] << ", " << zahlen[2] << ", " << endl <<
    "  " << zahlen[3] << ", " << zahlen[4] << ", " << zahlen[5] << ", " << endl <<
    "  " << zahlen[6] << ", " << zahlen[7] << ", " << zahlen[8] << ", " << endl;
    mft_text->hinein ( s.str() ); DBG
    break;
  case 2: // Eingangskurven
    DBG
    mft_viewer->hinein_kurven (
                     profile.getTagCurves (tag_nummer, ICCtag::CURVE_IN),
                     profile.getTagChannelNames (tag_nummer, ICCtag::CURVE_IN) ); DBG
    break;
  case 3: // 3D Tabelle
    DBG
    break;
  case 4: // Ausgangskurven
    mft_viewer->hinein_kurven (
                     profile.getTagCurves (tag_nummer, ICCtag::CURVE_OUT),
                     profile.getTagChannelNames (tag_nummer, ICCtag::CURVE_OUT) ); DBG
    break;
  }

  gewaehlter_eintrag = mw->value();
}

void d_haendler(void* o) {
  Fl::remove_timeout( (void(*)(void*))d_haendler, 0 );
  if (!Fl::has_timeout( (void(*)(void*))d_haendler, 0 )
   && ((TagDrawings*)o)->active()
   && ((TagDrawings*)o)->visible_r()
   && ((TagDrawings*)o)->wiederholen) {
    ((TagDrawings*)o)->ruhig_neuzeichnen();
    #ifdef DEBUG
    cout << " wiederholen"; DBG
    #endif
  }
}

void zeig_mich(void* widget) {
  // zeigt das ausgew�hlte Fenster (widget)

  tabellengruppe->hide();
  mft_viewer->hide();
  mft_text->hide();
  
  tag_viewer->hide(); DBG
  tag_viewer->clear_visible(); DBG
  tag_text->hide();
  ((Fl_Widget*)widget)->parent()->show(); DBG
  ((Fl_Widget*)widget)->show(); DBG
}

std::vector<std::string> zeilenNachVector(std::string text) {
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


  return texte;
}

GL_Ansicht::GL_Ansicht(int X,int Y,int W,int H) : Fl_Widget(X,Y,W,H), X(X), Y(Y), W(W), H(H) {
}

void GL_Ansicht::draw() {
  // Kurven oder Punkte malen
  cout << punkte.size() << "/" << kurven.size() <<" "<< texte.size() <<" "; DBG

  if (punkte.size() >= 3) {
    wiederholen = true;
    draw_cie_shoe(x(),y(),w(),h(),texte,punkte,false);
    Fl::add_timeout( 3.0, (void(*)(void*))d_haendler ,(void*)this);

  } else {
    wiederholen = false;
    draw_kurve   (x(),y(),w(),h(),texte,kurven);
  }
  DBG
}

void GL_Ansicht::hinein_punkt(std::vector<double> vect, std::vector<std::string> txt) {
  //CIExyY aus tag_browser anzeigen
  punkte.clear();
  for (unsigned int i = 0; i < vect.size(); i++)
    punkte.push_back (vect[i]);
  texte.clear();
  for (unsigned int i = 0; i < txt.size(); i++)
    texte.push_back (txt[i]);
  kurven.clear();

  zeig_mich(this);
}

void GL_Ansicht::hinein_kurven(std::vector<std::vector<double> >vect, std::vector<std::string> txt) {
  //Kurve aus tag_browser anzeigen
  kurven = vect;
  texte = txt;
  punkte.clear();

  zeig_mich(this);
}

void GL_Ansicht::ruhig_neuzeichnen(void) {
  draw_cie_shoe(x(),y(),w(),h(),texte,punkte,true);
}
