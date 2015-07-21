#include <ngl/ShaderLib.h>
#include "texturelib.h"
#include "include/concrete/standardwall.h"
#include "window.h"

#define PI 3.14159265

//-------------------------------------------------------------------//

StandardWall::StandardWall(
    NodePtr _linkedNode,
    unsigned int _id
    ) :
  StaticEntity(_linkedNode, WALL, _id)
{
  initialiseMesh("wall");
  publish();

  _linkedNode->setVisibility(true);
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
  TextureLib *tex = TextureLib::instance();
  ngl::ShaderLib *shader = ngl::ShaderLib::instance();

  ngl::Vec4 colour = ngl::Vec4(0.3,0.2,0.9,1);

  (*shader)["Constant"]->use();
  r->loadMatrixToShader(m_transformStack.getCurrentTransform().getMatrix(), "Constant");
  ngl::Vec3 c = Window::instance()->IDToColour(m_ID);
  c = c/255.0f;

  shader->setShaderParam4f("colour", colour[0], colour[1], colour[2], colour[3]);
  shader->setShaderParam1f("textured",1);
  if(m_highlighted == 1)
  {
     shader->setShaderParam4f("highlightColour", 0.737,0.835,0.925,1);
  }
  shader->setShaderParam4f("colourSelect", c[0], c[1], c[2], 1);

  tex->bindTexture("wall_AO");
  r->draw("wall", "Constant");
   shader->setShaderParam4f("highlightColour", 1,1,1,1);


}
