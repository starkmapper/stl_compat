#include <hayai.hpp>
#include <std_compat/condition_variable>
#include <std_compat/thread>
#include <std_compat/chrono>

namespace
{
  void waiting_thread(std_compat::condition_variable *cv, std::mutex *m, volatile bool &done)
  {
    std::unique_lock<std::mutex> lock(*m);
    cv->wait(lock);
    done = true;
  }
  class fixture : public ::hayai::Fixture
  {
  public:
    virtual void SetUp()
    {
      done = false;
      t1 = std::thread(waiting_thread, &cv, &m, done);
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    virtual void TearDown()
    {

    }
    std::thread t1;
    std::thread t2;
    std_compat::condition_variable cv;
    std::mutex m;
    volatile bool done;

  };
  BENCHMARK_F(fixture, notifyOne, 10, 10000)
  {
    cv.notify_one();
    t1.join();
  }
}