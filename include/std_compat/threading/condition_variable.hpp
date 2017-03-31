#pragma hdrstop

#ifndef condition_variable_HPP
  #define condition_variable_HPP
  #include "../helper/cppversion_detection.hpp"
#ifdef cpp11
  #include <condition_variable>
#else
  #pragma warn -8128
  #include <boost/thread/condition_variable.hpp>
  #include "mutex.hpp"
  #include "utilities/chrono.hpp"
  #pragma warn .8128
#endif

namespace std_compat
{
#if cpp11
  using std::condition_variable;
  using std::condition_variable_any;
  using std::cv_status;
#else
  enum class cv_status
  {
    timeout,
    no_timeout
  };
  class condition_variable : public boost::condition_variable
  {
  public:
    template<typename duration_type> 
    cv_status wait_for(unique_lock<mutex>& lock, duration_type const& rel_time)
    {
      return timed_wait(lock, rel_time);
    }
    template<typename duration_type, typename predicate_type>
    bool wait_for(unique_lock<mutex>& lock, duration_type const& rel_time, predicate_type predicate)
    {
      return timed_wait(lock, rel_time, predicate);
    }
  };

  class condition_variable_any : public boost::condition_variable_any
  {
  public:
    template<typename duration_type>
    cv_status wait_for(unique_lock<mutex>& lock, duration_type const& rel_time)
    {
      return timed_wait(lock, rel_time);
    }
    template<typename duration_type, typename predicate_type>
    bool wait_for(unique_lock<mutex>& lock, duration_type const& rel_time, predicate_type predicate)
    {
      return timed_wait(lock, rel_time, predicate);
    }
  };
#endif
}

#if !cpp11
namespace std
{
  using std_compat::cv_status;
}
#endif
#endif