#include "renderer.h"
#include "window.h"
#include "ngl/ShaderLib.h"
#include "game.h"
#include "boost/foreach.hpp"
#include "boost/lexical_cast.hpp"


Renderer* Renderer::s_instance = 0;
//-------------------------------------------------------------------//
Renderer::Renderer()
{
}
//-------------------------------------------------------------------//
Renderer::~Renderer()
{
//    glDeleteTextures(3,&m_textures);
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
    std::cout<<"OpenGL Version: "<<glGetString(GL_VERSION)<<std::endl;

    m_cam = CameraPtr(new Camera(ngl::Vec4(10,10,10,1),Game::instance()->getBasePos(),ngl::Vec4(0,1,0,0)));

    m_lights.push_back(PointLight::create(ngl::Vec4(0,10,0,1),ngl::Vec4(0,0,0,1),ngl::Vec4(0.3,0.3,0.3,1), ngl::Vec4(1,1,1,1)));
    m_lights.push_back(PointLight::create(ngl::Vec4(40,10,0,1),ngl::Vec4(0,0,0,1),ngl::Vec4(0.3,0.3,0.3,1), ngl::Vec4(1,1,1,1)));
    m_lights.push_back(PointLight::create(ngl::Vec4(0,10,40,1),ngl::Vec4(0,0,0,1),ngl::Vec4(0.3,0.3,0.3,1), ngl::Vec4(1,1,1,1)));
    m_lights.push_back(PointLight::create(ngl::Vec4(40,10,40,1),ngl::Vec4(0,0,0,1),ngl::Vec4(0.3,0.3,0.3,1), ngl::Vec4(1,1,1,1)));

    ngl::ShaderLib *shader = ngl::ShaderLib::instance();    

    glClearColor(1,1,1,1);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//    glEnable(GL_MULTISAMPLE_EXT);


    /* NEED TO REDO create shader to allow for more flexibility */
//    createShader("Phong",2);
//    createShader("Colour",2);

    shader->createShaderProgram("Phong");

    shader->attachShader("PhongVertex",ngl::VERTEX);
    shader->attachShader("PhongFragment",ngl::FRAGMENT);
    shader->loadShaderSource("PhongVertex", "shaders/Phong.vs");
    shader->loadShaderSource("PhongFragment","shaders/Phong.fs");

    shader->compileShader("PhongVertex");
    shader->compileShader("PhongFragment");

    shader->attachShaderToProgram("Phong","PhongVertex");
    shader->attachShaderToProgram("Phong","PhongFragment");

    shader->bindAttribute("Phong", 0, "inVert");
    shader->bindAttribute("Phong", 1, "inUV");
    shader->bindAttribute("Phong", 2, "inNormal");
    shader->linkProgramObject("Phong");

    glBindFragDataLocation(shader->getProgramID("Phong"),0,"outColour");

    m_shaderNames.push_back("Phong");


    shader->createShaderProgram("Constant");

    shader->attachShader("ConstantVertex",ngl::VERTEX);
    shader->attachShader("ConstantFragment",ngl::FRAGMENT);
    shader->loadShaderSource("ConstantVertex", "shaders/Constant.vs");
    shader->loadShaderSource("ConstantFragment","shaders/Constant.fs");

    shader->compileShader("ConstantVertex");
    shader->compileShader("ConstantFragment");

    shader->attachShaderToProgram("Constant","ConstantVertex");
    shader->attachShaderToProgram("Constant","ConstantFragment");

    shader->bindAttribute("Constant", 0, "inVert");
    shader->bindAttribute("Constant", 1, "inUV");
    shader->bindAttribute("Constant", 2, "inNormal");
    shader->linkProgramObject("Constant");

    glBindFragDataLocation(shader->getProgramID("Constant"),0,"outColour");

    m_shaderNames.push_back("Constant");


    shader->createShaderProgram("TexturedConstant");

    shader->attachShader("TexturedConstVertex",ngl::VERTEX);
    shader->attachShader("TexturedConstFragment",ngl::FRAGMENT);
    shader->loadShaderSource("TexturedConstVertex", "shaders/TexturedConst.vs");
    shader->loadShaderSource("TexturedConstFragment","shaders/TexturedConst.fs");

    shader->compileShader("TexturedConstVertex");
    shader->compileShader("TexturedConstFragment");

    shader->attachShaderToProgram("TexturedConstant","TexturedConstVertex");
    shader->attachShaderToProgram("TexturedConstant","TexturedConstFragment");

    shader->bindAttribute("TexturedConstant", 0, "inVert");
    shader->bindAttribute("TexturedConstant", 1, "inUV");
    shader->bindAttribute("TexturedConstant", 2, "inNormal");
    shader->linkProgramObject("TexturedConstant");

    glBindFragDataLocation(shader->getProgramID("TexturedConstant"),0,"outColour");

    m_shaderNames.push_back("TexturedConstant");


    shader->createShaderProgram("UI");

    shader->attachShader("UIVertex",ngl::VERTEX);
    shader->attachShader("UIFragment",ngl::FRAGMENT);
    shader->loadShaderSource("UIVertex", "shaders/UI.vs");
    shader->loadShaderSource("UIFragment","shaders/UI.fs");

    shader->compileShader("UIVertex");
    shader->compileShader("UIFragment");

    shader->attachShaderToProgram("UI","UIVertex");
    shader->attachShaderToProgram("UI","UIFragment");

    shader->bindAttribute("UI", 0, "inVert");
    shader->bindAttribute("UI",1,"inUV");
    shader->linkProgramObject("UI");

    shader->autoRegisterUniforms("UI");

    m_shaderNames.push_back("UI");

    shader->createShaderProgram("Texture");
    shader->attachShader("TextureVertex", ngl::VERTEX);
    shader->attachShader("TextureFragment", ngl::FRAGMENT);
    shader->loadShaderSource("TextureVertex", "shaders/Texture.vs");
    shader->loadShaderSource("TextureFragment", "shaders/Texture.fs");

    shader->compileShader("TextureVertex");
    shader->compileShader("TextureFragment");

    shader->attachShaderToProgram("Texture", "TextureVertex");
    shader->attachShaderToProgram("Texture", "TextureFragment");

    shader->bindAttribute("Texture", 0, "inVert");
    shader->bindAttribute("Texture", 1, "inUV");
    shader->linkProgramObject("Texture");

    shader->autoRegisterUniforms("Texture");

    m_shaderNames.push_back("Texture");

    createFramebufferObject("Texture");

    resize();
}
//-------------------------------------------------------------------//

