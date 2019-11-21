#include "iplayerfeature.h"
#include <QMessageBox>
#include <QObject>
#include <QWidget>
#include <QString>

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
