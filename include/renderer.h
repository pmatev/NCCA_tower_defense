#ifndef RENDERER_H
#define RENDERER_H

#include "ngl/Types.h"
#include "ngl/Light.h"
#include "camera.h"
#include "ngl/VertexArrayObject.h"
#include "ngl/TransformStack.h"
#include "ngl/Obj.h"



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

class Renderer
{

public:
    const static int TEXTURE_WIDTH=2048;
    const static int TEXTURE_HEIGHT=2048;
    struct vertData
    {
      GLfloat x; // position
      GLfloat y;
      GLfloat z;
      GLfloat nx; // normal
      GLfloat ny;
      GLfloat nz;
    };
    struct vertData2D
    {
      GLfloat x;
      GLfloat y;
    };


    //-------------------------------------------------------------------//
    /// @brief instances the singleton
    //-------------------------------------------------------------------//
    static Renderer* instance();
    //-------------------------------------------------------------------//
    /// @brief destroys the singleton
    //-------------------------------------------------------------------//
    void destroy();
    //-------------------------------------------------------------------//
    /// @brief initialises the renderer. Creates the shader programs, registers
    /// uniforms and creates the FBOs
    //-------------------------------------------------------------------//
    void init();

    //-------------------------------------------------------------------//
    /// @brief gets called when the window resizes. Rebuilds the glViewport and cam
    /// @param [in] _w, width
    /// @param [in] _h, height
    //-------------------------------------------------------------------//
    void resize(const unsigned int _w, const unsigned int _h);

    //-------------------------------------------------------------------//
    /// SHOULD BE REMOVED
    /// @brief wrapper to build shader of default structure quickly.
    /// @param [in] _name, name of the shader (must match the .vs and .fs files)
    /// @param [in] _numAttribs, height
    //-------------------------------------------------------------------//
    void createShader(std::string _name, int _numAttribs);

    //-------------------------------------------------------------------//
    /// @brief creates a VAO and stores it in the map
    /// @param [in] _id, id of the object which creates it
    /// @param [in] _drawType, OpenGL drawing type. GL_TRIANGLES etc.
    //-------------------------------------------------------------------//
    void createVAO(std::string _id, GLenum _drawType);

    //-------------------------------------------------------------------//
    /// @brief removes the vao from the map (which should delete it through smartpointers).
    /// @param [in] _id, id of the vao to delete
    //-------------------------------------------------------------------//
    void deleteVAO(std::string _id);

/* THESE ARE NOT WELL DESIGNED */
    void setDataToVAO(std::string _id, unsigned int _size, GLfloat &_data, unsigned int _numIndices);
    void setIndexedDataToVAO(std::string _id, unsigned int _size, unsigned int _step, const GLfloat &_data, unsigned int _indexSize, const GLvoid *_indexData, unsigned int _numIndices);
    void setIndexedData2D(std::string _id, unsigned int _size, unsigned int _step, const GLfloat &_data, unsigned int _indexSize, const GLvoid *_indexData, unsigned int _numIndices);
/* -------------------- */

    //-------------------------------------------------------------------//
    /// @brief return a pointer to the vao with given id
    /// @param [in] _id, ID for lookup in map
    //-------------------------------------------------------------------//
    VAOPtr getVAObyID(std::string _id);

    //-------------------------------------------------------------------//
    /// @brief bind a VAO by id string (in map)
    /// @param [in] _id, id string to lookup in map
    //-------------------------------------------------------------------//
//    VAOPtr bindVAOByID(const std::string &_id);


    void bindTexture(const std::string &_name);


    //-------------------------------------------------------------------//
    /// @brief object with given id and shader
    /// @param [in] _id, ID of object
    /// @param [in] _shader, "nice" name of shader to draw with
    //-------------------------------------------------------------------//
    void draw(std::string _id, std::string _shader);

    //-------------------------------------------------------------------//
    /// PROBABLY SHOULD BE REMOVED
    /// @brief gets called when the window resizes. Rebuilds the glViewport and cam
    /// @param [in] _id, integer ID of the object to draw
    /// @param [in] _idStr, string ID (to avoid conversion within the function)
    //-------------------------------------------------------------------//
    void drawSelection(unsigned int _id, std::string _idStr);

    //-------------------------------------------------------------------//
    /// PROBABLY SHOULD BE REMOVED
    /// @brief should be called before the draw selection method to ensure
    /// everything is set up correctly
    //-------------------------------------------------------------------//
    void prepareDrawSelection();

