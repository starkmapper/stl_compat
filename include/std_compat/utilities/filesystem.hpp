#ifndef std_compat_filesystemH
#define std_compat_filesystemH
#include "../helper/cppversion_detection.hpp"

#if cpp17
#include <filesystem>
namespace std_compat
{
  namespace filesystem
  {
    using namespace std::filesystem;
  }
}
#else
#pragma warn -8104
#pragma warn -8092
#include <boost/filesystem.hpp>
#pragma warn .8092
#pragma warn .8104

namespace std_compat
{
  namespace filesystem
  {
    using namespace boost::filesystem;
  }
}
namespace std
{
  namespace filesystem
  {
    using namespace boost::filesystem;

    path absolute(const path& p)
    {
      return boost::filesystem::system_complete(p);
    }

    //path absolute(const path& p, std::error_code& ec)
    template <typename T>
    path absolute(const path& p, T& ec)
    {
      static_assert(std::is_same<T, std::false_type>::value, "Not Supported in boost");
    }
  }
}
#endif

#endif