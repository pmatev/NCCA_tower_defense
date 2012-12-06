#ifndef UIELEMENT_H
#define UIELEMENT_H

#include <ngl/Vec2.h>
#include <boost/function.hpp>
#include"smartpointers.h"

DECLARESMART(UIElement)

//-------------------------------------------------------------------//
/// @file uielement.h
/// @brief The  base class for all elements which make up the interface
/// @author Luke Gravett
/// @version 1
/// @date 28/11/12
/// Revision History :
/// Initial Version 28/11/12
/// @class UIElement
//-------------------------------------------------------------------//

class UIElement



{

public:

    typedef  boost::function<void()> functionPtr;
    //-------------------------------------------------------------------//
    /// @brief a parameterised constructor
    /// @param [in] _pos, a Vec2 value for the starting position of the
    /// button
    /// @param [in] _imageFile, a string containing the image file path name
    /// @param [in] inputs a string for the name of the element
    //-------------------------------------------------------------------//
    UIElement( ngl::Vec2 _pos,
               std::string _imageFile,
               std::string _name);

    //-------------------------------------------------------------------//
    /// @brief the destructor
    //-------------------------------------------------------------------//
    ~UIElement();


    //-------------------------------------------------------------------//
    /// @brief virtual draw function passed through to other elements
    //-------------------------------------------------------------------//
    virtual void draw() const = 0;

    //virtual void generateMesh() =0;

    virtual void drawSelection() = 0;

    //-------------------------------------------------------------------//
    /// @brief virtual execute function passed through to other elements
    /// only elements which can interact with user will have anything
    /// implemeneted in it
    //-------------------------------------------------------------------//

    virtual void isClicked() = 0;

    //-------------------------------------------------------------------//
    /// @brief sets the position of the button
    /// @param [in] takes in an vector for position
    //-------------------------------------------------------------------//
    void setPosition(ngl::Vec2 _pos);

    //-------------------------------------------------------------------//
    /// @brief gets the name of the element
    /// @param [out] returns the name of the element
    //-------------------------------------------------------------------//
    inline const std::string getName() {return m_name;}

    //-------------------------------------------------------------------//
    /// @brief sets the function to run
    /// @param [in] takes in a boost::function
    //-------------------------------------------------------------------//
    virtual void setFunction(functionPtr _func) = 0;


    //-------------------------------------------------------------------//
    /// @brief converts the percentage values
    /// @param [in] takes in a boost::function
    //-------------------------------------------------------------------//
    void percentageToPixels(int _maxX);


    std::string getImagefile();




protected:

    //-------------------------------------------------------------------//
    /// @brief position of uielement in 2d space
    //-------------------------------------------------------------------//
    ngl::Vec2 m_pos;

    //-------------------------------------------------------------------//
    /// @brief image file used for the button
    //-------------------------------------------------------------------//
    std::string m_imageFile;

    //-------------------------------------------------------------------//
    /// @brief stores the elements function
    //-------------------------------------------------------------------//
    functionPtr m_execute;

    //-------------------------------------------------------------------//
    /// @brief ID used to query whether it has been clicked or not
    //-------------------------------------------------------------------//
    unsigned int m_ID;

    //-------------------------------------------------------------------//
    /// @brief stores the maximum size in x direction can either be percentage
    /// or pixel value. Will be relative to size of menu
    //-------------------------------------------------------------------//
    float m_maxBoundsX;

    //-------------------------------------------------------------------//
    /// @brief stores the maximum size in y direction can either be percentage
    /// or pixel value. Will be relative to size of menu
    //-------------------------------------------------------------------//
    float m_maxBoundsY;

    //-------------------------------------------------------------------//
    /// @brief stores the name of the element
    //-------------------------------------------------------------------//
    std::string m_name;
};


#endif // UIELEMENT_H
