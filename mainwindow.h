#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGlobal>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class PlayerController;
class IPlayerFeature;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void ConnectedBtnFeature();
public slots:
    void WorkBtnFileOpen(IPlayerFeature* pIP);
    void WorkBtnAbout(IPlayerFeature* pIP);
    void HandleProgressBarChanged(qint64 val);
    void HandleProgressBarPressed();
    void HandleProgressBarMoved();
    void HandleProgressBarReleasedFromView();

signals:
    void SendProgressBarPressed(int val);
    void SendProgressBarMoved(int val);
    void SendProgressBarReleased();
    void EmitTimerStopSignal();
private:
    Ui::MainWindow *ui;
    PlayerController* m_pPlayerController;
    QThread* m_pThread;
    int m_nMaxlength;
};
#endif // MAINWINDOW_H
