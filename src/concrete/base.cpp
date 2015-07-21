#include "ngl/ShaderLib.h"
#include "texturelib.h"
#include "window.h"
#include "concrete/base.h"
#include "renderer.h"
#include "meshlib.h"

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

//-------------------------------------------------------------------//

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

//-------------------------------------------------------------------//

void Base::draw()
{
    Renderer *r = Renderer::instance();
    ngl::ShaderLib *shader = ngl::ShaderLib::instance();

    (*shader)["Constant"]->use();
    r->loadMatrixToShader(m_transformStack.getCurrentTransform().getMatrix(), "Constant");
    ngl::Vec3 c = Window::instance()->IDToColour(m_ID);
    c = c/255.0f;

    shader->setShaderParam4f("colourSelect", c[0], c[1], c[2], 1);
    shader->setShaderParam1f("textured",1);

    ngl::Vec4 colour = ngl::Vec4(0.8,0.7,1,1);
    shader->setShaderParam4f("colour", colour[0], colour[1], colour[2], colour[3]);

    TextureLib *tex = TextureLib::instance();
    tex->bindTexture("hexagon_AO");
    r->draw("hexagon", "Constant");
}

//-------------------------------------------------------------------//
