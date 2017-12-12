#ifndef mutexHPP
#define mutexHPP
#include "../helper/cppversion_detection.hpp"

#if cpp11
  #include <mutex>
  #define mutex_namespace std
  #define lock_namespace std
#else
  #include "../boost/thread/win32/basic_timed_mutex.hpp"
  #include <boost/thread/mutex.hpp>
  #include <boost/thread/recursive_mutex.hpp>
  #include <boost/thread/locks.hpp>
  #define mutex_namespace boost
  #define lock_namespace boost
#endif


namespace std_compat
{
  using mutex_namespace::mutex;
  using mutex_namespace::recursive_mutex;
  using mutex_namespace::defer_lock_t;
  using mutex_namespace::try_to_lock_t;
  using mutex_namespace::adopt_lock_t;
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
  using std_compat::defer_lock_t;
  using std_compat::try_to_lock_t;
  using std_compat::adopt_lock_t;
}
#endif

#ifdef __BORLANDC__
static void __fix_boost_8080_warnings_mutex()
{
    (void)(boost::detail::win32::invalid_handle_value);
    (void)(boost::defer_lock);
    (void)(boost::try_to_lock);
    (void)(boost::adopt_lock);
}
#endif

#endif