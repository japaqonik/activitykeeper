#include <windows.h>
#include <iostream>
#include "mousemover.h"

MouseMover::MouseMover(IMouseHandler *_mouseHandler, bool enabledObservability) : mouseHandler{_mouseHandler}, observabilityEnabled{enabledObservability}
{

}

void MouseMover::jump()
{
    auto screenSize = mouseHandler->getScreenSize();

    auto cursorPos = mouseHandler->getCursorPos();

    Point newCursorPos;
    newCursorPos.x = increment(cursorPos.x, lastXOpposite, screenSize.x);
    newCursorPos.y = increment(cursorPos.y, lastYOpposite, screenSize.y);

    mouseHandler->setCursorPos(newCursorPos);
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
