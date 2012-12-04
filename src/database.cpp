#include "database.h"

Database * Database::s_instance =0;

//-------------------------------------------------------------------//

Database::Database(
    int _numCellsX,
    int _numCellsY,
    float _environMaxX,
    float _environMaxY,
    float _environMinX,
    float _environMinY
    ):
  m_numCellsX(_numCellsX),
  m_environMinX(_environMinX),
  m_environMinY(_environMinY)
{
  //checks that the min values are less than the max values
  //and if not it swaps them

  if (m_environMinX > _environMaxX)
  {
    float temp = m_environMinX;
    m_environMinX = _environMaxX;
    _environMaxX = temp;
  }

  if (m_environMinY > _environMaxY)
  {
    float temp = m_environMinY;
    m_environMinY = _environMaxY;
    _environMaxY = temp;
  }


  //calculate the width and depth

  float width = _environMaxX - m_environMinX;
  float depth = _environMaxY - m_environMinY;

  //calculate and assign the scale x and scale y values

  m_scaleX = 1.0/(width/m_numCellsX);
  m_scaleY = 1.0/(depth/_numCellsY);

  // initialise the vector

  for (int i = 0; i < _numCellsX; i++)
  {
    for (int j = 0; j < _numCellsY; j++)
    {
      entityRecordListPtr list (new std::list<EntityRecord>);
      m_grid.push_back(list);
    }
  }
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
  //conversion to grid space for assigning to a grid cell

  float gridSpaceX = (_record.m_x - m_environMinX)* m_scaleX;
  float gridSpaceY = (_record.m_y - m_environMinY) * m_scaleY;

  //conversion from float to int

  int floorX = floor(gridSpaceX);
  int floorY = floor(gridSpaceY);

  //calculating the index

  int index = floorX + (floorY*m_numCellsX);

  //store the record in the appropriate list

  (*m_grid[index]).push_back(_record);
}

//-------------------------------------------------------------------//

Database::entityRecordListPtr Database::getLocalEntities(
    float _minX,
    float _minY,
    float _maxX,
    float _maxY
    ) const
{
  //checks that the min values are smaller than the max values,
  //and if not it swaps them

  if(_minX > _maxX)
  {
    float temp = _minX;
    _minX = _maxX;
    _maxX = temp;
  }

  if(_minY > _maxY)
  {
    float temp = _minY;
    _minY = _maxY;
    _maxY = temp;
  }

  //conversion of min and max values to grid space

  float minXGrid = (_minX - m_environMinX)* m_scaleX;
  float maxXGrid = (_maxX - m_environMinX)* m_scaleX;
  float minYGrid = (_minY - m_environMinY)* m_scaleY;
  float maxYGrid = (_maxY - m_environMinY)* m_scaleY;

  //conversion from float to int

  int minXId = floor(minXGrid);
  int maxXId = floor(maxXGrid);
  int minYId = floor(minYGrid);
  int maxYId = floor(maxYGrid);

  //initialise a pointer to a list of entity records

  entityRecordListPtr returnList(new std::list<EntityRecord>);

  //and initialise an iterator for that list

  std::list<EntityRecord>::iterator returnListIt;

  //loop through each index of a cell overlapped by the bounding
  //box

  for (int i = minYId; i <= maxYId; i++)
  {
    for (int j = minXId; j <= maxXId; j++)
    {
      //if the return list is empty and there is an entity record stored in
      //the currently selected cell

      if (returnList->size()==0 && (*m_grid[j+(i*m_numCellsX)]).size()!=0)
      {
        //
        //initialise an iterator to the beginning of the cell list

        std::list<EntityRecord>::iterator cellListIt;
        cellListIt = (*m_grid[j+(i*m_numCellsX)]).begin();

        //push the first element of the list into the return list

        returnList->push_back(*cellListIt);

        // then increment the cell list iterator

        cellListIt++;

        //and set an iterator to the end of the return list

        returnListIt = returnList->end();

        //and insert the rest of the cell list onto the end of the list

        returnList->insert(
              returnListIt,
              cellListIt,
              (*m_grid[j+(i*m_numCellsX)]).end()
              );
      }
      //otherwise, if the return list already has some values in it

      else if (returnList->size()!=0)
      {
        //set the return list iterator to the end of the list

        returnListIt = returnList->end();

        //insert the whole  cell list ont the end of the return list

        returnList->insert(
              returnListIt,
              (*m_grid[j+(i*m_numCellsX)]).begin(),
              (*m_grid[j+(i*m_numCellsX)]).end()
              );
      }
    }
  }

  //return a pointer to the list

  return returnList;
}
//-------------------------------------------------------------------//

void Database::clearRecords()
{
  // create an iterater to cycle through the cell lists and set it to the
  //beginning of the vector of lists

  std::vector<entityRecordListPtr>::iterator it;
  it = m_grid.begin();

  //then for each one

  for (; it < m_grid.end(); it++)
  {
    //clear the list

    (*it)->clear();
  }
}

//-------------------------------------------------------------------//
