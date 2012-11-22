#include <iostream>
#include <cstdlib>
#include <ImathVec.h>

int main(int argc, char *argv[])
{
  Imath::Vec3<float> a(1,2,3);
  std::cout<<a.x<<std::endl;

  return EXIT_SUCCESS;
}
