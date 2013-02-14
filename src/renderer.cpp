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
    delete m_orthoCam;
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

    m_orthoCam = new ngl::Camera(ngl::Vec3(0,0,0.1),ngl::Vec3(0,0,0),ngl::Vec3(0,1,0),ngl::ORTHOGRAPHIC);

    float w = window->getScreenWidth();
    float h = window->getScreenHeight();

    resize(w, h);

    glEnable(GL_DEPTH_TEST);
}
//-------------------------------------------------------------------//

void Renderer::resize(const unsigned int _w, const unsigned int _h)
{
  // set the viewport for openGL
  glViewport(0,0,_w,_h);
  //set camera shape
  m_cam->setShape(45,(float)_w/_h,0.5,150);
  m_orthoCam->setShape(45,(float)_w/_h,0.5,150);

  setScreenSize();
}



//-------------------------------------------------------------------//
void Renderer::createShader(std::string _name, int _numAttribs)
{
//  GLuint prog_id = glCreateProgram();

//  GLuint shader_id = glCreateShader(GL_VERTEX_SHADER);

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

    if(_numAttribs>=1)
    {
      shader->bindAttribute(_name,0,"inVert");
      if(_numAttribs>=2)
      {
      shader->bindAttribute(_name,1,"inNormal");
      }
    }
    //shader->bindAttribute(_name,1,"inUV");

    shader->linkProgramObject(_name);

    m_shaderNames.push_back(_name);

}
//-------------------------------------------------------------------//
void Renderer::createVAO(std::string _id, GLenum _drawType)
{
  m_mapVAO[_id] = VAOPtr(ngl::VertexArrayObject::createVOA(_drawType));

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
void Renderer::setIndexedDataToVAO(std::string _id,
                                   unsigned int _size,
                                   unsigned int _step,
                                   const GLfloat &_data,
                                   unsigned int _indexSize,
                                   const GLvoid *_indexData,
                                   unsigned int _numIndices)
{
  VAOPtr vao = bindVAOByID(_id);

  vao->setIndexedData(_size,
                      _data,
                      _indexSize,
                      _indexData,
                      GL_UNSIGNED_BYTE,
                      GL_STATIC_DRAW);

  // vert position attribute
  vao->setVertexAttributePointer(0,_step,GL_FLOAT,sizeof(vertData),0);
  // vert normals attribute
  vao->setVertexAttributePointer(1,_step,GL_FLOAT,sizeof(vertData),_step);

  vao->setNumIndices(_numIndices);

  vao->unbind();
}
//-------------------------------------------------------------------//
void Renderer::setIndexedData2D(std::string _id,
                                   unsigned int _size,
                                   unsigned int _step,
                                   const GLfloat &_data,
                                   unsigned int _indexSize,
                                   const GLvoid *_indexData,
                                   unsigned int _numIndices)
{
  VAOPtr vao = bindVAOByID(_id);

  vao->setIndexedData(_size,
                      _data,
                      _indexSize,
                      _indexData,
                      GL_UNSIGNED_BYTE,
                      GL_STATIC_DRAW);

  // vert position attribute
  vao->setVertexAttributePointer(0,_step,GL_FLOAT,sizeof(vertData2D),0);

  vao->setNumIndices(_numIndices);

  vao->unbind();
}


VAOPtr Renderer::getVAObyID(std::string _id)
{
  std::map<std::string, VAOPtr>::iterator it = m_mapVAO.find(_id);
  if(it == m_mapVAO.end())
  {
    return VAOPtr();
  }
  return it->second;
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

void Renderer::deleteVAO(std::string _id)
{
  m_mapVAO.erase(_id);
}

void Renderer::drawSelection(unsigned int _id, std::string _idStr)
{
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  (*shader)["Colour"]->use();

  VAOPtr v = bindVAOByID(_idStr);

  ngl::Vec3 c = Window::instance()->IDToColour(_id);

  shader->setShaderParam4f("Colour", c.m_x/255.0f, c.m_y/255.0f, c.m_z/255.0f, 1);

  //std::cout<<c<<std::endl;

  v->draw();
  v->unbind();
}

//-------------------------------------------------------------------//
void Renderer::prepareDrawSelection()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glDisable(GL_LIGHTING);
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_FOG);
}
ngl::Vec3 Renderer::readColourSelection(const int _x, const int _y)
{
  // get color information from frame buffer
  unsigned char pixel[3];
  // get the viweport
  GLint viewport[4];
  glGetIntegerv(GL_VIEWPORT, viewport);
  // read the pixels (1,1 at present but could do wider area)
  glReadPixels(_x, viewport[3] - _y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
  // now loop for each object and see if the colour matches
  // need to use a reference object as we will change the class Active value
  ngl::Vec3 p(pixel[0], pixel[1], pixel[2]);
  return p;
}

//-------------------------------------------------------------------//
void Renderer::loadMatrixToShader( ngl::TransformStack &_tx,  std::string _shader)
{
    ngl::ShaderLib *shader=ngl::ShaderLib::instance();

    (*shader)[_shader]->use();

    ngl::Mat4 M;
    ngl::Mat4 V;
    ngl::Mat4 P;
    M=_tx.getCurrentTransform().getMatrix();
    V= m_cam->getViewMatrix();
    P= m_cam->getProjectionMatrix();

    shader->setShaderParamFromMat4("MVP",M*V*P);
}
//-------------------------------------------------------------------//
void Renderer::set2DPosToShader(ngl::Vec2 _pos,  std::string _shader)
{
    ngl::ShaderLib *shader=ngl::ShaderLib::instance();

    (*shader)[_shader]->use();

    shader->setRegisteredUniform1f("xpos",_pos.m_x);
    shader->setRegisteredUniform1f("ypos",_pos.m_y);
    shader->setRegisteredUniform3f("colour",0.3,0.4,0.6);

}

void Renderer::setScreenSize()
{
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  Window *window = Window::instance();
  int w = window->getScreenWidth();
  int h = window->getScreenHeight();

  (*shader)["UI"]->use();

  float scaleX=2.0/w;
  float scaleY=-2.0/h;

  shader->setRegisteredUniform1f("scaleX",scaleX);
  shader->setRegisteredUniform1f("scaleY",scaleY);
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
