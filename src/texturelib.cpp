#include "include/texturelib.h"
#include "QImage"
#include <iostream>

TextureLib* TextureLib::s_instance = 0;
//-------------------------------------------------------------------//
TextureLib::TextureLib()
{
}
//-------------------------------------------------------------------//
TextureLib::~TextureLib()
{
}
//-------------------------------------------------------------------//

TextureLib* TextureLib::instance()
{
    if(s_instance == 0)
    {
        s_instance = new TextureLib();
    }
    return s_instance;
}
//-------------------------------------------------------------------//
void TextureLib::destroy()
{
    if(s_instance)
    {
        delete s_instance;
    }
}
//-------------------------------------------------------------------//
void TextureLib::init()
{
    load("debug", "textures/default_texture.png");
    load("healthbar", "textures/HealthBar_flat.png");
    load("noMoneyButton","textures/noMoney.png");
}
//-------------------------------------------------------------------//
void TextureLib::load(const std::string &_name, const std::string &_file)
{
    Texture t(_file);

    m_mapTextureIDs[_name] = t.getID();

}
//-------------------------------------------------------------------//
void TextureLib::bindTexture(const std::string &_name)
{
    if(m_mapTextureIDs[_name])
    {
        glBindTexture(GL_TEXTURE_2D, m_mapTextureIDs[_name]);
        m_boundTexture = _name;
    }
    else
    {
        std::cout<<"Couldn't bind texture "<<_name<<std::endl;
    }
}
//-------------------------------------------------------------------//
void TextureLib::bindTexture(const GLuint &_id)
{
    glBindTexture(GL_TEXTURE_2D, _id);
}

