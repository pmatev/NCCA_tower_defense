#include "include/meshlib.h"

MeshLibPtr MeshLib::create()
{
  MeshLibPtr a(new MeshLib());
  return a;
}


MeshLib::MeshLib()
{
  createMeshFromObj("models/turret_base.obj",
                    "turret_base");
  createMeshFromObj("models/turret_cannon.obj",
                    "turret_cannon");
  createMeshFromObj("models/enemy.obj",
                    "enemy");
  createMeshFromObj("models/hexagon.obj",
                    "hexagon");
  createMeshFromObj("models/base.obj",
                    "base");
  createMeshFromObj("models/wall.obj",
                    "wall");
}

//Uses data in an obj to create a VAO.
void MeshLib::createMeshFromObj(const std::string &_file,
                                std::string _name)
{
  //Create Mesh
  m_meshes.push_back(Mesh::create(_file,
                                  _name));
}

