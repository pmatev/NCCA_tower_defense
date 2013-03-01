#include "include/concrete/invisiblewall.h"
#include "ngl/ShaderLib.h"

#define PI 3.14159265

//-------------------------------------------------------------------//

InvisibleWall::InvisibleWall(
    NodePtr _linkedNode,
    unsigned int _id
    ) :
  Wall(_linkedNode, _id)
{
  initialiseMesh("wall");
  publish();

  _linkedNode->setVisibility(false);
  _linkedNode->setOccupied(true);
}

//-------------------------------------------------------------------//

EntityPtr InvisibleWall::create(NodePtr _linkedNode, unsigned int _id)
{
  EntityPtr a(new InvisibleWall(_linkedNode,_id));
  return a;
}

//-------------------------------------------------------------------//

void InvisibleWall::update(double _dt)
{
  Q_UNUSED(_dt);
}

//-------------------------------------------------------------------//

void InvisibleWall::filterViewVolume(EntityRecordWCList &o_localEntities)
{
  Q_UNUSED(o_localEntities);
}

//-------------------------------------------------------------------//

void InvisibleWall::generateViewBBox()
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
void InvisibleWall::draw()
{
}
