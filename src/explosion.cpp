#include "include/explosion.h"
#include <boost/foreach.hpp>
#include <ngl/ShaderLib.h>
#include "database.h"
#include "renderer.h"


//-------------------------------------------------------------------//

Explosion::Explosion(float _power, float _damage, float _radius, const ngl::Vec3 &_pos, float _lifetime):
  m_power(_power),
  m_damage(_damage),
  m_radius(_radius),
  m_sqrRadius(_radius*_radius),
  m_pos(_pos),
  m_currentAge(0),
  m_lifetime(_lifetime)
{
}

//-------------------------------------------------------------------//

ExplosionPtr Explosion::create(float _power, float _damage, float _radius, const ngl::Vec3 &_pos, float _lifetime)
{
  ExplosionPtr a(new Explosion(_power, _damage, _radius, _pos, _lifetime));
  return a;
}

//-------------------------------------------------------------------//

bool Explosion::execute(
    float _dt,
    std::list<Damage> &o_damages,
    std::list<Impulse> &o_impulses
    )
{
  if(m_currentAge == 0)
  {
    preformExplosion(o_damages, o_impulses);
  }
  // adjust time
  m_currentAge += _dt;

  // Check if dead and return
  return m_currentAge > m_lifetime;
}

void Explosion::preformExplosion(
    std::list<Damage> &o_damages,
    std::list<Impulse> &o_impulses
    )
{

  // Get local entities
  EntityRecordWCList localRecords;
  Database *db = Database::instance();
  if(db)
  {
    std::list<GeneralType> types;
    types.push_back(ENEMY);
    db->getLocalEntities(
          localRecords,
          m_pos.m_x - m_sqrRadius,
          m_pos.m_z - m_sqrRadius,
          m_pos.m_x + m_sqrRadius,
          m_pos.m_z + m_sqrRadius,
          types
          );

    // Go through each local Entity add damage and impulses
    BOOST_FOREACH(EntityRecordWCPtr recordWeak, localRecords)
    {
      EntityRecordCPtr recordStrong = recordWeak.lock();
      if(recordStrong)
      {
        ngl::Vec3 relVec(
              m_pos.m_x - recordStrong->m_x,
              m_pos.m_y - recordStrong->m_y,
              m_pos.m_z - recordStrong->m_z
              );
        // find sqr dist
        float sqrDist =
            pow(relVec.m_x, 2) +
            pow(relVec.m_y, 2) +
            pow(relVec.m_z, 2);

        if(sqrDist < m_sqrRadius)
        {
          float weight  = (m_sqrRadius - sqrDist) / m_sqrRadius;
          pow(weight, 2);
          //weight = 1 - weight;
          o_damages.push_back(
                Damage(
                  recordStrong->m_id,
                  m_damage * weight
                  )
                );
          ngl::Vec3 impulseVec = relVec;
          // cap the vector to the plane
          impulseVec[1] = 0;
          float len = impulseVec.length();
          if(len)
          {
            impulseVec /= len;
            impulseVec *= weight * m_power * -1;
          }
          o_impulses.push_back(
                Impulse(
                  recordStrong->m_id,
                  impulseVec
                  )
                );
        }
      }
    }
  }
}

//-------------------------------------------------------------------//

void Explosion::draw()
{
  Renderer *r = Renderer::instance();

  ngl::ShaderLib *shader = ngl::ShaderLib::instance();

  (*shader)["Constant"]->use();

  float explosionSize;
  float weight;
  if(m_currentAge)
  {
    weight = (m_lifetime - m_currentAge) / m_lifetime;
    explosionSize = m_radius * weight;
  }
  else
  {
    explosionSize = m_radius;
  }
  explosionSize *= 15; // adjust for bullet size

  ngl::Mat4 matrix;
  matrix.translate(m_pos.m_x, m_pos.m_y, m_pos.m_z);
  matrix.scale(explosionSize, explosionSize, explosionSize);
  r->loadMatrixToShader(matrix, "Constant");

  shader->setShaderParam4f("colour", 1,1,1,weight*weight);

  r->draw("bullet", "Constant");

}

//-------------------------------------------------------------------//

Explosion::~Explosion()
{
  //std::cout<<"Explosion killed"<<std::endl;
}
