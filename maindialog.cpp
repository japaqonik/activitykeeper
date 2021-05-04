#include "maindialog.h"
#include <QIcon>
#include <QLayout>
#include <QCloseEvent>
#include <chrono>
#include <iostream>


MainDialog::MainDialog(ConfigHandler *_cfgHandler, QWidget *parent) : QDialog(parent), cfgHandler(_cfgHandler)
{
    auto checkStateToSet = Qt::Checked;
    auto timeSliderValue = 30;
    if(cfgHandler->configFileExists())
    {
        checkStateToSet = cfgHandler->getEnabled() ? Qt::Checked : Qt::Unchecked;
        timeSliderValue = cfgHandler->getTimerValue();
    }
    else
    {
        cfgHandler->setEnabled(true);
        cfgHandler->setTimerValue(timeSliderValue);
    }
    setWindowTitle("Cursor mover");
    setFixedSize(250, 100);
    setWindowIcon(QIcon(":icons/mouse.png"));
    setWindowFlags(Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);

    auto layout = new QBoxLayout(QBoxLayout::TopToBottom, this);

    auto checkBox = new QCheckBox("Enabled");

    checkBox->setCheckState(checkStateToSet);
    connect(checkBox, &QCheckBox::stateChanged, this, &MainDialog::onCheckBoxStateChange);
    layout->addWidget(checkBox, 0, Qt::AlignCenter);

    timeSlider = new QSlider(Qt::Horizontal, this);
    timeSlider->setRange(1, 60);
    timeSlider->setFixedSize(230, 20);
    timeSlider->setTickPosition(QSlider::TicksBelow);
    timeSlider->setTickInterval(5);
    timeSlider->setSingleStep(5);
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
        cfgHandler->setEnabled(true);
    }
    else if(state == Qt::Unchecked)
    {
        if(timer.isActive())
        {
            timer.stop();
        }
        cfgHandler->setEnabled(false);
    }
}

void MainDialog::onSliderValueChange(int value)
{
    sliderLabel->setText(QString::fromStdString(std::to_string(value)) + "s");

    updateTimer(value);

    cfgHandler->setTimerValue(value);
}

void MainDialog::updateTimer(int newValue)
{
    std::chrono::seconds timeInSeconds(newValue);
    timer.setInterval(std::chrono::milliseconds(timeInSeconds));
}

void MainDialog::onTimerTimeout()
{
    mouseMover.jump();
}

void MainDialog::closeEvent(QCloseEvent *e)
{
    hide();
    e->ignore();
}
