#ifndef UDPEXTRADATACACC_H
#define UDPEXTRADATACACC_H

#include <QObject>
#include <QSettings>
#include <QUdpSocket>
#include <QDebug>

struct ExtraDataCACCStruct{
    quint8 CACCState; //0:nothing, 1:CACC Enabled, 2:CACC Active, 3: ACC enabled, 4:ACC active
    quint8 CACCTargetActive; //0:false, 1:true (also used for target in ACC)
    quint8 CACCDegraded;//0: false, 1:Overheated brakes (I guess you don't need this one)
    quint8 CACCActiveConnectionToTarget;//0:no connection 1:connection (if this or the next line equals 1 the WIFI icon will appear)
    quint8 CACCActiveConnectionFromFollower;//0:no connection, 1:connection
//    quint8 timeGapActive;//0-1
    quint8 CACCTimeGap;//0-4
    quint8 ACCTimeGap;//0-4
    quint8 CACCEvents;//0:"No popup", 1:"FCW",2:"Brake Capacity",3:"LC Left",4:"LC Right",5:"Obstacle ahead",6:"Connection lost"
    quint8 platooningState;//0:"Platooning",1:"Joining",2:"Leaving",3:"Left",4:"Dissolving",5:"Dissolved" (NOT CURRENTLY USED!)
    quint8 counter;//Counter for dissolving, not implemented for the moment
};

class udpExtraDataCACC : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint16 CACCState READ CACCState WRITE setCACCState NOTIFY CACCStateChanged)
    Q_PROPERTY(quint16 CACCTargetActive READ CACCTargetActive WRITE setCACCTargetActive NOTIFY CACCTargetActiveChanged)
    Q_PROPERTY(quint16 CACCDegraded READ CACCDegraded WRITE setCACCDegraded NOTIFY CACCDegradedChanged)
    Q_PROPERTY(quint16 CACCActiveConnectionToTarget READ CACCActiveConnectionToTarget WRITE setCACCActiveConnectionToTarget NOTIFY CACCActiveConnectionToTargetChanged)
    Q_PROPERTY(quint16 CACCActiveConnectionFromTarget READ CACCActiveConnectionFromTarget WRITE setCACCActiveConnectionFromTarget NOTIFY CACCActiveConnectionFromTargetChanged)
    Q_PROPERTY(quint16 timeGapActive READ timeGapActive WRITE setTimeGapActive NOTIFY timeGapActiveChanged)
    Q_PROPERTY(quint16 CACCTimeGap READ CACCTimeGap WRITE setCACCTimeGap NOTIFY CACCTimeGapChanged)
    Q_PROPERTY(quint16 ACCTimeGap READ ACCTimeGap WRITE setACCTimeGap NOTIFY ACCTimeGapChanged)
    Q_PROPERTY(quint16 CACCEvents READ CACCEvents WRITE setCACCEvents NOTIFY CACCEventsChanged)
    Q_PROPERTY(quint16 platooningState READ platooningState WRITE setPlatooningState NOTIFY platooningStateChanged)
    Q_PROPERTY(quint16 counter READ counter WRITE setCounter NOTIFY counterChanged)

    Q_PROPERTY(bool udpActive READ udpActive WRITE setUdpActive NOTIFY udpActiveChanged)
    quint16 m_CACCState;

    quint16 m_CACCTargetActive;

    quint16 m_CACCDegraded;

    quint16 m_CACCActiveConnectionToTarget;

    quint16 m_CACCActiveConnectionFromTarget;

    quint16 m_platooningState;

    quint16 m_CACCTimeGap;

    quint16 m_ACCTimeGap;

    quint16 m_CACCEvents;

    quint16 m_timeGapActive;

private:
    ExtraDataCACCStruct m_extraDataStruct;
    QUdpSocket *udpSocket;

    bool m_udpActive;

    quint16 m_counter;



public:
    explicit udpExtraDataCACC(QObject *parent = 0);

quint16 CACCState() const
{
    return m_CACCState;
}

quint16 CACCTargetActive() const
{
    return m_CACCTargetActive;
}

quint16 CACCDegraded() const
{
    return m_CACCDegraded;
}

quint16 CACCActiveConnectionToTarget() const
{
    return m_CACCActiveConnectionToTarget;
}

quint16 CACCActiveConnectionFromTarget() const
{
    return m_CACCActiveConnectionFromTarget;
}

