#ifndef RENDERER_H
#define RENDERER_H

#include "ngl/Util.h"
#include "SDL/SDL_opengl.h"
#include "ngl/ShaderLib.h"
#include "ngl/Light.h"
#include "camera.h"
#include "ngl/VertexArrayObject.h"

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

typedef boost::shared_ptr<ngl::VertexArrayObject> VAOPtr;
typedef boost::shared_ptr<ngl::TransformStack> TXPtr;

struct vertData
{
  GLfloat x; // position
  GLfloat y;
  GLfloat z;
  GLfloat nx; // normal
  GLfloat ny;
  GLfloat nz;
};

class Renderer
{
public:
    static Renderer* instance();
    void destroy();

    void init();

    void resize(const unsigned int _w, const unsigned int _h);

    void createShader(std::string _name);

    void createVAO(std::string _id, GLenum _drawType);


    void setDataToVAO(std::string _id, unsigned int _size, GLfloat &_data, unsigned int _numIndices);
    void setIndexedDataToVAO(std::string _id, unsigned int _size, const GLfloat &_data, unsigned int _indexSize, const GLvoid *_indexData, unsigned int _numIndices);
    void draw(std::string _id, std::string _shader);

    void drawSelection(unsigned int _id, std::string _idStr);
    void prepareDrawSelection();
    ngl::Vec3 readColourSelection(const int _x, const int _y);

    //vertData packData(const ngl::Vec3 &_vert, ngl::Vec3 &_norm);

    void loadMatrixToShader(ngl::TransformStack &_tx, std::string _shader);
    void loadMatrixToShaderSS(ngl::TransformStack &_tx, std::string _shader);
    void loadLightToShader(ngl::Light *_light, std::string _shader);

    VAOPtr bindVAOByID(const std::string _id);

    inline Camera* getCam() const {return m_cam;}



protected:
    Renderer();
    ~Renderer();

    static Renderer* s_instance;

    std::vector<std::string> m_shaderNames;
    std::vector<ngl::Light> m_lights;

    std::map<std::string, VAOPtr> m_mapVAO;

    Camera *m_cam;
    ngl::Camera *m_orthoCam;




};

#endif // RENDERER_H
