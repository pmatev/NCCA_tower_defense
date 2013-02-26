#include "concrete/bullet.h"

//-------------------------------------------------------------------//

Bullet::Bullet(
    const ngl::Vec3 &_pos,
    const ngl::Vec3 &_aim,
    unsigned int _id
    ) :
  Projectile(_pos,_aim, _id)
{
  m_damage = 20;
  m_maxVelocity = 10;
  m_velocity = 2;
  generateMesh();
}

void Bullet::init()
{
}

//-------------------------------------------------------------------//

EntityPtr Bullet::create(
    const ngl::Vec3 &_pos,
    const ngl::Vec3 &_aim,
    unsigned int _id
    )
{
  //create and return a smart pointer to the bullet

  EntityPtr bullet(new Bullet(_pos,_aim, _id));
  return bullet;
}

//-------------------------------------------------------------------//

//void Bullet::draw()
//{
//  Renderer *r = Renderer::instance();
//  //m_transformStack.setScale(0.3, 0.3, 0.3);
//  r->loadMatrixToShader(m_transformStack, "Phong");

//  r->draw(m_IDStr, "Phong");
//}

//-------------------------------------------------------------------//

void Bullet::generateMesh()
{
  const static GLubyte indices[]=  {
                                      0,1,5,0,4,5, // back
                                      3,2,6,7,6,3, // front
                                      0,1,2,3,2,0, // top
                                      4,5,6,7,6,4, // bottom
                                      0,3,4,4,7,3,
                                      1,5,2,2,6,5
                                   };

  GLfloat vertices[] = {-0.1,0.1,-0.1,
                        0.1,0.1,-0.1,
                        0.1,0.1,0.1,
                        -0.1,0.1,0.1,
                        -0.1,-0.1,-0.1,
                        0.1,-0.1,-0.1,
                        0.1,-0.1,0.1,
                        -0.1,-0.1,0.1
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

  std::vector<Renderer::vertData> boxData;
  Renderer::vertData d;
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


  //call to generate the bounding box

  generateLsBBox(boxData);
  Renderer *render = Renderer::instance();

  render->createVAO(m_IDStr, GL_TRIANGLES);
  render->setIndexedDataToVAO(
        m_IDStr,
        sizeof(Renderer::vertData)*boxData.size(),
        3,
        boxData[0].x,
        sizeof(indices),
        &indices[0],
        sizeof(indices)/sizeof(GLubyte)
        );
}


//-------------------------------------------------------------------//

//void Bullet::drawSelection()
//{
//  Renderer *r = Renderer::instance();
//  //m_transformStack.setScale(0.3, 0.3, 0.3);
//  r->loadMatrixToShader(m_transformStack, "Colour");

//  r->drawSelection(m_ID, m_IDStr);
//}

//-------------------------------------------------------------------//

ngl::Vec3 Bullet::brain()
{
  // for the moment just have the bullet follow it's aim

  return m_aimVector;
}

//-------------------------------------------------------------------//

void Bullet::filterViewVolume(EntityRecordList &o_localEntities)
{
  Q_UNUSED(o_localEntities);
}
