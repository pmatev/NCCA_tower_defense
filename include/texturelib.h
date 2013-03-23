#ifndef TEXTURELIB_H
#define TEXTURELIB_H

#include <map>
#include <string>
#include "texture.h"

class TextureLib
{
public:
    //-------------------------------------------------------------------//
    /// @brief instances the singleton
    //-------------------------------------------------------------------//
    static TextureLib* instance();

    //-------------------------------------------------------------------//
    /// @brief destroys the singleton
    //-------------------------------------------------------------------//
    void destroy();

    //-------------------------------------------------------------------//
    /// @brief initialises the texture lib.
    //-------------------------------------------------------------------//
    void init();



    void bindTexture(const std::string &_name);

    void bindTexture(const GLuint &_id);

    void load(const std::string &_name, const std::string &_file);

    void createTexture(const std::string &_name);
    void loadTexture(const std::string &_name, const std::string &_file);

    inline TextureWPtr getTexture(const std::string &_name){return m_mapTextures[_name];}


private:
    //-------------------------------------------------------------------//
    /// @brief ctor
    //-------------------------------------------------------------------//
    TextureLib();
    //-------------------------------------------------------------------//
    /// @brief dtor
    //-------------------------------------------------------------------//
    ~TextureLib();

    //-------------------------------------------------------------------//
    /// @brief static singleton variable
    //-------------------------------------------------------------------//
    static TextureLib* s_instance;

    std::map<std::string, TexturePtr> m_mapTextures;

    std::string m_boundTexture;

};

#endif // TEXTURELIB_H
