#ifndef UIELEMENT_H
#define UIELEMENT_H

#include <ngl/TransformStack.h>
#include <boost/function.hpp>
#include"smartpointers.h"
#include <QString>
#include "texture.h"
#include "billboard.h"
#include "fwd/uielement.h"


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

    //-------------------------------------------------------------------//
    /// @brief a parameterised constructor
    /// @param [in] _pos, a Vec2 value for the starting position of the
    /// button
    /// @param [in] _name name of element
    /// @param [in] _type type of element being created
    /// @param [in] _imageFile, a string containing the image file path name
    //-------------------------------------------------------------------//

    /* ADD ID TO CONSTRUCTOR + SETUP RELEVANT SYSTEMS */
    UIElement( ngl::Vec2 _pos,
               std::string _name,
               ElementType _type,
               std::string _imageFile
              );


    //-------------------------------------------------------------------//
    /// @brief the destructor
    //-------------------------------------------------------------------//
    ~UIElement();

    //-------------------------------------------------------------------//
    /// @brief virtual draw function passed through to other elements
    //-------------------------------------------------------------------//
    virtual void draw();

    //-------------------------------------------------------------------//
    /// @brief virtual draw selection function passed through to other
    /// elements which will implement it. This draw function will draw
    /// the menus with a colour which will then be used for selection
    /// purposes
    //-------------------------------------------------------------------//
    virtual void generateMesh();

    //-------------------------------------------------------------------//
    /// @brief sets the position of the element
    /// @param [in] _pos takes in an vector for position
    //-------------------------------------------------------------------//
    virtual void setPosition(ngl::Vec2 _pos);

    //-------------------------------------------------------------------//
    /// @brief sets the size of the element
    /// @param [in] _size takes in an vector for size
    //-------------------------------------------------------------------//
    virtual void setSize(ngl::Vec2 _size) {m_size =_size;}

    //-------------------------------------------------------------------//
    /// @brief gets the name of the element
    //-------------------------------------------------------------------//
    inline const std::string getName() {return m_name;}

    //-------------------------------------------------------------------//
    /// @brief returns the m_type variable
    //-------------------------------------------------------------------//
    inline ElementType getType() {return m_type;}

    //-------------------------------------------------------------------//
    /// @brief sets the elements id value
    /// @param [in] _ID takes in an id value given by window
    //-------------------------------------------------------------------//
    void setID(unsigned int _ID) ;

    //-------------------------------------------------------------------//
    /// @brief returns the elements id
    //-------------------------------------------------------------------//
    inline unsigned int getID() {return m_ID;}

    //-------------------------------------------------------------------//
    /// @brief get function for max x
    //-------------------------------------------------------------------//
    inline ngl::Vec2 getSize() {return m_size;}

    //-------------------------------------------------------------------//
    /// @brief get function for position
    //-------------------------------------------------------------------//
    inline ngl::Vec2 getPosition() {return m_pos;}

    //-------------------------------------------------------------------//
    /// @brief setter function for texture
    /// @param [in] _texture string containing texure name
    //-------------------------------------------------------------------//
    virtual inline void setTexture(std::string _texture) {m_imageFile = _texture;}

    //-------------------------------------------------------------------//
    /// @brief set function to set the elements rest Position
    /// @param [in] _restPos used to set m_restPosition
    //-------------------------------------------------------------------//
    inline void setRestPosition(ngl::Vec2 _restPos){m_restPosition = _restPos;}

    //-------------------------------------------------------------------//
    /// @brief gets the m_restPosition variable
    //-------------------------------------------------------------------//
    inline ngl::Vec2 getRestPosition(){return m_restPosition;}

    //-------------------------------------------------------------------//
    /// @brief gets the m_imageFile variable
    //-------------------------------------------------------------------//
    inline std::string getTexture() {return m_imageFile;}

    //-------------------------------------------------------------------//
    /// @brief sets the m_tileable flag
    /// @param [in] _tile bool to state whether the elements texture is
    /// to be tiled or not
    //-------------------------------------------------------------------//
    inline void setTileable(bool _tile) {m_tileable = _tile;}



protected:
    //-------------------------------------------------------------------//
    /// @brief stores the name of the element
    //-------------------------------------------------------------------//
    std::string m_name;

    //-------------------------------------------------------------------//
    /// @brief position of uielement in 2d space
    //-------------------------------------------------------------------//
    ngl::Vec2 m_pos;

    //-------------------------------------------------------------------//
    /// @brief ID used to query whether it has been clicked or not
    //-------------------------------------------------------------------//
    unsigned int m_ID;

    //-------------------------------------------------------------------//
    /// @brief string version of ID used for openGL
    //-------------------------------------------------------------------//
    std::string m_IDStr;

    //-------------------------------------------------------------------//
    /// @brief enum representing the type of element it is
    //-------------------------------------------------------------------//
    ElementType m_type;

    //-------------------------------------------------------------------//
    /// @brief stores the maximum size in x direction can either be percentage
    /// or pixel value. Will be relative to size of menu
    //-------------------------------------------------------------------//
    ngl::Vec2 m_size;

    //-------------------------------------------------------------------//
    /// @brief string containing image file location
    //-------------------------------------------------------------------//
    std::string m_imageFile;

    //-------------------------------------------------------------------//
    /// @brief the position which is classed as the elements rest or
    /// default position
    //-------------------------------------------------------------------//
    ngl::Vec2 m_restPosition;

    //-------------------------------------------------------------------//
    /// @brief shared pointer to the elements billboard
    //-------------------------------------------------------------------//
    BillboardPtr m_billboard;

    //-------------------------------------------------------------------//
    /// @brief states whether the elments texture is tileable
    //-------------------------------------------------------------------//
    bool m_tileable;

};


#endif // UIELEMENT_H
