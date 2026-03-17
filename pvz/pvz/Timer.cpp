#include "Timer.h"

void Timer::Restart() {
    passTime = 0;
    isTrigger = false;
    isRunning = true;
    isPaused = false;
}

void Timer::SetWaitTime(int val) {
    waitTime = val;
}

void Timer::SetOneTrigger(bool flag) {
    isOneTrigger = flag;
}

void Timer::SetCallback(std::function<void()> callback) {
    this->callback = callback;
}

void Timer::Pause() {
    isPaused = true;
    isRunning = false;
}

void Timer::Resume() {
    isPaused = false;
    isRunning = true;
}

void Timer::Update(int delta) {
    if (isPaused) {
        return;
    }
    passTime += delta;
    if (passTime >= waitTime) {
        if ((!isOneTrigger || !isTrigger) && callback) {
            callback();
            if (isOneTrigger) {
                isRunning = false;
            }
        }
        isTrigger = true;
        passTime = 0;
    }
}

bool Timer::IsTrigger() {
    return isTrigger;
}
