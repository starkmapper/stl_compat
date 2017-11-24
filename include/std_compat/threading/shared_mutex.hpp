#ifndef shared_mutexHPP
#define shared_mutexHPP

#include "../helper/cppversion_detection.hpp"

#if cpp17
  #include <shared_mutex>
  #define shared_mutex_namespace std
  #define shared_lock_namespace std
#elif cpp11
  #include "detail/shared_mutex.hpp"
  #include "detail/shared_mutex.cpp"
  #define shared_mutex_namespace ting
  #define shared_lock_namespace ting
#else
#ifdef __BORLANDC__
  #include "../boost/thread/win32/basic_timed_mutex.hpp"
#endif
  #include <boost/thread/shared_mutex.hpp>
  #include <boost/thread/locks.hpp>
  #define shared_mutex_namespace boost
  #define shared_lock_namespace boost
#endif


namespace std_compat
{
  using shared_mutex_namespace::shared_mutex;
  using shared_lock_namespace::shared_lock;
}
namespace std
{
#ifndef _MSC_VER
#if !cpp17
  using std_compat::shared_mutex;
#endif
#endif
#if !cpp11
  using std_compat::shared_lock;
#endif
}

#endif