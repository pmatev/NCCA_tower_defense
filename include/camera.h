#ifndef CAMERA_H
#define CAMERA_H



#include <ngl/Camera.h>
#include <ngl/TransformStack.h>
#include <ngl/Vec3.h>
#include <ngl/Vec4.h>
#include "fwd/window.h"

/// @file Camera.h
/// @brief An extension of the ngl::Camera class to provide smooth navigation.
/// @author Peter Matev
/// @version 1.0
/// @date 29/03/2012
/// Revision History :
/// Initial Version 29/03/2012
/// @class Camera
/// @brief Extends the functionality of the ngl::Camera to provide dolly, track and tumble movement using quaternions.
/// Also provides a mechanism for following a Bundle and tumbling around it.
class Camera : public ngl::Camera {


public:
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Constructor for Camera
    //----------------------------------------------------------------------------------------------------------------------
    Camera();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Constructor for Camera
    /// @param [in] _from eye vector
    /// @param [in] _to look vector
    /// @param [in] _up the up vector
    //----------------------------------------------------------------------------------------------------------------------
    Camera(const ngl::Vec4 &_from, const ngl::Vec4 &_to, const ngl::Vec4 &_up);
    //Camera(Bundle *_parentBundle);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Destructor for Camera
    //----------------------------------------------------------------------------------------------------------------------
    ~Camera();


    //----------------------------------------------------------------------------------------------------------------------
    /// @brief update the eye and look vectors
    //----------------------------------------------------------------------------------------------------------------------
    void update();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief set the eye and look vectors to the ngl::Camera
    //----------------------------------------------------------------------------------------------------------------------
    void setNew();

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief function to tumble the camera around the look position using quaternion rotations
    /// @param [in] _oldX previous mouse position X coord
    /// @param [in] _oldX previous mouse position Y coord
    /// @param [in] _newX mouse position X coord
    /// @param [in] _newX mouse position Y coord
    //----------------------------------------------------------------------------------------------------------------------
    void tumble(int _oldX, int _oldY, int _newX, int _newY);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief function to track the camera
    /// @param [in] _oldX previous mouse position X coord
    /// @param [in] _oldX previous mouse position Y coord
    /// @param [in] _newX mouse position X coord
    /// @param [in] _newX mouse position Y coord
    //----------------------------------------------------------------------------------------------------------------------
    void track(int _oldX, int _oldY, int _newX, int _newY);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief function to dolly the camera in and out along the viewing normal
    /// @param [in] _oldX previous mouse position X coord
    /// @param [in] _newX mouse position X coord
    //----------------------------------------------------------------------------------------------------------------------
    void dolly(int _oldX, int _newX);


    /// @brief set the radius of the sphere which the camera eye can move on
    //----------------------------------------------------------------------------------------------------------------------
    inline void setRadius(float _z){m_radius = _z;}
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief get the radius of the sphere which the camera eye can move on
    //----------------------------------------------------------------------------------------------------------------------
    inline float getRadius(){return m_radius;}

protected:

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief tumble velocity - for momentum tumble /* NOT IMPLEMENTED */
    //----------------------------------------------------------------------------------------------------------------------
    float m_tumbleVel;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief tumble angle - for momentum tumble /* NOT IMPLEMENTED */
    //----------------------------------------------------------------------------------------------------------------------
    float m_tumbleAngle;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief radius of the sphere in screen space
    //----------------------------------------------------------------------------------------------------------------------
    float m_radius;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the axis about which to rotate when tumbling
    //----------------------------------------------------------------------------------------------------------------------
    ngl::Vec3 m_rotAxis;
};
#endif // CAMERA_H
