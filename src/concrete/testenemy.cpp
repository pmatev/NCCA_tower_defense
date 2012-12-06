#include "concrete/testenemy.h"
#include "renderer.h"
//-------------------------------------------------------------------//

TestEnemy::TestEnemy(
    float _damage,
    float _maxVelocity,
    const ngl::Vec3 & _pos,
    float _initialVelocity,
    const ngl::Vec3 &_aim
    ):
  Enemy(
    _damage,
    _maxVelocity,
    _pos,
    _initialVelocity,
    _aim
    )
{
  // ctor just passes everything to parent class
  // HACKY TESTING HERE
  generateMesh();
  m_active = false;
}

//-------------------------------------------------------------------//

TestEnemy::~TestEnemy()
{
  //currently using default
}

//-------------------------------------------------------------------//

EntityPtr TestEnemy::create(
    float _damage,
    float _maxVelocity,
    const ngl::Vec3 &_pos,
    float _initialVelocity,
    const ngl::Vec3 &_aim
    )
{
  EntityPtr a(
        new TestEnemy(
          _damage,
          _maxVelocity,
          _pos,
          _initialVelocity,
          _aim
          )
        );
  return a;
}

//-------------------------------------------------------------------//

void TestEnemy::generateMesh()
{
  const static GLubyte indices[]=  {
                                      0,1,5,0,4,5, // back
                                      3,2,6,7,6,3, // front
                                      0,1,2,3,2,0, // top
                                      4,5,6,7,6,4, // bottom
                                      0,3,4,4,7,3,
                                      1,5,2,2,6,5
                                   };

  GLfloat vertices[] = {-1,1,-1,
                        1,1,-1,
                        1,1,1,
                        -1,1,1,
                        -1,-1,-1,
                        1,-1,-1,
                        1,-1,1,
                        -1,-1,1
                       };
  GLfloat normals[] = {-1,1,-1,
                        1,1,-1,
                        1,1,1,
                        -1,1,1,
                        -1,-1,-1,
                        1,-1,-1,
                        1,-1,1,
                        -1,-1,1
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


  Renderer *render = Renderer::instance();

  render->createVAO(m_IDStr, GL_TRIANGLES);

  render->setIndexedDataToVAO(
        m_IDStr,
        sizeof(vertData)*boxData.size(),
        boxData[0].x,
        sizeof(indices),
        &indices[0],
        sizeof(indices)/sizeof(GLubyte)
        );

}

//-------------------------------------------------------------------//

ngl::Vec3 TestEnemy::brain()
{
  // TEST value (tells it to just go forward)
  return ngl::Vec3(0.0, 0, 0);
}

//-------------------------------------------------------------------//

void TestEnemy::draw()
{
    Renderer *r = Renderer::instance();

    r->loadMatrixToShader(m_transformStack, "Phong");

    r->draw(m_IDStr, "Phong");

}

//-------------------------------------------------------------------//

void TestEnemy::drawSelection()
{
  Renderer *r = Renderer::instance();

  r->loadMatrixToShader(m_transformStack, "Colour");

  r->drawSelection(m_ID, m_IDStr);
}

//-------------------------------------------------------------------//
