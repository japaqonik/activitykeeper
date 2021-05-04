#include <string>

#ifndef MOUSEMOVER_H
#define MOUSEMOVER_H


class MouseMover
{
public:
    MouseMover();
    MouseMover(bool enabledObservability);
    void jump();
private:
    bool lastYOpposite = false;
    bool lastXOpposite = false;
    bool observabilityEnabled = false;
    static constexpr double ABSOLUTE_CURSOR_BOUND = 0xffff;
    void move();
    void printMsg(std::string msg);
    long increment(long point, bool & opposite, long bound);
    void moveCursorTo(long x, long y);
    long mapValue(long value, long bound);
};

#endif // MOUSEMOVER_H
