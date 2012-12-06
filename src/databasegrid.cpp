#include "databasegrid.h"
#include "entity.h"

//-------------------------------------------------------------------//

DatabaseGrid::DatabaseGrid(
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

DatabaseGrid::~DatabaseGrid()
{
  //currently using default destructor
}

//-------------------------------------------------------------------//

DatabaseGridPtr DatabaseGrid::create(
    int _numCellsX,
    int _numCellsY,
    float _environMaxX,
    float _environMaxY,
    float _environMinX,
    float _environMinY
    )
{
  DatabaseGridPtr instance(new DatabaseGrid(
                  _numCellsX,
                  _numCellsY,
                  _environMaxX,
                  _environMaxY,
                  _environMinX,
                  _environMinY
                  ));

  return instance;
}

//-------------------------------------------------------------------//

void DatabaseGrid::addRecord(EntityRecord _record)
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

entityRecordListPtr DatabaseGrid::getLocalEntities(
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
      //if there are elements in the selected cell

      if ((*m_grid[j+(i*m_numCellsX)]).size()!=0)
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

        //insert the whole  cell list into the return list

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

void DatabaseGrid::clearRecords()
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

void DatabaseGrid::unPublish(unsigned int _id)
{
  //initialise a boolean to check if the entity is unregistered

  bool isUnregistered = false;

  //first cycle through each cell

  unsigned int i = 0;

  while ( i <= m_grid.size() && isUnregistered != true )
  {
    //check that the cell is not empty

    if (m_grid[i]->size() !=0)
    {
      //then set an iterator to cycle through the currenly selected list

      std::list<EntityRecord>::iterator listIt = m_grid[i]->begin();

      //then cycle through each element and check it's id against the
      //one provided

      for (; listIt != m_grid[i]->end(); listIt++)
      {
        //if the ids match

        if ((*listIt).m_id == _id)
        {
          //erase that element and set the boolean to true

          m_grid[i]->erase(listIt);
          isUnregistered = true;

          //then break out of the for loop

          break;
        }
      }
    }
    i++;
  }
}
