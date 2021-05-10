#include "maindialog.h"
#include <QIcon>
#include <QCloseEvent>
#include <chrono>

MainDialog::MainDialog() : QDialog{}
{
    setWindowTitle("Activity keeper");
    setFixedSize(180, 100);
    setWindowIcon(QIcon(":icons/icon.ico"));
    setWindowFlags(Qt::WindowCloseButtonHint);

    layout = std::unique_ptr<QBoxLayout>(new QBoxLayout(QBoxLayout::TopToBottom, this));

    enabledCheckBox = std::unique_ptr<QCheckBox>(new QCheckBox("Enabled"));
    layout->addWidget(enabledCheckBox.get(), 0, Qt::AlignCenter);

    shadowCheckBox = std::unique_ptr<QCheckBox>(new QCheckBox("Shadow moves"));
    layout->addWidget(shadowCheckBox.get(), 0, Qt::AlignCenter);

    timeSlider = std::unique_ptr<QSlider>(new QSlider(Qt::Horizontal));
    timeSlider->setRange(1, 60);
    timeSlider->setFixedSize(160, 20);
    timeSlider->setTickPosition(QSlider::TicksBelow);
    timeSlider->setTickInterval(5);
    timeSlider->setSingleStep(1);
    layout->addWidget(timeSlider.get(), 0, Qt::AlignCenter);

    sliderLabel = std::unique_ptr<QLabel>(new QLabel());
    layout->addWidget(sliderLabel.get(), 0, Qt::AlignCenter);

    timer = std::unique_ptr<QTimer>(new QTimer());
}

void MainDialog::setEnabledStateChangeAction(std::function<void (int)> action)
{
    enabledStateChangeAction = action;
    connect(enabledCheckBox.get(), &QCheckBox::stateChanged, this, &MainDialog::onEnabledCheckBoxStateChange);
}

void MainDialog::onEnabledCheckBoxStateChange(int state)
{
    enabledStateChangeAction(state);
}

void MainDialog::setShadowStateChangeAction(std::function<void (int)> action)
{
    shadowStateChangeAction = action;
    connect(shadowCheckBox.get(), &QCheckBox::stateChanged, this, &MainDialog::onShadowCheckBoxStateChange);
}

void MainDialog::onShadowCheckBoxStateChange(int state)
{
    shadowStateChangeAction(state);
}

void MainDialog::setSliderChangeAction(std::function<void (int)> action)
{
    sliderChangeAction = action;
    connect(timeSlider.get(), &QSlider::valueChanged, this, &MainDialog::onSliderValueChange);
}

void MainDialog::onSliderValueChange(int value)
{
    sliderChangeAction(value);
}

void MainDialog::setTimerTimeoutAction(std::function<void()> action)
{
    timeoutAction = action;
    connect(timer.get(), &QTimer::timeout, this, &MainDialog::onTimerTimeout);
}

void MainDialog::onTimerTimeout()
{
    timeoutAction();
}

void MainDialog::closeEvent(QCloseEvent *e)
{
    hide();
    e->ignore();
}
