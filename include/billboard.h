#ifndef BILLBOARD_H
#define BILLBOARD_H

#include "ngl/Vec4.h"
#include "ngl/Mat4.h"
#include "smartpointers.h"
#include <string>

DECLARESMART(Billboard)

class Billboard
{
public:
    enum Type{
        b2D, // 2D billboard
        b3D // 3D billboard
    };

    struct vertData
    {
    float x;
    float y;
    float u;
    float v;
    };


    static BillboardPtr create(const Type &_type, const ngl::Vec4 &_pos, const float &_width, const float &_height);
    void init();

    ~Billboard();

    void draw(const std::string &_shader);


    void setUVScale(const float _s);
    inline void setPos(const ngl::Vec4 _v){m_pos = _v;}
    inline void setMatrix(const ngl::Mat4 _m){m_transform = _m;}
    inline ngl::Vec4 getPos() const {return m_pos;}
    inline ngl::Mat4 getMatrix() const {return m_transform;}

    void setTextureID(const unsigned int &_id);
    unsigned int getTextureID() const {return m_texture;}

protected:

    Type m_type;
    ngl::Vec4 m_pos;
    float m_width;
    float m_height;

    unsigned int m_texture;

    ngl::Mat4 m_transform;

    unsigned int m_ID;

    std::string m_IDStr;

private:
    Billboard(const Type &_type, const ngl::Vec4 &_pos, const float &_width, const float &_height);
};

#endif // BILLBOARD_H
