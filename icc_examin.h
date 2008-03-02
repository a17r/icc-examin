// generated by Fast Light User Interface Designer (fluid) version 1.0104

#ifndef icc_examin_h
#define icc_examin_h
#include <FL/Fl.H>
#define DEBUG
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_File_Chooser.H> 
#include <FL/Fl_Hold_Browser.H> 
#include <FL/Fl_File_Icon.H> 
#include <FL/Fl_Shared_Image.H> 
#include <FL/Fl_PNM_Image.H>
class TagDrawings;
class TagBrowser;
class TagTexts;
class MftChoice;
#include <openvrml/browser.h>
#include <openvrml/gl/viewer.h>
#include "vFLGLWidget.h"
#include "ViewerFLTK.h"
//#define DBG cout << __FILE__<<":"<<__LINE__ <<" "<< __func__ << "()" << endl;
#define _(text) text
#include "icc_profile.h"
#include "icc_utils.h"
extern ICCprofile profile;
#include <FL/Fl_Double_Window.H>
extern Fl_Double_Window *details;
#include <FL/Fl_Group.H>
#include <FL/Fl_Menu_Bar.H>
extern Fl_Menu_Bar *Fl_lookat_MenuBar;
#include <FL/Fl_Tile.H>
extern Fl_Tile *examin;
extern TagBrowser *tag_browser;
extern Fl_Group *ansichtsgruppe;
extern Fl_Group *tag_3D;
extern vFLGLWidget *canvas;
extern TagDrawings *tag_viewer;
extern TagTexts *tag_text;
extern Fl_Group *tabellengruppe;
extern MftChoice *mft_choice;
extern TagDrawings *mft_viewer;
extern TagTexts *mft_text;
extern Fl_Group *inspekt;
#include <FL/Fl_Box.H>
extern Fl_Box *stat;
#include <FL/Fl_Progress.H>
extern Fl_Progress *load_progress;
extern Fl_Menu_Item menu_Fl_lookat_MenuBar[];
#define menueintrag_Voll (menu_Fl_lookat_MenuBar+5)
#define menueintrag_inspekt (menu_Fl_lookat_MenuBar+6)
std::string open(int interaktiv);
void quit(void);
void worldChangedCB( const openvrml::browser::cb_reason reason );
void timeIT();
char* icc_read_info(char* filename);

class TagBrowser : public Fl_Hold_Browser {
  int X; int Y; int W; int H; char* start_info; std::string selectedTagName;
public:
  TagBrowser(int X,int Y,int W,int H,char* start_info) ;
  void reopen();
  void select_item(int item);
};

class TagTexts : public Fl_Hold_Browser {
  int X; int Y; int W; int H; char* start_info;
public:
  TagTexts(int X,int Y,int W,int H,char* start_info) ;
  void hinein(std::string text);
};

class TagDrawings : public Fl_Widget {
  int X; int Y; int W; int H; std::vector<std::string>texte; std::vector<double>punkte; std::vector<std::vector<double> >kurven;
public:
  int wiederholen;
  TagDrawings(int X,int Y,int W,int H) ;
  void draw();
  void hinein_punkt(std::vector<double> vect, std::vector<std::string> txt);
  void hinein_kurven(std::vector<std::vector<double> >vect, std::vector<std::string> txt);
  void ruhig_neuzeichnen(void);
};

class MftChoice : public Fl_Choice {
  int X; int Y; int W; int H; char* start_info; char typ[5]; std::vector<std::string> Info; int gewaehlter_eintrag;
public:
  MftChoice(int X,int Y,int W,int H,char* start_info) ;
  void profil_tag(int _tag);
  void auswahl_cb(void);
};
void d_haendler(void* o);
void zeig_mich(void* widget);
std::vector<std::string> zeilenNachVector(std::string text);
#endif
