#include "playercontroller.h"
#include "featurefactory.h"
#include "iplayerfeature.h"
#include <QThread>
#include <QDebug>

PlayerController::PlayerController(QWidget *pmember, QWidget *parent) : QObject(parent)
  ,m_pParent(pmember)
{
    SettingFuctionFeature();
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
    pF->WorkedFeature(m_pParent);
}

void PlayerController::HandleBtnAboutVersion()
{
    qDebug()<<"PlayerController:"<<QThread::currentThreadId()<<"\n";
    IPlayerFeature* pF = FeatureFactory::CreateFeature("About");
    pF->WorkedFeature(m_pParent);
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
