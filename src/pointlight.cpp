#include "include/pointlight.h"
#include "ngl/ShaderLib.h"
#include "renderer.h"

PointLight::PointLight(const ngl::Vec4 &_pos, const ngl::Vec4 &_ambCol, const ngl::Vec4 &_diffCol, const ngl::Vec4 &_specCol):
    m_pos(_pos),
    m_ambientColor(_ambCol),
    m_diffuseColor(_diffCol),
    m_specularColor(_specCol)
{

}

PointLight::~PointLight()
{

}

PointLightPtr PointLight::create(const ngl::Vec4 &_pos, const ngl::Vec4 &_ambCol, const ngl::Vec4 &_diffCol, const ngl::Vec4 &_specCol)
{
    return PointLightPtr(new PointLight(_pos, _ambCol, _diffCol, _specCol));
}

void PointLight::loadToShader(const std::string &_uniform, const std::string &_shader) const
{
    ngl::ShaderLib *shader = ngl::ShaderLib::instance();
    (*shader)[_shader]->use();

    shader->setShaderParam4f(_uniform+".pos",
                             m_pos[0],
                             m_pos[1],
                             m_pos[2],
                             m_pos[3]);
    shader->setShaderParam4f(_uniform+".ambCol",
                             m_ambientColor[0],
                             m_ambientColor[1],
                             m_ambientColor[2],
                             m_ambientColor[3]);
    shader->setShaderParam4f(_uniform+".diffCol",
                             m_diffuseColor[0],
                             m_diffuseColor[1],
                             m_diffuseColor[2],
                             m_diffuseColor[3]);
    shader->setShaderParam4f(_uniform+".specCol",
                             m_specularColor[0],
                             m_specularColor[1],
                             m_specularColor[2],
                             m_specularColor[3]);

}

void PointLight::draw()
{
    Renderer *r = Renderer::instance();
    ngl::ShaderLib *shader = ngl::ShaderLib::instance();
    (*shader)["Constant"]->use();

    shader->setShaderParam4f("colour", 0,1,0,1);
    shader->setShaderParam1f("textured",0);
    ngl::Mat4 mat;
    mat.translate(m_pos[0],m_pos[1],m_pos[2]);
    r->loadMatrixToShader(mat,"Constant");
    r->draw("enemy", "Constant");
}
