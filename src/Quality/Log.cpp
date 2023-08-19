#include "Log.h"

unsigned long int saveTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
unsigned long int saveUserTimeUs = 0;
unsigned long int saveSysTimeUs = 0;

Log::Log()
{
}

bool Log::send(std::string messageType, std::string message)
{
    struct rusage r;

    float percentUserCpu, percentSysCpu;
    unsigned long int rss, diffTime, userTimeUs, sysTimeUs;
    unsigned int go, mo, ko, o;

    unsigned short int y, ms, us;
    unsigned short int m, d, h, mins, s;

    auto currentTime = std::chrono::system_clock::now();

    std::time_t currentTime_t = std::chrono::system_clock::to_time_t(currentTime);
    std::tm *currentTime_tm = std::localtime(&currentTime_t);
    auto duration = currentTime.time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() % 1000;
    auto micros = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();

    y = 1900 + currentTime_tm->tm_year;
    m = 1 + currentTime_tm->tm_mon;
    d = currentTime_tm->tm_mday;
    h = currentTime_tm->tm_hour;
    mins = currentTime_tm->tm_min;
    s = currentTime_tm->tm_sec;
    ms = millis;
    us = micros % 1000;

    diffTime = micros - saveTime;

    getrusage(RUSAGE_SELF, &r);
    rss = r.ru_maxrss * 1024;
    go = rss / 1000000000;
    rss -= go * 1000000000;
    mo = rss / 1000000;
    rss -= mo * 1000000;
    ko = rss / 1000;
    rss -= ko * 1000;
    o = rss;

    userTimeUs = r.ru_utime.tv_sec * 1000000 + r.ru_utime.tv_usec;
    sysTimeUs = r.ru_stime.tv_sec * 1000000 + r.ru_stime.tv_usec;

    percentUserCpu = (float)(userTimeUs - saveUserTimeUs) / (float)diffTime * 100.0 / 16;
    percentSysCpu = (float)(sysTimeUs - saveSysTimeUs) / (float)diffTime * 100.0 / 16;

    // printf("%d-%d-%d %d:%d:%d:%d:%d {CPU user = %f, CPU system = %f, RAM = %d Go %d Mo %d Ko %d o} [%s] -> %s\n",
    //         m, d, y, h, mins, s, ms, us, percentUserCpu, percentSysCpu, go, mo, ko, o, messageType, message
    // );

    std::cout << m << "-" << d << "-" << y << " " << h << ":" << mins << ":" << s << ":" << ms << ":" << us
              << " {CPU user = " << percentUserCpu << "%, CPU system = " << percentSysCpu
              << "%, RAM = " << go << " Go " << mo << " Mo " << ko << " Ko " << o << " o} [" << messageType
              << "] -> " << message << std::endl;

    saveTime = micros;
    saveUserTimeUs = userTimeUs;
    saveSysTimeUs = sysTimeUs;

    return true;
}

Log::~Log()
{
}