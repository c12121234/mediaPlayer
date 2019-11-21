#ifndef FEATUREFACTORY_H
#define FEATUREFACTORY_H
#include <map>
#include <QString>
#include <memory>

using std::shared_ptr;

class IPlayerFeature;
class FeatureFactory
{
public:
    static void RegisterFeature(const QString& strText,IPlayerFeature* pIplayerFeature);
    static void UnregisterFeature(const QString& strText);
    static IPlayerFeature* CreateFeature(const QString& strText);
private:
    FeatureFactory();
    FeatureFactory(const FeatureFactory& cptr) = delete;
    FeatureFactory& operator=(const FeatureFactory& asop) = delete;
    typedef std::map<QString,IPlayerFeature*> CallBack;
    static CallBack m_CallBackMap;
};

#endif // FEATUREFACTORY_H
