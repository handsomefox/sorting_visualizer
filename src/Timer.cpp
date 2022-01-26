#include "Timer.h"

Timer::Timer() {
    m_start = clock::now();
}
void Timer::stop() {
    m_end = clock::now();
}
int64_t Timer::GetElapsed() {
    std::chrono::duration<float> duration = m_end - m_start;
    auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
    return dur.count();
}
