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
  #include <boost/enable_shared_from_this.hpp>
  #include <boost/pointer_cast.hpp>
#endif

namespace std_compat
{
  using unique_namespace::unique_ptr;
  using ptr_namespace::shared_ptr;
  using ptr_namespace::weak_ptr;
  using ptr_namespace::make_shared;
  using ptr_namespace::allocate_shared;
  using ptr_namespace::enable_shared_from_this;
  using ptr_namespace::static_pointer_cast;
  using ptr_namespace::dynamic_pointer_cast;
  using ptr_namespace::const_pointer_cast;
  using ptr_namespace::reinterpret_pointer_cast;
}
#if !cpp11
namespace std
{
  using std_compat::shared_ptr;
  using std_compat::weak_ptr;
  using std_compat::weak_ptr;
  using std_compat::make_shared;
  using std_compat::allocate_shared;
  using std_compat::enable_shared_from_this;
  using std_compat::static_pointer_cast;
  using std_compat::dynamic_pointer_cast;
  using std_compat::const_pointer_cast;
  using std_compat::reinterpret_pointer_cast;
}
#endif

#endif