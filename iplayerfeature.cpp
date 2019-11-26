#include "iplayerfeature.h"
#include <QMessageBox>
#include <QObject>
#include <QWidget>
#include <QString>
#include <QMediaPlayer>
#include <QUrl>
#include <QFileDialog>
#include <QThread>
#include <QDebug>

IPlayerFeature::IPlayerFeature(PlayerController** ppPCL):
    m_ppPCL(ppPCL)
{

}

IPlayerFeature::~IPlayerFeature()
{
}

void IPlayerFeature::WorkedFeature(QWidget *parent)
{

}

AboutFeature::AboutFeature(PlayerController **ppPCL):
    IPlayerFeature(ppPCL)
{

}

void AboutFeature::WorkedFeature(QWidget *parent)
{
    QMessageBox::about(parent,QObject::tr("about"),QObject::tr("test123"));
}

OpenFileFeature::OpenFileFeature(PlayerController **ppPCL):
    IPlayerFeature(ppPCL)
  ,m_pMediaPlayer(new QMediaPlayer())
{

}

void OpenFileFeature::WorkedFeature(QWidget *parent)
{
    qDebug()<<"OpenFileFeature:"<<QThread::currentThreadId()<<"\n";
    QString strPath = QFileDialog::getOpenFileName(parent,"open file:",QDir::currentPath(),"*.mp3 *.FLAC");
    m_pMediaPlayer->setMedia(QUrl(strPath));
    m_pMediaPlayer->play();
}
