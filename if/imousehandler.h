#include "point.h"

#ifndef IMOUSEHANDLER_H
#define IMOUSEHANDLER_H

class IMouseHandler
{
public:
    virtual Point getScreenSize() = 0;
    virtual Point getCursorPos() = 0;
    virtual void setCursorPos(Point target) = 0;
};

#endif // IMOUSEHANDLER_H
