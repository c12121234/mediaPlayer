#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "playercontroller.h"
#include "iplayerfeature.h"
#include <memory>
#include <QThread>
#include <QDebug>
#include <QPushButton>
#include <QMediaPlayer>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_pPlayerController(new PlayerController(this))
    , m_pThread(new QThread())
    , m_nMaxlength(1000)
{
    ui->setupUi(this);   
    ui->BtnPlay->hide();
    ui->BtnStop->hide();
    ui->BtnPause->hide();
    ui->horizontalSlider->hide();
    ui->verticalSlider->hide();
    ConnectedBtnFeature();
    qDebug()<<"MainWindow:"<<QThread::currentThreadId()<<"\n";
    m_pPlayerController->moveToThread(m_pThread);
    m_pThread->start();
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::ConnectedBtnFeature()
{
    connect(ui->actionVersion,&QAction::triggered,m_pPlayerController,&PlayerController::HandleBtnAboutVersion);
    connect(ui->actionOpen,&QAction::triggered,m_pPlayerController,&PlayerController::HandleBtnFileOpen);
    connect(m_pPlayerController,&PlayerController::SendHandleBtnFileOpenSignal,this,&MainWindow::WorkBtnFileOpen);
    connect(m_pPlayerController,&PlayerController::SendHandleBtnAboutVersion,this,&MainWindow::WorkBtnAbout);
    connect(ui->BtnPause,&QPushButton::clicked,m_pPlayerController,&PlayerController::HandleBtnPause);
    connect(ui->BtnPlay,&QPushButton::clicked,m_pPlayerController,&PlayerController::HandleBtnStart);
    connect(ui->BtnStop,&QPushButton::clicked,m_pPlayerController,&PlayerController::HandleBtnStop);
    connect(ui->horizontalSlider,&QAbstractSlider::sliderPressed,this,&MainWindow::HandleProgressBarPressed);
    connect(this,&MainWindow::SendProgressBarPressed,m_pPlayerController,&PlayerController::HandleProgressBarClicked);
    connect(this,&MainWindow::EmitTimerStopSignal,m_pPlayerController,&PlayerController::HandleTimerStopFromView);
    connect(ui->horizontalSlider,&QAbstractSlider::sliderMoved,this,&MainWindow::HandleProgressBarMoved);
    connect(this,&MainWindow::SendProgressBarMoved,m_pPlayerController,&PlayerController::HandleProgressBarmoved);
    connect(ui->horizontalSlider,&QAbstractSlider::sliderReleased,this,&MainWindow::HandleProgressBarReleasedFromView);
    connect(this,&MainWindow::SendProgressBarReleased,m_pPlayerController,&PlayerController::HandleProgressBarReleased);
}

void MainWindow::WorkBtnFileOpen(IPlayerFeature *pIP)
{
    ui->BtnPlay->setVisible(true);
    ui->BtnStop->setVisible(true);
    ui->BtnPause->setVisible(true);
    ui->horizontalSlider->setVisible(true);
    ui->horizontalSlider->setRange(0,m_nMaxlength);
    ui->verticalSlider->setVisible(true);
    OpenFileFeature* pOF = dynamic_cast<OpenFileFeature*>(pIP);
    connect(pOF,&OpenFileFeature::SendPositionDurationSignal,this,&MainWindow::HandleProgressBarChanged);
    pOF->WorkedFeature(this);

}

void MainWindow::WorkBtnAbout(IPlayerFeature *pIP)
{
    pIP->WorkedFeature(this);
}

void MainWindow::HandleProgressBarChanged(qint64 val)
{
    ui->horizontalSlider->setValue(val);
}

void MainWindow::HandleProgressBarPressed()
{
    int nVal = ui->horizontalSlider->value();
    emit SendProgressBarPressed(nVal);
}

void MainWindow::HandleProgressBarMoved()
{
    emit EmitTimerStopSignal();
    int nVal = ui->horizontalSlider->value();
    emit SendProgressBarMoved(nVal);

}

void MainWindow::HandleProgressBarReleasedFromView()
{
    emit SendProgressBarReleased();
}
