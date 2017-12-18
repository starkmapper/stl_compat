#ifndef chrono_boost_wrapper_hpp
#define chrono_boost_wrapper_hpp

#include <std_compat/ratio>
#include "boost/date_time/posix_time/posix_time.hpp"

namespace std_compat
{
  namespace chrono
  {
    template <class Rep, class Period>
    class duration
    {
    private:
      Rep const ticks;

    public:
      typename Rep tick_type;
      typename Period tick_interval;

      duration(Rep ticks)
        : ticks(ticks)
      {

      }

      duration(duration<Rep, Period> const & src)
        : ticks(src.ticks)
      {

      }

      Rep count() const
      {
        return ticks;
      }
    };

    class high_resolution_clock
    {
    public:
      typedef duration<long long, std::nano> duration;

      struct time_point
      {
        boost::posix_time::ptime ptime;
        time_point(boost::posix_time::ptime const & ptime)
          : ptime(ptime)
        {

        }

        duration operator -(time_point const & other)
        {
          return duration((ptime - other.ptime).total_nanoseconds());
        }
        template<class Duration>
        time_point operator +(Duration d)
        {
          return ptime + d;
        }
        bool operator <(time_point const & other)
        {
          return (ptime < other.ptime);
        }
      };

      static time_point now()
      {
        return time_point(boost::posix_time::microsec_clock::local_time());
      }
    };

    template <class To, class Rep, class Period>
    To duration_cast(duration<Rep,Period> const & from)
    {
      static_assert("Not Implemented");
    }

    template <>
    duration<double, std::milli> duration_cast<duration<double, std::milli>, long long, std::nano>(duration<long long, std::nano> const & from)
    {
      return duration<double, std::milli>(from.count() / 1000000.0);
    }
	}
}

#endif