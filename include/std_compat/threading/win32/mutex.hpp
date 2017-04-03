#ifndef std_compat_win32_mutexH
#define std_compat_win32_mutexH

#include <Windows.h>

namespace std_compat
{
  namespace win32
  {


    class basic_mutex
    {
    public:
      typedef PCRITICAL_SECTION native_handle_type;

      basic_mutex()
      {
        InitializeCriticalSection(&cs);
      }

      ~basic_mutex()
      {
        DeleteCriticalSection(&cs);
      }

      bool try_lock()
      {
        return TryEnterCriticalSection(&cs);
      }

      void lock()
      {
        EnterCriticalSection(&cs);
      }

      void unlock()
      {
        LeaveCriticalSection(&cs);
      }

      native_handle_type native_handle()
      {
        return &cs;
      }

    protected:
      CRITICAL_SECTION cs;
    };

    class mutex : public basic_mutex
    {
    public:
 
      bool try_lock()
      {
        bool locked = basic_mutex::try_lock();
        if (locked && cs.RecursionCount > 1)
        {
          // basic_mutex::unlock();
          // throw mutex_recursion
        }
        return locked;
      }

      void lock()
      {
        basic_mutex::lock();
        if (cs.RecursionCount > 1)
        {
          // basic_mutex::unlock();
          // throw mutex_recursion
        }
      }

      mutex(const mutex&) = delete;
      mutex& operator=(const mutex&) = delete;
    };

    class recursive_mutex : public basic_mutex
    {
    public:

      recursive_mutex(const recursive_mutex&) = delete;
      recursive_mutex& operator=(const recursive_mutex&) = delete;
    };
  }
}

#endif
