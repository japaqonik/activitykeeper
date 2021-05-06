#include <QDialog>
#include <QLabel>
#include <QSlider>
#include <QCheckBox>
#include <QTimer>
#include "mousemover.h"
#include "confighandler.h"

#ifndef MAINDIALOG_H
#define MAINDIALOG_H


class MainDialog: public QDialog
{
public:
    MainDialog(IConfigHandler *_cfgHandler, IMouseMover *_mouseMover, QWidget *parent = nullptr);

private:
    QLabel * sliderLabel;
    QSlider * timeSlider;
    QTimer timer;
    IMouseMover *mouseMover;
    IConfigHandler *cfgHandler;
    void onCheckBoxStateChange(int state);
    void onSliderValueChange(int value);
    void onTimerTimeout();
    void closeEvent(QCloseEvent *e);
    void updateTimer(int newValue);
};

#endif // MAINDIALOG_H
