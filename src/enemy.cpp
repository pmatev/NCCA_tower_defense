#include "enemy.h"
#include "nodemanager.h"
#include "game.h"
#include "boost/utility.hpp"
#include "fwd/database.h"
#include "database.h"
#include "fsm/states/enemystates.h"
#include "ngl/ShaderLib.h"
#include "texturelib.h"

//-------------------------------------------------------------------//

Enemy::Enemy(
    const ngl::Vec3 &_pos,
    const ngl::Vec3 &_aim,
    unsigned int _id,
    int _currencyValue,
    int _scoreValue,
    float _maxPathDistance
    ) :
  DynamicEntity(_pos,_aim,ENEMY, _id),
  m_needNewPath(false),
  m_maxPathDistance(_maxPathDistance),
  m_pathTargetThreshold(1.2), //THIS SHOULD BE A PROPORTION OF THE DISTANCE BETWEEN NODES!!!!!
  //IF ITS TOO LOW ENEMIES WILL NOT MOVE
  m_currencyValue(_currencyValue),
  m_scoreValue(_scoreValue),
  m_killedByUser(true)
{
  m_healthBar = Billboard::create(Billboard::b3D, ngl::Vec4(m_pos), 1, 0.07);

  if(generateTempPath())
  {
    finalisePath();
  }
}

void Enemy::prepareForUpdate()
{
  // Check to see if it's path needs updating
  if(m_needNewPath)
  {
    if(generateTempPath())
    {
      finalisePath();
    }
  }

  //generate the view box
  generateViewBBox();

  // Get the local entities
  std::list<GeneralType> types;
  types.push_back(TURRET);
  types.push_back(ENEMY);
  types.push_back(WALL);
  m_localEntities = EntityRecordWCListPtr(new EntityRecordWCList());
  //EntityRecordList localEntities;
  calculateLocalEntities(*m_localEntities, types);
  // Filter the entities
  filterViewVolume(*m_localEntities);
}

void Enemy::update(const double _dt)
{
  //    //In seconds
  //    float dt = _dt / 1000;

  //    //update the state machine
  //    m_stateMachine->update();

  //    ngl::Vec3 steeringForce = brain();
  //    ngl::Vec3 acceleration = steeringForce / m_mass;
  //    float maxAcceleration = 0.1;

  //    //truncate acceleration to max acc
  //    float accDiff = maxAcceleration / acceleration.length(); //COULD FAIL IF 0
  //    float accScaleFactor = (accDiff < 1.0) ? accDiff : 1.0;
  //    acceleration *= accScaleFactor;

  ////    ngl::Vec3 impulses = m_currentImpulses;
  ////    // if below the ground plane push up
  ////    if(m_pos.m_y < 0)
  ////    {
  ////      impulses += ngl::Vec3(0, -m_pos.m_y, 0);
  ////    }
  ////    else
  ////    {
  ////      // gravity
  ////      impulses += ngl::Vec3(0, -9.8, 0);
  ////    }

  ////    // Add in impulses
  ////    acceleration += impulses / m_mass;


  //    m_velocity += acceleration;

  //    //truncate velocity to max speed
  //    float diff = m_maxVelocity / m_velocity.length(); //COULD FAIL IF 0
  //    float scaleFactor = (diff < 1.0) ? diff : 1.0;
  //    m_velocity *= scaleFactor;

  //    //update position
  //    m_prevPos = m_pos;
  //    m_pos += m_velocity * dt;

  //    enforceGridBoundaries();

  //    m_transformStack.setPosition(m_pos);

  move(_dt);
  ngl::Vec4 healthBarPos(m_pos.m_x, m_pos.m_y+1, m_pos.m_z);
  m_healthBar->setPos(healthBarPos);
}

//-------------------------------------------------------------------//

