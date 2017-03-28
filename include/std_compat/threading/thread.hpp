#ifndef threadHPP
#define threadHPP
#include "../helper/cppversion_detection.hpp"

#ifdef cpp11
   #include <thread>
  #define thread_namespace std
#else
  #pragma warn -8128
  #include <boost/thread.hpp>
  #pragma warn .8128
  #define thread_namespace boost
namespace boost
{
  namespace this_thread
  {
    template <class TimeDuration>
    void sleep_for(TimeDuration const& rel_time)
    {
      sleep(rel_time);
    }
  }
}
#endif

namespace std_compat
{
  using thread_namespace::thread;
  using thread_namespace::swap;
  using thread_namespace::operator==;
  using thread_namespace::operator!=;
  using thread_namespace::operator<;
  using thread_namespace::operator<=;
  using thread_namespace::operator>;
  using thread_namespace::operator>=;
  using thread_namespace::operator<<;
  
  namespace this_thread
  {
    using namespace thread_namespace::this_thread;
  }
}

#if !cpp11
namespace std
{
  using std_compat::thread;
  using std_compat::swap;  
  using std_compat::operator==;
  using std_compat::operator!=;
  using std_compat::operator<;
  using std_compat::operator<=;
  using std_compat::operator>;
  using std_compat::operator>=;
  using std_compat::operator<<;
  namespace this_thread
  {
    using namespace std_compat::this_thread;
  }
}
#endif

#endif