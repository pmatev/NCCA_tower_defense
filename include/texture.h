#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include "ngl/Types.h"
#include "smartpointers.h"

DECLARESMART(Texture)


class Texture
{
public:

    static TexturePtr create(const std::string &_name);
    static TexturePtr create(const std::string &_name, const std::string &_file);

    ~Texture();

    bool load(const std::string &_file);

    GLuint getID() const {return m_id;}
    GLuint getWidth() const {return m_width;}
    GLuint getHeight() const {return m_height;}
    std::string getFilePath() const {return m_filepath;}
    void loadData(const int _width, const int _height, const int _bpp, const void *_data);

    void setWrap(GLenum _wrap);
    inline GLenum getWrap(){return m_wrap;}

protected:
    Texture(const std::string &_name);
    Texture(const std::string &_name, const std::string &_file);


    void generateGLTex();

    std::string m_name;

    std::string m_filepath;

    GLenum m_wrap;

    std::vector<unsigned char> m_data;

    GLuint m_width;

    GLuint m_height;

    bool m_hasAlpha;

    GLuint m_bpp;

    GLenum m_format;

    // id assigned when opengl glGenTextures() is called
    GLuint m_id;


};

#endif // TEXTURE_H
