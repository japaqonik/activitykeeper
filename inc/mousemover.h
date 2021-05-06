#include <string>
#include "imousemover.h"
#include "imousehandler.h"

#ifndef MOUSEMOVER_H
#define MOUSEMOVER_H


class MouseMover : public IMouseMover
{
public:
    MouseMover(IMouseHandler *_mouseHandler, bool enabledObservability = false);
    void jump() override;
private:
    IMouseHandler *mouseHandler;
    bool lastYOpposite = false;
    bool lastXOpposite = false;
    bool observabilityEnabled = false;

    long increment(long point, bool &opposite, long bound);
    void printMsg(std::string msg);
};

#endif // MOUSEMOVER_H
