#pragma hdrstop
#include "../TestBase.h"

#include <std_compat/functional>
#include <std_compat/mutex>
#include <std_compat/condition_variable>
#include <std_compat/thread>

using namespace std;

TDOG_SUITE(stl_compat)
{
  TDOG_SUITE(condition_variable)
  {
    struct condition_variableFixture
    {
      bool setup()
      {
        mtx.reset(new std::mutex());
        cv.reset(new std_compat::condition_variable());
        count = 0;

        return true;
      }

      void teardown()
      {
        mtx.reset();
      }

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

      void notifyOnce()
      {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        {
          std::unique_lock<std::mutex> lock(*mtx.get());

          count++;
        }

        cv->notify_all();
      }

      void waitOnce()
      {
        std::unique_lock<std::mutex> lock(*mtx.get());

        cvArmed = true;

        cv->wait(lock);

        cvReached = true;
      }

      bool islocked()
      {
        std::thread td(&condition_variableFixture::testMutex, this);
        td.join();

        return mtxIsLocked;
      }

    public:
      std::unique_ptr<std::mutex> mtx;
      std::unique_ptr<std_compat::condition_variable> cv;
      volatile bool mtxIsLocked;
      volatile bool cvArmed;
      volatile bool cvReached;
      int count;
    };

    TDOG_TEST_FIXTURE(ShouldReleaseLockDuringWait, condition_variableFixture)
    {
      cvArmed = false;
      cvReached = false;

      std::thread td(&condition_variableFixture::waitOnce, this);

      while (!cvArmed) { std::this_thread::sleep_for(std::chrono::milliseconds(1)); }

      std::this_thread::sleep_for(std::chrono::milliseconds(1));

      TDOG_ASSERT_EQ(false, islocked());

      {
        std::unique_lock<std::mutex> lock(*mtx.get());

        TDOG_ASSERT_EQ(true, islocked());

        cv->notify_one();

      }
    }

    TDOG_TEST_FIXTURE(ShouldNotTriggerOnVariableSnapshot, condition_variableFixture)
    {
      int limit = 1;

      std::thread td1(&condition_variableFixture::notifyOnce, this);
      std::thread td2(&condition_variableFixture::notifyOnce, this);

      std::unique_lock<std::mutex> lock(*mtx.get());
      bool status = cv->wait_for(lock, std::chrono::milliseconds(200), std::bind(std::greater<volatile int>(), count, limit));

      TDOG_ASSERT_EQ(2, count);
      TDOG_ASSERT_NOT(status);
    }

    TDOG_TEST_FIXTURE(ShouldTriggerOnVariableReference, condition_variableFixture)
    {
      int limit = 1;

      std::thread td1(&condition_variableFixture::notifyOnce, this);
      std::thread td2(&condition_variableFixture::notifyOnce, this);

      std::unique_lock<std::mutex> lock(*mtx.get());
      bool status = cv->wait_for(lock, std::chrono::milliseconds(200), std::bind(std::greater<int>(), std::ref(count), limit));

      TDOG_ASSERT_EQ(2, count);
      TDOG_ASSERT(status);
    }

    TDOG_CLOSE_SUITE
  }

  TDOG_CLOSE_SUITE
}
