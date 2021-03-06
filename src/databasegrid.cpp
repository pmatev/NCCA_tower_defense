#include <boost/foreach.hpp>

#include "databasegrid.h"
#include "entity.h"

//-------------------------------------------------------------------//

DatabaseGrid::DatabaseGrid(
    int _numCellsX,
    int _numCellsZ,
    float _environMaxX,
    float _environMaxZ,
    float _environMinX,
    float _environMinZ
    ):
  m_numCellsX(_numCellsX),
  m_numCellsZ(_numCellsZ),
  m_environMinX(_environMinX),
  m_environMinZ(_environMinZ)
{
  //checks that the min values are less than the max values
  //and if not it swaps them

  if (m_environMinX > _environMaxX)
  {
    float temp = m_environMinX;
    m_environMinX = _environMaxX;
    _environMaxX = temp;
  }

  if (m_environMinZ > _environMaxZ)
  {
    float temp = m_environMinZ;
    m_environMinZ = _environMaxZ;
    _environMaxZ = temp;
  }


  //calculate the width and depth

  float width = _environMaxX - m_environMinX;
  float depth = _environMaxZ - m_environMinZ;

  //calculate and assign the scale x and scale Z values

  m_scaleX = m_numCellsX/width;
  m_scaleZ = _numCellsZ/depth;

  // initialise the vector

  for (int i = 0; i < _numCellsX; i++)
  {
    for (int j = 0; j < _numCellsZ; j++)
    {
      EntityRecordListPtr list (new EntityRecordList);
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
    int _numCellsZ,
    float _environMaxX,
    float _environMaxZ,
    float _environMinX,
    float _environMinZ
    )
{
  DatabaseGridPtr instance(new DatabaseGrid(
                  _numCellsX,
                  _numCellsZ,
                  _environMaxX,
                  _environMaxZ,
                  _environMinX,
                  _environMinZ
                  ));

  return instance;
}

//-------------------------------------------------------------------//

void DatabaseGrid::addRecord(EntityRecordPtr _record)
{
  //conversion to grid space for assigning to a grid cell

  float gridSpaceX = (_record->m_x - m_environMinX)* m_scaleX;
  float gridSpaceZ = (_record->m_z - m_environMinZ) * m_scaleZ;

  //conversion from float to int

  int floorX = floor(gridSpaceX);
  int floorZ = floor(gridSpaceZ);

  // clamp values to num cells
  floorX = floorX < 0 ? 0 : floorX > m_numCellsX - 1 ? m_numCellsX -1 : floorX;
  floorZ = floorZ < 0 ? 0 : floorZ > m_numCellsZ - 1 ? m_numCellsZ -1 : floorZ;

  //calculating the index

  int index = floorX + (floorZ*m_numCellsX);

  //store the record in the appropriate list

  (*m_grid[index]).push_back(_record);
}

//-------------------------------------------------------------------//

void DatabaseGrid::getLocalEntities(
    EntityRecordWCList &o_newList,
    float _minX,
    float _minZ,
    float _maxX,
    float _maxZ
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

  if(_minZ > _maxZ)
  {
    float temp = _minZ;
    _minZ = _maxZ;
    _maxZ = temp;
  }

  //conversion of min and max values to grid space

  float minXGrid = ( _minX - m_environMinX)* m_scaleX;
  float maxXGrid = ( _maxX - m_environMinX)* m_scaleX;
  float minZGrid = (_minZ - m_environMinZ)* m_scaleZ;
  float maxZGrid = (_maxZ - m_environMinZ)* m_scaleZ;

  //conversion from float to int

  int minXId = std::max(0, int(minXGrid));
  int maxXId = std::min(m_numCellsX - 1, int(maxXGrid));
  int minZId = std::max(0, int(minZGrid));
  int maxZId = std::min(m_numCellsZ - 1, int(maxZGrid));

  //and initialise an iterator for that list

  EntityRecordWCList::iterator returnListIt;

  //loop through each index of a cell overlapped by the bounding
  //box

  for (int i = minZId; i <= maxZId; i++)
  {
    for (int j = minXId; j <= maxXId; j++)
    {
      //calculate the cell number to check

      int id = j+(i*(m_numCellsX));
      //if there are elements in the selected cell

      if ((*m_grid[id]).size()!=0)
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

        //insert the whole  cell list into the return list

        o_newList.insert(
              returnListIt,
              (*m_grid[j+(i*(m_numCellsX))]).begin(),
              (*m_grid[j+(i*(m_numCellsX))]).end()
              );
      }
    }
  }
}
//-------------------------------------------------------------------//

void DatabaseGrid::clearRecords()
{
  // create an iterater to cycle through the cell lists and set it to the
  //beginning of the vector of lists

  std::vector<EntityRecordListPtr>::iterator it;
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

  while ( i < m_grid.size() && isUnregistered != true )
  {
    //check that the cell is not empty

    if (m_grid[i]->size() !=0)
    {
      //then set an iterator to cycle through the currenly selected list

      EntityRecordList::iterator listIt = m_grid[i]->begin();

      //then cycle through each element and check it's id against the
      //one provided

      for (; listIt != m_grid[i]->end(); listIt++)
      {
        //if the ids match

        if ((*listIt)->m_id == _id)
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

//-------------------------------------------------------------------//
