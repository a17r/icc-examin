// generated by Fast Light User Interface Designer (fluid) version 1.0106

#ifndef icc_betrachter_h
#define icc_betrachter_h
#include <FL/Fl.H>
#include <cassert>
#include <iostream>
//#include <sstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Box.H>
#include "icc_fenster.h" 
#include <FL/Fl_Hold_Browser.H>
#include <FL/Fl_Choice.H>
class TagDrawings;
class TagBrowser;
class TagTexts;
class MftChoice;
class GL_Ansicht;
#include "icc_examin.h"
#include "icc_profile.h"
#include "icc_utils.h"
#include "icc_ueber.h"
#include "icc_helfer.h"
#include "icc_helfer_fltk.h"
char* iccReadInfo(char* filename);

class TagBrowser : public Fl_Hold_Browser {
public:
  int X; int Y; int W; int H; const char* start_info; std::string selectedTagName;
  TagBrowser(int X,int Y,int W,int H,const char* start_info) ;
  void reopen_nicht();
  void selectItem(int item);
  int visible();
};

class TagTexts : public Fl_Hold_Browser {
  int X; int Y; int W; int H; const char* start_info;
public:
  int inspekt_topline;
  TagTexts(int X,int Y,int W,int H,const char* start_info) ;
  void hinein(std::string text);
};

class MftChoice : public Fl_Choice {
  int X; int Y; int W; int H; const char* start_info; char typ[5];
public:
  std::vector<std::string> Info; int gewaehlter_eintrag;
  MftChoice(int X,int Y,int W,int H,const char* start_info) ;
  void profilTag(int _tag, std::string text);
  void auswahlCb(void);
};

class My_Fl_Box : public Fl_Box {
public:
  My_Fl_Box(int X,int Y,int W, int H, const char* title = 0) ;
  int handle( int event );
};
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Help_View.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Tile.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Progress.H>

class ICCfltkBetrachter {
public:
  bool setTitleUrl;

 int px,py,pw,ph;
 int fullscreen;
  
 int tag_nummer;
  
