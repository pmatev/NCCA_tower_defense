#include "database.h"
#include "entity.h"

Database * Database::s_instance =0;

//-------------------------------------------------------------------//

Database::Database(
    int _numCellsX,
    int _numCellsY,
    float _environMaxX,
    float _environMaxY,
    float _environMinX,
    float _environMinY
    ) :
    m_base(0,BASE,0,0,0)
{
  //initialise the grids

  m_enemyGrid = DatabaseGrid::create(
        _numCellsX,
        _numCellsY,
        _environMaxX,
        _environMaxY,
        _environMinX,
        _environMinY
        );

  m_projectileGrid = DatabaseGrid::create(
        _numCellsX,
        _numCellsY,
        _environMaxX,
        _environMaxY,
        _environMinX,
        _environMinY
        );

  m_turretGrid = DatabaseGrid::create(
        _numCellsX,
        _numCellsY,
        _environMaxX,
        _environMaxY,
        _environMinX,
        _environMinY
        );

  m_wallGrid = DatabaseGrid::create(
        _numCellsX,
        _numCellsY,
        _environMaxX,
        _environMaxY,
        _environMinX,
        _environMinY
        );

  m_nodeGrid = DatabaseGrid::create(
        _numCellsX,
        _numCellsY,
        _environMaxX,
        _environMaxY,
        _environMinX,
        _environMinY
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

Database * Database::create(
    int _numCellsX,
    int _numCellsY,
    float _environMaxX,
    float _environMaxY,
    float _environMinX,
    float _environMinY
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
            _numCellsY,
            _environMaxX,
            _environMaxY,
            _environMinX,
            _environMinY
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

//-------------------------------------------------------------------//

void Database::addRecord(EntityRecord _record)
{
  //check the type of the enemy and set it according to that variable

  switch (_record.m_generalType)
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

entityRecordListPtr Database::getLocalEntities(
    float _minX,
    float _minY,
    float _maxX,
    float _maxY,
    std::list<GeneralType> &_typeList
    ) const
{
  //initialise a pointer to a list of entity records

  entityRecordListPtr returnList(new std::list<EntityRecord>);

  //initialise an iterator to the beginning of the list of entity
  //records

  std::list<GeneralType>::iterator typeListIt;

  typeListIt = _typeList.begin();

  //and initialise an iterator for the return list

  std::list<EntityRecord>::iterator returnListIt;

  //set up a tempory list to store the reult in

  entityRecordListPtr tempList;

  //cycle through each element of the type list

  for (; typeListIt != _typeList.end(); typeListIt++)
  {
    //then switch through the types and get the local entities of the
    //selected type

    switch ((*typeListIt))
    {
    case ENEMY:
      tempList = m_enemyGrid->getLocalEntities(_minX,_minY,_maxX,_maxY);
      break;
    case PROJECTILE:
      tempList = m_projectileGrid->getLocalEntities(_minX,_minY,_maxX,_maxY);
      break;
    case TURRET:
      tempList = m_turretGrid->getLocalEntities(_minX,_minY,_maxX,_maxY);
      break;
    case WALL:
      tempList = m_wallGrid->getLocalEntities(_minX,_minY,_maxX,_maxY);
      break;
    case NODE:
      tempList = m_nodeGrid->getLocalEntities(_minX,_minY,_maxX,_maxY);
      break;
    case BASE:
      tempList->push_back(m_base);
      break;
    }

    //now add the tempList to the return list if it has elements:

    if (tempList->size()!=0)
    {
      //and if the return list is empty

      if (returnList->size()==0)
      {
        //set the return list iterator to the beginning of the list

        returnListIt = returnList->begin();
      }
      else
      {
        //set the return list iterator to the end of the list

        returnListIt = returnList->end();
      }

      //insert the whole cell list into the return list

      returnList->splice(
            returnListIt,
            (*tempList),
            tempList->begin(),
            tempList->end()
            );
    }

  }


  return returnList;
}
//-------------------------------------------------------------------//

void Database::clearRecords()
{
  // call clear in both of the dynamic entity grids

  m_enemyGrid->clearRecords();
  m_projectileGrid->clearRecords();
}

//-------------------------------------------------------------------//
