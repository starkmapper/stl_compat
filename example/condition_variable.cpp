#pragma hdrstop

#include <iostream>
#include <string>
#include <std_compat/thread>
#include <std_compat/mutex>
#include <std_compat/condition_variable>
#include <std_compat/chrono>
std::mutex m;
std_compat::condition_variable cv;
std::string data;
bool ready = false;
bool processed = false;

bool GetReady()
{
  return ready;
}

void worker_thread()
{
  // Wait until main() sends data
  std::unique_lock<std::mutex> lk(m);
  cv.wait(lk, GetReady);

  // after the wait, we own the lock.
  std::cout << "Worker thread is processing data\n";
  data += " after processing";

  // Send data back to main()
  processed = true;
  std::cout << "Worker thread signals data processing completed\n";

  // Manual unlocking is done before notifying, to avoid waking up
  // the waiting thread only to block again (see notify_one for details)
  lk.unlock();
  cv.notify_one();
}

class BoolPred
{
public:
  BoolPred(bool &value)
    :value(value) {}
    bool &value;
  bool operator()() { return value; }
};


std_compat::condition_variable cv2;
std::mutex cv_m;
int i;
bool IsIOne()
{
  return i == 1;
}
void waits(int idx)
{
  std::unique_lock<std::mutex> lk(cv_m);
  if (cv2.wait_for(lk, std::chrono::milliseconds(idx * 100), IsIOne))
    std::cerr << "Thread " << idx << " finished waiting. i == " << i << '\n';
  else
    std::cerr << "Thread " << idx << " timed out. i == " << i << '\n';
}

void signals()
{
  std::this_thread::sleep_for(std::chrono::milliseconds(120));
  std::cerr << "Notifying...\n";
  cv2.notify_all();
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  {
    std::lock_guard<std::mutex> lk(cv_m);
    i = 1;
  }
  std::cerr << "Notifying again...\n";
  cv2.notify_all();
}



int main()
{
  std::thread worker(worker_thread);

  data = "Example data";
  // send data to the worker thread
  {
    std::lock_guard<std::mutex> lk(m);
    ready = true;
    std::cout << "main() signals data ready for processing\n";
  }
  cv.notify_one();

  // wait for the worker
  {
    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, BoolPred(processed));
  }
  std::cout << "Back in main(), data = " << data << '\n';

  worker.join();
  std::cout << "Running wait_for" << std::endl;
  
  std::thread t1(waits, 1), t2(waits, 2), t3(waits, 3), t4(signals);
  t1.join(); t2.join(), t3.join(), t4.join();
}
