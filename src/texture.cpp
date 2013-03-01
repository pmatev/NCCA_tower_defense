#include "include/texture.h"
#include <iostream>

Texture::Texture()
{
}
Texture::Texture(const std::string &_file):
    m_filepath(_file)
{
    load(_file);
}
Texture::~Texture()
{
    delete m_data;
}
bool Texture::load(const std::string &_file)
{
    m_filepath = _file;

    std::cout<<"loading texture: "<<_file<<std::endl;
    QImage *image = new QImage();
    bool loaded=image->load(_file.c_str());
    if(loaded == true)
    {
      m_width=image->width();
      m_height=image->height();
      m_hasAlpha=image->hasAlphaChannel();
      if(m_hasAlpha == true)
      {
        m_bpp=4;
        m_format = GL_RGBA;
      }
      else
      {
        m_bpp=3;
        m_format = GL_RGB;
      }

      m_data = new unsigned char[ m_width*m_height*m_bpp];
      unsigned int index=0;
      QRgb colour;
      for(unsigned int y=m_height-1; y>0; y--)
      {
        for(unsigned int x=0; x<m_width; ++x)
        {
          colour=image->pixel(x,y);

          m_data[index++]=qRed(colour);
          m_data[index++]=qGreen(colour);
          m_data[index++]=qBlue(colour);
          if(m_hasAlpha)
          {
            m_data[index++]=qAlpha(colour);
          }
        }
      }

      std::cout<<"Image size ="<<m_width<<"x"<<m_height<<std::endl;

      // generates the opengl texture and assigns m_id
      generateGLTex();

      return true;

    }
    else return false;
}

void Texture::generateGLTex()
{
    glGenTextures(1, &m_id);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D,0,m_format,m_width,m_height,0,m_format,GL_UNSIGNED_BYTE,m_data);
    glGenerateMipmapEXT(GL_TEXTURE_2D); //  Allocate the mipmaps

    glBindTexture(GL_TEXTURE_2D, 0);

}
