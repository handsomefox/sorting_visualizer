#pragma once

#include <chrono>

class Timer {
public:
    Timer();
    void stop();
    int64_t GetElapsed();

private:
    using clock = std::chrono::high_resolution_clock;
    std::chrono::time_point<clock> m_start{};
    std::chrono::time_point<clock> m_end{};
};
