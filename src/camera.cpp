#include <iostream>
#include "ngl/Camera.h"
#include "ngl/Quaternion.h"
#include "ngl/Mat4.h"
#include "camera.h"
#include "window.h"

Camera::Camera()
{
    this->setDefaultCamera();
}
//----------------------------------------------------------------------------------------------------------------------
Camera::Camera(const ngl::Vec4 &_eye, const ngl::Vec4 &_look, const ngl::Vec4 &_up)
{
    //ngl::Camera.m_projectionMode = ngl::PERSPECTIVE;
    this->setDefaultCamera();
    //this->set(_eye,_look,_up);

    m_eye = _eye;
    m_look = _look;
    m_up = _up;

    m_rotAxis = ngl::Vec4(0,1,0,0);
    m_radius=1.5;

    update();

}
//----------------------------------------------------------------------------------------------------------------------
Camera::~Camera()
{
    std::cout<<"dtor Camera"<<std::endl;
}
//--------------------------------------------------------------------------------//
void Camera::update()
{
    this->set(m_eye.toVec3(), m_look.toVec3(), ngl::Vec3(0,1,0));

   // std::cout<<m_eye<<" "<<m_look<<" "<<std::endl;
}


//----------------------------------------------------------------------------------------------------------------------
void Camera::dolly(int _oldX, int _newX)
{
    int dx =  _oldX - _newX;
    //m_radius = dx*0.01;

    ngl::Vec4 N = getN();

    m_eye += N*(dx*0.1);

    update();

    //std::cout<<"dolly"<<std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
void Camera::track(int _oldX, int _oldY, int _newX, int _newY)
{

    int dx = _newX - _oldX;
    int dy = _newY - _oldY;
    dx*=-1;

    ngl::Vec4 v(dx, dy, 0);
    v.normalize();
    v = getViewMatrix()*v;

    v *= 0.1;

    m_eye += v;
    m_look += v;

    update();

    //std::cout<<"track"<<std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
void Camera::tumble(int _oldX, int _oldY, int _newX, int _newY)
{

    Window* window = Window::instance();
    double screenWidth = window->getScreenWidth();
    double screenHeight = window->getScreenHeight();


    /* Ensure mouse has moved */
    if(_oldX == _newX && _oldY==_newY)
    {
        return;
    }

    //update();


    /* Map screen coords of v1 and v2 to sphere in camera space */

    ngl::Mat4 V = this->getViewMatrix();

    double oldX = 2*(double) _oldX / (double) screenWidth;
    double oldY = 2*(double) _oldY / (double) screenHeight;
    oldX = oldX - 1;
    oldY = 1 - oldY;

    double oldZ = std::sqrt(m_radius*m_radius - oldX*oldX - oldY*oldY);

    ngl::Vec4 cam_v1(oldX, oldY, oldZ);
    //std::cout<<v1<<std::endl;


    double newX = 2*(double) _newX / (double) screenWidth;
    double newY = 2*(double) _newY / (double) screenHeight;

    newX = newX - 1;
    newY = 1 - newY;


    double newZ = std::sqrt(m_radius*m_radius - newX*newX - newY*newY);

    ngl::Vec4 cam_v2(newX, newY, newZ);

    /* map to world space */

    ngl::Vec4 wrld_v1 = V*cam_v1;
    ngl::Vec4 wrld_v2 = V*cam_v2;


    // get rotation axis by v1 x v2
    m_rotAxis = wrld_v1.cross(wrld_v2);
    // get angle from v1 dot v2
    float theta = wrld_v1.angleBetween(wrld_v2);

    /* quaternion rotation from axis angle */
    ngl::Quaternion q, q_I, q_cam;
    q.fromAxisAngle(m_rotAxis,theta*300);
    q_I = q.inverse();

    ngl::Vec4 camEye = m_eye - m_look;                        // move back to origin to rotate
    q_cam = ngl::Quaternion(0,camEye[0],camEye[1],camEye[2]);   // make camEye quaternion

    ngl::Quaternion q_newCamEye = q_I*q_cam*q;                  // rotate camEye by rotation quaternion
    ngl::Vec4 newCamEye = q_newCamEye.getVector();
    //ngl::Vector newCamEye = rotQuat * camEye;

    //ngl::Vector d_Eye = newCamEye - camEye;
    //this->moveEye(d_Eye[0],d_Eye[1],d_Eye[2]);

    m_eye = newCamEye + m_look;                                 //move back to look pos

    update();

    //std::cout<<"tumble"<<std::endl;
}
