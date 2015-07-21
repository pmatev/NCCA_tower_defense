#ifndef CAMERA_H
#define CAMERA_H

#include <ngl/Camera.h>
#include "fwd/camera.h"
#include "fwd/window.h"

/// @file Camera.h
/// @brief An extension of the ngl::Camera class to provide smooth navigation.
/// @author Peter Matev
/// @version 1.1
/// @date 24/03/2013
/// Revision History :
/// Initial Version 29/03/2012
/// @class Camera
/// @brief Extends the functionality of the ngl::Camera to provide dolly, track and tumble movement using quaternions.
/// This version of the camera class has been customised specifically for this Tower Defence project.

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

    /// @brief radius of the sphere in screen space
    //----------------------------------------------------------------------------------------------------------------------
    float m_radius;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the axis about which to rotate when tumbling
    //----------------------------------------------------------------------------------------------------------------------
    ngl::Vec3 m_rotAxis;
};
#endif // CAMERA_H