quint16 platooningState() const
{
    return m_platooningState;
}

quint16 CACCTimeGap() const
{
    return m_CACCTimeGap;
}

quint16 ACCTimeGap() const
{
    return m_ACCTimeGap;
}

quint16 CACCEvents() const
{
    return m_CACCEvents;
}

bool udpActive() const
{
    return m_udpActive;
}

quint16 counter() const
{
    return m_counter;
}

quint16 timeGapActive() const
{
    return m_timeGapActive;
}

signals:

void CACCStateChanged(quint16 CACCState);

void CACCTargetActiveChanged(quint16 CACCTargetActive);

void CACCDegradedChanged(quint16 CACCDegraded);

void CACCActiveConnectionToTargetChanged(quint16 CACCActiveConnectionToTarget);

void CACCActiveConnectionFromTargetChanged(quint16 CACCActiveConnectionFromTarget);

void platooningStateChanged(quint16 platooningState);

void CACCTimeGapChanged(quint16 CACCTimeGap);

void ACCTimeGapChanged(quint16 ACCTimeGap);

void CACCEventsChanged(quint16 CACCEvents);

void udpActiveChanged(bool udpActive);

void counterChanged(quint16 counter);

void timeGapActiveChanged(quint16 timeGapActive);

public slots:
    void readPendingDatagrams();
void setCACCState(quint16 CACCState)
{
    if (m_CACCState == CACCState)
        return;

    m_CACCState = CACCState;
    emit CACCStateChanged(CACCState);
}
void setCACCTargetActive(quint16 CACCTargetActive)
{
    if (m_CACCTargetActive == CACCTargetActive)
        return;

    m_CACCTargetActive = CACCTargetActive;
    emit CACCTargetActiveChanged(CACCTargetActive);
}
void setCACCDegraded(quint16 CACCDegraded)
{
    if (m_CACCDegraded == CACCDegraded)
        return;

    m_CACCDegraded = CACCDegraded;
    emit CACCDegradedChanged(CACCDegraded);
}
void setCACCActiveConnectionToTarget(quint16 CACCActiveConnectionToTarget)
{
    if (m_CACCActiveConnectionToTarget == CACCActiveConnectionToTarget)
        return;

    m_CACCActiveConnectionToTarget = CACCActiveConnectionToTarget;
    emit CACCActiveConnectionToTargetChanged(CACCActiveConnectionToTarget);
}
void setCACCActiveConnectionFromTarget(quint16 CACCActiveConnectionFromTarget)
{
    if (m_CACCActiveConnectionFromTarget == CACCActiveConnectionFromTarget)
        return;

    m_CACCActiveConnectionFromTarget = CACCActiveConnectionFromTarget;
    emit CACCActiveConnectionFromTargetChanged(CACCActiveConnectionFromTarget);
}
void setPlatooningState(quint16 platooningState)
{
    if (m_platooningState == platooningState)
        return;

    m_platooningState = platooningState;
    emit platooningStateChanged(platooningState);
}
void setCACCTimeGap(quint16 CACCTimeGap)
{
    if (m_CACCTimeGap == CACCTimeGap)
        return;

    m_CACCTimeGap = CACCTimeGap;
    emit CACCTimeGapChanged(CACCTimeGap);
}
void setACCTimeGap(quint16 ACCTimeGap)
{
    if (m_ACCTimeGap == ACCTimeGap)
        return;

    m_ACCTimeGap = ACCTimeGap;
    emit ACCTimeGapChanged(ACCTimeGap);
}
void setCACCEvents(quint16 CACCEvents)
{
    if (m_CACCEvents == CACCEvents)
        return;

    m_CACCEvents = CACCEvents;
    emit CACCEventsChanged(CACCEvents);
}
void setUdpActive(bool udpActive)
{
    if (m_udpActive == udpActive)
        return;

    m_udpActive = udpActive;
    emit udpActiveChanged(udpActive);
}
void setCounter(quint16 counter)
{
    if (m_counter == counter)
        return;

    m_counter = counter;
    emit counterChanged(counter);
}
void setTimeGapActive(quint16 timeGapActive)
{
    if (m_timeGapActive == timeGapActive)
        return;

    m_timeGapActive = timeGapActive;
    emit timeGapActiveChanged(timeGapActive);
}
};

#endif // UDPEXTRADATACACC_H
