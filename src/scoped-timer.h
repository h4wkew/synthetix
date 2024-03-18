#ifndef SCOPED_TIMER_H
#define SCOPED_TIMER_H

#include <string>
#include <chrono>

class scoped_timer
{
public:
    scoped_timer(const std::string &name);
    ~scoped_timer();

private:
    std::string m_name;
    std::chrono::steady_clock::time_point m_start;
};

#endif