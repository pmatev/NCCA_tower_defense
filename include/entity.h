#ifndef ENTITY_H
#define ENTITY_H

#include <ngl/Vec3.h>
#include <list>

#include "smartpointers.h"
#include "fwd/database.h"
#include "fwd/entity.h"
#include "ngl/TransformStack.h"

//-------------------------------------------------------------------//
/// @file entity.h
/// @brief The base class for all renderable objects in the game
/// @author Peter May, Jared Auty
/// @version 1
/// @date 22/11/12
/// Revision History :
/// Initial Version 22/11/12
/// @class Entity
//-------------------------------------------------------------------//

typedef boost::shared_ptr<ngl::TransformStack> TXPtr;

class Entity
{
public: //typedefs and structs
  //-------------------------------------------------------------------//
  /// @struct a struct to contain the bounding box of the entity's visible
  /// area
  //-------------------------------------------------------------------//

  struct BBox
  {
    //-------------------------------------------------------------------//
    /// @brief the minimum x value of the entity's visible area
    //-------------------------------------------------------------------//

    float m_minX;

    //-------------------------------------------------------------------//
    /// @brief the minimum y value of the entity's visible area
    //-------------------------------------------------------------------//

    float m_minY;

    //-------------------------------------------------------------------//
    /// @brief the minimum z value of the entity's visible area
    //-------------------------------------------------------------------//

    float m_minZ;

    //-------------------------------------------------------------------//
    /// @brief the maximum x value of the entity's visible area
    //-------------------------------------------------------------------//

    float m_maxX;

    //-------------------------------------------------------------------//
    /// @brief the maximum y value of the entity's visible area
    //-------------------------------------------------------------------//

    float m_maxY;

    //-------------------------------------------------------------------//
    /// @brief the maximum z value of the entity's visible area
    //-------------------------------------------------------------------//

    float m_maxZ;

    //-------------------------------------------------------------------//
    /// @brief constructor for the struct
    /// @param [in] _minX the minimum x value
    /// @param [in] _minY the minimum y value
    /// @param [in] _minZ the minimum z value
    /// @param [in] _maxX the maximum x value
    /// @param [in] _maxY the maximum y value
    /// @param [in] _maxZ the maximum z value
    //-------------------------------------------------------------------//

    BBox(
        float _minX,
        float _minY,
        float _minZ,
        float _maxX,
        float _maxY,
        float _maxZ
        ):
      m_minX(_minX),
      m_minY(_minY),
      m_minZ(_minZ),
      m_maxX(_maxX),
      m_maxY(_maxY),
      m_maxZ(_maxZ)
    {}
  };

public: //methods
  //-------------------------------------------------------------------//
  /// @brief a parameterised constructor
  /// @param [in] _pos, a vector containing the initial position in 3D
  /// space of the entity
  /// @param [in] _health, the initial health value of the entity
  //-------------------------------------------------------------------//

  Entity(const ngl::Vec3 & _pos, GeneralType _type);


  //-------------------------------------------------------------------//
  /// @brief the destructor
  //-------------------------------------------------------------------//

  ~Entity();

  //-------------------------------------------------------------------//
  /// @brief a virtual method which will update the entity when
  /// implemented in child classes
  //-------------------------------------------------------------------//

  virtual void update() = 0;

  //-------------------------------------------------------------------//
  /// @brief a virtual method which will draw the entity when
  /// implemented in child classes
  //-------------------------------------------------------------------//

  virtual void draw()  = 0;

  //-------------------------------------------------------------------//
  /// @brief a virtual method that draws the selection frame (where each
  /// object is rendered with a colour based on it's id)
  //-------------------------------------------------------------------//

  virtual void drawSelection()  = 0;

  //-------------------------------------------------------------------//
  /// @brief a method which will publish the entity's position to the
  /// central database
  //-------------------------------------------------------------------//

  void publish();

  //-------------------------------------------------------------------//
  /// @brief method to return the health value
  /// @param [out] m_health, the health value of the entity
  //-------------------------------------------------------------------//

  inline float getHealth() const {return m_health;}

  //-------------------------------------------------------------------//
  /// @brief method to get the ID of the entity
  /// @param [out] m_ID, the ID of the entity
  //-------------------------------------------------------------------//

  inline unsigned int getID() const {return m_ID;}

  //-------------------------------------------------------------------//
  /// @brief a method to update the list of localEntities
  //-------------------------------------------------------------------//

  entityRecordListPtr updateLocalEntities(
      std::list<GeneralType> &_typeList
      );

  //-------------------------------------------------------------------//
  /// @brief a method to clear the list of local entities
  //-------------------------------------------------------------------//

  void clearLocalEntities();

  //-------------------------------------------------------------------//
  /// @brief a method to return the type string
  //-------------------------------------------------------------------//

  inline GeneralType getGeneralType() const {return m_generalType;}

  //-------------------------------------------------------------------//
  /// @brief a method to return the position of the entity
  //-------------------------------------------------------------------//

  inline ngl::Vec3 getPos() const {return m_pos;}

  //-------------------------------------------------------------------//
  /// @brief a method to return the bounding box of the entity's mesh
  //-------------------------------------------------------------------//

  inline BBox getMeshBBox() const {return m_lsMeshBBox;}

  //-------------------------------------------------------------------//
  /// @brief a method to generate the mesh of the entity, pure virtual
  //-------------------------------------------------------------------//

  virtual void generateMesh() = 0;

protected: //attributes

  //-------------------------------------------------------------------//
  /// @brief Identifier for the entity
  //-------------------------------------------------------------------//

  unsigned int m_ID;

  std::string m_IDStr;

  //-------------------------------------------------------------------//
  /// @brief the vector to store the position of the entity
  //-------------------------------------------------------------------//

  ngl::Vec3 m_pos;

  //-------------------------------------------------------------------//
  /// @brief the health value of the entity
  //-------------------------------------------------------------------//

  float m_health;

  //-------------------------------------------------------------------//
  /// @brief a pointer to a list of entity records
  //-------------------------------------------------------------------//

  entityRecordListPtr m_localEntities;

  //-------------------------------------------------------------------//
  /// @brief a variable storing the bounding box of the entity's view
  /// area, ws stands for world space
  //-------------------------------------------------------------------//

  BBox m_wsViewBBox;

  //-------------------------------------------------------------------//
  /// @brief a variable storing the bounding box of the entity's mesh,
  /// ls stands for local space
  //-------------------------------------------------------------------//

  BBox m_lsMeshBBox;

  ngl::TransformStack m_transformStack;

  //-------------------------------------------------------------------//
  /// @brief an enum to store the generaltype of the entity
  //-------------------------------------------------------------------//

  GeneralType m_generalType;

};


#endif // ENTITY_H
