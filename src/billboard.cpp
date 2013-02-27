#include "include/billboard.h"
#include "boost/lexical_cast.hpp"
#include "window.h"
#include "renderer.h"

Billboard::Billboard(const Type _type, const ngl::Vec4 _pos, const float _width, const float _height):
    m_type(_type),
    m_pos(_pos),
    m_width(_width),
    m_height(_height)
{
    Window *w = Window::instance();
    m_ID = w->getID();
    m_IDStr = boost::lexical_cast<std::string>(m_ID);
}

void Billboard::init()
{
    vertData d[6];
 // divide by 2!
    d[0].x=-m_width;
    d[0].y=-m_height;
    d[0].u=0.0f;
    d[0].v=0.0f;

    d[1].x=m_width;
    d[1].y=-m_height;
    d[1].u=1.0f;
    d[1].v=0.0f;

    d[2].x=-m_width;
    d[2].y=m_height;
    d[2].u=0.0f;
    d[2].v=1.0f;

    d[3].x=-m_width;
    d[3].y=m_height;
    d[3].u=0.0f;
    d[3].v=1.0f;

    d[4].x=m_width;
    d[4].y=-m_height;
    d[4].u=1.0f;
    d[4].v=0.0f;

    d[5].x=m_width;
    d[5].y=m_height;
    d[5].u=1.0f;
    d[5].v=1.0f;

    Renderer *render = Renderer::instance();

    render->createVAO(m_IDStr, GL_TRIANGLES);

    VAOPtr v = render->getVAObyID(m_IDStr);
    v->bind();
    int size = sizeof(vertData);
    v->setData(6*size,d[0].x);
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
//    m_transform = cam->getViewMatrix().inverse();
//    m_transform.m_30 = m_pos.m_x;
//    m_transform.m_31 = m_pos.m_y;
//    m_transform.m_32 = m_pos.m_z;
    }

//    if(m_type == b3D)
//    {
//        r->loadMatrixToShader(m_transform, _shader);
//    }

    r->draw(m_IDStr, _shader);
}
