#include "uielement.h"
#include "uiSelection.h"
#include "renderer.h"
#include "boost/lexical_cast.hpp"

//-------------------------------------------------------------------//

UIElement::UIElement(ngl::Vec2 _pos,
                     std::string _imageFile,
                     std::string _name):
  m_pos(_pos),
  m_imageFile(_imageFile),
  m_name(_name)

{
}


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



void UIElement::generateMesh()
{


  struct quadVertData
  {
  ngl::Real x;
  ngl::Real y;
  };
  // we are creating a billboard with two triangles so we only need the
  // 6 verts, (could use index and save some space but shouldn't be too much of an
  // issue
  quadVertData d[6];
  // load values for triangle 1
  d[0].x=0;
  d[0].y=0;

  d[1].x=100;
  d[1].y=0;

  d[2].x=0;
  d[2].y=100;

  d[3].x=0;
  d[3].y=100;


  d[4].x=100;
  d[4].y=0;

  d[5].x=100;
  d[5].y=100;


  Renderer *render = Renderer::instance();

  render->createVAO(m_IDStr, GL_TRIANGLES);

  VAOPtr v = render->getVAObyID(m_IDStr);
  v->bind();
  v->setData(6*sizeof(quadVertData),d[0].x);
  v->setVertexAttributePointer(0,2,GL_FLOAT,sizeof(quadVertData),0);
  v->setNumIndices(6);
  v->unbind();
}


//-------------------------------------------------------------------//


std::string UIElement::getImagefile()
{
    return m_imageFile;
}


UIElement::~UIElement()
{

}
