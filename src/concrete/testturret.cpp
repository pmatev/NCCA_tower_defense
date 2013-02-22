#include "include/concrete/testturret.h"
#include "renderer.h"

//-------------------------------------------------------------------//
TestTurret::TestTurret(
    NodePtr _linkedNode,
    unsigned int &_id
    ):
  Turret(
    _linkedNode,
    _id
    )
{
  m_fov = 90;
  m_viewDistance = 10;
  m_maxRotationSpeed = 3;
  // pass everything into the turret
  generateMesh();
  publish();
}

//-------------------------------------------------------------------//

EntityPtr TestTurret::create(
    NodePtr _linkedNode,
    unsigned int _id
    )
{
  // pass everything to the ctor
  EntityPtr a(new TestTurret(
                    _linkedNode,
                    _id
                    )
                  );
  return a;
}
//-------------------------------------------------------------------//

void TestTurret::generateMesh()
{
  const static GLubyte indices[]=  {
                                      0,1,5,0,4,5, // back
                                      3,2,6,7,6,3, // front
                                      0,1,2,3,2,0, // top
                                      4,5,6,7,6,4, // bottom
                                      0,3,4,4,7,3,
                                      1,5,2,2,6,5
                                   };

  GLfloat vertices[] = {-0.5,0.5,-0.5,
                        0.5,0.5,-0.5,
                        0.5,0.5,0.5,
                        -0.5,0.5,0.5,
                        -0.5,-0.5,-0.5,
                        0.5,-0.5,-0.5,
                        0.5,-0.5,0.5,
                        -0.5,-0.5,0.5
                       };
  GLfloat normals[] = {0,1,-1,
                        0,1,-1,
                        0,1,1,
                       0,1,1,
                        0,-1,-1,
                        0,-1,-1,
                        0,-1,1,
                        0,-1,1
                       };

  std::vector<vertData> boxData;
  vertData d;
  for(int j=0; j<8; j++)
  {
    d.x = vertices[j*3];
    d.y = vertices[(j*3)+1];
    d.z = vertices[(j*3)+2];
    d.nx = normals[j*3];
    d.ny = normals[(j*3)+1];
    d.nz = normals[(j*3)+2];

    boxData.push_back(d);
  }


  //call top generate the mesh bounding box

  generateLsBBox(boxData);

  Renderer *render = Renderer::instance();

  render->createVAO(m_IDStr, GL_TRIANGLES);

  render->setIndexedDataToVAO(
        m_IDStr,
        sizeof(vertData)*boxData.size(),
        3,
        boxData[0].x,
        sizeof(indices),
        &indices[0],
        sizeof(indices)/sizeof(GLubyte)
        );
}

//-------------------------------------------------------------------//

void TestTurret::draw()
{
  Renderer *r = Renderer::instance();
  //m_transformStack.setScale(0.5, 0.5, 0.5);
  r->loadMatrixToShader(m_transformStack, "Phong");

  r->draw(m_IDStr, "Phong");
}

//-------------------------------------------------------------------//

void TestTurret::drawSelection()
{
  Renderer *r = Renderer::instance();
  //m_transformStack.setScale(0.5, 0.5, 0.5);
  r->loadMatrixToShader(m_transformStack, "Colour");

  r->drawSelection(m_ID, m_IDStr);
}

//-------------------------------------------------------------------//

ngl::Vec3 TestTurret::brain()
{
  // do something
  // return test aim
  return ngl::Vec3(0, 1, 0);
}

//-------------------------------------------------------------------//

