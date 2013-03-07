#ifndef CREATETOWERBUTTON_H
#define CREATETOWERBUTTON_H

#include "smartpointers.h"
#include "uibutton.h"


//-------------------------------------------------------------------//
/// @file createbutton.h
/// @brief specific type of button used only for creating towers,
/// inherits from uibutton class
/// @author Luke Gravett
/// @version 1
/// @date 25/02/13
/// Revision History :
/// Initial Version 25/02/13
/// @class createButton
//-------------------------------------------------------------------//

DECLARESMART(CreateTowerButton)

class CreateTowerButton : public UIButton
{
public:

    //-------------------------------------------------------------------//
    /// @brief a parameterised constructor
    /// @param [in] _pos, a Vec2 value for the starting position of the
    /// button
    /// @param [in] _imageFile, a string containing the image file path name
    /// @param [in] inputs a string for the name of the element
    /// @param [in] inputs the cost of the tower being created
    /// @param [in] the user money value at the time used to check if it is
    /// affordable or not
    /// @param [in] string for towerType to build
    /// @param [in] max x size of button
    /// @param [in] max y size of button
    //-------------------------------------------------------------------//
    CreateTowerButton
            (
                ngl::Vec2 _pos,
                std::string _imageFile,
                std::string _name,
                TablePtr _parent,
                int _cost,
                std::string _towerType,
                float _maxX,
                float _maxY
                );

    //-------------------------------------------------------------------//
    /// @brief default destructor
    //-------------------------------------------------------------------//
    ~CreateTowerButton();

    //-------------------------------------------------------------------//
    /// @brief checks to see if the tower can be bought if not it switches the
    /// the flag to false
    //-------------------------------------------------------------------//
    void checkAffordable();

    //-------------------------------------------------------------------//
    /// @brief gets the affordable flag
    /// @param [out] returns m_affordable bool
    //-------------------------------------------------------------------//
    inline bool getAffordable() {
        return m_affordable;}

    //-------------------------------------------------------------------//
    /// @brief gets the cost of turret
    /// @param [out] returns m_m_cost int
    //-------------------------------------------------------------------//
    inline int getCost() {return m_cost;}

    //-------------------------------------------------------------------//
    /// @brief gets the type of turret to create
    /// @param [out] returns m_m_towertype
    //-------------------------------------------------------------------//
    inline std::string getTowertype() {return m_towerType;}


protected:
    //-------------------------------------------------------------------//
    /// @brief cost of turret
    //-------------------------------------------------------------------//
    int m_cost;

    //-------------------------------------------------------------------//
    /// @brief flag for drawing to say whether it can be bought or not
    //-------------------------------------------------------------------//
    bool m_affordable;

    //-------------------------------------------------------------------//
    /// @brief stores which tower type to create
    //-------------------------------------------------------------------//
    std::string m_towerType;

};



#endif // CREATETOWERBUTTON_H