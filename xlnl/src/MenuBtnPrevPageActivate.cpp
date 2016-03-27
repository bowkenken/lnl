#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>

#include <WSDmouse.h>

#include "GlobalVar.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void MenuBtnPrevPageActivate(WSCbase* object){
  //do something...
	WSDmouse *mouse = WSGIappMouse();

	if( mouse->getTargetBtn() & WS_MOUSE_BTN1 ){
		gKey.setString( "4" );
	} else if( mouse->getTargetBtn() & WS_MOUSE_BTN3 ){
		gKey.setString( "6" );
	}
}
static WSCfunctionRegister  op("MenuBtnPrevPageActivate",(void*)MenuBtnPrevPageActivate);
