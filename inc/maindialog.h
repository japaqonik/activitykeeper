#include <QDialog>
#include <QLabel>
#include <QSlider>
#include <QCheckBox>
#include <QTimer>
#include "mousemover.h"
#include <memory>
#include <QLayout>
#include "confighandler.h"

#ifndef MAINDIALOG_H
#define MAINDIALOG_H


class MainDialog: public QDialog
{
public:
    MainDialog();

    std::unique_ptr<QBoxLayout> layout;
    std::unique_ptr<QLabel> sliderLabel;
    std::unique_ptr<QSlider> timeSlider;
    std::unique_ptr<QCheckBox> enabledCheckBox;
    std::unique_ptr<QCheckBox> shadowCheckBox;
    std::unique_ptr<QTimer> timer;

    void setEnabledStateChangeAction(std::function<void(int)> action);
    void setShadowStateChangeAction(std::function<void(int)> action);
    void setSliderChangeAction(std::function<void(int)> action);
    void setTimerTimeoutAction(std::function<void()> action);

private:
    IMouseMover *mouseMover;
    IConfigHandler *cfgHandler;

    std::function<void(int)> enabledStateChangeAction;
    std::function<void(int)> shadowStateChangeAction;
    std::function<void(int)> sliderChangeAction;
    std::function<void()> timeoutAction;

    void onEnabledCheckBoxStateChange(int state);
    void onShadowCheckBoxStateChange(int state);
    void onSliderValueChange(int value);
    void onTimerTimeout();
    void closeEvent(QCloseEvent *e);
};

#endif // MAINDIALOG_H
