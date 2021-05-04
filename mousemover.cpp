#include <windows.h>
#include <iostream>
#include "mousemover.h"

MouseMover::MouseMover()
{

}

MouseMover::MouseMover(bool enabledObservability) : observabilityEnabled{enabledObservability}
{

}

void MouseMover::move()
{
    const auto width = GetSystemMetrics( SM_CXSCREEN ) - 1;
    const auto height = GetSystemMetrics( SM_CYSCREEN ) - 1;

    printMsg("Screen size: " + std::to_string(width) + "x" + std::to_string(height));

    POINT point;

    if(GetCursorPos(&point))
    {
        printMsg("Current cursor posiztion: " + std::to_string(point.x) + "x" + std::to_string(point.y));

        auto newX = increment(point.x, lastXOpposite, width);
        auto newY = increment(point.y, lastYOpposite, height);

        printMsg("New cursor posiztion: " + std::to_string(newX) + "x" + std::to_string(newY));
        printMsg("----------------------------------");

        moveCursorTo(mapValue(newX, width), mapValue(newY, height));
        printMsg("==================================");
    }
}

long MouseMover::mapValue(long value, long bound)
{
    const double factor = ABSOLUTE_CURSOR_BOUND / bound;
    printMsg("Multiplication factor: " + std::to_string(factor));

    const long result = value * factor;
    printMsg("Normalized value: " + std::to_string(result) + " from value: " + std::to_string(value));

    return result;
}

void MouseMover::moveCursorTo(long x, long y)
{
    INPUT inpt;
    memset(&inpt, 0, sizeof(inpt));
    inpt.type = INPUT_MOUSE;
    inpt.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
    inpt.mi.dx = x;
    inpt.mi.dy = y;
    SendInput(1, &inpt, sizeof(inpt));
}

void MouseMover::jump()
{
    move();
    move();
}

long MouseMover::increment(long point, bool &opposite, long bound)
{
    if(opposite)
    {
        if(point == 0)
        {
            return ++point;
        }
        else
        {
            opposite = !opposite;
            return --point;
        }
    }
    else
    {
        if(point == bound)
        {
            return --point;
        }
        else
        {
            opposite = !opposite;
            return ++point;
        }
    }
}

void MouseMover::printMsg(std::string msg)
{
    if(observabilityEnabled)
    {
       std::cout << msg << std::endl;
    }
}
