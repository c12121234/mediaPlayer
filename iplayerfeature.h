#ifndef IPLAYERFEATURE_H
#define IPLAYERFEATURE_H
#include <memory>

using std::shared_ptr;
class PlayerController;
class QWidget;
class QMediaPlayer;
class IPlayerFeature
{
public:
    IPlayerFeature(PlayerController** ppPCL);
    virtual ~IPlayerFeature();
    virtual void WorkedFeature(QWidget* parent);
protected:
    PlayerController** m_ppPCL;
};

class AboutFeature : public IPlayerFeature
{
public:
    AboutFeature(PlayerController** ppPCL);
    void WorkedFeature(QWidget* parent) override;
};

class OpenFileFeature : public IPlayerFeature
{
public:
    OpenFileFeature(PlayerController** ppPCL);
    void WorkedFeature(QWidget* parent) override;
private:
    QMediaPlayer* m_pMediaPlayer;
};

#endif // IPLAYERFEATURE_H
