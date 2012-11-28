#ifndef SMARTPOINTERS_H
#define SMARTPOINTERS_H

#include <boost/shared_ptr.hpp>

#define DECLARESMART(X) \
  class X; \
  typedef boost::shared_ptr< X > X ## Ptr; \
  typedef boost::shared_ptr< const X > X ## CPtr;

#endif // SMARTPOINTERS_H
