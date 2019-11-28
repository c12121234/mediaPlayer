#include "iplayerfeature.h"
#include "playercontroller.h"
#include <QMessageBox>
#include <QObject>
#include <QWidget>
#include <QString>
#include <QMediaPlayer>
#include <QUrl>
#include <QFileDialog>
#include <QThread>
#include <QDebug>
#include <QTimer>

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

OpenFileFeature::~OpenFileFeature()
{
    delete m_pMediaPlayer;
}

void OpenFileFeature::WorkedFeature(QWidget *parent)
{
    qDebug()<<"OpenFileFeature:"<<QThread::currentThreadId()<<"\n";
    QString strPath = QFileDialog::getOpenFileName(parent,"open file:",QDir::currentPath(),"*.mp3 *.FLAC");
    m_pMediaPlayer->setMedia(QUrl(strPath));
    QTimer* pTimer = new QTimer();
    pTimer->setInterval(500);
    connect(pTimer,&QTimer::timeout,this,&OpenFileFeature::EmitPositionAndDuration);
    connect(*(this->m_ppPCL),&PlayerController::EmitTimerStopSignal,pTimer,&QTimer::stop);
    connect(this,&OpenFileFeature::DurationEndSignal,pTimer,&QTimer::deleteLater);
    m_pMediaPlayer->play();
    pTimer->start();
}

void OpenFileFeature::PlayerPause()
{
    qDebug()<<"function name:"<<Q_FUNC_INFO;
    if(m_pMediaPlayer->state()==QMediaPlayer::PlayingState)
        m_pMediaPlayer->pause();
}

void OpenFileFeature::PlayerStart()
{
    qDebug()<<"function name:"<<Q_FUNC_INFO;
    qDebug()<<QThread::currentThreadId()<<"\n";
    if(m_pMediaPlayer->state()!= QMediaPlayer::PlayingState)
        m_pMediaPlayer->play();
}

void OpenFileFeature::PlayerStop()
{
    qDebug()<<"function name:"<<Q_FUNC_INFO;
    qDebug()<<QThread::currentThreadId()<<"\n";
    if(m_pMediaPlayer->state()== QMediaPlayer::PlayingState)
        m_pMediaPlayer->stop();
}

void OpenFileFeature::SetPlayerVolume(int nVal)
{
    //default 100 = max 0 = min
    m_pMediaPlayer->setVolume(nVal);
}

int OpenFileFeature::GetPlayerVolume()
{
    return m_pMediaPlayer->volume();
}

qint64 OpenFileFeature::GetPlayerPosition()
{
    return m_pMediaPlayer->position();
}

qint64 OpenFileFeature::GetPlayerDuration()
{
    return m_pMediaPlayer->duration();
}

void OpenFileFeature::SetPlayerPosition(qint64 pos)
{
    m_pMediaPlayer->setPosition(pos);
}

void OpenFileFeature::EmitPositionAndDuration()
{
    qint64 pos =m_pMediaPlayer->position();
    qint64 dur = m_pMediaPlayer->duration();
    double dVal = 0.0000;
    if(dur!=0)
    {
        dVal = (double)pos/(double)dur;
        qint64 nVal = dVal*1000; //1000 is silder Max value.
        emit SendPositionDurationSignal(nVal);
    }
    else if(dur == 0 && m_pMediaPlayer->state() == QMediaPlayer::StoppedState)
        emit DurationEndSignal();
}