 enum{ WID_0, WID_3D, WID_INSPEKT }; int widget_oben;
  Fl_Double_Window* init(int argc, char** argv);
  Fl_Double_Window *ueber;
  Fl_Help_View *ueber_html;
  Fl_Button *ja;
private:
  inline void cb_ja_i(Fl_Button*, void*);
  static void cb_ja(Fl_Button*, void*);
public:
  Fl_Double_Window *vcgt;
  TagDrawings *vcgt_viewer;
  Fl_Button *vcgt_set_button;
private:
  inline void cb_vcgt_set_button_i(Fl_Button*, void*);
  static void cb_vcgt_set_button(Fl_Button*, void*);
public:
  Fl_Button *vcgt_reset_button;
private:
  inline void cb_vcgt_reset_button_i(Fl_Button*, void*);
  static void cb_vcgt_reset_button(Fl_Button*, void*);
public:
  Fl_Button *vcgt_load_button;
private:
  inline void cb_vcgt_load_button_i(Fl_Button*, void*);
  static void cb_vcgt_load_button(Fl_Button*, void*);
public:
  Fl_Button *vcgt_refresh_button;
private:
  inline void cb_vcgt_refresh_button_i(Fl_Button*, void*);
  static void cb_vcgt_refresh_button(Fl_Button*, void*);
public:
  Fl_Button *vcgt_close_button;
private:
  inline void cb_vcgt_close_button_i(Fl_Button*, void*);
  static void cb_vcgt_close_button(Fl_Button*, void*);
public:
  Fl_Double_Window *details;
  Fl_Menu_Bar *menueleiste;
  static Fl_Menu_Item menu_menueleiste[];
private:
  inline void cb_Open_i(Fl_Menu_*, void*);
  static void cb_Open(Fl_Menu_*, void*);
public:
  static Fl_Menu_Item *menueintrag_html_speichern;
private:
  inline void cb_menueintrag_html_speichern_i(Fl_Menu_*, void*);
  static void cb_menueintrag_html_speichern(Fl_Menu_*, void*);
public:
  static Fl_Menu_Item *menueintrag_gamut_speichern;
private:
  inline void cb_menueintrag_gamut_speichern_i(Fl_Menu_*, void*);
  static void cb_menueintrag_gamut_speichern(Fl_Menu_*, void*);
public:
  static Fl_Menu_Item *menueintrag_gamut_vrml_speichern;
private:
  inline void cb_menueintrag_gamut_vrml_speichern_i(Fl_Menu_*, void*);
  static void cb_menueintrag_gamut_vrml_speichern(Fl_Menu_*, void*);
  inline void cb_Quit_i(Fl_Menu_*, void*);
  static void cb_Quit(Fl_Menu_*, void*);
  inline void cb_Oyranos_i(Fl_Menu_*, void*);
  static void cb_Oyranos(Fl_Menu_*, void*);
public:
  static Fl_Menu_Item *menueintrag_gamutwarn;
private:
  inline void cb_menueintrag_gamutwarn_i(Fl_Menu_*, void*);
  static void cb_menueintrag_gamutwarn(Fl_Menu_*, void*);
public:
  static Fl_Menu_Item *menueintrag_huelle;
private:
  inline void cb_menueintrag_huelle_i(Fl_Menu_*, void*);
  static void cb_menueintrag_huelle(Fl_Menu_*, void*);
public:
  static Fl_Menu_Item *menueintrag_Voll;
private:
  inline void cb_menueintrag_Voll_i(Fl_Menu_*, void*);
  static void cb_menueintrag_Voll(Fl_Menu_*, void*);
public:
  static Fl_Menu_Item *menueintrag_3D;
private:
  inline void cb_menueintrag_3D_i(Fl_Menu_*, void*);
  static void cb_menueintrag_3D(Fl_Menu_*, void*);
public:
  static Fl_Menu_Item *menueintrag_inspekt;
private:
  inline void cb_menueintrag_inspekt_i(Fl_Menu_*, void*);
  static void cb_menueintrag_inspekt(Fl_Menu_*, void*);
public:
  static Fl_Menu_Item *menueintrag_zeigcgats;
private:
  inline void cb_menueintrag_zeigcgats_i(Fl_Menu_*, void*);
  static void cb_menueintrag_zeigcgats(Fl_Menu_*, void*);
public:
  static Fl_Menu_Item *menueintrag_vcgt;
private:
  inline void cb_menueintrag_vcgt_i(Fl_Menu_*, void*);
  static void cb_menueintrag_vcgt(Fl_Menu_*, void*);
public:
  static Fl_Menu_Item *menueintrag_testkurven;
private:
  inline void cb_menueintrag_testkurven_i(Fl_Menu_*, void*);
  static void cb_menueintrag_testkurven(Fl_Menu_*, void*);
public:
  static Fl_Menu_Item *untermenue_3D;
  static Fl_Menu_Item *menu_hilfe;
private:
  inline void cb_About_i(Fl_Menu_*, void*);
  static void cb_About(Fl_Menu_*, void*);
public:
  GL_Ansicht *DD_farbraum;
  Fl_Help_View *inspekt_html;
  Fl_Tile *examin;
  TagBrowser *tag_browser;
private:
  inline void cb_tag_browser_i(TagBrowser*, void*);
  static void cb_tag_browser(TagBrowser*, void*);
public:
  Fl_Group *ansichtsgruppe;
  Fl_Group *tabellengruppe;
  MftChoice *mft_choice;
private:
  inline void cb_mft_choice_i(MftChoice*, void*);
  static void cb_mft_choice(MftChoice*, void*);
public:
  TagDrawings *mft_viewer;
  TagTexts *mft_text;
  GL_Ansicht *mft_gl;
  TagDrawings *tag_viewer;
  TagTexts *tag_text;
  Fl_Box *box_stat;
  Fl_Progress *load_progress;
  My_Fl_Box *no_box;
  void run();
  std::vector<std::string> open(std::vector<std::string> dateinamen);
  void quit(void);
  void zeig_mich_(void* widget);
  void measurement(bool has_measurement);
};
void dHaendler(void* o);
#endif
