#include "ngl/ShaderLib.h"

#include "window.h"
#include "concrete/base.h"
#include "renderer.h"

//---TEST CODE (replace when generateMesh properly implemented)---//
#define PI 3.14159265

//-------------------------------------------------------------------//

Base::Base(
    NodePtr _linkedNode,
    unsigned int _id
    ) :
  StaticEntity(_linkedNode,BASE, _id)
{
  generateMesh();
  publish();

}

void Base::stateInit()
{

}

//-------------------------------------------------------------------//

BasePtr Base::create(NodePtr _linkedNode, unsigned int _id)
{
  BasePtr a = BasePtr(new Base(_linkedNode,_id));
  return a;
}

//-------------------------------------------------------------------//

void Base::update(const double _dt)
{
  //Q unused to remove warnings, will be replaced if used

  Q_UNUSED(_dt);
  // do something
}

//-------------------------------------------------------------------//

//void Base::draw()
//{
//  Renderer *r = Renderer::instance();
//  r->loadMatrixToShader(m_transformStack, "Phong");
//  r->draw(m_IDStr, "Phong");
//}

//-------------------------------------------------------------------//

//void Base::drawSelection()
//{
//  // do something
//}

//-------------------------------------------------------------------//

void Base::generateMesh()
{
  float m_hexagonSize = 2.0;
  const static GLubyte indices[]=  {
                                      0,1,5, // back
                                      1,2,3, // front
                                      3,4,5, // top
                                      1,3,5
                                   };

  GLfloat vertices[] = {-m_hexagonSize/2, 0.0, 0.0,
                        -m_hexagonSize/4, 0.0, std::cos(30*PI/180)*m_hexagonSize/2,
                        m_hexagonSize/4, 0.0, std::cos(30*PI/180)*m_hexagonSize/2,
                        m_hexagonSize/2, 0.0, 0.0,
                        m_hexagonSize/4, 0.0, -(std::cos(30*PI/180)*m_hexagonSize/2),
                        -m_hexagonSize/4, 0.0, -(std::cos(30*PI/180)*m_hexagonSize/2),
                       };
  GLfloat normals[] = {1,1,1,
                       1,1,1,
                       1,1,1,
                       1,1,1,
                       1,1,1,
                       1,1,1
                       };

  std::vector<Renderer::vertData> boxData;
  Renderer::vertData d;
  for(int j=0; j<12; j++)
  {
    d.x = vertices[j*3];
    d.y = vertices[(j*3)+1];
    d.z = vertices[(j*3)+2];
    d.nx = normals[j*3];
    d.ny = normals[(j*3)+1];
    d.nz = normals[(j*3)+2];

    boxData.push_back(d);
  }

  unsigned int vertSize = sizeof(Renderer::vertData);
  Renderer *render = Renderer::instance();

  render->createVAO(m_IDStr, GL_TRIANGLES);

  render->setIndexedDataToVAO(m_IDStr,
                              vertSize*boxData.size(),
                              3,
                              boxData[0].x,
                              sizeof(indices),
                              &indices[0],
                              12);

  generateLsBBox(boxData);
}

//-------------------------------------------------------------------//


void Base::filterViewVolume(EntityRecordWCList &o_localEntities)
{
  Q_UNUSED(o_localEntities);
}

//-------------------------------------------------------------------//

void Base::generateViewBBox()
{
  // initialise world space view box
  m_wsViewBBox = BBox(
        m_lsMeshBBox.m_minX*1 + m_pos.m_x,
        m_lsMeshBBox.m_minY*1 + m_pos.m_y,
        m_lsMeshBBox.m_minZ*1 + m_pos.m_z,
        m_lsMeshBBox.m_maxX*1 + m_pos.m_x,
        m_lsMeshBBox.m_maxY*1 + m_pos.m_y,
        m_lsMeshBBox.m_maxZ*1 + m_pos.m_z
        );
}

void Base::draw()
{
  Renderer *r = Renderer::instance();

  ngl::ShaderLib *shader = ngl::ShaderLib::instance();

  r->loadMatrixToShader(m_transformStack.getCurrentTransform().getMatrix(), "Phong");
  (*shader)["Phong"]->use();

  shader->setShaderParam4f("colourSelect", 0, 0, 0, 0);

  shader->setShaderParam4f("colour", 0.1, 0.1, 0.8, 1);

  r->draw("base", "Phong");
}

//-------------------------------------------------------------------//
