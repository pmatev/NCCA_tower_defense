#include "database.h"

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
  //calculate the width and depth

  float width = _environMaxX - m_environMinX;
  float depth = _environMaxY - m_environMinY;

  //calculate and assign the scale x and scale y values

  m_scaleX = 1/(width/m_numCellsX);
  m_scaleY = 1/(depth/_numCellsY);

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

DatabasePtr Database::create(
    int _numCellsX,
    int _numCellsY,
    float _environMaxX,
    float _environMaxY,
    float _environMinX,
    float _environMinY
    )
{
  DatabasePtr db(new Database(
        _numCellsX,
        _numCellsY,
        _environMaxX,
        _environMaxY,
        _environMinX,
        _environMinY
        ));
  return db;
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
    float _maxX,
    float _minY,
    float _maxY
    ) const
{
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

  //create a list of IDs in the bounding box

  entityRecordListPtr returnList;

  for (int i = minYId; i <= maxYId; i++)
  {
    for (int j = minXId; j <= maxXId; j++)
    {
      //splice the list stored in the grid cell onto the end of the
      //return list

      //set the iterator to the end of the return list

      std::list<EntityRecord>::iterator it;
      it = returnList->end();

      //and splice the current list onto the end of it

      returnList->splice(it,(*m_grid[i+(j*m_numCellsX)]));
    }
  }

  //return a pointer to the list

  return returnList;
}
//-------------------------------------------------------------------//
