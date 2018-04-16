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
#include <boost/filesystem.hpp>

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
      static_assert(false, "Not Supported in boost");
    }
  }
}
#endif

#endif