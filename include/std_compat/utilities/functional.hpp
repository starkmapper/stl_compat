#ifndef std_compat_functionalH
#define std_compat_functionalH
#include "../helper/cppversion_detection.hpp"

#if cpp11
#include <functional>
namespace std_compat
{
  using std::function;
  using std::bind;
  using std::ref;
  using std::cref;
  using std::reference_wrapper;
}
using namespace std::placeholders;
#else
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/ref.hpp>

namespace std_compat
{
  using boost::function;
  using boost::bind;
  using boost::ref;
  using boost::cref;
  using boost::reference_wrapper;

  // TODO: boost has no 'empty()' function.
}
namespace std
{
  using boost::function;
  using boost::bind;
  using boost::ref;
  using boost::cref;
  using boost::reference_wrapper;
}
#endif

#endif