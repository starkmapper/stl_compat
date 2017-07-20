#ifndef std_compat_exceptionH
#define std_compat_exceptionH
#include "../helper/cppversion_detection.hpp"
#include <exception>

#if cpp11
namespace std_compat
{
  using std::exception_ptr;
  using std::make_exception_ptr;
  using std::rethrow_exception;
}
#else
#include <boost/exception_ptr.hpp>
  
namespace std_compat
{
  using boost::exception_ptr;
  using boost::current_exception;
  using boost::rethrow_exception;
  
  template<class E>
  exception_ptr make_exception_ptr(E const & e)
  {
    return boost::copy_exception(e);
  }
}
namespace std
{
  using std_compat::exception_ptr;
  using std_compat::current_exception;
  using std_compat::rethrow_exception;
  using std_compat::make_exception_ptr;
}
#endif

#endif