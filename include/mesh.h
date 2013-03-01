#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <vector>

#include "ngl/Vec3.h"

#include "smartpointers.h"

DECLARESMART(Mesh)

//NOTE: lots of code in this class is taken from NGL.

class Face
{
public :
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the number of vertices in the face
  //----------------------------------------------------------------------------------------------------------------------
  unsigned int m_numVerts;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief The vertices index
  //----------------------------------------------------------------------------------------------------------------------
  std::vector<unsigned long int> m_vert;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief The texture co-ord index
  //----------------------------------------------------------------------------------------------------------------------
  std::vector<unsigned long int> m_tex;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the normal index
  //----------------------------------------------------------------------------------------------------------------------
  std::vector<unsigned long int> m_norm;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief debug flag to turn face on and off
  //----------------------------------------------------------------------------------------------------------------------
  bool m_textureCoord;
  bool m_normals;
};

class Mesh
{
public:
  static MeshPtr create(const std::string& _file,
                 std::string _name);
protected:
  Mesh(const std::string& _file,
       std::string _name);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Uses data stored in an OBJ to construct a VAO.
  /// @param[in] _file the OBJ file.
  //----------------------------------------------------------------------------------------------------------------------
  void loadObj(const std::string& _file);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Creates VAO using data loaded from the OBJ.
  //----------------------------------------------------------------------------------------------------------------------
  void createVAO();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief parser function to parse the vertex used by boost::spirit parser
  /// @param[in] _begin the start of the string to parse
  //----------------------------------------------------------------------------------------------------------------------
  void parseVertex(const char *_begin);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief parser function to parse the Norma used by boost::spirit parser
  /// @param[in] _begin the start of the string to parse
  //----------------------------------------------------------------------------------------------------------------------
  void parseNormal(const char *_begin);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief parser function to parse the text cord used by boost::spirit parser
  /// @param[in] _begin the start of the string to parse
  //----------------------------------------------------------------------------------------------------------------------
  void parseTextureCoordinate(const char * _begin);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief parser function to parse the Face data used by boost::spirit parser
  /// @param[in] _begin the start of the string to parse
  //----------------------------------------------------------------------------------------------------------------------
  void parseFace(const char * _begin);
  bool isTriangular();


  /// @brief The name of the mesh
  std::string m_name;
  /// @brief The number of vertices in the object
  unsigned long int m_nVerts;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief The number of normals in the object
  //----------------------------------------------------------------------------------------------------------------------
  unsigned long int m_nNorm;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the number of texture co-ordinates in the object
  //----------------------------------------------------------------------------------------------------------------------
  unsigned long int m_nTex;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the number of faces in the object
  //----------------------------------------------------------------------------------------------------------------------
  unsigned long int m_nFaces;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Pointer to the Vertex list
  //----------------------------------------------------------------------------------------------------------------------
  std::vector<ngl::Vec3> m_verts;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Pointer to the Normal List
  //----------------------------------------------------------------------------------------------------------------------
  std::vector<ngl::Vec3> m_norm;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Pointer to the Texture co-ord list (note that only x and y are used)
  //----------------------------------------------------------------------------------------------------------------------
  std::vector<ngl::Vec3> m_tex;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Pointer to the Face list
  //----------------------------------------------------------------------------------------------------------------------
  std::vector<Face> m_face;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  determines if the data is Packed as either TRI or QUAD
  //----------------------------------------------------------------------------------------------------------------------
  GLuint m_dataPackType;
};

#endif // MESH_H
