#include <hayai.hpp>
#include <std_compat/condition_variable>
#include <std_compat/thread>
#include <std_compat/chrono>

namespace
{
  void waiting_thread(std_compat::condition_variable *cv, std::mutex *m, volatile bool &done)
  {
    std::unique_lock<std::mutex> lock(*m);
    cv->notify_one();
    cv->wait(lock);
    done = true;
  }
  class condition_variable : public ::hayai::Fixture
  {
  public:
    virtual void SetUp()
    {
      done = false;
      std::unique_lock<std::mutex> lock(m);
      t1 = std::thread(waiting_thread, &cv, &m, done);
      cv.wait(lock);
    }

    virtual void TearDown()
    {
      t1.join();
    }
    std::thread t1;
    std::thread t2;
    std_compat::condition_variable cv;
    std::mutex m;
    volatile bool done;

  };
  BENCHMARK_F(condition_variable, notifyOne, 100, 10000)
  {
    cv.notify_one();
  }
}
  BENCHMARK_F(condition_variable, notifyOne, 100, 10000)
  {

  }  
