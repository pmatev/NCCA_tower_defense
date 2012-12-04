#include "include/renderer.h"
#include "window.h"


Renderer* Renderer::s_instance = 0;

Renderer::Renderer()
{
}
Renderer::~Renderer()
{
    delete m_cam;
}


Renderer* Renderer::instance()
{
    if(s_instance == 0)
    {
        s_instance = new Renderer();
    }
    return s_instance;
}

void Renderer::destroy()
{
    if(s_instance)
    {
        delete s_instance;
    }
}



void Renderer::init()
{
    Window *window = Window::instance();

    m_cam = new Camera();

    // set the viewport for openGL
    glViewport(0,0,window->getScreenWidth(),window->getScreenHeight());

}

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
    shader->bindAttribute(_name,1,"inUV");
    shader->bindAttribute(_name,2,"inNormal");

    shader->linkProgramObject("Surface");

    m_shaderNames.push_back(_name);

}

void Renderer::loadMatrixToShader(ngl::TransformStack &_tx, std::string _shader)
{
    ngl::ShaderLib *shader=ngl::ShaderLib::instance();

    (*shader)[_shader]->use();
    shader->setShaderParam3f("viewerPos",m_cam->getEye().m_x,m_cam->getEye().m_y,m_cam->getEye().m_z);

    ngl::Mat4 MV;
    ngl::Mat4 MVP;
    ngl::Mat3 normalMatrix;
    ngl::Mat4 M;
    M=_tx.getCurrentTransform().getMatrix();
    MV=  _tx.getCurrAndGlobal().getMatrix()*m_cam->getViewMatrix();
    MVP=  MV*m_cam->getProjectionMatrix();
    normalMatrix=MV;
    normalMatrix.inverse();

    shader->setShaderParamFromMat4("MV",MV);
    shader->setShaderParamFromMat4("MVP",MVP);
    shader->setShaderParamFromMat3("normalMatrix",normalMatrix);
    shader->setShaderParamFromMat4("M",M);


}

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