bool Enemy::generateTempPath()
{
  // THIS IS REALLY MESSY AND NEEDS A COMPLETE REFACTOR, ENEMIES SHOULD NOT HAVE
  // TO ACCESS THE NODEMANAGER!
  EnvironmentPtr env = Game::instance()->getEnvironmentWeakPtr().lock();
  if(env)
  {
    NodeManagerPtr nm = env->getNodeManagerWeakPtr().lock();
    if(nm)
    {
      return nm->findPathFromPos(
            m_tempPathNodes,
            m_pos,
            Game::instance()->getBasePos()
            );
    }
  }
  return false;
}

//-------------------------------------------------------------------//

void Enemy::finalisePath()
{
  m_pathNodes = m_tempPathNodes;
  m_tempPathNodes.clear();
  m_needNewPath = false;
}

//-------------------------------------------------------------------//

Node::NodeWList Enemy::getPath() const
{
  return m_pathNodes;
}

//-------------------------------------------------------------------//

void Enemy::enforceGridBoundaries()
{
  //get an instance of the database

  Database* db = Database::instance();

  //get the minimum and maximum extents of the grid

  ngl::Vec2 minExts = db->getMinGridExtents();
  ngl::Vec2 maxExts = db->getMaxGridExtents();

  //check the position of the entity against the boundaries
  //comparison between z and y because x and z are the planar
  //axis but a vec2 has no m_z component

  if (m_pos.m_x < minExts.m_x)
  {
    //set the x value to the minimum extents of the grid

    m_pos.m_x = minExts.m_x;
  }
  else if (m_pos.m_x > maxExts.m_x)
  {
    //set it to the max

    m_pos.m_x = maxExts.m_x;
  }
  //then check z

  if (m_pos.m_z < minExts.m_y)
  {
    m_pos.m_z = minExts.m_y;
  }
  else if (m_pos.m_z > maxExts.m_y)
  {
    m_pos.m_z = maxExts.m_y;
  }
}

//-------------------------------------------------------------------//

bool Enemy::sphereBBoxCollision(const ngl::Vec3 &_pos,
                                float _radius) const
{
  //set up  the return boolean

  bool result = false;

  //first check if the position of the enemy is within the sphere

  //calculate the square distance from the enemy to the sphere

  float sqDist = (_pos.m_x-m_pos.m_x)*(_pos.m_x-m_pos.m_x)+
      (_pos.m_y-m_pos.m_y)*(_pos.m_y-m_pos.m_y)+
      (_pos.m_z-m_pos.m_z)*(_pos.m_z-m_pos.m_z);

  //calculate the radius squared

  float sqRadius = _radius*_radius;

  //if the distance is less than the radius squared

  if (sqRadius >= sqDist)
  {
    //set the result boolean to be true

    result = true;
  }

  else
  {
    //otherwise, clamp position of the sphere within the boundaries
    //of the bounding box, finding the closest point on the bounding
    //box to the sphere object

    float xPos = _pos.m_x;
    float yPos = _pos.m_y;
    float zPos = _pos.m_z;

    //x

    if(xPos > m_lsMeshBBox.m_maxX+m_pos.m_x)
    {
      xPos = m_lsMeshBBox.m_maxX+m_pos.m_x;
    }
    else if (xPos < m_lsMeshBBox.m_minX+m_pos.m_x)
    {
      xPos = m_lsMeshBBox.m_minX+m_pos.m_x;
    }

    //y

    if(yPos > m_lsMeshBBox.m_maxY+m_pos.m_y)
    {
      yPos = m_lsMeshBBox.m_maxY+m_pos.m_y;
    }
    else if (yPos < m_lsMeshBBox.m_minY+m_pos.m_y)
    {
      yPos = m_lsMeshBBox.m_minY+m_pos.m_y;
    }

    //z

    if(zPos > m_lsMeshBBox.m_maxZ+m_pos.m_z)
    {
      zPos = m_lsMeshBBox.m_maxZ+m_pos.m_z;
    }
    else if (zPos < m_lsMeshBBox.m_minZ+m_pos.m_z)
    {
      zPos = m_lsMeshBBox.m_minZ+m_pos.m_z;
    }

    //then check if the squared distance between the point and
    //the sphere is less than the radius squared

    sqDist = (_pos.m_x-xPos)*(_pos.m_x-xPos)+
        (_pos.m_y-yPos)*(_pos.m_y-yPos)+
        (_pos.m_z-zPos)*(_pos.m_z-zPos);

    if (sqRadius>sqDist)
    {
      result = true;
    }

  }

  return result;
}

