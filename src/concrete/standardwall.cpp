#include "include/concrete/standardwall.h"

#define PI 3.14159265

//-------------------------------------------------------------------//

StandardWall::StandardWall(
    NodePtr _linkedNode,
    unsigned int _id
    ) :
  Wall(_linkedNode, _id)
{
  generateMesh();
  publish();

  _linkedNode->setVisibility(false);
  _linkedNode->setOccupied(true);
}

//-------------------------------------------------------------------//

EntityPtr StandardWall::create(NodePtr _linkedNode, unsigned int _id)
{
  EntityPtr a(new StandardWall(_linkedNode,_id));
  return a;
}

//-------------------------------------------------------------------//

void StandardWall::update(double _dt)
{
  Q_UNUSED(_dt);
}

//-------------------------------------------------------------------//

void StandardWall::generateMesh()
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
  GLfloat normals[] = {0.5,0.5,0.5,
                       0.5,0.5,0.5,
                       0.5,0.5,0.5,
                       0.5,0.5,0.5,
                       0.5,0.5,0.5,
                       0.5,0.5,0.5
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

void StandardWall::filterViewVolume(EntityRecordWCList &o_localEntities)
{
  Q_UNUSED(o_localEntities);
}

//-------------------------------------------------------------------//

void StandardWall::generateViewBBox()
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
