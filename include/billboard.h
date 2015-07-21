#ifndef BILLBOARD_H
#define BILLBOARD_H

#include "ngl/Vec4.h"
#include "ngl/Mat4.h"
#include "smartpointers.h"
#include <string>

DECLARESMART(Billboard)

/// @file billboard.h
/// @brief Provides functionality for 2D and 3D billboards.
/// @author Peter Matev
/// @version 1.0
/// @date 01/03/2013
/// Revision History :
/// Initial Version 01/03/2013
/// @class Billboard
/// @brief A simple textured quad which can be used to draw 2D or 3D camera-
/// facing objects such as health-bars/sprites as well as UI elements and
/// camera-space geometry.

class Billboard
{
public:
    //-------------------------------------------------------------------//
    /// @enum defines the two types of billboards
    //-------------------------------------------------------------------//
    enum Type{
        b2D, // 2D billboard
        b3D // 3D billboard
    };

    //-------------------------------------------------------------------//
    /// @struct a struct to define the vertex data packing structure
    //-------------------------------------------------------------------//
    struct VertData
    {
    float x;
    float y;
    float u;
    float v;
    };

    //-------------------------------------------------------------------//
    /// @brief a parameterised constructor
    /// @param [in] _type   : the type of billboard to create (b2D or b3D)
    /// @param [in] _pos    : position
    /// @param [in] _width  : width
    /// @param [in] _height : height
    //-------------------------------------------------------------------//
    static BillboardPtr create( const Type &_type,
                                const ngl::Vec4 &_pos,
                                const float &_width,
                                const float &_height);

    //-------------------------------------------------------------------//
    /// @brief destructor
    //-------------------------------------------------------------------//
    ~Billboard();

    //-------------------------------------------------------------------//
    /// @brief a function to initialize the vert data and create the
    /// relevant VAOs.
    //-------------------------------------------------------------------//
    void init();

    //-------------------------------------------------------------------//
    /// @brief draw the billboard to the screen.
    /// @param [in] _shader : the shader to use when drawing the billboard
    //-------------------------------------------------------------------//
    void draw(const std::string &_shader);

    //-------------------------------------------------------------------//
    /// @brief scales the UV coordinates of the mesh relative the center
    /// @param [in] _scaleU : scale factor in U
    /// @param [in] _scaleV : scale factor in V
    //-------------------------------------------------------------------//
    void setUVScale(const float _scaleU, const float _scaleV);

    /* --------------------- GETTERS AND SETTERS ----------------------- */
    //-------------------------------------------------------------------//
    /// @brief setter for the position variable
    /// @param [in] _v : position to set
    //-------------------------------------------------------------------//
    inline void setPos(const ngl::Vec4 _v){m_pos = _v;}

    //-------------------------------------------------------------------//
    /// @brief getter for the position variable
    //-------------------------------------------------------------------//
    inline ngl::Vec4 getPos() const {return m_pos;}

    //-------------------------------------------------------------------//
    /// @brief setter for the transform matrix
    /// @param [in] _m : matrix to set to.
    //-------------------------------------------------------------------//
    inline void setMatrix(const ngl::Mat4 _m){m_transform = _m;}

    //-------------------------------------------------------------------//
    /// @brief getter for the transform matrix
    //-------------------------------------------------------------------//
    inline ngl::Mat4 getMatrix() const {return m_transform;}

protected:

    //-------------------------------------------------------------------//
    /// @brief stores the type of billboard this is
    //-------------------------------------------------------------------//
    Type m_type;

    //-------------------------------------------------------------------//
    /// @brief position
    //-------------------------------------------------------------------//
    ngl::Vec4 m_pos;

    //-------------------------------------------------------------------//
    /// @brief width
    //-------------------------------------------------------------------//
    float m_width;

    //-------------------------------------------------------------------//
    /// @brief height
    //-------------------------------------------------------------------//
    float m_height;

    //-------------------------------------------------------------------//
    /// @brief transformation matrix
    //-------------------------------------------------------------------//
    ngl::Mat4 m_transform;

    //-------------------------------------------------------------------//
    /// @brief unique ID
    //-------------------------------------------------------------------//
    unsigned int m_ID;

    //-------------------------------------------------------------------//
    /// @brief unique ID in string format
    //-------------------------------------------------------------------//
    std::string m_IDStr;

    //-------------------------------------------------------------------//
    /// @brief stores 6 sets of VertData: 2 triangles, to make a quad.
    //-------------------------------------------------------------------//
    VertData m_data[6];

private:
    //-------------------------------------------------------------------//
    /// @brief hidden constructor ensures the create() method is always used.
    /// @param [in] _type   : the type of billboard to create (b2D or b3D)
    /// @param [in] _pos    : position
    /// @param [in] _width  : width
    /// @param [in] _height : height
    //-------------------------------------------------------------------//
    Billboard(const Type &_type,
              const ngl::Vec4 &_pos,
              const float &_width,
              const float &_height);
};

#endif // BILLBOARD_H