void Renderer::resize()
{
  Window *window = Window::instance();
  int w = window->getScreenWidth();
  int h = window->getScreenHeight();
  // set the viewport for openGL
  glViewport(0,0,w,h);
  //set camera shape
  m_cam->setShape(45,(float)w/h,0.5,150);
//  m_orthoCam->setShape(45,(float)_w/_h,0.5,150);

  ngl::ShaderLib *shader=ngl::ShaderLib::instance();

  (*shader)["UI"]->use();

  GLfloat scaleX=2.0/w;
  GLfloat scaleY=-2.0/h;

  shader->setRegisteredUniform1f("scaleX",scaleX);
  shader->setRegisteredUniform1f("scaleY",scaleY);


//  std::cout<<"resized window"<<std::endl;

}


//-------------------------------------------------------------------//
void Renderer::createShader(std::string _name, int _numAttribs)
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

    if(_numAttribs>=1)
    {
      shader->bindAttribute(_name,0,"inVert");

      if(_numAttribs>=2)
      {
      shader->bindAttribute(_name,1,"inNormal");
      }
    }
    //shader->bindAttribute(_name,1,"inUV");

    glBindFragDataLocation(shader->getProgramID(_name),0,"outColour");
    shader->linkProgramObject(_name);

    m_shaderNames.push_back(_name);


}
//-------------------------------------------------------------------//
void Renderer::createVAO(std::string _id, GLenum _drawType)
{
  m_mapVAO[_id] = VAOPtr(ngl::VertexArrayObject::createVOA(_drawType));

}
//-------------------------------------------------------------------//
//void Renderer::setDataToVAO(std::string _id, unsigned int _size, GLfloat &_data, unsigned int _numIndices)
//{
//  VAOPtr vao = bindVAOByID(_id);

//  vao->setData(_size,_data,GL_STREAM_DRAW);

