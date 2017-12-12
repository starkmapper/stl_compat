#ifndef optionalHPP
#define optionalHPP
#include "../helper/cppversion_detection.hpp"
#if cpp17
  #include <optional>
#else
    #include <boost/optional/optional.hpp>
#endif
#include <exception>
namespace std_compat
{
  #if cpp17
    using std::optional;
    using std::bad_optional_access;
  #else
    class bad_optional_access : public std::exception
    {
    public:
      virtual ~bad_optional_access() noexcept {};
      char const* what() const {return "optional<T>::value: value not set.";}
    };

    template <class T>
    class optional: public boost::optional<T>
    {
      typedef boost::optional<T> base;
      public:
      optional () : base() {}
      optional ( T const& v ):base(v) {};
      optional ( bool condition, T const& v ) : base(condition,v){}
      optional ( optional const& rhs ): base(rhs) {}

      T& value()
      {
         if (*this)
          return base::get();
        throw bad_optional_access();
      }

      T const & value() const
      {
        if (*this)
          return base::get();
        throw bad_optional_access();
      }

      T value_or( T const & def ) const
      {
        return base::get_value_or(def);
      }
    };

  #endif
}

#if !cpp17
namespace std
{
  using std_compat::bad_optional_access;
  using std_compat::optional;
}

#endif


#ifdef __BORLANDC__
static void __fix_boost_8080_warnings_optional()
{
    (void)(boost::none);
}
#endif

#endif