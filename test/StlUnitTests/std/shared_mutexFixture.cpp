#pragma hdrstop
#include "../TestBase.h"

#include <std_compat/shared_mutex>
#include <std_compat/mutex>
#include <std_compat/thread>
#include "windows.h"
TDOG_SUITE(stl_compat)
{
  TDOG_SUITE(shared_mutex)
  {
    struct mutexFixture
    {
      bool setup()
      {
        mtx.reset(new std::shared_mutex());
        uniqueLocksPassed = 0;
        sharedLocksPassed = 0;
        return true;
      }

      void teardown()
      {
        UniqueLock lk1(*mtx);
        mtx.reset();
      }
    protected:
      void TryUniqueLock()
      {
        UniqueLock lock(*mtx,std::try_to_lock_t());
        if(lock.owns_lock())
        {
          InterlockedIncrement(&uniqueLocksPassed);
        }
      }
      void TrySharedLock()
      {
        SharedLock lock(*mtx,std::try_to_lock_t());
        if (lock.owns_lock())
        {
          InterlockedIncrement(&sharedLocksPassed);
        }
      }
      void TestTryUniqueLock()
      {
        threadList.Add(new std::thread(&mutexFixture::TryUniqueLock, this));
      }
      void TestTrySharedLock()
      {
        threadList.Add(new std::thread(&mutexFixture::TrySharedLock, this));
      }
      std::unique_ptr<std::shared_mutex> mtx;
      typedef std::unique_lock<std::shared_mutex> UniqueLock;
      typedef std::shared_lock<std::shared_mutex> SharedLock;
      class ThreadList
      {
        std::vector<std::thread*> threads;
      public:
        void Clear()
        {
          foreach(std::thread *t,threads)
          {
            t->join();
            delete t;
          }
        }
        void Add(std::thread *thread)
        {
          threads.push_back(thread);
        }
        
      };
      ThreadList threadList;

      volatile long sharedLocksPassed;
      volatile long uniqueLocksPassed;
    };

    TDOG_TEST_FIXTURE(ShouldBlockSecondUniqueLock, mutexFixture)
    {
      TestTryUniqueLock();
      
      threadList.Clear();
      TDOG_ASSERT_EQ(1,uniqueLocksPassed);
    }

    TDOG_TEST_FIXTURE(MultipleSharedLocks, mutexFixture)
    {
      const long nrOfLocks = 42;
      for(long i = nrOfLocks; i > 0; --i)
        TestTrySharedLock();

      threadList.Clear();
      TDOG_ASSERT_EQ(nrOfLocks,sharedLocksPassed);
    }
    TDOG_TEST_FIXTURE(UniqueBlocksShared, mutexFixture)
    {
      UniqueLock lock2(*mtx);
      TestTrySharedLock();
      
      threadList.Clear();
      TDOG_ASSERT_EQ(0,sharedLocksPassed);
    }
    TDOG_TEST_FIXTURE(SharedBlocksUnique, mutexFixture)
    {
      SharedLock lock2(*mtx);
      TestTryUniqueLock();
      
      threadList.Clear();
      TDOG_ASSERT_EQ(0,uniqueLocksPassed);
    }

    TDOG_CLOSE_SUITE
  }

  TDOG_CLOSE_SUITE
}
