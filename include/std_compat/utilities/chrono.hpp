#ifndef chronoHPP
#define chronoHPP
#include "../helper/cppversion_detection.hpp"

#if cpp11
  #include <chrono>
  #define chrono_namespace std::chrono
#else
  #include <boost/date_time/posix_time/posix_time_types.hpp>
  #define chrono_namespace boost::posix_time
  #include "chrono/chrono_boost_wrapper.hpp"
#endif

namespace std_compat
{
  namespace chrono
  {
    using namespace chrono_namespace;
  }
}

#if !cpp11
namespace std
{
  namespace chrono
  {
    using namespace std_compat::chrono;
  }
}
#endif

#endif