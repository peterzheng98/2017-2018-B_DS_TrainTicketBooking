//
// Created by Peter Zheng on 2018/05/08.
//

#ifndef SERVERSIDEPROGRAM_TIMER_H
#define SERVERSIDEPROGRAM_TIMER_H


typedef unsigned long long ull;
typedef long long ll;
typedef unsigned short us;
class Timer {
protected:
    ull cTimer;
public:
    Timer() : cTimer(0) {}

    Timer(ull startTime) : cTimer(startTime) {}

    Timer(const Timer &rhs) : cTimer(rhs.cTimer) {}

    Timer &operator=(const Timer &rhs) {
        if (this != &rhs) return *this;
        cTimer = rhs.getTime();
        return *this;
    }

    const ull getTime() const { return cTimer; }

    Timer &operator++() {
        cTimer++;
        return *this;
    };

    Timer operator++(int) {
        auto tmp = *this;
        cTimer++;
        return tmp;
    }

};

#endif //SERVERSIDEPROGRAM_TIMER_H