    //-------------------------------------------------------------------//
    /// @brief read the pixel data at a given x,y coord in screen space.
    /// @param [in] _x, x pos
    /// @param [in] _y, y pos
    //-------------------------------------------------------------------//
    ngl::Vec4 readPixels(const int _x, const int _y);

    //-------------------------------------------------------------------//
    /// @brief load a transformation matrix to a 3D shader (won't work for
    /// shader which doesnt have MVP uniform
    /// @param [in] _tx, transformation stack (matrix)
    /// @param [in] _shader, which shader to pass the matrix to.
    //-------------------------------------------------------------------//
    void loadMatrixToShader(const ngl::Mat4 &_tx, const std::string &_shader);

    //-------------------------------------------------------------------//
    /// OBSOLETE
    /// @brief read the pixel data at a given x,y coord in screen space.
    /// @param [in] _x, x pos
    /// @param [in] _y, y pos
    //-------------------------------------------------------------------//
    void set2DPosToShader(ngl::Vec2 _pos, std::string _shader);

    //-------------------------------------------------------------------//
    /// @brief laod a light to a given 3D shader
    /// @param [in] _light, pointer to a light object
    /// @param [in] _shader, shader to upload the light to
    //-------------------------------------------------------------------//
    void loadLightToShader(ngl::Light *_light, std::string _shader);

    //-------------------------------------------------------------------//
    /// @brief creates a frame buffer object and puts it in the map with
    /// given "nice" name.
    /// @param [in] _name, nice name to store the fbo id under in the map
    //-------------------------------------------------------------------//
    void createFramebufferObject(const std::string &_name);

    //-------------------------------------------------------------------//
    /// @brief binds a framebuffer by name
    /// @param [in] _name, name to lookup in the map
    //-------------------------------------------------------------------//
    void bindFrameBuffer(const std::string &_name);

    //-------------------------------------------------------------------//
    /// @brief binds a framebuffer directly by id (0 is opengl default i.e. screen)
    /// @param [in] _id, id
    //-------------------------------------------------------------------//
    void bindFrameBuffer(const GLuint _id);

    //-------------------------------------------------------------------//
    /// @brief return a pointer to the camera
    /// @param [out] CameraWPtr: weak pointer to a Camera object
    //-------------------------------------------------------------------//
    inline CameraWPtr getCam() const {return CameraWPtr(m_cam);}

    //-------------------------------------------------------------------//
    /// @brief print out a slightly more intelligent error message
    /// @param [in] _error, OpenGL error to process
    //-------------------------------------------------------------------//
    void fboError(GLenum _error);



    GLuint getTexture(const unsigned int &_i){return m_textures[_i];}

protected:
    //-------------------------------------------------------------------//
    /// @brief constructor
    //-------------------------------------------------------------------//
    Renderer();
    //-------------------------------------------------------------------//
    /// @brief destructor
    //-------------------------------------------------------------------//
    ~Renderer();

    //-------------------------------------------------------------------//
    /// @brief static singleton variable
    //-------------------------------------------------------------------//
    static Renderer* s_instance;

    //-------------------------------------------------------------------//
    /// @brief list of all created shaders
    //-------------------------------------------------------------------//
    std::vector<std::string> m_shaderNames;

    //-------------------------------------------------------------------//
    /// @brief list of all created lights
    //-------------------------------------------------------------------//
    std::vector<ngl::Light> m_lights;

    //-------------------------------------------------------------------//
    /// @brief map of idstrings to vaos
    //-------------------------------------------------------------------/
    std::map<std::string, VAOPtr> m_mapVAO;

    //-------------------------------------------------------------------//
    /// @brief map of "nice" names to frame buffer object ids
    //-------------------------------------------------------------------//
    std::map<std::string, GLuint> m_mapFBO;

    //-------------------------------------------------------------------//
    /// @brief map of "nice" names to mesh OBJ
    //-------------------------------------------------------------------//
    std::map<std::string, ngl::Obj> m_mapMesh;

    //-------------------------------------------------------------------//
    /// @brief the camera
    //-------------------------------------------------------------------//
    CameraPtr m_cam;

    // TMP //
    GLuint m_textures[3];
    GLuint m_boundTexture;
    GLuint m_boundFBO;


};

#endif // RENDERER_H
