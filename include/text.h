#ifndef TEXT_H
#define TEXT_H

#include <SDL_ttf.h>
#include <string>
#include "ngl/VertexArrayObject.h"
#include "ngl/Types.h"
#include "ngl/Vec2.h"
#include "smartpointers.h"
#include "uielement.h"

//-------------------------------------------------------------------//
/// @file text.h
/// @brief This class defines text objects which can be drawn to screen
/// @author Luke Gravett
/// @version 1
/// @date 25/02/13
/// Revision History :
/// Initial Version 25/02/13
/// @class Text
//-------------------------------------------------------------------//

DECLARESMART(Text)

class Text : public UIElement

{


public:

    //-------------------------------------------------------------------//
    /// @brief constructor
    //-------------------------------------------------------------------//
    Text
            (
                ngl::Vec2 _pos,
                const char *_text,
                const char *_fontFile,
                int _ptsize,
                std::string _name
                );

    //-------------------------------------------------------------------//
    /// @brief default destructor
    //-------------------------------------------------------------------//
    ~Text();

    //-------------------------------------------------------------------//
    /// @brief loads the font to the text
    /// @param[in] file of text
    /// @param[in] size of font
    //-------------------------------------------------------------------//
    void setFont(const char *_fontFile, int _ptsize);

    //-------------------------------------------------------------------//
    /// @brief set colour
    /// @param[in] array of char values for RGBA
    //-------------------------------------------------------------------//
    void setColour(char _rvalue, char _gvalue, char _bvalue, char _avalue);

    //-------------------------------------------------------------------//
    /// @brief set background colour
    /// @param[in] array of char values for RGBA
    //-------------------------------------------------------------------//
    void setBackgroundColour
            (
                char _rvalue,
                char _gvalue,
                char _bvalue,
                char _avalue
                );

    //-------------------------------------------------------------------//
    /// @brief draw function for text
    //-------------------------------------------------------------------//
    void draw();

    //-------------------------------------------------------------------//
    /// @brief generates VAO object to be used for drawing the text
    //-------------------------------------------------------------------//
    void generateMesh();

    inline void setText(const char *_text) {m_text =_text;
                                           generateMesh();}

    inline void setTexture(std::string _texture) {m_imageFile = _texture;
                                                     generateMesh();}


private:

    //-------------------------------------------------------------------//
    /// @brief stores the font itself
    //-------------------------------------------------------------------//
    TTF_Font* m_font;

    //-------------------------------------------------------------------//
    /// @brief colour of text
    //-------------------------------------------------------------------//
    SDL_Color m_colour;

    //-------------------------------------------------------------------//
    /// @brief colour of background if shaded is picked for renderQuality
    //-------------------------------------------------------------------//
    SDL_Color m_bgColour;

    //-------------------------------------------------------------------//
    /// @brief string version of ID used for openGL
    //-------------------------------------------------------------------//
    SDL_Surface *m_textSurface;

    //-------------------------------------------------------------------//
    /// @brief contains text to be rendered
    //-------------------------------------------------------------------//
    const char *m_text;

    //-------------------------------------------------------------------//
    /// @brief
    //-------------------------------------------------------------------//
    GLuint m_textureID;

};




#endif // TEXT_H
