#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>

#include <WSDmouse.h>

#include "GlobalVar.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void MenuBtnCancelActivate(WSCbase* object){
  //do something...
	WSDmouse *mouse = WSGIappMouse();

	if( mouse->getTargetBtn() & WS_MOUSE_BTN1 ){
		gKey.setString( "0" );
	} else if( mouse->getTargetBtn() & WS_MOUSE_BTN3 ){
		gKey.setString( "0" );
	}
}
static WSCfunctionRegister  op("MenuBtnCancelActivate",(void*)MenuBtnCancelActivate);
