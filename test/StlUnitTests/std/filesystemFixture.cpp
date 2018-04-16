#pragma hdrstop
#include "../TestBase.h"
#include <std_compat/filesystem>
TDOG_SUITE(stl_compat)
{
  TDOG_SUITE(filesystem)
  {
    namespace fs = std::filesystem;
    TDOG_TEST_CASE(current_dir_should_be_dir)
    {
      fs::path localdir = "./";
      TDOG_ASSERT(fs::is_directory(localdir));
    }
    TDOG_CLOSE_SUITE
  }
  TDOG_CLOSE_SUITE
}