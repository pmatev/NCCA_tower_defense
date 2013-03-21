#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "smartpointers.h"
#include "ngl/Vec4.h"

DECLARESMART(PointLight)

class PointLight
{
public:
    static PointLightPtr create(const ngl::Vec4 &_pos, const ngl::Vec4 &_ambCol, const ngl::Vec4 &_diffCol, const ngl::Vec4 &_specCol);

    ~PointLight();

    inline void setPos(const ngl::Vec4 &_pos){m_pos = _pos;}
    inline void setAmbient(const ngl::Vec4 &_col){m_ambientColor = _col;}
    inline void setDiffuse(const ngl::Vec4 &_col){m_diffuseColor = _col;}
    inline void setSpecular(const ngl::Vec4 &_col){m_specularColor = _col;}
    inline ngl::Vec4 getPos() const {return m_pos;}
    inline ngl::Vec4 getAmbient() const {return m_ambientColor;}
    inline ngl::Vec4 getDiffuse() const {return m_diffuseColor;}
    inline ngl::Vec4 getSpecular() const {return m_specularColor;}

    void loadToShader(const std::string &_uniform, const std::string &_shader) const;

    void draw();

protected:

    ngl::Vec4 m_pos;
    ngl::Vec4 m_ambientColor;
    ngl::Vec4 m_diffuseColor;
    ngl::Vec4 m_specularColor;


private:
    PointLight(const ngl::Vec4 &_pos, const ngl::Vec4 &_ambCol, const ngl::Vec4 &_diffCol, const ngl::Vec4 &_specCol);
};

#endif // LIGHT_H
