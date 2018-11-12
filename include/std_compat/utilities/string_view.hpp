#ifndef std_compat_string_viewH
#define std_compat_string_viewH
#include "../helper/cppversion_detection.hpp"

#if cpp17
namespace std_compat
{
  using std::string_view;
  using std::wstring_view;
  using std::u16string_view;
  using std::u32string_view;
}
#else
#include <boost/utility/string_view.hpp>

namespace std_compat
{
  using boost::string_view;
  using boost::wstring_view;
  using boost::u16string_view;
  using boost::u32string_view;
}
namespace std
{
  using std_compat::string_view;
  using std_compat::wstring_view;
  using std_compat::u16string_view;
  using std_compat::u32string_view;
}
#endif

#endif