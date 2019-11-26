#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class PlayerController;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void ConnectedBtnFeature();

private:
    Ui::MainWindow *ui;
    PlayerController* m_pPlayerController;
    QThread* m_pThread;
};
#endif // MAINWINDOW_H
