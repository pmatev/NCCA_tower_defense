#include "include/renderer.h"
#include "window.h"
#include "game.h"

Renderer* Renderer::s_instance = 0;
//-------------------------------------------------------------------//
Renderer::Renderer()
{
}
//-------------------------------------------------------------------//
Renderer::~Renderer()
{
    delete m_cam;
}
//-------------------------------------------------------------------//

Renderer* Renderer::instance()
{
    if(s_instance == 0)
    {
        s_instance = new Renderer();
    }
    return s_instance;
}
//-------------------------------------------------------------------//
void Renderer::destroy()
{
    if(s_instance)
    {
        delete s_instance;
    }
}

//-------------------------------------------------------------------//

void Renderer::init()
{
    Window *window = Window::instance();

    m_cam = new Camera(ngl::Vec4(10,10,10,1),ngl::Vec4(0,0,0,1),ngl::Vec4(0,1,0,0));

    float w = window->getScreenWidth();
    float h = window->getScreenHeight();

    // set the viewport for openGL
    glViewport(0,0,w,h);
    //set camera shape
    m_cam->setShape(45,(float)w/h,0.5,150);


    glEnable(GL_DEPTH_TEST);
}
//-------------------------------------------------------------------//
void Renderer::createShader(std::string _name)
{
    ngl::ShaderLib *shader = ngl::ShaderLib::instance();

    shader->createShaderProgram(_name);

    shader->attachShader(_name+"Vertex",ngl::VERTEX);
    shader->attachShader(_name+"Fragment",ngl::FRAGMENT);

    shader->loadShaderSource(_name+"Vertex", "shaders/"+_name+".vs");
    shader->loadShaderSource(_name+"Fragment","shaders/"+_name+".fs");

    shader->compileShader(_name+"Vertex");
    shader->compileShader(_name+"Fragment");

    shader->attachShaderToProgram(_name,_name+"Vertex");
    shader->attachShaderToProgram(_name,_name+"Fragment");

    shader->bindAttribute(_name,0,"inVert");
    shader->bindAttribute(_name,1,"inNormal");
    //shader->bindAttribute(_name,1,"inUV");

    shader->linkProgramObject(_name);

    m_shaderNames.push_back(_name);

}
//-------------------------------------------------------------------//
void Renderer::createVAO(std::string _id)
{
  m_mapVAO[_id] = VAOPtr(ngl::VertexArrayObject::createVOA(GL_TRIANGLES));

}
//-------------------------------------------------------------------//
void Renderer::setDataToVAO(std::string _id, unsigned int _size, GLfloat &_data, unsigned int _numIndices)
{
  VAOPtr vao = bindVAOByID(_id);

  vao->setData(_size,_data,GL_STREAM_DRAW);

  // vert position attribute
  vao->setVertexAttributePointer(0,3,GL_FLOAT,sizeof(vertData),0);
  // vert normals attribute
  vao->setVertexAttributePointer(1,3,GL_FLOAT,sizeof(vertData),3);

  vao->setNumIndices(_numIndices);

  vao->unbind();
}
//-------------------------------------------------------------------//
void Renderer::setIndexedDataToVAO(std::string _id, unsigned int _size, const GLfloat &_data, unsigned int _indexSize, const GLvoid *_indexData, unsigned int _numIndices)
{
  VAOPtr vao = bindVAOByID(_id);

  vao->setIndexedData(_size, _data, _indexSize, _indexData, GL_UNSIGNED_BYTE, GL_STATIC_DRAW);

  // vert position attribute
  vao->setVertexAttributePointer(0,3,GL_FLOAT,sizeof(vertData),0);
  // vert normals attribute
  vao->setVertexAttributePointer(1,3,GL_FLOAT,sizeof(vertData),3);

  vao->setNumIndices(_numIndices);

  vao->unbind();
}
//-------------------------------------------------------------------//
void Renderer::draw(std::string _id, std::string _shader)
{
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  (*shader)[_shader]->use();

  VAOPtr v = bindVAOByID(_id);

  v->draw();
  v->unbind();
}
//-------------------------------------------------------------------//
void Renderer::drawSelection()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glDisable(GL_LIGHTING);
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_FOG);

}
//-------------------------------------------------------------------//
void Renderer::loadMatrixToShader( ngl::TransformStack &_tx,  std::string _shader)
{
    ngl::ShaderLib *shader=ngl::ShaderLib::instance();

    (*shader)[_shader]->use();

    ngl::Mat4 M;
    ngl::Mat4 V;
    ngl::Mat4 P;
    ngl::Mat3 normalMatrix;
    M=_tx.getCurrentTransform().getMatrix();
    V= m_cam->getViewMatrix();
    P= m_cam->getProjectionMatrix();
    normalMatrix=M*V;
    normalMatrix.inverse();

    shader->setShaderParamFromMat4("MVP",M*V*P);


}
//-------------------------------------------------------------------//
void Renderer::loadLightToShader(ngl::Light *_light, std::string _shader)
{
    ngl::ShaderLib *shader=ngl::ShaderLib::instance();
    (*shader)[_shader]->use();
    ngl::Mat4 iv=m_cam->getProjectionMatrix();
    iv.transpose();
    _light->setTransform(iv);
    // load these values to the shader as well
    _light->loadToShader("light");
}
//-------------------------------------------------------------------//
VAOPtr Renderer::bindVAOByID(const std::string _id)
{
  std::map<std::string, VAOPtr>::iterator it = m_mapVAO.find(_id);
  VAOPtr vao= (*it).second;
  vao->bind();
  return vao;
}
