#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void InpStrWinInit(WSCbase* object){
  //do something...
}
static WSCfunctionRegister  op("InpStrWinInit",(void*)InpStrWinInit);
