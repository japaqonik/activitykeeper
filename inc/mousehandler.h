#include "imousehandler.h"
#include "point.h"

#ifndef MOUSEHANDLER_H
#define MOUSEHANDLER_H


class MouseHandler : public IMouseHandler
{
public:
    MouseHandler();

    Point getScreenSize() override;
    Point getCursorPos() override;
    void setCursorPos(Point target) override;

private:
    static constexpr double ABSOLUTE_CURSOR_BOUND = 0xffff;
    int normalize(int from, int upperBound);
};

#endif // MOUSEHANDLER_H
