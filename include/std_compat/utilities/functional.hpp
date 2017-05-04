#ifndef std_compat_functionalH
#define std_compat_functionalH
#include "../helper/cppversion_detection.hpp"

#if cpp11
#include <functional>
namespace std_compat
{
  using std::function;
}
#else
#include <boost/function.hpp>
namespace std_compat
{
  using boost::function;
  // TODO: boost has no 'empty()' function.
}
namespace std
{
  using std_compat::function;
}
#endif

#endif