#ifndef ENTITY_H
#define ENTITY_H

#include "ngl/Vec3.h"
#include <list>
#include "boost/enable_shared_from_this.hpp"

#include "smartpointers.h"
#include "fwd/database.h"
#include "fwd/entity.h"
#include "renderer.h"
#include "ngl/TransformStack.h"
#include "fsm/statemachine.h"

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

class StateMachine;

class Entity : public boost::enable_shared_from_this<Entity>
{
public: //typedefs and structs
  //-------------------------------------------------------------------//
  /// @struct a struct to contain the bounding box of the entity's visible
  /// area
  //-------------------------------------------------------------------//

  struct BBox
  {
    //-------------------------------------------------------------------//
    /// @brief union to allow for index notation
    //-------------------------------------------------------------------//

    union
    {
      struct
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
      };

      //-------------------------------------------------------------------//
      /// @brief an array storing all the values
      //-------------------------------------------------------------------//

      float m_bbox[6];
    };

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

  Entity(const ngl::Vec3 & _pos, GeneralType _type, unsigned int _id);


  //-------------------------------------------------------------------//
  /// @brief the destructor
  //-------------------------------------------------------------------//

  ~Entity();

  //-------------------------------------------------------------------//
  /// @brief called after the constructor
  //-------------------------------------------------------------------//
  virtual void init();

  //-------------------------------------------------------------------//
  /// @brief a virtual method which will update the entity when
  /// implemented in child classes
  //-------------------------------------------------------------------//

  virtual void update(const double _dt) = 0;

  //-------------------------------------------------------------------//
  /// @brief a virtual method which will draw the entity when
  /// implemented in child classes
  //-------------------------------------------------------------------//

  virtual void draw();

  //-------------------------------------------------------------------//
  /// @brief a virtual method that draws the selection frame (where each
  /// object is rendered with a colour based on it's id)
  //-------------------------------------------------------------------//

//  virtual void drawSelection()  = 0;

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
  /// @brief Deal a certain amount of damage to the entity.
  /// @param[in] _damage, the amount of damage to deal
  //-------------------------------------------------------------------//

  inline void dealDamage(float _damage)
  {
    m_health-= _damage;
  }

  //-------------------------------------------------------------------//
  /// @brief Kill the entity by reducing it's health to 0
  //-------------------------------------------------------------------//

  inline void kill()
  {
    m_health = 0;
  }

  //-------------------------------------------------------------------//
  /// @brief method to get the ID of the entity
  /// @param [out] m_ID, the ID of the entity
  //-------------------------------------------------------------------//

  inline unsigned int getID() const {return m_ID;}

  //-------------------------------------------------------------------//
  /// @brief gets localEntities
  //-------------------------------------------------------------------//

  inline EntityRecordListWPtr getLocalEntities() const {
    return EntityRecordListWPtr(m_localEntities);
  }

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

  //-------------------------------------------------------------------//
  /// @brief a method to calculate the local space bounding box of the
  /// entity
  /// @param [in] _meshData, a list of vertData structs from which to
  /// calculate the bounding box
  //-------------------------------------------------------------------//

  void generateLsBBox(const std::vector<Renderer::vertData> & _meshData);

  //-------------------------------------------------------------------//
  /// @brief gets the statemachine, obviously.
  //-------------------------------------------------------------------//
  inline StateMachine* getStateMachine() const {return m_stateMachine;}

protected:
  //-------------------------------------------------------------------//
  /// @brief a method to update the list of localEntities
  //-------------------------------------------------------------------//

  void calculateLocalEntities(
      EntityRecordList &o_newList,
      std::list<GeneralType> &_typeList
      );

  //-------------------------------------------------------------------//
  /// @brief a method to clear the list of local entities
  //-------------------------------------------------------------------//

  void clearLocalEntities();

  //-------------------------------------------------------------------//
  /// @brief pure virtual method for filtering the local entity list based
  /// on view volume. This should be implemented in the concrete type.
  /// @param[out] o_localEntities pointer to the local entities
  //-------------------------------------------------------------------//

  virtual void filterViewVolume(EntityRecordList &o_localEntities) = 0;

  //-------------------------------------------------------------------//
  /// @brief this method is used for running all the functions that need
  /// to be run before the entity is updated. This should be implemented
  /// at dynamic or static entity level. This will normally get all the local
  /// entities and run the filterViewVolume method. This is for all things
  /// that should be done outside of update loop to keep thread-safe.
  //-------------------------------------------------------------------//

  virtual void prepareForUpdate() = 0;



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
  /// @brief the current velocity of the dynamic entity
  //-------------------------------------------------------------------//

  ngl::Vec3 m_velocity;

  //-------------------------------------------------------------------//
  /// @brief the health value of the entity
  //-------------------------------------------------------------------//

  float m_health;

  //-------------------------------------------------------------------//
  /// @brief a pointer to a list of entity records
  //-------------------------------------------------------------------//

  EntityRecordListPtr m_localEntities;

  //-------------------------------------------------------------------//
  /// @brief the statemachine.
  //-------------------------------------------------------------------//
  StateMachine *m_stateMachine;


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

private:
  //-------------------------------------------------------------------//
  /// @brief an enum to store the generaltype of the entity
  //-------------------------------------------------------------------//

  GeneralType m_generalType;

};


#endif // ENTITY_H
