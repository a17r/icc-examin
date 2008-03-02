// generated by Fast Light User Interface Designer (fluid) version 1.0107

#ifndef icc_betrachter_h
#define icc_betrachter_h
#include <FL/Fl.H>
#include "icc_examin.h"
#include "icc_profile.h"
#include "config.h"
#include "icc_utils.h"
#include "icc_ueber.h"
#include "icc_helfer.h"
#include "icc_helfer_fltk.h"
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
#include "icc_dateiwahl.h" 
#include <FL/Fl_Hold_Browser.H>
#include <FL/Fl_Choice.H>
class TagDrawings;
class TagBrowser;
class TagTexts;
class MftChoice;
class GL_Ansicht;
const char* iccReadInfo(char* filename);

class TagBrowser : public Fl_Hold_Browser {
public:
  int X; int Y; int W; int H; const char* start_info; std::string selectedTagName;
  TagBrowser(int X,int Y,int W,int H,const char* start_info) ;
  void reopen_nicht();
  void selectItem(int item);
  int visible();
};
typedef const char* (*tagTextsCB_f)(int * line);

class TagTexts : public Fl_Hold_Browser {
  int X; int Y; int W; int H; const char* start_info;
public:
  int inspekt_topline;
  TagTexts(int X,int Y,int W,int H,const char* start_info) ;
  void hinein(std::string text, std::vector<int> patches);
  void hinein(std::string text);
  tagTextsCB_f cb;
  void selectItem(int item);
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
#include <FL/Fl_Group.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Help_View.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Tile.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Pack.H>
#include <FL/Fl_Progress.H>

class ICCfltkBetrachter {
public:
  bool setTitleUrl;

 int px,py,pw,ph;
 int fullscreen;
  
 int tag_nummer;
  
