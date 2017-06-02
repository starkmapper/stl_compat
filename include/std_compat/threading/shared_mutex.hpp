#ifndef shared_mutexHPP
#define shared_mutexHPP

#include "../helper/cppversion_detection.hpp"

#if cpp17
  #include <shared_mutex>
  #define mutex_namespace std
  #define lock_namespace std
#else
  #include "../boost/thread/win32/basic_timed_mutex.hpp"
  #include <boost/thread/shared_mutex.hpp>
  #include <boost/thread/locks.hpp>
  #define mutex_namespace boost
  #define lock_namespace boost
#endif


namespace std_compat
{
  using mutex_namespace::shared_mutex;
  using lock_namespace::shared_lock;
}

#if !cpp17
namespace std
{
  using std_compat::shared_mutex;
  using std_compat::shared_lock;
}
#endif

#endif