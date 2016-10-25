#ifndef __TIMER_H_
#define __TIMER_H_

#ifdef _MSC_VER
#  define SPRINTF(a, b, c) sprintf_s(a, b, c)
#else
#  define SPRINTF(a, b, c) sprintf(a, b, c)
#endif // _MSC_VER

#include <stdio.h>
#include <string>
#include <sstream>

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread.hpp>
#include <boost/format.hpp>

using namespace boost::gregorian;
using namespace std;

class Timer
{
  public:
    // TODO: thread safe
    static unsigned long getTime()
    {
#ifndef _MSC_VER
      timeval getTimeOfDayTime;
      gettimeofday(&getTimeOfDayTime, 0);
      return ((getTimeOfDayTime.tv_sec  % 10000) * 1000 + getTimeOfDayTime.tv_usec / 1000);
#else // _MSC_VER
      return 0;
#endif // _MSC_VER
    };

    static unsigned long getUTime()
    {
#ifndef _MSC_VER
      timeval getTimeOfDayTime;
      gettimeofday(&getTimeOfDayTime, 0);
      return ((getTimeOfDayTime.tv_sec  % 10000) * 1000 + getTimeOfDayTime.tv_usec);
#else // _MSC_VER
      return 0;
#endif // _MSC_VER

    }

    static void getDateString(std::string *dateString)
    {
      date d(day_clock::local_day());
      *dateString = to_iso_extended_string(d);
    };

    static void getDateTimeString(std::string *dateString)
    {
      stringstream oss;
#ifndef _MSC_VER
      char buf[2];
      time_t rawtime;
      struct tm * ptm;
      time ( &rawtime );
      ptm = gmtime ( &rawtime );

      date d(day_clock::local_day());
      string s = to_iso_extended_string(d);
      oss << s << "-";
      oss << boost::format("%02d-%02d-%02d") % ptm->tm_hour % ptm->tm_min % ptm->tm_sec;
#else // _MSC_VER
      cout << "getDateTimeString not yet supported in windows version" << endl;
#endif // _MSC_VER

      *dateString = oss.str();
    };

    Timer()
    {
      _last = boost::posix_time::microsec_clock::local_time();
    };

    void reset()
    {
      _last = boost::posix_time::microsec_clock::local_time();
    };

    long get()
    {
      boost::posix_time::ptime now = boost::posix_time::microsec_clock::local_time();
      boost::posix_time::time_duration  diff = now - _last;
      return diff.total_microseconds();
    };


    void sleep(long m)
    {
      boost::this_thread::sleep(boost::posix_time::microsec(m));
    };

  private:
      boost::posix_time::ptime _last;

};

#endif // __TIMER_H_

