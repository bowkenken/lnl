//WINDOW BUILDER PROJECT MASTER SRC//
#include <WScom.h>
#include <WSDappDev.h>
#include <WSCbaseList.h>

#include <WSClocaleSet.h>

#ifdef MSW
WS_WINMAIN
#endif

char* mou[] = {
WS_DEFAULT_MOUSE_ID,
NULL};

void _mouse_init_(){
  WSGFloadMouseCursorData(mou);
}

char* fon[] = {
"14 * 0 0 ",
"16 iso8859 * * * r *",
"18 iso8859 * * * r *",
"20 iso8859 * * * r *",
"22 iso8859 * * * r *",
"24 iso8859 * * * r *",
"26 iso8859 * * * r *",
"30 iso8859 * * * r *",
NULL};

void _font_init_(){
  WSGFloadFontData(fon);
}
class _init_app_class_{
  public: _init_app_class_(){
    WSGFdeviceInitialize();
    WSGIappDev()->setInitHandler(_font_init_);
    WSGIappDev()->setInitHandler(_mouse_init_);
    WSDappDev* app = WSGIappDev();
    app->setInstanceName("xlnl-ws");
  };
};
static _init_app_class_ _execute_app_class_;

//--- OBJECT execute auto initialize ---//
extern WSDLEX WSCbase* _create_win_MapWin();
class _initialize_window_0{
 public: _initialize_window_0(){
  WSGIappDev()->setInitHandler((void(*)())_create_win_MapWin);
 };
};
static _initialize_window_0 _execute_initialize_0;

