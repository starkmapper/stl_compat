#ifndef ArrayH
#define ArrayH
#include "../cppversion_detection.hpp"
#include <array>
namespace std_compat
{
  #if CPP11
  using std::array;
  #else
  using boost::array;
  #endif
}
#endif