 enum{ WID_0, WID_3D, WID_INSPEKT }; int widget_oben;
  icc_examin_ns::MyFl_Double_Window* init(int argc, char** argv);
  icc_examin_ns::MyFl_Double_Window *ueber;
  Fl_Help_View *ueber_html;
  Fl_Help_View *hilfe_html;
  Fl_Help_View *lizenz_html;
  Fl_Help_View *dank_html;
  Fl_Output *links_text;
  Fl_Button *ja;
private:
  void cb_ja_i(Fl_Button*, void*);
  static void cb_ja(Fl_Button*, void*);
public:
  icc_examin_ns::MyFl_Double_Window *vcgt;
  TagDrawings *vcgt_viewer;
  Fl_Button *vcgt_set_button;
private:
  void cb_vcgt_set_button_i(Fl_Button*, void*);
  static void cb_vcgt_set_button(Fl_Button*, void*);
public:
  Fl_Button *vcgt_reset_button;
private:
  void cb_vcgt_reset_button_i(Fl_Button*, void*);
  static void cb_vcgt_reset_button(Fl_Button*, void*);
public:
  Fl_Button *vcgt_load_button;
private:
  void cb_vcgt_load_button_i(Fl_Button*, void*);
  static void cb_vcgt_load_button(Fl_Button*, void*);
public:
  Fl_Button *vcgt_close_button;
private:
  void cb_vcgt_close_button_i(Fl_Button*, void*);
  static void cb_vcgt_close_button(Fl_Button*, void*);
public:
  icc_examin_ns::MyFl_Double_Window *DD;
  Fl_Menu_Bar *DD_menueleiste;
  static Fl_Menu_Item menu_DD_menueleiste[];
private:
  void cb_Quit_i(Fl_Menu_*, void*);
  static void cb_Quit(Fl_Menu_*, void*);
public:
  static Fl_Menu_Item *DD_menueintrag_Voll;
private:
  void cb_DD_menueintrag_Voll_i(Fl_Menu_*, void*);
  static void cb_DD_menueintrag_Voll(Fl_Menu_*, void*);
public:
  static Fl_Menu_Item *menueintrag_gamutwarn;
private:
  void cb_menueintrag_gamutwarn_i(Fl_Menu_*, void*);
  static void cb_menueintrag_gamutwarn(Fl_Menu_*, void*);
public:
  static Fl_Menu_Item *menueintrag_phot_intent;
private:
  void cb_menueintrag_phot_intent_i(Fl_Menu_*, void*);
  static void cb_menueintrag_phot_intent(Fl_Menu_*, void*);
public:
  static Fl_Menu_Item *menueintrag_rel_col_intent;
private:
  void cb_menueintrag_rel_col_intent_i(Fl_Menu_*, void*);
  static void cb_menueintrag_rel_col_intent(Fl_Menu_*, void*);
public:
  static Fl_Menu_Item *menueintrag_abs_col_intent;
private:
  void cb_menueintrag_abs_col_intent_i(Fl_Menu_*, void*);
  static void cb_menueintrag_abs_col_intent(Fl_Menu_*, void*);
public:
  static Fl_Menu_Item *menueintrag_bpc;
private:
  void cb_menueintrag_bpc_i(Fl_Menu_*, void*);
  static void cb_menueintrag_bpc(Fl_Menu_*, void*);
  void cb_Show_i(Fl_Menu_*, void*);
  static void cb_Show(Fl_Menu_*, void*);
public:
  GL_Ansicht *DD_farbraum;
  Fl_Box *DD_box_stat;
  My_Fl_Box *no_box2;
  icc_examin_ns::MyFl_Double_Window *details;
  Fl_Menu_Bar *menueleiste;
  static Fl_Menu_Item menu_menueleiste[];
private:
  void cb_Open_i(Fl_Menu_*, void*);
  static void cb_Open(Fl_Menu_*, void*);
public:
  static Fl_Menu_Item *menueintrag_html_speichern;
private:
  void cb_menueintrag_html_speichern_i(Fl_Menu_*, void*);
  static void cb_menueintrag_html_speichern(Fl_Menu_*, void*);
public:
  static Fl_Menu_Item *menueintrag_gamut_speichern;
private:
  void cb_menueintrag_gamut_speichern_i(Fl_Menu_*, void*);
  static void cb_menueintrag_gamut_speichern(Fl_Menu_*, void*);
public:
  static Fl_Menu_Item *menueintrag_gamut_vrml_speichern;
private:
  void cb_menueintrag_gamut_vrml_speichern_i(Fl_Menu_*, void*);
  static void cb_menueintrag_gamut_vrml_speichern(Fl_Menu_*, void*);
  void cb_Quit1_i(Fl_Menu_*, void*);
  static void cb_Quit1(Fl_Menu_*, void*);
public:
  static Fl_Menu_Item *menueintrag_huelle;
private:
  void cb_menueintrag_huelle_i(Fl_Menu_*, void*);
  static void cb_menueintrag_huelle(Fl_Menu_*, void*);
public:
  static Fl_Menu_Item *menueintrag_Voll;
private:
  void cb_menueintrag_Voll_i(Fl_Menu_*, void*);
  static void cb_menueintrag_Voll(Fl_Menu_*, void*);
public:
  static Fl_Menu_Item *menu_einstellungen;
  static Fl_Menu_Item *menueintrag_oyranos;
private:
  void cb_menueintrag_oyranos_i(Fl_Menu_*, void*);
  static void cb_menueintrag_oyranos(Fl_Menu_*, void*);
public:
  static Fl_Menu_Item *menueintrag_lang;
private:
  void cb_menueintrag_lang_i(Fl_Menu_*, void*);
  static void cb_menueintrag_lang(Fl_Menu_*, void*);
public:
  static Fl_Menu_Item *menueintrag_3D;
private:
  void cb_menueintrag_3D_i(Fl_Menu_*, void*);
  static void cb_menueintrag_3D(Fl_Menu_*, void*);
public:
  static Fl_Menu_Item *menueintrag_inspekt;
private:
  void cb_menueintrag_inspekt_i(Fl_Menu_*, void*);
  static void cb_menueintrag_inspekt(Fl_Menu_*, void*);
public:
  static Fl_Menu_Item *menueintrag_zeigcgats;
private:
  void cb_menueintrag_zeigcgats_i(Fl_Menu_*, void*);
  static void cb_menueintrag_zeigcgats(Fl_Menu_*, void*);
public:
  static Fl_Menu_Item *menueintrag_vcgt;
private:
  void cb_menueintrag_vcgt_i(Fl_Menu_*, void*);
  static void cb_menueintrag_vcgt(Fl_Menu_*, void*);
public:
  static Fl_Menu_Item *menueintrag_testkurven;
private:
  void cb_menueintrag_testkurven_i(Fl_Menu_*, void*);
  static void cb_menueintrag_testkurven(Fl_Menu_*, void*);
public:
  static Fl_Menu_Item *menu_hilfe;
private:
  void cb_About_i(Fl_Menu_*, void*);
  static void cb_About(Fl_Menu_*, void*);
  void cb_Help_i(Fl_Menu_*, void*);
  static void cb_Help(Fl_Menu_*, void*);
  void cb_License_i(Fl_Menu_*, void*);
  static void cb_License(Fl_Menu_*, void*);
public:
  Fl_Help_View *inspekt_html;
  Fl_Tile *examin;
  TagBrowser *tag_browser;
private:
  void cb_tag_browser_i(TagBrowser*, void*);
  static void cb_tag_browser(TagBrowser*, void*);
public:
  Fl_Group *ansichtsgruppe;
  Fl_Group *tabellengruppe;
  MftChoice *mft_choice;
private:
  void cb_mft_choice_i(MftChoice*, void*);
  static void cb_mft_choice(MftChoice*, void*);
public:
  TagDrawings *mft_viewer;
  TagTexts *mft_text;
private:
  void cb_mft_text_i(TagTexts*, void*);
  static void cb_mft_text(TagTexts*, void*);
public:
  Fl_Group *mft_gl_group;
  GL_Ansicht *mft_gl;
  Fl_Pack *mft_gl_button_pack;
  Fl_Button *mft_gl_alltables_button;
private:
  void cb_mft_gl_alltables_button_i(Fl_Button*, void*);
  static void cb_mft_gl_alltables_button(Fl_Button*, void*);
public:
  Fl_Pack *twoD_pack;
  TagTexts *tag_text;
private:
  void cb_tag_text_i(TagTexts*, void*);
  static void cb_tag_text(TagTexts*, void*);
public:
  TagDrawings *tag_viewer;
  Fl_Box *box_stat;
  Fl_Progress *load_progress;
  My_Fl_Box *no_box;
  int run(int argc, char** argv);
  std::vector<std::string> open_veraltet(std::vector<std::string> dateinamen);
  void quit(void);
  void zeig_mich_(void* widget);
  void measurement(bool has_measurement);
private:
  Fl_Button ** mft_gl_tables_buttons;
public:
  void mft_gl_boxAdd( const char ** names_short, const char** names, int n, int actual );
};
void dHaendler(void* o);
void initHilfe();
#endif
