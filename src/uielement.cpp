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

    m_transformStack;
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
    m_pos += _pos;
}


void UIElement::generateMesh()
{
  const static GLubyte indices[]= {
                                    0,1,2,
                                    2,1,3
                                  };

  GLfloat vertices[] = {0,0,-10,
                        0,10,-10,
                        10,0,-10,
                        10,10,-10,
                       };
  GLfloat normals[] = { 0,1,1,
                        0,0,1,
                        1,0,1,
                        1,1,1,
                       };

  std::vector<vertData> quad;
  vertData d;
  for(int j=0; j<4; j++)
  {
    d.x = vertices[j*3];
    d.y = vertices[(j*3)+1];
    d.z = vertices[(j*3)+2];
    d.nx = normals[j*3];
    d.ny = normals[(j*3)+1];
    d.nz = normals[(j*3)+2];

    quad.push_back(d);
  }


  Renderer *render = Renderer::instance();

  render->createVAO(m_IDStr, GL_TRIANGLES);

  render->setIndexedDataToVAO(
        m_IDStr,
        sizeof(vertData)*quad.size(),
        quad[0].x,
        sizeof(indices),
        &indices[0],
        sizeof(indices)/sizeof(GLubyte)
        );
}


//-------------------------------------------------------------------//


std::string UIElement::getImagefile()
{
    return m_imageFile;
}


UIElement::~UIElement()
{

}
