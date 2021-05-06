#include <windows.h>
#include <iostream>
#include "mousehandler.h"

MouseHandler::MouseHandler()
{

}

Point MouseHandler::getScreenSize()
{
    Point screenSize;
    screenSize.x = GetSystemMetrics( SM_CXSCREEN ) - 1;
    screenSize.y = GetSystemMetrics( SM_CYSCREEN ) - 1;

    return screenSize;
}

Point MouseHandler::getCursorPos()
{
    Point cursorPos;
    cursorPos.x = 0;
    cursorPos.y = 0;

    POINT point;
    if(GetCursorPos(&point))
    {
        cursorPos.x = point.x;
        cursorPos.y = point.y;
    }

    return cursorPos;
}

void MouseHandler::setCursorPos(Point target)
{
    constexpr unsigned int numberOfInputs = 1;
    const auto screenSize = getScreenSize();

    INPUT inpt;
    memset(&inpt, 0, sizeof(inpt));
    inpt.type = INPUT_MOUSE;
    inpt.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
    inpt.mi.dx = normalize(target.x, screenSize.x);
    inpt.mi.dy = normalize(target.y, screenSize.y);
    SendInput(numberOfInputs, &inpt, sizeof(inpt));
}

int MouseHandler::normalize(int from, int upperBound)
{
    const double factor = ABSOLUTE_CURSOR_BOUND / upperBound;
    return from * factor;
}


