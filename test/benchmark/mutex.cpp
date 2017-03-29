#pragma hdrstop

#include <hayai.hpp>
#include <std_compat/mutex>

namespace
{
  class fixture :   public ::hayai::Fixture
  {
  protected:

  public:
      fixture()
      : doneStuff(false)
      {}
      virtual void SetUp()
      {
      }

      virtual void TearDown()
      {

      }
      std::mutex stdMutex;
      std::recursive_mutex stdRecursiveMutex;
      volatile bool doneStuff;
  };

  BENCHMARK_F(fixture, LockGuardMutex, 100, 10000)
  {
    std::lock_guard<std::mutex> lock(stdMutex);
    doneStuff = true;
  }
  BENCHMARK_F(fixture, LockGuardRecursiveMutex, 100, 10000)
  {
    std::lock_guard<std::recursive_mutex> lock(stdRecursiveMutex);
    doneStuff = true;
  }
  BENCHMARK_F(fixture, UniqueLockRecursiveMutex, 10, 10000)
  {
    std::unique_lock<std::mutex> lock(stdMutex);
    doneStuff = true;
  }
}