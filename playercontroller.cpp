#include "playercontroller.h"
#include "featurefactory.h"
#include "iplayerfeature.h"

PlayerController::PlayerController(QWidget *parent) : QObject(parent)
  ,m_pParent(parent)
{
    SettingFuctionFeature();
}

PlayerController::~PlayerController()
{
    IPlayerFeature* pAbout = FeatureFactory::CreateFeature("About");
    FeatureFactory::UnregisterFeature("About");
    delete pAbout;
}

void PlayerController::HandleBtnFileOpen()
{

}

void PlayerController::HandleBtnAboutVersion()
{
    IPlayerFeature* pF = FeatureFactory::CreateFeature("About");
    pF->WorkedFeature(m_pParent);
}

void PlayerController::SettingFuctionFeature()
{
    PlayerController* pSelf = this;
    AboutFeature* pAbout = new AboutFeature(&pSelf);
    FeatureFactory::RegisterFeature("About",pAbout);
}
