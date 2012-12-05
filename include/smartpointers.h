#ifndef SMARTPOINTERS_H
#define SMARTPOINTERS_H

#include <boost/shared_ptr.hpp>
#include <list>

//-------------------------------------------------------------------//
/// @file smartpointers.h
/// @brief This file is for holding macros for aiding the creation of
/// boost smart pointers
/// @author Jared Auty
/// @version 1
/// @date 28/11/12
/// Revision History :
/// Initial Version 28/11/12
//-------------------------------------------------------------------//

//-------------------------------------------------------------------//
/// @brief preprocessor macro to aid in the creation of boost::shared_ptrs
//-------------------------------------------------------------------//

#define DECLARESMART(X) \
  class X; \
  typedef boost::shared_ptr< X > X ## Ptr; \
  typedef boost::shared_ptr< const X > X ## CPtr;\


//-------------------------------------------------------------------//
/// @brief preprocessor macro to aid in the creation of lists of shared pointer
//-------------------------------------------------------------------//

#define DECLARESMARTLIST(X) \
  DECLARESMART(X); \
  typedef std::list< X ## Ptr > X ## List; \
  typedef boost::shared_ptr< X ## List > X ## ListPtr;\


#endif // SMARTPOINTERS_H
