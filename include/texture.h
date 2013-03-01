#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include "ngl/Types.h"

class Texture
{
public:
    Texture();
    Texture(const std::string &_file);
    ~Texture();

    bool load(const std::string &_file);

    GLuint getID() const {return m_id;}
    GLuint getWidth() const {return m_width;}
    GLuint getHeight() const {return m_height;}
    std::string getFilePath() const {return m_filepath;}

protected:
    void generateGLTex();

    std::string m_filepath;

    unsigned char *m_data;

    GLuint m_width;

    GLuint m_height;

    bool m_hasAlpha;

    GLuint m_bpp;

    GLenum m_format;

    // id assigned when opengl glGenTextures() is called
    GLuint m_id;


};

#endif // TEXTURE_H
