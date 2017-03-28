#ifndef condition_variable_HPP
#define condition_variable_HPP
#include "../helper/cppversion_detection.hpp"
#ifdef cpp11
#include <condition_variable>
#define condition_namespace std
#else
#define timed_wait wait_for
#include <boost/thread/condition_variable.hpp>
#undef timed_wait
#include "mutex.hpp"
#define condition_namespace boost
#endif

namespace std_compat
{
  using condition_namespace::condition_variable;
  using condition_namespace::condition_variable_any;
}
#endif