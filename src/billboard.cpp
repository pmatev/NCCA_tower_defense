#include "include/billboard.h"
#include "boost/lexical_cast.hpp"
#include "window.h"
#include "renderer.h"

Billboard::Billboard(const Type &_type, const ngl::Vec4 &_pos, const float &_width, const float &_height):
    m_type(_type),
    m_pos(_pos),
    m_width(_width),
    m_height(_height)
{
    Window *w = Window::instance();
    m_ID = w->getID();
    m_IDStr = boost::lexical_cast<std::string>(m_ID);
    init();
}

BillboardPtr Billboard::create(const Type &_type, const ngl::Vec4 &_pos, const float &_width, const float &_height)
{
    BillboardPtr a(new Billboard(   _type,
                                    _pos,
                                    _width,
                                    _height));
    return a;
}

Billboard::~Billboard()
{
    Renderer *r = Renderer::instance();
    r->deleteVAO(m_IDStr);
}

void Billboard::init()
{
    if(m_type == b3D) // 3D has Pivot in center (e.g. healthbars)
    {
        m_data[0].x=-m_width/2.0;
        m_data[0].y=-m_height/2.0;
        m_data[0].u=0.0f;
        m_data[0].v=0.0f;

        m_data[1].x=m_width/2.0;
        m_data[1].y=-m_height/2.0;
        m_data[1].u=1.0f;
        m_data[1].v=0.0f;

        m_data[2].x=-m_width/2.0;
        m_data[2].y=m_height/2.0;
        m_data[2].u=0.0f;
        m_data[2].v=1.0f;

        m_data[3].x=-m_width/2.0;
        m_data[3].y=m_height/2.0;
        m_data[3].u=0.0f;
        m_data[3].v=1.0f;

        m_data[4].x=m_width/2.0;
        m_data[4].y=-m_height/2.0;
        m_data[4].u=1.0f;
        m_data[4].v=0.0f;

        m_data[5].x=m_width/2.0;
        m_data[5].y=m_height/2.0;
        m_data[5].u=1.0f;
        m_data[5].v=1.0f;
    }
    else if(m_type == b2D) // 2D has Pivot bottom left e.g. UI
    {
        m_data[0].x=m_pos.m_x;
        m_data[0].y=m_pos.m_y;
        m_data[0].u=0.0f;
        m_data[0].v=0.0f;

        m_data[1].x=m_pos.m_x+m_width;
        m_data[1].y=m_pos.m_y;
        m_data[1].u=1.0f;
        m_data[1].v=0.0f;

        m_data[2].x=m_pos.m_x;
        m_data[2].y=m_pos.m_y+m_height;
        m_data[2].u=0.0f;
        m_data[2].v=1.0f;

        m_data[3].x=m_pos.m_x;
        m_data[3].y=m_pos.m_y+m_height;
        m_data[3].u=0.0f;
        m_data[3].v=1.0f;

        m_data[4].x=m_pos.m_x+m_width;
        m_data[4].y=m_pos.m_y;
        m_data[4].u=1.0f;
        m_data[4].v=0.0f;

        m_data[5].x=m_pos.m_x+m_width;
        m_data[5].y=m_pos.m_y+m_height;
        m_data[5].u=1.0f;
        m_data[5].v=1.0f;
    }
    Renderer *render = Renderer::instance();

    render->createVAO(m_IDStr, GL_TRIANGLES);

    VAOPtr v = render->getVAObyID(m_IDStr);
    v->bind();
    int size = sizeof(VertData);
    v->setData(6*size,m_data[0].x);
    v->setVertexAttributePointer(0,2,GL_FLOAT,size,0);
    v->setVertexAttributePointer(1,2,GL_FLOAT,size,2);
    v->setNumIndices(6);
    v->unbind();

}


void Billboard::draw(const std::string &_shader)
{
    Renderer *r = Renderer::instance();
    CameraPtr cam = r->getCam().lock();
    if(cam)
    {
        m_transform = cam->getViewMatrix().inverse();
        m_transform.m_30 = m_pos.m_x;
        m_transform.m_31 = m_pos.m_y;
        m_transform.m_32 = m_pos.m_z;
    }

    if(m_type == b3D)
    {
        r->loadMatrixToShader(m_transform, _shader);
    }

    r->draw(m_IDStr, _shader);
}

void Billboard::setUVScale(const float _scaleU, const float _scaleV)
{
    if(m_data)
    {
        m_data[0].u=0.0f;
        m_data[0].v=0.0f;

        m_data[1].u=_scaleU;
        m_data[1].v=0.0f;

        m_data[2].u=0.0f;
        m_data[2].v=_scaleV;

        m_data[3].u=0.0f;
        m_data[3].v=_scaleV;

        m_data[4].u=_scaleU;
        m_data[4].v=0.0f;

        m_data[5].u=_scaleU;
        m_data[5].v=_scaleV;
    }
    else
    {
        std::cerr<<"data not initialized before setting UV Scale"<<std::endl;
    }
    Renderer *render = Renderer::instance();

    VAOPtr v = render->getVAObyID(m_IDStr);
    v->bind();
    int size = sizeof(VertData);
    v->setData(6*size,m_data[0].x);
    v->setVertexAttributePointer(0,2,GL_FLOAT,size,0);
    v->setVertexAttributePointer(1,2,GL_FLOAT,size,2);
    v->setNumIndices(6);
    v->unbind();
}
