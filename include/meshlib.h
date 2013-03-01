#ifndef MESHLIB_H
#define MESHLIB_H

#include <iostream>
#include <vector>

#include "smartpointers.h"
#include "mesh.h"

DECLARESMART(MeshLib)

class MeshLib
{
public:
  static MeshLibPtr create();
protected:
  MeshLib();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Uses data stored in an OBJ to construct a VAO.
  /// @param[in] _file the OBJ file.
  //----------------------------------------------------------------------------------------------------------------------
  void createMeshFromObj(const std::string& _file, std::string _name);

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Vector to hold meshes
  //----------------------------------------------------------------------------------------------------------------------
  std::vector<MeshPtr> m_meshes;
};

#endif // MESHLIB_H
