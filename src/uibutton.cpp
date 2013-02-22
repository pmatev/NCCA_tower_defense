#include "uibutton.h"
#include "renderer.h"
#include "uimenu.h"
#include "ngl/ShaderLib.h"
#include "window.h"


//-------------------------------------------------------------------//
UIButton::UIButton(ngl::Vec2 _pos,
                   std::string _imageFile,
                   std::string _name,
                   UIMenu *_parent):

  UIElement( _pos, _name),
  m_parent(_parent),
  m_imageFile(_imageFile)

{

}



//-------------------------------------------------------------------//


UIButton::~UIButton()
{
    std::cout<<"button dtor called"<<std::endl;

}


//-------------------------------------------------------------------//

void UIButton::generateMesh()
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

    GLuint textureID;
    glGenTextures(1,&textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
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

  d[1].x=200.0f;
  d[1].y=0.0f;
  d[1].u=1.0f;
  d[1].v=0.0f;

  d[2].x=0.0f;
  d[2].y=200.0f;
  d[2].u=0.0f;
  d[2].v=1.0f;

  d[3].x=0.0f;
  d[3].y=200.0f;
  d[3].u=0.0f;
  d[3].v=1.0f;

  d[4].x=200.0f;
  d[4].y=0.0f;
  d[4].u=1.0f;
  d[4].v=0.0f;

  d[5].x=200.0f;
  d[5].y=200.0f;
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


void UIButton::draw()
{
//  ngl::Transformation parentTX = m_parent->getTransformStack().getCurrentTransform();
//  m_transformStack.setGlobal(parentTX);
//  m_transformStack.pushTransform();
//    m_transformStack.setPosition(1.0,0.0,-1.0);
//  m_transformStack.popTransform();

  Renderer *render = Renderer::instance();
  Window *window = Window::instance();
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();

  VAOPtr v = render->getVAObyID(m_IDStr);
  (*shader)["UI"]->use();
//    (*shader)["Colour"]->use();

//  render->loadMatrixToShader(m_transformStack,"Colour");

//  shader->setRegisteredUniform3f("Colour",1,1,1);

  float scaleX = 2.0/window->getScreenWidth();
  float scaleY = 2.0/window->getScreenHeight();

  shader->setShaderParam1f("xpos",m_pos.m_x);
  shader->setShaderParam1f("ypos",m_pos.m_y);
  shader->setShaderParam1f("scaleX",scaleX);
  shader->setShaderParam1f("scaleY",scaleY);



  v->bind();
  v->draw();
  v->unbind();

//  std::cout<<"drawing button "<<m_name<<" "<<m_pos<<std::endl;
}


//-------------------------------------------------------------------//

void UIButton::drawSelection()
{
  Renderer *r = Renderer::instance();
  //r->loadMatrixToShaderSS(m_transformStack, "Colour");
  r->drawSelection(m_ID, m_IDStr);
}
