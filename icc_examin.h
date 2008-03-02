// generated by Fast Light User Interface Designer (fluid) version 1.0104

#ifndef icc_examin_h
#define icc_examin_h
#include <FL/Fl.H>
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
#include <openvrml/browser.h>
#include <openvrml/gl/viewer.h>
#include "vFLGLWidget.h"
#include "ViewerFLTK.h"
#include <FL/Fl_Double_Window.H>
extern Fl_Double_Window *details;
#include <FL/Fl_Group.H>
#include <FL/Fl_Menu_Bar.H>
extern Fl_Menu_Bar *Fl_lookat_MenuBar;
#include <FL/Fl_Box.H>
extern Fl_Box *stat;
#include <FL/Fl_Progress.H>
extern Fl_Progress *load_progress;
#include <FL/Fl_Tile.H>
extern Fl_Hold_Browser *tag_browser;
extern Fl_Box *tag_viewer;
#include <FL/Fl_Text_Display.H>
extern Fl_Text_Display *tag_texts;
extern vFLGLWidget *canvas;
extern Fl_Menu_Item menu_Fl_lookat_MenuBar[];
#define Voll (menu_Fl_lookat_MenuBar+5)
#define normal_ansicht (menu_Fl_lookat_MenuBar+6)
const char* open(void);
void quit(void);
void worldChangedCB( const openvrml::browser::cb_reason reason );
void timeIT();
char* icc_read_info(char* filename);

class IccProfile {
public:
  char *data;
  char *filename;
  int size;
  void getChar(int type);
private:
  char* read_header();
};
#endif
