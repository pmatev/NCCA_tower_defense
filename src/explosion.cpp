#include "include/explosion.h"
#include <boost/foreach.hpp>
#include "database.h"


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
  // adjust time
  m_currentAge += _dt;

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
          // make the enemy is not exactly on the edge
//          float weight;
//          if(m_sqrRadius - sqrDist == 0)
//          {
//            weight = 0;
//          }
//          else
//          {
//            weight  = m_sqrRadius/(m_sqrRadius - sqrDist);

//          }
          float weight  = (m_sqrRadius - sqrDist) / m_sqrRadius;
          o_damages.push_back(
                Damage(
                  recordStrong->m_id,
                  m_damage * weight
                  )
                );
          ngl::Vec3 impulseVec = relVec;
          float len = impulseVec.length();
          if(len)
          {
            impulseVec /= len;
            impulseVec *= weight * m_power * -1;
            impulseVec[1] = 0;
          }
          // invert vector
//          for(int i =0; i<3; ++i)
//          {
//            if(impulseVec[i] != 0)
//            {
//              impulseVec[i] = (1.0 / impulseVec[i]) * m_power;
//            }
//            else
//            {
//              impulseVec[i] = m_power;
//            }
//          }
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

  // Check if dead and return
  return m_currentAge > m_lifetime;
}
