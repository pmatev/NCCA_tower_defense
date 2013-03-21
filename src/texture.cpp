#include "include/texture.h"
#include <iostream>


TexturePtr Texture::create(const std::string &_name)
{
  TexturePtr a(new Texture(_name));
  return a;
}
//-------------------------------------------------------------------//
TexturePtr Texture::create( const std::string &_name,
                            const std::string &_file)
{
  TexturePtr a(new Texture(_name,_file));
  return a;
}
//-------------------------------------------------------------------//

Texture::Texture(const std::string &_name):
    m_name(_name)
{
    generateGLTex();
}
//-------------------------------------------------------------------//
Texture::Texture(const std::string &_name, const std::string &_file):
    m_name(_name),
    m_filepath(_file)
{
    generateGLTex();
    load(_file);
}
//-------------------------------------------------------------------//
Texture::~Texture()
{
    glDeleteTextures(1,&m_id);
}
//-------------------------------------------------------------------//
bool Texture::load(const std::string &_file)
{
    // Based on Jon Macey's ngl::Texture //

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
      QRgb colour;
      m_data.resize(m_width*m_height*m_bpp);
      unsigned int index =0;
      for(unsigned int y=m_height-1; y>0; y--)
      {
        for(unsigned int x=0; x<m_width; ++x)
        {
          colour=image->pixel(x,y);

          m_data[index++] = qRed(colour);
          m_data[index++] = qGreen(colour);
          m_data[index++] = qBlue(colour);
          if(m_hasAlpha == true)
          {
            m_data[index++] = qAlpha(colour);
          }
        }
      }

      std::cout<<"Image size ="<<m_width<<"x"<<m_height<<std::endl;

      loadData(m_width, m_height, m_bpp, &m_data[0]);

      return true;

    }
    else return false;
}
//-------------------------------------------------------------------//
void Texture::generateGLTex()
{
    glGenTextures(1, &m_id);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, 0);

}
//-------------------------------------------------------------------//
void Texture::loadData(const int _width, const int _height, const int _bpp, const void *_data)
{
    glBindTexture(GL_TEXTURE_2D, m_id);

    if(_bpp == 4){m_format = GL_RGBA;}
    if(_bpp == 3){m_format = GL_RGB;}

    if(m_data.size()==0)
    {
        unsigned char *charBuf = (unsigned char *)_data;

        m_data.resize(_width*_height*_bpp);

        for(int i=0; i< _width*_height*_bpp; i++)
        {
            m_data[i] = charBuf[i];
        }
    }
    glTexImage2D(GL_TEXTURE_2D,0,m_format,_width,_height,0,m_format,GL_UNSIGNED_BYTE,_data);
    glGenerateMipmapEXT(GL_TEXTURE_2D); //  Allocate the mipmaps

    glBindTexture(GL_TEXTURE_2D, 0);
}
