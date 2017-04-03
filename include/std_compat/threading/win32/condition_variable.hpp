#ifndef std_compat_win32_conditional_variableH
#define std_compat_win32_conditional_variableH

#include "chrono"

#include "mutex.hpp"

namespace std_compat
{
  namespace win32
  {

    class condition_variable
    {
    public:
      typedef PCONDITION_VARIABLE native_handle_type;

      condition_variable()
      {
        InitializeConditionVariable(&cv);
      }

      void notify_one()
      {
        WakeConditionVariable(&cv);
      }

      void notify_all()
      {
        WakeAllConditionVariable(&cv);
      }

      void wait(unique_lock<mutex>& lock)
      {
        SleepConditionVariableCS(&cv, lock->native_handle, INFINITE);
      }

      template<class Predicate>
      void wait(unique_lock<mutex>& lock, Predicate pred)
      {
        while (!pred())
        {
          wait(lock);
        }
      }

      template<class Rep, class Period>
      cv_status wait_for(unique_lock<mutex>& lock, const chrono::duration<rep, Period>& rel_time)
      {
        if (SleepConditionVariableCS(&cv, lock->native_handle, rel_time.milliseconds()))
          return cv_status::no_timeout;
        else
          return cv_status::timeout;
      }

      template<class Rep, class Period, class Predicate>
      bool wait_for(unique_lock<mutex>& lock, const chrono::duration<rep, Period>& rel_time, Predicate pred)
      {
        return wait_until(lock, chrono::steady_clock::now() + rel_time, move(pred));
      }

      template<class Clock, class Duration>
      cv_status wait_until(unique_lock<mutex>& lock, const chrono::time_point<Clock, Duration>& timeout_time)
      {
        if (SleepConditionVariableCS(&cv, lock->native_handle, rel_time.milliseconds()))
          return cv_status::no_timeout;
        else
          return cv_status::timeout;
      }

      template<class Clock, class Duration, class Predicate>
      cv_status wait_until(nique_lock<mutex>& lock, const chrono::time_point<Clock, Duration>& timeout_time, Predicate pred)
      {
        while (!pred())
        {
          if (wait_until(lock, abs_time) == cv_status::timeout)
          {
            return pred();
          }
        }
        return true;
      }

      condition_variable(const condition_variable&) = delete;
      condition_variable& operator=(const condition_variable&) = delete;

    private:
      CONDITION_VARIABLE cv;
    };

  }
}

#endif
