#ifndef cmathHPP
#define cmathHPP

#include "../helper/cppversion_detection.hpp"

#if cpp11
  #include <cmath>  
#else
namespace std
{
  bool isnan(float arg)
  {
    return arg != arg;
  }

  bool isnan(double arg)
  {
    return arg != arg;
  }

  bool isnan(long double arg)
  {
    return arg != arg;
  }

  template<class Integral>
  bool isnan(Integral arg)
  {
    double d = std::static_cast<double>(arg);
    return isnan(d);
  }
}
#endif

namespace std_compat
{
  using std::isnan;
}
#endif
