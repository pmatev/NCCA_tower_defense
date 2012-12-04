#ifndef BUTTON_H
#define BUTTON_H

#include "smartpointers.h"
#include "uielement.h"

//-------------------------------------------------------------------//
/// @file button.h
/// @brief The button class used for ui buttons to run function,
/// inherits from uielement class
/// @author Luke Gravett
/// @version 1
/// @date 03/12/12
/// Revision History :
/// Initial Version 03/12/12
/// @class Database
//-------------------------------------------------------------------//

DECLARESMART(Button)

class Button : public UIElement

{
public:

    Button();

    ~Button();

    void execute();

    void setExecuteFunction(void (*_executeFunction)());


protected:

    typedef void (*function_type)();

    function_type m_executeFunction;


};

#endif // BUTTON_H
