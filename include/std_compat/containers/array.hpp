#ifndef std_compat_arrayH
#define std_compat_arrayH
#include "../helper/cppversion_detection.hpp"

#if cpp11
  #include <array>
  namespace std_compat
  {
    using std::array;
  }
#else
  #include <boost/array.hpp>
  namespace std_compat
  {
    using boost::array;
  }
  namespace std
  {
    using boost::array;
  }
#endif

#endif