#include "scoped-timer.h"

#include <iostream>

scoped_timer::scoped_timer(const std::string &name)
    : m_name(name)
    , m_start(std::chrono::steady_clock::now())
{}

scoped_timer::~scoped_timer()
{
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - m_start);
    
    std::cout << "Timer " << m_name << " took " << duration.count() << " microseconds" << std::endl;
}