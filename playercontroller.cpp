#include "playercontroller.h"
#include "featurefactory.h"
#include "iplayerfeature.h"
#include <QThread>
#include <QDebug>
#include <QTimer>

PlayerController::PlayerController(QWidget *pmember, QWidget *parent) : QObject(parent)
  ,m_pParent(pmember)
  ,m_bBtnClicked(false)
{
    //SettingFuctionFeature();
    QTimer::singleShot(20,this,&PlayerController::SettingFuctionFeature);
}

PlayerController::~PlayerController()
{
    IPlayerFeature* pAbout = FeatureFactory::CreateFeature("About");
    FeatureFactory::UnregisterFeature("About");
    IPlayerFeature* pOpenFile = FeatureFactory::CreateFeature("OpenFile");
    FeatureFactory::UnregisterFeature("OpenFile");
    delete pAbout;
    delete pOpenFile;
}

void PlayerController::HandleBtnFileOpen()
{
    qDebug()<<"PlayerController:"<<QThread::currentThreadId()<<"\n";
    IPlayerFeature* pF = FeatureFactory::CreateFeature("OpenFile");
    //pF->WorkedFeature(m_pParent);
    emit SendHandleBtnFileOpenSignal(pF);
}

void PlayerController::HandleBtnAboutVersion()
{
    qDebug()<<"PlayerController:"<<QThread::currentThreadId()<<"\n";
    IPlayerFeature* pF = FeatureFactory::CreateFeature("About");    
    //pF->WorkedFeature(m_pParent);
    emit SendHandleBtnAboutVersion(pF);
}

void PlayerController::HandleBtnPause()
{
    qDebug()<<"function name:"<<Q_FUNC_INFO;
    IPlayerFeature* pF = FeatureFactory::CreateFeature("OpenFile");
    OpenFileFeature* pOF = dynamic_cast<OpenFileFeature*>(pF);
    pOF->PlayerPause();
    m_bBtnClicked = true;
}

void PlayerController::HandleBtnStart()
{
    IPlayerFeature* pF = FeatureFactory::CreateFeature("OpenFile");
    OpenFileFeature* pOF = dynamic_cast<OpenFileFeature*>(pF);
    pOF->PlayerStart();
    m_bBtnClicked = false;
}

void PlayerController::HandleBtnStop()
{
    IPlayerFeature* pF = FeatureFactory::CreateFeature("OpenFile");
    OpenFileFeature* pOF = dynamic_cast<OpenFileFeature*>(pF);
    pOF->PlayerStop();
}

void PlayerController::HandleProgressBarClicked(qint64 val)
{
    IPlayerFeature* pF = FeatureFactory::CreateFeature("OpenFile");
    OpenFileFeature* pOF = dynamic_cast<OpenFileFeature*>(pF);
    qint64 dur = pOF->GetPlayerDuration();
    //pOF->PlayerPause();
    pOF->SetPlayerPosition(val*dur/1000); //1000 is slider max value;
}

void PlayerController::HandleProgressBarmoved(qint64 val)
{
    IPlayerFeature* pF = FeatureFactory::CreateFeature("OpenFile");
    OpenFileFeature* pOF = dynamic_cast<OpenFileFeature*>(pF);
    qint64 dur = pOF->GetPlayerDuration();
    pOF->SetPlayerPosition(val*dur/1000); //1000 is slider max value;
}

void PlayerController::HandleProgressBarReleased()
{
    IPlayerFeature* pF = FeatureFactory::CreateFeature("OpenFile");
    OpenFileFeature* pOF = dynamic_cast<OpenFileFeature*>(pF);
    pOF->PlayerStart();
}

void PlayerController::HandleTimerStopFromView()
{
    emit EmitTimerStopSignal();
}

void PlayerController::SettingFuctionFeature()
{
    PlayerController* pSelf = this;
    AboutFeature* pAbout = new AboutFeature(&pSelf);
    FeatureFactory::RegisterFeature("About",pAbout);
    OpenFileFeature* pOpenFile = new OpenFileFeature(&pSelf);
    FeatureFactory::RegisterFeature("OpenFile",pOpenFile);
    qDebug()<<"PlayerController:"<<QThread::currentThreadId()<<"\n";
}

void PlayerController::HandleVolumeChanged(int nVal)
{
    IPlayerFeature* pF = FeatureFactory::CreateFeature("OpenFile");
    OpenFileFeature* pOF = dynamic_cast<OpenFileFeature*>(pF);
    pOF->SetPlayerVolume(nVal);
}
