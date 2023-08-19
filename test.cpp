#include <iostream>
#include <chrono>
#include <ctime>

int main() {
    // Get the current time point
    auto currentTime = std::chrono::system_clock::now();

    // Convert the time point to a time_t object
    std::time_t currentTime_t = std::chrono::system_clock::to_time_t(currentTime);

    // Convert the time_t object to a tm structure (broken down time)
    std::tm* currentTime_tm = std::localtime(&currentTime_t);

    // Get the milliseconds and microseconds
    auto duration = currentTime.time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() % 1000;
    auto micros = std::chrono::duration_cast<std::chrono::microseconds>(duration).count() % 1000;

    // Print the current date and time components
    std::cout << "Year: " << 1900 + currentTime_tm->tm_year << std::endl;
    std::cout << "Month: " << 1 + currentTime_tm->tm_mon << std::endl;
    std::cout << "Day: " << currentTime_tm->tm_mday << std::endl;
    std::cout << "Hours: " << currentTime_tm->tm_hour << std::endl;
    std::cout << "Minutes: " << currentTime_tm->tm_min << std::endl;
    std::cout << "Seconds: " << currentTime_tm->tm_sec << std::endl;
    std::cout << "Milliseconds: " << millis << std::endl;
    std::cout << "Microseconds: " << micros << std::endl;

    return 0;
}
