#ifndef UDPSERET_H
#define UDPSERET_H

#include <QObject>
#include <QSettings>
#include <QUdpSocket>
#include <QDebug>

struct StringStruct {
  quint8 type; // 0=nothing 1=truck 2=truck with communication error
  quint8 hasIntruder; //0:false, 1:truck, 2:car, 3:MC (PATH: The graphical indication is the same for all intruders)
  quint8 isBraking; //0:false, 1:braking, 2:hard braking (PATH: same red indication for both 1 & 2)
//  quint8 isTemporaryLeader; //0:false, 1:true
};

struct SeretUdpStruct{
    quint8 platooningState; //0=standby, 1=joining, 2=platooning, 3=leaving, 4=dissolve (PATH: I guess only 0 and 2 is used)
    qint8 position; //-1:nothing (follower with no platoon), 0:leader, >0 Follower (Ego position of vehicle)
    quint8 TBD; //Not used for the moment
    quint8 popup;//0:no popup, 1:Platoon found - join?
    quint32 exitDistance; //value/10.0 km (PATH: Not currently used)
    StringStruct vehicles[3];
};

class UdpSeret : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint16 platooningState READ platooningState WRITE setPlatooningState NOTIFY platooningStateChanged)
    Q_PROPERTY(qint16 position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(quint16 nrOfVehicles READ nrOfVehicles WRITE setNrOfVehicles NOTIFY nrOfVehiclesChanged)
    Q_PROPERTY(quint16 popup READ popup WRITE setPopup NOTIFY popupChanged)
    Q_PROPERTY(quint32 exitDistance READ exitDistance WRITE setExitDistance NOTIFY exitDistanceChanged)
    Q_PROPERTY(QVariantList vehicleArray READ vehicleArray WRITE setVehicleArray NOTIFY vehicleArrayChanged)

public:
    explicit UdpSeret(QObject *parent = 0);



    quint16 platooningState() const
    {
        return m_platooningState;
    }

    qint16 position() const
    {
        return m_position;
    }

    quint16 nrOfVehicles() const
    {
        return m_nrOfVehicles;
    }

    quint16 popup() const
    {
        return m_popup;
    }

    quint32 exitDistance() const
    {
        return m_exitDistance;
    }

    QVariantList vehicleArray() const
    {
        return m_vehicleArray;
    }

signals:



    void platooningStateChanged(quint16 platooningState);

    void positionChanged(qint16 position);

    void nrOfVehiclesChanged(quint16 nrOfVehicles);

    void popupChanged(quint16 popup);

    void exitDistanceChanged(quint32 exitDistance);

    void vehicleArrayChanged(QVariantList vehicleArray);

private:

    SeretUdpStruct m_seretUdpStruct;
    QUdpSocket *udpSocket;



    quint16 m_platooningState;

    qint16 m_position;

    quint16 m_nrOfVehicles;

    quint16 m_popup;

    quint32 m_exitDistance;

    QVariantList m_vehicleArray;

public slots:
    void readPendingDatagrams();
    void sendCommand(QByteArray command,QString hostAdress,quint16 port);
    void fetchUDPdata(QVariantList datan, QVariantList typer, QVariantList ip, quint16 port);

    void setPlatooningState(quint16 platooningState)
    {
        if (m_platooningState == platooningState)
            return;

        m_platooningState = platooningState;
        emit platooningStateChanged(platooningState);
    }
    void setPosition(qint16 position)
    {
        if (m_position == position)
            return;

        m_position = position;
        emit positionChanged(position);
    }
    void setNrOfVehicles(quint16 nrOfVehicles)
    {
        if (m_nrOfVehicles == nrOfVehicles)
            return;

        m_nrOfVehicles = nrOfVehicles;
        emit nrOfVehiclesChanged(nrOfVehicles);
    }
    void setPopup(quint16 popup)
    {
        if (m_popup == popup)
            return;

        m_popup = popup;
        emit popupChanged(popup);
    }
    void setExitDistance(quint32 exitDistance)
    {
        if (m_exitDistance == exitDistance)
            return;

        m_exitDistance = exitDistance;
        emit exitDistanceChanged(exitDistance);
    }
    void setVehicleArray(QVariantList vehicleArray)
    {
        if (m_vehicleArray == vehicleArray)
            return;

        m_vehicleArray = vehicleArray;
        emit vehicleArrayChanged(vehicleArray);
    }
};

#endif // UDPSERET_H
