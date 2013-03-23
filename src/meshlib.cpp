#include "include/meshlib.h"

//-------------------------------------------------------------------//
MeshLibPtr MeshLib::s_instance = MeshLibPtr();

MeshLibWPtr MeshLib::instance()
{
    if(!s_instance)
    {
        s_instance = MeshLibPtr(new MeshLib());
    }
    return s_instance;
}

//-------------------------------------------------------------------//

MeshLib::MeshLib()
{
}

//-------------------------------------------------------------------//

MeshLib::~MeshLib()
{
}

//-------------------------------------------------------------------//

void MeshLib::init()
{
  createMeshFromObj("models/turret_base.obj",
                    "turret_base");
  createMeshFromObj("models/turret_cannon.obj",
                    "turret_cannon");
  createMeshFromObj("models/enemy2.obj",
                    "enemy");
  createMeshFromObj("models/hexagon2.obj",
                    "hexagon");
  createMeshFromObj("models/base.obj",
                    "base");
  createMeshFromObj("models/wall.obj",
                    "wall");
  createMeshFromObj("models/bullet.obj",
                    "bullet");
}

void MeshLib::createMeshFromObj(const std::string &_file,
                                std::string _name)
{
  //Create Mesh
  m_meshes[_name] = Mesh::create(_file,
                                 _name);
}

std::vector<Renderer::vertData> MeshLib::getVertDataFromMesh(std::string _name)
{
  MeshPtr mesh = m_meshes[_name];
  return mesh->getVertData();
}