void Enemy::draw()
{
    Renderer *r = Renderer::instance();
    TextureLib *tex = TextureLib::instance();
    ngl::ShaderLib *shader = ngl::ShaderLib::instance();

    // draw enemy
    (*shader)["Constant"]->use();
    r->loadMatrixToShader(m_transformStack.getCurrentTransform().getMatrix(), "Constant");

    shader->setShaderParam4f("colour", 0.1,0.1,0.1,1);
    shader->setShaderParam4f("colourSelect", 0,0,0,0);
    r->draw(m_IDStr, "Constant");

    // draw healthbar
    m_healthBar->setUVScale(50/m_health);
    tex->bindTexture("healthbar");
    m_healthBar->draw("TexturedConstant");
}

//-------------------------------------------------------------------//

Damage Enemy::baseTest() const
{
  //first generate a list of local entity records
  Database* db = Database::instance();
//  std::list<GeneralType> typeList;
//  typeList.push_back(BASE);
//  EntityRecordWCList localEntities;
//  db->getLocalEntities(
//        localEntities,
//        m_pos.m_x+m_lsMeshBBox.m_minX-0.5,
//        m_pos.m_z+m_lsMeshBBox.m_minZ-0.5,
//        m_pos.m_x+m_lsMeshBBox.m_maxX+0.5,
//        m_pos.m_z+m_lsMeshBBox.m_maxZ+0.5,
//        typeList
//        );

//  //initialise the return collision

//  Damage c(0,0);

//  //if the list is not empty

//  if (localEntities.size() != 0)
//  {

//    //then tent the iterator
//    EntityRecordWCList::iterator listIt = localEntities.begin();

//    //get the id of the element pointed to by the iterator
//    EntityRecordCPtr recordStrong = listIt->lock();
//    if(recordStrong)
//    {
//      //get the relevant information

//      ngl::Vec3 pos (recordStrong->m_x,recordStrong->m_y,recordStrong->m_z);
//      float  radius = (recordStrong->m_maxX -recordStrong->m_minX)/2;

//      //check for collisions between the entity checking and the one
//      //it's checking against

//      bool result = sphereBBoxCollision(pos,radius);
//      //if there was a collision

//      if (result == true)
//      {
//        //set the id of the collision being returned from the null value
//        //to the one tested

//        c.m_id = recordStrong->m_id;

//        //then set the damage value

//        c.m_damage = m_damage;
//      }
//    }
//  }
    Damage c(0,0);
  EntityRecordWCPtr recordWeak;
  db->getBaseRecord(recordWeak);
  EntityRecordCPtr recordStrong = recordWeak.lock();
  if(recordStrong)
  {
    //get the relevant information

    ngl::Vec3 pos (recordStrong->m_x,recordStrong->m_y,recordStrong->m_z);
    float  radius = (recordStrong->m_maxX -recordStrong->m_minX)/2;

    //check for collisions between the entity checking and the one
    //it's checking against

    bool result = sphereBBoxCollision(pos,radius);
    //if there was a collision

    if (result == true)
    {
      //set the id of the collision being returned from the null value
      //to the one tested

      c.m_id = recordStrong->m_id;

      //then set the damage value

      c.m_damage = m_damage;
    }
  }

  //finally return the collision struct

  return c;
}

//-------------------------------------------------------------------//

Enemy::~Enemy()
{
}
