#include "Log.h"

Log *Log::instance = nullptr;

Log::Log()
{
    saveTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    saveUserTimeUs = 0;
    saveSysTimeUs = 0;
    logFile.open("logs/" + timeValueRefactoring() + ".log", std::ios::app);
}

Log *Log::getInstance()
{
    if (instance == nullptr)
    {
        instance = new Log();
    }
    return instance;
}

std::string Log::ramValueRefactoring(unsigned long int rss)
{
    std::string ramRefactoring;
    unsigned int go, mo, ko, o;
    go = rss / 1000000000;
    rss -= go * 1000000000;
    mo = rss / 1000000;
    rss -= mo * 1000000;
    ko = rss / 1000;
    rss -= ko * 1000;
    o = rss;
    ramRefactoring = std::to_string(go) + " Go " +
                     std::to_string(mo) + " mo " +
                     std::to_string(ko) + " ko " +
                     std::to_string(o) + " o";
    return ramRefactoring;
}

std::string Log::timeValueRefactoring()
{
    std::string timeRefactoring;
    unsigned short int y, m, d, h, mins, s;

    auto currentTime = std::chrono::system_clock::now();

    std::time_t currentTime_t = std::chrono::system_clock::to_time_t(currentTime);
    std::tm *currentTime_tm = std::localtime(&currentTime_t);

    y = 1900 + currentTime_tm->tm_year;
    m = 1 + currentTime_tm->tm_mon;
    d = currentTime_tm->tm_mday;
    h = currentTime_tm->tm_hour;
    mins = currentTime_tm->tm_min;
    s = currentTime_tm->tm_sec;

    timeRefactoring = std::to_string(m) + "-" +
                      std::to_string(d) + "-" +
                      std::to_string(y) + " " +
                      std::to_string(h) + ":" +
                      std::to_string(mins) + ":" +
                      std::to_string(s);

    return timeRefactoring;
}

bool Log::logMessage(std::string messageType, std::string message)
{
    struct rusage r;

    float percentUserCpu, percentSysCpu;
    unsigned long int diffTime, userTimeUs, sysTimeUs;

    auto currentTime = std::chrono::system_clock::now();
    auto duration = currentTime.time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() % 1000;
    auto micros = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();

    diffTime = micros - saveTime;

    getrusage(RUSAGE_SELF, &r);

    userTimeUs = r.ru_utime.tv_sec * 1000000 + r.ru_utime.tv_usec;
    sysTimeUs = r.ru_stime.tv_sec * 1000000 + r.ru_stime.tv_usec;

    percentUserCpu = (float)(userTimeUs - saveUserTimeUs) / (float)diffTime * 100.0 / 16;
    percentSysCpu = (float)(sysTimeUs - saveSysTimeUs) / (float)diffTime * 100.0 / 16;

    if (logFile.is_open())
    {
        logFile << timeValueRefactoring() << ":" << millis << ":" << micros % 1000
                << " {CPU user = " << percentUserCpu << "%, CPU system = " << percentSysCpu
                << "%, RAM = " << ramValueRefactoring(r.ru_maxrss * 1024) << "} [" << messageType
                << "] -> " << message
                << std::endl;
        logFile.flush();
    }

    saveTime = micros;
    saveUserTimeUs = userTimeUs;
    saveSysTimeUs = sysTimeUs;

    return true;
}

Log::~Log()
{
    if (logFile.is_open())
    {
        logFile.close();
    }
}