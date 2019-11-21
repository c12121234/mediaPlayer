#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <QObject>
#include <QAction>


class PlayerController : public QObject
{
    Q_OBJECT
public:
    explicit PlayerController(QWidget *parent = nullptr);
    ~PlayerController();
public slots:
    void HandleBtnFileOpen();
    void HandleBtnAboutVersion();

signals:

private:
    void SettingFuctionFeature();
    QWidget* m_pParent;

};

#endif // PLAYERCONTROLLER_H
