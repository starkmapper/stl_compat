#ifndef std_compat_bindH
#define std_compat_bindH
#include "../helper/cppversion_detection.hpp"

#include "functional.hpp"

#if cpp11
#include <bind>
namespace std_compat
{
  using std::bind;
}
#else
#include <boost/bind.hpp>
namespace std_compat
{
  using boost::bind;
}
namespace std
{
  using boost::bind;
}
#endif

#endif