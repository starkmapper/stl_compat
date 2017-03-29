#ifndef SharedPtrHPP
#define SharedPtrHPP
#include "../helper/cppversion_detection.hpp"

#if cpp11
  #include <memory>
  #define ptr_namespace std
  #define unique_namespace std
#else
  #if cpp03
  // TR1 includes unique_ptr in std
    #include <boost/tr1/tr1/memory>
    #define unique_namespace std
    #define ptr_namespace boost
  #endif
  #include <boost/shared_ptr.hpp>
  #include <boost/weak_ptr.hpp>
  #include <boost/make_shared.hpp>
#endif

namespace std_compat
{
  using unique_namespace::unique_ptr;
  using ptr_namespace::shared_ptr;
  using ptr_namespace::weak_ptr;
  using ptr_namespace::make_shared;
  using ptr_namespace::allocate_shared;
}
#if !cpp11
namespace std
{
  using std_compat::shared_ptr;
  using std_compat::weak_ptr;
  using std_compat::weak_ptr;
  using std_compat::make_shared;
  using std_compat::allocate_shared;
}
#endif

#endif