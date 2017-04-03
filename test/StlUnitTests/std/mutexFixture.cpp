#pragma hdrstop
#include "../TestBase.h"

#include <std_compat/mutex>
#include <std_compat/thread>

using namespace std;

TDOG_SUITE(stl_compat)
{
  TDOG_SUITE(mutex)
  {
    struct mutexFixture
    {
      bool setup()
      {
        mtx.reset(new std::mutex());

        return true;
      }

      void teardown()
      {
        mtx.reset();
      }

    private:
      void testMutex()
      {
        if (mtx->try_lock())
        {
          mtxIsLocked = false;
          mtx->unlock();
        }
        else
        {
          mtxIsLocked = true;
        }
      }

    public:
      bool islocked()
      {
        std::thread td(&mutexFixture::testMutex, this);
        td.join();

        return mtxIsLocked;
      }

    public:
      std::unique_ptr<std::mutex> mtx;
      volatile bool mtxIsLocked;
    };

    TDOG_TEST_FIXTURE(TryLockShouldPass, mutexFixture)
    {
      bool result = mtx->try_lock();

      TDOG_ASSERT_EQ(true, result);

      TDOG_ASSERT_EQ(true, islocked());

      mtx->unlock();

      TDOG_ASSERT_EQ(false, islocked());
    }

    TDOG_TEST_FIXTURE(LockShouldPass, mutexFixture)
    {
      mtx->lock();

      TDOG_ASSERT_EQ(true, islocked());

      mtx->unlock();

      TDOG_ASSERT_EQ(false, islocked());
    }

    TDOG_CLOSE_SUITE
  }

  TDOG_CLOSE_SUITE
}
