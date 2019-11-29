#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <QObject>
#include <QAction>
class IPlayerFeature;

class PlayerController : public QObject
{
    Q_OBJECT
public:
    explicit PlayerController(QWidget* pmember, QWidget *parent = nullptr);
    ~PlayerController();
public slots:
    void HandleBtnFileOpen();
    void HandleBtnAboutVersion();
    void HandleBtnPause();
    void HandleBtnStart();
    void HandleBtnStop();
    void HandleProgressBarClicked(qint64 val);
    void HandleProgressBarmoved(qint64 val);
    void HandleProgressBarReleased();
    void HandleTimerStopFromView();
    void SettingFuctionFeature();
    void HandleVolumeChanged(int nVal);

signals:
    void SendHandleBtnFileOpenSignal(IPlayerFeature* pIP);
    void SendHandleBtnAboutVersion(IPlayerFeature* pIP);
    void SendHandleBtnPauseSignal(IPlayerFeature* pIP);
    void EmitTimerStopSignal();
    void EmitProgressNOPauseClicked();
private:
    QWidget* m_pParent;
    bool m_bBtnClicked;

};

#endif // PLAYERCONTROLLER_H
