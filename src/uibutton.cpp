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
  glDisable(GL_DEPTH_TEST);

  Renderer *render = Renderer::instance();
  Window *window = Window::instance();
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();

  GLfloat scaleX = 2.0/window->getScreenWidth();
  GLfloat scaleY = 2.0/window->getScreenHeight();


  (*shader)["UI"]->use();
  shader->setRegisteredUniform1f("xpos",m_pos.m_x);
  shader->setRegisteredUniform1f("ypos",m_pos.m_y);
  shader->setRegisteredUniform1f("scaleX",scaleX);
  shader->setRegisteredUniform1f("scaleY",scaleY);

  ngl::Vec3 c = Window::instance()->IDToColour(m_ID);
  shader->setRegisteredUniform4f("colour", c.m_x/255.0f, c.m_y/255.0f, c.m_z/255.0f, 1);

  glBindTexture(GL_TEXTURE_2D, m_texture);
  render->draw(m_IDStr, "UI");

  glEnable(GL_DEPTH_TEST);
//  std::cout<<"drawing button "<<m_name<<" "<<m_pos<<std::endl;
}


//-------------------------------------------------------------------//

//void UIButton::drawSelection()
//{
//  Renderer *render = Renderer::instance();
//  Window *window = Window::instance();
//  ngl::ShaderLib *shader=ngl::ShaderLib::instance();

//  (*shader)["UIColour"]->use();

//  float scaleX = 2.0/window->getScreenWidth();
//  float scaleY = 2.0/window->getScreenHeight();

//  shader->setShaderParam1f("xpos",m_pos.m_x);
//  shader->setShaderParam1f("ypos",m_pos.m_y);
//  shader->setShaderParam1f("scaleX",scaleX);
//  shader->setShaderParam1f("scaleY",scaleY);

//  ngl::Vec3 c = Window::instance()->IDToColour(m_ID);
//  shader->setShaderParam4f("colour", c.m_x/255.0f, c.m_y/255.0f, c.m_z/255.0f, 1);

//  VAOPtr v = render->getVAObyID(m_IDStr);
//  v->bind();
//  v->draw();
//  v->unbind();

//}
