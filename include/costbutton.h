#ifndef COSTBUTTON_H
#define COSTBUTTON_H

#include "smartpointers.h"
#include "uibutton.h"


//-------------------------------------------------------------------//
/// @file costbutton.h
/// @brief specific type of button used only for any button which has
/// to check cost attributes i.e upgrade or create tower buttons inherits
/// from uibutton class
/// @author Luke Gravett
/// @version 1
/// @date 25/02/13
/// Revision History :
/// Initial Version 25/02/13
/// @class createButton
//-------------------------------------------------------------------//

DECLARESMART(CostButton)

class CostButton : public UIButton
{
public:

    //-------------------------------------------------------------------//
    /// @brief a parameterised constructor
    /// @param [in] _pos, a Vec2 value for the starting position of the
    /// button
    /// @param [in] _imageFile, a string containing the image file path name
    /// @param [in] _name inputs a string for the name of the element
    /// @param [in] _type type of element being created
    /// @param [in] _cost the user money value at the time used to check if it is
    /// affordable or not
    /// @param [in] _maxX max x size of button
    /// @param [in] _maxY max y size of button
    //-------------------------------------------------------------------//
    CostButton
            (
                ngl::Vec2 _pos,
                std::string _imageFile,
                std::string _name,
                ElementType _type,
                int _cost,
                float _maxX,
                float _maxY
                );

    //-------------------------------------------------------------------//
    /// @brief default destructor
    //-------------------------------------------------------------------//
    ~CostButton();

    //-------------------------------------------------------------------//
    /// @brief checks to see if the tower can be bought if not it switches the
    /// the flag to false
    //-------------------------------------------------------------------//
    void checkAffordable();

    //-------------------------------------------------------------------//
    /// @brief gets the affordable flag
    //-------------------------------------------------------------------//
    inline bool getAffordable() {
        return m_affordable;}

    //-------------------------------------------------------------------//
    /// @brief gets the cost of turret
    //-------------------------------------------------------------------//
    inline int getCost() {return m_cost;}

    //-------------------------------------------------------------------//
    /// @brief sets m_cost
    /// @param [in] _cost integer containg the cost
    //-------------------------------------------------------------------//
    inline void setCost(int _cost) {m_cost = _cost;}

protected:
    //-------------------------------------------------------------------//
    /// @brief cost of turret
    //-------------------------------------------------------------------//
    int m_cost;

    //-------------------------------------------------------------------//
    /// @brief flag for drawing to say whether it can be bought or not
    //-------------------------------------------------------------------//
    bool m_affordable;
};



#endif // COSTBUTTON_H
