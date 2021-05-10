#include <QSystemTrayIcon>
#include <QAction>

#ifndef SYSTEMTRAYICON_H
#define SYSTEMTRAYICON_H


class SystemTrayIcon : public QSystemTrayIcon
{
public:
    SystemTrayIcon(QWidget *parent);

    QAction *open;
    QAction *exit;

    void setOnOpenAction(std::function<void()> action);
    void setOnExitAction(std::function<void()> action);
    void setOnTrayIconTriggeredAction(std::function<void(ActivationReason)> action);

private:
    std::function<void()> onOpenAction;
    std::function<void()> onExitAction;
    std::function<void(ActivationReason)> onTrayIconTriggeredAction;

    void onOpen();
    void onExit();
    void onTrayIconTriggered(ActivationReason reason);

};

#endif // SYSTEMTRAYICON_H
