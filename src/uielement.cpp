#include "uielement.h"
#include "renderer.h"
#include <boost/lexical_cast.hpp>
#include <QImage>
//-------------------------------------------------------------------//

UIElement::UIElement(ngl::Vec2 _pos,
                     std::string _name,
                     std::string _type,
                     std::string _imageFile):
  m_name(_name),
  m_pos(_pos),
  m_type(_type),
  m_imageFile(_imageFile)
{
}

//-------------------------------------------------------------------//
void UIElement::setID(unsigned int _ID)
{
  m_ID = _ID;
  m_IDStr = boost::lexical_cast<std::string>(m_ID);
  generateMesh(); // SHOULDN'T BE HERE!! FIND A PLACE FOR HIM!
}

//-------------------------------------------------------------------//

void UIElement::setPosition(ngl::Vec2 _pos)
{
    m_pos = _pos;
}



//-------------------------------------------------------------------//
void UIElement::generateMesh()
{
  // Load Texture

  QImage *image = new QImage();
  const char *str = m_imageFile.c_str();
  bool loaded=image->load(str, "JPG");
  if(loaded == true)
  {
    int width=image->width();
    int height=image->height();

    unsigned char *data = new unsigned char[ width*height*3];
    unsigned int index=0;
    QRgb colour;
    for( int y=0; y<height; ++y)
    {
      for( int x=0; x<width; ++x)
      {
        colour=image->pixel(x,y);

        data[index++]=qRed(colour);
        data[index++]=qGreen(colour);
        data[index++]=qBlue(colour);
      }
    }

    glGenTextures(1,&m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);

    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
    glGenerateMipmapEXT(GL_TEXTURE_2D); //  Allocate the mipmaps
  }
  else
  {
    std::cerr<<"Couldn't load texture"<<std::endl;
  }

  // BUILD BILLBOARD
  struct quadVertData
  {
  float x;
  float y;
  float u;
  float v;
  };

  quadVertData d[6];

  d[0].x=0.0f;
  d[0].y=0.0f;
  d[0].u=0.0f;
  d[0].v=0.0f;

  d[1].x=m_size.m_x;
  d[1].y=0.0f;
  d[1].u=1.0f;
  d[1].v=0.0f;

  d[2].x=0.0f;
  d[2].y=m_size.m_y;
  d[2].u=0.0f;
  d[2].v=1.0f;

  d[3].x=0.0f;
  d[3].y=m_size.m_y;
  d[3].u=0.0f;
  d[3].v=1.0f;

  d[4].x=m_size.m_x;
  d[4].y=0.0f;
  d[4].u=1.0f;
  d[4].v=0.0f;

  d[5].x=m_size.m_x;
  d[5].y=m_size.m_y;
  d[5].u=1.0f;
  d[5].v=1.0f;

  Renderer *render = Renderer::instance();

  render->createVAO(m_IDStr, GL_TRIANGLES);

  VAOPtr v = render->getVAObyID(m_IDStr);
  v->bind();
  int size = sizeof(quadVertData);
  v->setData(6*size,d[0].x);
  v->setVertexAttributePointer(0,2,GL_FLOAT,size,0);
  v->setVertexAttributePointer(1,2,GL_FLOAT,size,2);
  v->setNumIndices(6);
  v->unbind();

}

//-------------------------------------------------------------------//


UIElement::~UIElement()
{

}
