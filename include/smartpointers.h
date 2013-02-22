#ifndef SMARTPOINTERS_H
#define SMARTPOINTERS_H

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <list>
#include <vector>

//-------------------------------------------------------------------//
/// @file smartpointers.h
/// @brief This file is for holding macros for aiding the creation of
/// boost smart pointers. This is handy but it may increase compile
/// times quite a bit.
/// @author Jared Auty
/// @version 1.1
/// @date 5/12/12
/// Revision History :
/// Initial Version 28/11/12
//-------------------------------------------------------------------//

//-------------------------------------------------------------------//
/// @brief preprocessor macro to aid in the creation of boost::shared_ptrs
//-------------------------------------------------------------------//

#define DECLARESMART(X) \
  class X; \
  typedef boost::shared_ptr< X > X ## Ptr; \
  typedef boost::weak_ptr< X > X ## WPtr; \
  typedef boost::shared_ptr< const X > X ## CPtr;\
  typedef boost::weak_ptr< const X > X ## WCPtr;\

//-------------------------------------------------------------------//
/// @brief preprocessor macro to aid in the creation of lists of shared pointer
//-------------------------------------------------------------------//

#define DECLARESMARTLIST(X) \
  DECLARESMART(X); \
  typedef std::list< X ## Ptr > X ## List; \
  typedef boost::shared_ptr< X ## List > X ## ListPtr;\

//-------------------------------------------------------------------//
/// @brief preprocessor macro to aid in the creation of lists of shared pointer
//-------------------------------------------------------------------//

#define DECLARESMARTVEC(X) \
  DECLARESMART(X); \
  typedef std::vector< X ## Ptr > X ## Vec; \
  typedef boost::shared_ptr< X ## Vec > X ## VecPtr;\
  typedef std::vector< X ## WPtr > X ## WVec; \
  typedef boost::shared_ptr< X ## WVec > X ## WVecPtr;\




#endif // SMARTPOINTERS_H
