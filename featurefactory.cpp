#include "featurefactory.h"

FeatureFactory::CallBack FeatureFactory::m_CallBackMap;
void FeatureFactory::RegisterFeature(const QString &strText, IPlayerFeature *pIplayerFeature)
{
    m_CallBackMap[strText] = pIplayerFeature;
}

void FeatureFactory::UnregisterFeature(const QString &strText)
{
    if(m_CallBackMap.count(strText) == 1)
    {
        m_CallBackMap.erase(strText);
    }
}

IPlayerFeature *FeatureFactory::CreateFeature(const QString &strText)
{
    return m_CallBackMap.count(strText) !=0 ? m_CallBackMap[strText] : nullptr;
}




