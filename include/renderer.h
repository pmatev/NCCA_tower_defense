#ifndef RENDERER_H
#define RENDERER_H

#include "ngl/Util.h"
#include "ngl/ShaderLib.h"
#include "ngl/Light.h"
#include "camera.h"

//-------------------------------------------------------------------//
/// @file renderer.h
/// @brief The Renderer Class. Singleton which handles all the drawing
/// functions, lights, camera, shaders and scene rendering.
/// @author Peter Matev
/// @version 1
/// @date 04/12/12
/// Revision History :
/// Initial Version 04/12/12
/// @class Renderer
//-------------------------------------------------------------------//


class Renderer
{
public:
    static Renderer* instance();
    void destroy();

    void init();
    void loadMatrixToShader(ngl::TransformStack &_tx, std::string _shader);
    void loadLightToShader(ngl::Light *_light, std::string _shader);

    void createShader(std::string _name);

    inline Camera* getCam() const {return m_cam;}


protected:
    Renderer();
    ~Renderer();

    static Renderer* s_instance;

    std::vector<std::string> m_shaderNames;
    std::vector<ngl::Light> m_lights;

    Camera *m_cam;

};

#endif // RENDERER_H