//  // vert position attribute
//  vao->setVertexAttributePointer(0,3,GL_FLOAT,sizeof(vertData),0);
//  // vert normals attribute
//  vao->setVertexAttributePointer(1,3,GL_FLOAT,sizeof(vertData),3);

//  vao->setNumIndices(_numIndices);

//  vao->unbind();
//}
//-------------------------------------------------------------------//
void Renderer::setIndexedDataToVAO(std::string _id,
                                   unsigned int _size,
                                   unsigned int _step,
                                   const GLfloat &_data,
                                   unsigned int _indexSize,
                                   const GLvoid *_indexData,
                                   unsigned int _numIndices)
{
  VAOPtr vao = getVAObyID(_id);
  vao->bind();

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
////-------------------------------------------------------------------//
//void Renderer::setIndexedData2D(std::string _id,
//                                   unsigned int _size,
//                                   unsigned int _step,
//                                   const GLfloat &_data,
//                                   unsigned int _indexSize,
//                                   const GLvoid *_indexData,
//                                   unsigned int _numIndices)
//{
//  VAOPtr vao = bindVAOByID(_id);

//  vao->setIndexedData(_size,
//                      _data,
//                      _indexSize,
//                      _indexData,
//                      GL_UNSIGNED_BYTE,
//                      GL_STATIC_DRAW);

//  // vert position attribute
//  vao->setVertexAttributePointer(0,_step,GL_FLOAT,sizeof(vertData2D),0);

//  vao->setNumIndices(_numIndices);

//  vao->unbind();
//}


//-------------------------------------------------------------------//

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

  VAOPtr v = getVAObyID(_id);
  if(v){
      v->bind();
      v->draw();
      v->unbind();
  }else{
      std::cerr<<"Error drawing VAO. ID: "<< _id<<std::endl;
  }
}
//-------------------------------------------------------------------//

//void Renderer::drawSelection(unsigned int _id, std::string _idStr)
//{
//  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
//  (*shader)["Colour"]->use();

//  VAOPtr v = getVAObyID(_idStr);

//  ngl::Vec3 c = Window::instance()->IDToColour(_id);

//  shader->setShaderParam4f("colour", c.m_x/255.0f, c.m_y/255.0f, c.m_z/255.0f, 1);

//  //std::cout<<c<<std::endl;
//  v->bind();
//  v->draw();
//  v->unbind();
//}

//-------------------------------------------------------------------//
void Renderer::prepareDrawSelection()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glDisable(GL_LIGHTING);
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_FOG);
}


//-------------------------------------------------------------------//
void Renderer::deleteVAO(std::string _id)
{
  m_mapVAO.erase(_id);
}


//-------------------------------------------------------------------//

void Renderer::createFramebufferObject(const std::string &_name)
{
  glGenTextures(3, &m_textures[0]);
  glBindTexture(GL_TEXTURE_2D, m_textures[0]);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//  glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE); // automatic mipmap
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, TEXTURE_WIDTH, TEXTURE_HEIGHT, 0,
               GL_RGBA, GL_UNSIGNED_BYTE, 0);


  glBindTexture(GL_TEXTURE_2D, m_textures[1]);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE); // automatic mipmap
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, TEXTURE_WIDTH, TEXTURE_HEIGHT, 0,
               GL_RGBA, GL_UNSIGNED_BYTE, 0);

  glBindTexture(GL_TEXTURE_2D, m_textures[2]);
  glTexParameteri( GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_LUMINANCE );
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//  glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE); // automatic mipmap
  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, TEXTURE_WIDTH, TEXTURE_HEIGHT, 0,
               GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);
  glBindTexture(GL_TEXTURE_2D, 0);


//  GLuint rboID;
//  glGenRenderbuffers(1, &rboID);
//  glBindRenderbuffer(GL_RENDERBUFFER, rboID);
//  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT,TEXTURE_WIDTH,TEXTURE_HEIGHT);
//  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  GLuint fboID;
  glGenFramebuffers(1, &fboID);
  glBindFramebuffer(GL_FRAMEBUFFER, fboID);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textures[0],0);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, m_textures[1],0);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_textures[2],0);
