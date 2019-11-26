#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "playercontroller.h"
#include <memory>
#include <QThread>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_pPlayerController(new PlayerController(this))
    , m_pThread(new QThread())
{
    ui->setupUi(this);
    ConnectedBtnFeature();
    qDebug()<<"MainWindow:"<<QThread::currentThreadId()<<"\n";
    //m_pPlayerController->moveToThread(m_pThread);
    //m_pThread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
    //delete m_pPlayerController;
}

void MainWindow::ConnectedBtnFeature()
{
    connect(ui->actionVersion,&QAction::triggered,m_pPlayerController,&PlayerController::HandleBtnAboutVersion);
    connect(ui->actionOpen,&QAction::triggered,m_pPlayerController,&PlayerController::HandleBtnFileOpen);
}

