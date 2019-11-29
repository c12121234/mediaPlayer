#ifndef IPLAYERFEATURE_H
#define IPLAYERFEATURE_H
#include <QtGlobal>
#include <QObject>
#include <memory>
#include <QMediaPlayer>

using std::shared_ptr;
class PlayerController;
class QWidget;
class IPlayerFeature :public QObject
{
    Q_OBJECT
public:
    IPlayerFeature(PlayerController** ppPCL);
    virtual ~IPlayerFeature();
    virtual void WorkedFeature(QWidget* parent);
protected:
    PlayerController** m_ppPCL;
};

class AboutFeature : public IPlayerFeature
{
    Q_OBJECT
public:
    AboutFeature(PlayerController** ppPCL);
    void WorkedFeature(QWidget* parent) override;
};

class OpenFileFeature : public IPlayerFeature
{
    Q_OBJECT
public:
    OpenFileFeature(PlayerController** ppPCL);
    ~OpenFileFeature();
    void WorkedFeature(QWidget* parent) override;
    void PlayerPause();
    void PlayerStart();
    void PlayerStop();
    void SetPlayerVolume(int nVal);
    int GetPlayerVolume();
    qint64 GetPlayerPosition();
    qint64 GetPlayerDuration();
    void SetPlayerPosition(qint64 pos);
    QMediaPlayer::State GetPlayerState();

public slots:
    void EmitPositionAndDuration();
signals:
    void DurationEndSignal();
    void SendPositionDurationSignal(qint64 posdur);

private:
    QMediaPlayer* m_pMediaPlayer;
};

#endif // IPLAYERFEATURE_H
