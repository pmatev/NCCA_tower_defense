#include "button.h"

//-------------------------------------------------------------------//

void Button::execute()

{
    m_executeFunction();

}

//-------------------------------------------------------------------//

void Button::setExecuteFunction(void (*_funcToCall)())

{
    m_executeFunction = _funcToCall;
}

//-------------------------------------------------------------------//
