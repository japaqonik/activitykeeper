#include "maindialog.h"
#include <QIcon>
#include <QLayout>
#include <QCloseEvent>
#include <chrono>
#include <iostream>


MainDialog::MainDialog(IConfigHandler *_cfgHandler, IMouseMover *_mouseMover, QWidget *parent) : QDialog{parent}, mouseMover{_mouseMover}, cfgHandler{_cfgHandler}
{
    auto checkStateToSet = Qt::Checked;
    auto timeSliderValue = 30;
    const auto config = cfgHandler->getConfig();
    if(config)
    {
        checkStateToSet = static_cast<Qt::CheckState>(config->enabled);
        timeSliderValue = config->timerValue;
    }
    else
    {
        Config cfg;
        cfg.enabled = checkStateToSet;
        cfg.timerValue = timeSliderValue;
        cfgHandler->setConfig(cfg);
    }

    setWindowTitle("Cursor mover");
    setFixedSize(180, 100);
    setWindowIcon(QIcon(":icons/icon.ico"));
    setWindowFlags(Qt::WindowCloseButtonHint);

    auto layout = new QBoxLayout(QBoxLayout::TopToBottom, this);

    auto checkBox = new QCheckBox("Enabled");

    checkBox->setCheckState(checkStateToSet);
    connect(checkBox, &QCheckBox::stateChanged, this, &MainDialog::onCheckBoxStateChange);
    layout->addWidget(checkBox, 0, Qt::AlignCenter);

    timeSlider = new QSlider(Qt::Horizontal, this);
    timeSlider->setRange(1, 60);
    timeSlider->setFixedSize(160, 20);
    timeSlider->setTickPosition(QSlider::TicksBelow);
    timeSlider->setTickInterval(5);
    timeSlider->setSingleStep(1);
    timeSlider->setValue(timeSliderValue);
    connect(timeSlider, &QSlider::valueChanged, this, &MainDialog::onSliderValueChange);
    layout->addWidget(timeSlider, 0, Qt::AlignCenter);

    sliderLabel = new QLabel();
    sliderLabel->setText(QString::fromStdString(std::to_string(timeSlider->value())) + "s");
    layout->addWidget(sliderLabel, 0, Qt::AlignCenter);

    connect(&timer, &QTimer::timeout, this, &MainDialog::onTimerTimeout);
    updateTimer(timeSlider->value());
    timer.start();
}

void MainDialog::onCheckBoxStateChange(int state)
{
    if(state == Qt::Checked)
    {
        if(!timer.isActive())
        {
            timer.start();
        }
    }
    else if(state == Qt::Unchecked)
    {
        if(timer.isActive())
        {
            timer.stop();
        }
    }

    auto config = *cfgHandler->getConfig();
    config.enabled = state;
    cfgHandler->setConfig(config);
}

void MainDialog::onSliderValueChange(int value)
{
    sliderLabel->setText(QString::fromStdString(std::to_string(value)) + "s");

    updateTimer(value);

    auto config = *cfgHandler->getConfig();
    config.timerValue = value;
    cfgHandler->setConfig(config);
}

void MainDialog::updateTimer(int newValue)
{
    std::chrono::seconds timeInSeconds(newValue);
    timer.setInterval(std::chrono::milliseconds(timeInSeconds));
}

void MainDialog::onTimerTimeout()
{
    mouseMover->jump();
}

void MainDialog::closeEvent(QCloseEvent *e)
{
    hide();
    e->ignore();
}
