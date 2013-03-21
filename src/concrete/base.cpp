#include "ngl/ShaderLib.h"

#include "window.h"
#include "concrete/base.h"
#include "renderer.h"
#include "meshlib.h"

//---TEST CODE (replace when generateMesh properly implemented)---//
#define PI 3.14159265

//-------------------------------------------------------------------//

Base::Base(
    NodePtr _linkedNode,
    unsigned int _id
    ) :
  StaticEntity(_linkedNode,BASE, _id)
{
  initialiseMesh("base");
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

  (*shader)["Phong"]->use();
  r->loadMatrixToShader(m_transformStack.getCurrentTransform().getMatrix(), "Phong");

  shader->setShaderParam4f("colourSelect", 0, 0, 0, 0);

  shader->setShaderParam4f("colour", 1, 0.1, 1, 1);

  r->draw("base", "Phong");
}

//-------------------------------------------------------------------//
