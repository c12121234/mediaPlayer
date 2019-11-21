#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "playercontroller.h"
#include <memory>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_pPlayerController(new PlayerController(this))
{
    ui->setupUi(this);
    ConnectedBtnFeature();
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

