#include "projectile.h"
#include "database.h"

//-------------------------------------------------------------------//

Projectile::Projectile(
    const ngl::Vec3 &_pos,
    const ngl::Vec3 &_aim,
    unsigned int _id
    ) :
  DynamicEntity(_pos,_aim,PROJECTILE, _id)
{
  ;
}

//-------------------------------------------------------------------//

