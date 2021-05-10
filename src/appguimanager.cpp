#include "appguimanager.h"

AppGuiManager::AppGuiManager(IConfigHandler *_cfgHandler, IMouseMover *_mouseMover) : mouseMover{_mouseMover}, cfgHandler{_cfgHandler}
{
    widget = std::unique_ptr<QWidget>(new QWidget());
    tray = std::unique_ptr<SystemTrayIcon>(new SystemTrayIcon(widget.get()));
    tray->setOnOpenAction([this] { onOpen(); } );
    tray->setOnExitAction([this] { onExit(); } );
    tray->setOnTrayIconTriggeredAction([this] (QSystemTrayIcon::ActivationReason reason) { onTrayIconActivated(reason); } );

    dialog = std::unique_ptr<MainDialog>(new MainDialog());
    dialog->setEnabledStateChangeAction([this](int state) { onEnabledCheckBoxStateChange(state); } );
    dialog->setShadowStateChangeAction([this](int state) { onShadowCheckBoxStateChange(state); } );
    dialog->setSliderChangeAction([this](int value) { onSliderValueChange(value); } );
    dialog->setTimerTimeoutAction([this] { onTimerTimeout(); } );

    initConfig();
    const auto config = cfgHandler->getConfig();
    dialog->enabledCheckBox->setCheckState(static_cast<Qt::CheckState>(config->enabled));
    dialog->shadowCheckBox->setCheckState(static_cast<Qt::CheckState>(config->shadowEnabled));
    dialog->timeSlider->setValue(config->timerValue);

    updateTimer(config->timerValue);
    dialog->timer->start();
}

void AppGuiManager::initConfig()
{
    if(!cfgHandler->getConfig())
    {
        Config config;
        config.enabled = Qt::Checked;
        config.shadowEnabled = Qt::Checked;
        config.timerValue = 30;
        cfgHandler->setConfig(config);
    }
}

void AppGuiManager::updateTimer(int newValue)
{
    std::chrono::seconds timeInSeconds(newValue);
    dialog->timer->setInterval(std::chrono::milliseconds(timeInSeconds));
}

void AppGuiManager::onEnabledCheckBoxStateChange(int state)
{
    if(state == Qt::Checked)
    {
        if(!dialog->timer->isActive())
        {
            dialog->timer->start();
        }
    }
    else if(state == Qt::Unchecked)
    {
        if(dialog->timer->isActive())
        {
            dialog->timer->stop();
        }
    }

    auto config = *cfgHandler->getConfig();
    config.enabled = state;
    cfgHandler->setConfig(config);
}

void AppGuiManager::onShadowCheckBoxStateChange(int state)
{
    auto config = *cfgHandler->getConfig();
    config.shadowEnabled = state;
    cfgHandler->setConfig(config);
}

void AppGuiManager::onSliderValueChange(int value)
{
    dialog->sliderLabel->setText(QString::fromStdString(std::to_string(value)) + "s");

    updateTimer(value);

    auto config = *cfgHandler->getConfig();
    config.timerValue = value;
    cfgHandler->setConfig(config);
}

void AppGuiManager::onTimerTimeout()
{
    if(dialog->shadowCheckBox->checkState() == Qt::Checked)
    {
        mouseMover->jump();
    }
    mouseMover->jump();
}

void AppGuiManager::onOpen()
{
    if(!dialog->isVisible())
    {
        dialog->show();
    }
}

void AppGuiManager::onExit()
{
    std::exit(0);
}

void AppGuiManager::onTrayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if(reason == QSystemTrayIcon::DoubleClick)
    {
        if(dialog->isVisible())
        {
            dialog->hide();
        }
        else
        {
            dialog->show();
        }
    }
}

void AppGuiManager::start()
{
    tray->show();
    dialog->show();
}
