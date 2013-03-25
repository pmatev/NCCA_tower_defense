#ifndef FWD_UIELEMENT_H
#define FWD_UIELEMENT_H

#include "smartpointers.h"

DECLARESMART(UIElement)

enum ElementType
{
    TABLE,
            WINDOW,
            BUTTON,
            CREATEBUTTON,
            UPGRADEBUTTON,
            IMAGE,
            SELLBUTTON,
            TEXT
};

#endif // UIELEMENT_H
