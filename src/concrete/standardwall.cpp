#include <ngl/ShaderLib.h>

#include "include/concrete/standardwall.h"
#include "window.h"

#define PI 3.14159265

//-------------------------------------------------------------------//

StandardWall::StandardWall(
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

void StandardWall::draw()
{
  Renderer *r = Renderer::instance();

  ngl::ShaderLib *shader = ngl::ShaderLib::instance();

  (*shader)["Constant"]->use();
  r->loadMatrixToShader(m_transformStack.getCurrentTransform().getMatrix(), "Constant");

  shader->setShaderParam4f("colour", 0.4, 0.1, 0.8, 1);
  shader->setShaderParam4f("colourSelect", 0, 0, 0, 0);

  r->draw("wall", "Constant");

}