//  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboID);

  fboError(glCheckFramebufferStatus(GL_FRAMEBUFFER));


  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  m_mapFBO[_name] = fboID;


}
//-------------------------------------------------------------------//
void Renderer::bindFrameBuffer(const std::string &_name)
{
    GLuint id  = m_mapFBO[_name];
  glBindFramebuffer(GL_FRAMEBUFFER,id);
  m_boundFBO = id;
}
//-------------------------------------------------------------------//
void Renderer::bindFrameBuffer(const GLuint _id)
{
  glBindFramebuffer(GL_FRAMEBUFFER,_id);
  m_boundFBO = _id;
}

//void Renderer::bindTexture(const std::string &_name)
//{
//    glBindTexture(GL_TEXTURE_2D, m_textures[_name]);
//}

//-------------------------------------------------------------------//

ngl::Vec4 Renderer::readPixels(const int _x, const int _y)
{    
  Window *w = Window::instance();
  unsigned char pixel[3];
  glReadBuffer(GL_COLOR_ATTACHMENT1);

  int read_x = _x * (float(TEXTURE_WIDTH)/float(w->getScreenWidth()));
  int read_y = TEXTURE_HEIGHT - _y * (float(TEXTURE_HEIGHT)/float(w->getScreenHeight()));

  glReadPixels(read_x, read_y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
  ngl::Vec4 p(pixel[0], pixel[1], pixel[2], pixel[3]);
  return p;
}

void Renderer::fboError(GLenum _error)
{
    switch(_error)
    {
        case GL_FRAMEBUFFER_COMPLETE:                       std::cout<<"FBO Success"<<std::endl; break;
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:          std::cout<<"FBO Incomplete Attachment"<<std::endl; break;
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:  std::cout<<"FBO Incomplete Missing Attachment"<<std::endl; break;
        case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:      std::cout<<"FBO Incomplete Dimensions"<<std::endl; break;
        case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:         std::cout<<"FBO Incomplete Formats"<<std::endl; break;
        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:         std::cout<<"FBO Incomplete Draw buffer"<<std::endl; break;
        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:         std::cout<<"FBO Incomplete Read buffer"<<std::endl; break;
        case GL_FRAMEBUFFER_UNSUPPORTED:                    std::cout<<"FBO Unsupported"<<std::endl; break;
        default:                                            std::cout<<"Unknown"<<std::endl; break;
    }
}

//-------------------------------------------------------------------//
void Renderer::loadMatrixToShader( const ngl::Mat4 &_tx, const std::string &_shader)
{
    ngl::ShaderLib *shader=ngl::ShaderLib::instance();
    (*shader)[_shader]->use();

    ngl::Mat4 M = _tx;
    ngl::Mat4 V = m_cam->getViewMatrix();
    ngl::Mat4 P = m_cam->getProjectionMatrix();
    ngl::Mat4 MV = M*V;
    ngl::Real d[9];
    MV.as3x3Array(d);
    ngl::Mat3 normalMatrix;
    normalMatrix.m_00 = d[0];
    normalMatrix.m_01 = d[1];
    normalMatrix.m_02 = d[2];
    normalMatrix.m_10 = d[3];
    normalMatrix.m_11 = d[4];
    normalMatrix.m_12 = d[5];
    normalMatrix.m_20 = d[6];
    normalMatrix.m_21 = d[7];
    normalMatrix.m_22 = d[8];

    normalMatrix.inverse();
    normalMatrix = normalMatrix.transpose();

    shader->setShaderParamFromMat4("MVP",MV*P);
    if(_shader == "Phong")
    {
        shader->setShaderParamFromMat4("V",V);
        shader->setShaderParamFromMat3("normalMatrix",normalMatrix);
        shader->setShaderParamFromMat4("MV", MV);
    }
}
//-------------------------------------------------------------------//
void Renderer::loadLightsToShader(const std::string &_name) const
{
    int i=0;
    BOOST_FOREACH(PointLightPtr light, m_lights)
    {
        std::string i_str = boost::lexical_cast<std::string>(i);
        light->loadToShader("lights["+i_str+"]", _name);
        i++;
    }
}

void Renderer::visualiseLights()
{
    BOOST_FOREACH(PointLightPtr light, m_lights)
    {
        light->draw();
    }
}
