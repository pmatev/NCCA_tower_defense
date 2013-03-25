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
    /// @param [in] _pos intial position of text
    /// @param [in] _text text to be displayed
    /// @param [in] _fontFile string with path to fontFile
    /// @param [in] _ptsize size of font
    /// @param [in] _name name of text element
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
    /// @param[in] _fontFile file of text
    /// @param[in] _ptsize size of font
    //-------------------------------------------------------------------//
    void setFont(const char *_fontFile, int _ptsize);

    //-------------------------------------------------------------------//
    /// @brief set colour
    /// @param[in] _rvalue red component of the colour
    /// @param[in] _gvalue green component of the colour
    /// @param[in] _bvalue blue component of the colour
    /// @param[in] _avalue alpha component of the colour
    //-------------------------------------------------------------------//
    void setColour(char _rvalue, char _gvalue, char _bvalue, char _avalue);

    //-------------------------------------------------------------------//
    /// @brief draw function for text
    //-------------------------------------------------------------------//
    void draw();

    //-------------------------------------------------------------------//
    /// @brief generates VAO object to be used for drawing the text
    //-------------------------------------------------------------------//
    virtual void generateMesh();

    //-------------------------------------------------------------------//
    /// @brief sets the texts text and generates its mesh
    /// @param [in] _text the text too be displayed
    //-------------------------------------------------------------------//
    inline void setText(const char *_text) {m_text =_text;
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
    /// @brief sdl surface which is used to generate the text
    //-------------------------------------------------------------------//
    SDL_Surface *m_textSurface;

    //-------------------------------------------------------------------//
    /// @brief contains text to be rendered
    //-------------------------------------------------------------------//
    const char *m_text;

    //-------------------------------------------------------------------//
    /// @brief stores the textures id
    //-------------------------------------------------------------------//
    GLuint m_textureID;

};




#endif // TEXT_H
