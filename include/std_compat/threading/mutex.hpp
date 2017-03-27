#ifndef mutexHPP
#define mutexHPP
#include "../helper/cppversion_detection.hpp"

#if cpp11
  #include <mutex>
  #define mutex_namespace std
  #define lock_namespace std
#endif
  #include <boost/thread/mutex.hpp>
  #include <boost/thread/recursive_mutex.hpp>
  #include <boost/thread/locks.hpp>
  #define mutex_namespace boost
  #define lock_namespace boost
#endif


namespace cpp_compat
{
  using mutex_namespace::mutex;
  using mutex_namespace::recursive_mutex;
  using lock_namespace::unique_lock;
  using lock_namespace::lock_guard;
}

#if !cpp11
namespace std
{
  using std_compat::mutex;
  using std_compat::recursive_mutex;
  using std_compat::unique_lock;
  using std_compat::lock_guard;
}
#endif

#endif