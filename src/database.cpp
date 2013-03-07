#include "database.h"
#include "entity.h"

Database * Database::s_instance =0;

//-------------------------------------------------------------------//

Database::Database(
    int _numCellsX,
    int _numCellsZ,
    float _environMaxX,
    float _environMaxZ,
    float _environMinX,
    float _environMinZ
    ) :
  m_base(EntityRecord::create(0,BASE,0,0,0,0,0,0,0,0,0,0,0,0)),
  m_environmentMaxX(_environMaxX),
  m_environmentMinX(_environMinX),
  m_environmentMaxZ(_environMaxZ),
  m_environmentMinZ(_environMinZ)
{
  //initialise the grids

  m_enemyGrid = DatabaseGrid::create(
        _numCellsX,
        _numCellsZ,
        _environMaxX,
        _environMaxZ,
        _environMinX,
        _environMinZ
        );

  m_projectileGrid = DatabaseGrid::create(
        _numCellsX,
        _numCellsZ,
        _environMaxX,
        _environMaxZ,
        _environMinX,
        _environMinZ
        );

  m_turretGrid = DatabaseGrid::create(
        _numCellsX,
        _numCellsZ,
        _environMaxX,
        _environMaxZ,
        _environMinX,
        _environMinZ
        );

  m_wallGrid = DatabaseGrid::create(
        _numCellsX,
        _numCellsZ,
        _environMaxX,
        _environMaxZ,
        _environMinX,
        _environMinZ
        );

  m_nodeGrid = DatabaseGrid::create(
        _numCellsX,
        _numCellsZ,
        _environMaxX,
        _environMaxZ,
        _environMinX,
        _environMinZ
        );

  //initialise base with null values

  m_isBaseSet = false;
}

//-------------------------------------------------------------------//

Database::~Database()
{
  //currently using default destructor
}

//-------------------------------------------------------------------//

Database * Database::init(
    int _numCellsX,
    int _numCellsZ,
    float _environMaxX,
    float _environMaxZ,
    float _environMinX,
    float _environMinZ
    )
{
  //singleton patern based on code from Jon Macey's singleton template

  if (s_instance == 0)
  {
    // create a mutux to stop other threads accessing

    QMutex m;

    // the locker will auto unlock when out of scope

    QMutexLocker locker (&m);
    if (s_instance == 0)
    {
      s_instance = (new Database(
            _numCellsX,
            _numCellsZ,
            _environMaxX,
            _environMaxZ,
            _environMinX,
            _environMinZ
            ));
    }
  }
  return s_instance;
}

//-------------------------------------------------------------------//

Database * Database::instance()
{
  return s_instance;
}

//-------------------------------------------------------------------//

void Database::destroy()
{
  delete s_instance;
}

//-------------------------------------file:///usr/share/doc/HTML/index.html------------------------------//

void Database::addRecord(EntityRecordPtr _record)
{
  //check the type of the enemy and set it according to that variable

  switch (_record->m_generalType)
  {
  case ENEMY:
    m_enemyGrid->addRecord(_record);
    break;
  case PROJECTILE:
    m_projectileGrid->addRecord(_record);
    break;
  case TURRET:
    m_turretGrid->addRecord(_record);
    break;
  case WALL:
    m_wallGrid->addRecord(_record);
    break;
  case NODE:
    m_nodeGrid->addRecord(_record);
    break;
  case BASE:
    m_base = _record;
    m_isBaseSet = true;
    break;
  }
}

//-------------------------------------------------------------------//

void Database::getLocalEntities(
    EntityRecordWCList &o_newList,
    float _minX,
    float _minZ,
    float _maxX,
    float _maxZ,
    std::list<GeneralType> &_typeList
    ) const
{
//  if(!o_newList)
//  {
//    o_newList = std::list<EntityRecord>();
//  }

  //initialise an iterator to the beginning of the list of entity
  //records

  std::list<GeneralType>::iterator typeListIt;

  typeListIt = _typeList.begin();

  //and initialise an iterator for the return list

  EntityRecordWCList::iterator returnListIt;

  //set up a tempory list to store the reult in

  EntityRecordWCList tempList;

  //cycle through each element of the type list

  for (; typeListIt != _typeList.end(); typeListIt++)
  {
    //then switch through the types and get the local entities of the
    //selected type

    switch ((*typeListIt))
    {
    case ENEMY:
      m_enemyGrid->getLocalEntities(tempList, _minX,_minZ,_maxX,_maxZ);
      break;
    case PROJECTILE:
      m_projectileGrid->getLocalEntities(tempList, _minX,_minZ,_maxX,_maxZ);
      break;
    case TURRET:
      m_turretGrid->getLocalEntities(tempList, _minX,_minZ,_maxX,_maxZ);
      break;
    case WALL:
      m_wallGrid->getLocalEntities(tempList, _minX,_minZ,_maxX,_maxZ);
      break;
    case NODE:
      m_nodeGrid->getLocalEntities(tempList, _minX,_minZ,_maxX,_maxZ);
      break;
    case BASE:
      tempList.push_back(EntityRecordWCPtr(m_base));
      break;
    }

    //now add the tempList to the return list if it has elements:

    if (tempList.size()!=0)
    {
      //and if the return list is empty

      if (o_newList.size()==0)
      {
        //set the return list iterator to the beginning of the list

        returnListIt = o_newList.begin();
      }
      else
      {
        //set the return list iterator to the end of the list

        returnListIt = o_newList.end();
      }

      //insert the whole cell list into the return list

      o_newList.splice(
            returnListIt,
            tempList,
            tempList.begin(),
            tempList.end()
            );
    }

  }
}

void Database::getBaseRecord(EntityRecordWCPtr &o_baseRecord)
{
  o_baseRecord = EntityRecordWCPtr(m_base);
}

//-------------------------------------------------------------------//

void Database::clearRecords()
{
  // call clear in both of the dynamic entity grids

  m_enemyGrid->clearRecords();
  m_projectileGrid->clearRecords();
}

//-------------------------------------------------------------------//

void Database::unPublish(GeneralType _generalType, unsigned int _id)
{
  //switch through each type and if it matches the type passed in
  //call unpublish in the appropriate grid passing in the id

  switch (_generalType)
  {
  case ENEMY:
    m_enemyGrid->unPublish(_id);
    break;
  case PROJECTILE:
    m_projectileGrid->unPublish(_id);
    break;
  case TURRET:
    m_turretGrid->unPublish(_id);
    break;
  case WALL:
    m_wallGrid->unPublish(_id);
    break;
  case NODE:
    m_nodeGrid->unPublish(_id);
    break;
  case BASE:
    m_base->m_generalType = BASE;
    m_base->m_id = 0;
//    m_base->m_x = 0;
//    m_base->m_y = 0;
//    m_base->m_z = 0;
    m_isBaseSet = false;
    break;
  }
}

//-------------------------------------------------------------------//

