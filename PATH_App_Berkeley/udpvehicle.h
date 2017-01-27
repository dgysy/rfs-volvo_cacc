#ifndef UDPVEHICLE_H
#define UDPVEHICLE_H

#include <QObject>
#include <QSettings>
#include <QUdpSocket>
#include <QDebug>
#include <QtEndian>
#include <QProcess>

struct VehicleStruct{
    qreal speed;
    quint32 rpm;
    quint8 blink;
    quint8 accIcon;
    quint8 accTarget;
    quint8 targetSpeed;
    quint8 targetSpeedParanthesis;
    quint8 gearMode;
    quint8 gear;
    quint8 gearArrowUp;
    quint8 gearArrowDown;
    quint8 retarder;
    quint8 retarderIcon;
    quint8 fuelLevel;
    quint8 adBlueLevel;
    quint8 engineTemperature;
    quint8 outsideTemperature;
    quint8 freezeIcon;
    quint32 tripDistance2;
    quint32 totalTripDistance;
    quint8 lksIcon;
};


class UDPVehicle : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal speed READ speed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(quint32 rpm READ rpm WRITE setRpm NOTIFY rpmChanged)
    Q_PROPERTY(quint16 blink READ blink WRITE setBlink NOTIFY blinkChanged)
    Q_PROPERTY(quint16 accIcon READ accIcon WRITE setAccIcon NOTIFY accIconChanged)
    Q_PROPERTY(quint16 accTarget READ accTarget WRITE setAccTarget NOTIFY accTargetChanged)
    Q_PROPERTY(quint16 targetSpeed READ targetSpeed WRITE setTargetSpeed NOTIFY targetSpeedChanged)
    Q_PROPERTY(quint16 targetSpeedParanthesis READ targetSpeedParanthesis WRITE setTargetSpeedParanthesis NOTIFY targetSpeedParanthesisChanged)
    Q_PROPERTY(quint16 gearMode READ gearMode WRITE setGearMode NOTIFY gearModeChanged)
    Q_PROPERTY(quint16 gear READ gear WRITE setGear NOTIFY gearChanged)
    Q_PROPERTY(quint16 gearArrowUp READ gearArrowUp WRITE setGearArrowUp NOTIFY gearArrowUpChanged)
    Q_PROPERTY(quint16 gearArrowDown READ gearArrowDown WRITE setGearArrowDown NOTIFY gearArrowDownChanged)
    Q_PROPERTY(quint16 retarder READ retarder WRITE setRetarder NOTIFY retarderChanged)
    Q_PROPERTY(quint16 retarderIcon READ retarderIcon WRITE setRetarderIcon NOTIFY retarderIconChanged)
    Q_PROPERTY(quint16 fuelLevel READ fuelLevel WRITE setFuelLevel NOTIFY fuelLevelChanged)
    Q_PROPERTY(quint16 adBlueLevel READ adBlueLevel WRITE setAdBlueLevel NOTIFY adBlueLevelChanged)
    Q_PROPERTY(quint16 engineTemperature READ engineTemperature WRITE setEngineTemperature NOTIFY engineTemperatureChanged)
    Q_PROPERTY(quint16 outSideTemperature READ outSideTemperature WRITE setOutSideTemperature NOTIFY outSideTemperatureChanged)
    Q_PROPERTY(quint16 freezeIcon READ freezeIcon WRITE setFreezeIcon NOTIFY freezeIconChanged)
    Q_PROPERTY(quint32 tripDistance2 READ tripDistance2 WRITE setTripDistance2 NOTIFY tripDistance2Changed)
    Q_PROPERTY(quint32 totalTripDistance READ totalTripDistance WRITE setTotalTripDistance NOTIFY totalTripDistanceChanged)
    Q_PROPERTY(quint16 lksIcon READ lksIcon WRITE setLksIcon NOTIFY lksIconChanged)

public:
    explicit UDPVehicle(QObject *parent = 0);

    qreal speed() const
    {
        return m_speed;
    }

    quint32 rpm() const
    {
        return m_rpm;
    }

    quint16 blink() const
    {
        return m_blink;
    }

    quint16 accIcon() const
    {
        return m_accIcon;
    }

    quint16 accTarget() const
    {
        return m_accTarget;
    }


    quint16 gearMode() const
    {
        return m_gearMode;
    }

    quint16 gear() const
    {
        return m_gear;
    }

    quint16 gearArrowUp() const
    {
        return m_gearArrowUp;
    }

    quint16 gearArrowDown() const
    {
        return m_gearArrowDown;
    }

    quint16 retarder() const
    {
        return m_retarder;
    }

    quint16 retarderIcon() const
    {
        return m_retarderIcon;
    }

    quint16 adBlueLevel() const
    {
        return m_adBlueLevel;
    }

    quint16 engineTemperature() const
    {
        return m_engineTemperature;
    }

    quint16 outSideTemperature() const
    {
        return m_outSideTemperature;
    }

    quint16 freezeIcon() const
    {
        return m_freezeIcon;
    }

    quint32 tripDistance2() const
    {
        return m_tripDistance2;
    }

    quint32 totalTripDistance() const
    {
        return m_totalTripDistance;
    }

    quint16 lksIcon() const
    {
        return m_lksIcon;
    }

    quint16 fuelLevel() const
    {
        return m_fuelLevel;
    }

    quint16 targetSpeed() const
    {
        return m_targetSpeed;
    }

    quint16 targetSpeedParanthesis() const
    {
        return m_targetSpeedParanthesis;
    }

signals:
    void speedChanged(qreal arg);
    void rpmChanged(quint32 arg);
    void blinkChanged(quint16 arg);
    void accIconChanged(quint16 arg);
    void accTargetChanged(quint16 arg);
    void gearModeChanged(quint16 arg);
    void gearChanged(quint16 arg);
    void gearArrowUpChanged(quint16 arg);
    void gearArrowDownChanged(quint16 arg);
    void retarderChanged(quint16 arg);
    void retarderIconChanged(quint16 arg);
    void adBlueLevelChanged(quint16 arg);
    void engineTemperatureChanged(quint16 arg);
    void outSideTemperatureChanged(quint16 arg);
    void freezeIconChanged(quint16 arg);
    void tripDistance2Changed(quint32 arg);
    void totalTripDistanceChanged(quint32 arg);
    void lksIconChanged(quint16 arg);
    void fuelLevelChanged(quint16 arg);
    void targetSpeedChanged(quint16 arg);
    void targetSpeedParanthesisChanged(quint16 arg);

private:
    VehicleStruct m_vehicleStruct;
    QUdpSocket *udpSocket;

    qreal m_speed;
    quint32 m_rpm;
    quint16 m_blink;
    quint16 m_accIcon;
    quint16 m_accTarget;
    quint16 m_gearMode;
    quint16 m_gear;
    quint16 m_gearArrowUp;
    quint16 m_gearArrowDown;
    quint16 m_retarder;
    quint16 m_retarderIcon;
    quint16 m_adBlueLevel;
    quint16 m_engineTemperature;
    quint16 m_outSideTemperature;
    quint16 m_freezeIcon;
    quint32 m_tripDistance2;
    quint32 m_totalTripDistance;
    quint16 m_lksIcon;
    quint16 m_fuelLevel;
    quint16 m_targetSpeed;
    quint16 m_targetSpeedParanthesis;

public slots:
    void readPendingDatagrams();
    void sendCommand(QByteArray datagram,QString hostAdress,quint16 port);
    void fetchUDPdata(QVariantList datan, QVariantList typer, QVariantList ip, quint16 port);
    void triggLinuxSound(QString path);

    void setSpeed(qreal arg)
    {
        if (m_speed != arg) {
            m_speed = arg;
            emit speedChanged(arg);
        }
    }
    void setRpm(quint32 arg)
    {
        if (m_rpm != arg) {
            m_rpm = arg;
            emit rpmChanged(arg);
        }
    }
    void setBlink(quint16 arg)
    {
        if (m_blink != arg) {
            m_blink = arg;
            emit blinkChanged(arg);
        }
    }
    void setAccIcon(quint16 arg)
    {
        if (m_accIcon != arg) {
            m_accIcon = arg;
            emit accIconChanged(arg);
        }
    }
    void setAccTarget(quint16 arg)
    {
        if (m_accTarget != arg) {
            m_accTarget = arg;
            emit accTargetChanged(arg);
        }
    }

    void setGearMode(quint16 arg)
    {
        if (m_gearMode != arg) {
            m_gearMode = arg;
            emit gearModeChanged(arg);
        }
    }
    void setGear(quint16 arg)
    {
        if (m_gear != arg) {
            m_gear = arg;
            emit gearChanged(arg);
        }
    }
    void setGearArrowUp(quint16 arg)
    {
        if (m_gearArrowUp != arg) {
            m_gearArrowUp = arg;
            emit gearArrowUpChanged(arg);
        }
    }
    void setGearArrowDown(quint16 arg)
    {
        if (m_gearArrowDown != arg) {
            m_gearArrowDown = arg;
            emit gearArrowDownChanged(arg);
        }
    }
    void setRetarder(quint16 arg)
    {
        if (m_retarder != arg) {
            m_retarder = arg;
            emit retarderChanged(arg);
        }
    }
    void setRetarderIcon(quint16 arg)
    {
        if (m_retarderIcon != arg) {
            m_retarderIcon = arg;
            emit retarderIconChanged(arg);
        }
    }
    void setAdBlueLevel(quint16 arg)
    {
        if (m_adBlueLevel != arg) {
            m_adBlueLevel = arg;
            emit adBlueLevelChanged(arg);
        }
    }
    void setEngineTemperature(quint16 arg)
    {
        if (m_engineTemperature != arg) {
            m_engineTemperature = arg;
            emit engineTemperatureChanged(arg);
        }
    }
    void setOutSideTemperature(quint16 arg)
    {
        if (m_outSideTemperature != arg) {
            m_outSideTemperature = arg;
            emit outSideTemperatureChanged(arg);
        }
    }
    void setFreezeIcon(quint16 arg)
    {
        if (m_freezeIcon != arg) {
            m_freezeIcon = arg;
            emit freezeIconChanged(arg);
        }
    }
    void setTripDistance2(quint32 arg)
    {
        if (m_tripDistance2 != arg) {
            m_tripDistance2 = arg;
            emit tripDistance2Changed(arg);
        }
    }
    void setTotalTripDistance(quint32 arg)
    {
        if (m_totalTripDistance != arg) {
            m_totalTripDistance = arg;
            emit totalTripDistanceChanged(arg);
        }
    }
    void setLksIcon(quint16 arg)
    {
        if (m_lksIcon != arg) {
            m_lksIcon = arg;
            emit lksIconChanged(arg);
        }
    }
    void setFuelLevel(quint16 arg)
    {
        if (m_fuelLevel != arg) {
            m_fuelLevel = arg;
            emit fuelLevelChanged(arg);
        }
    }
    void setTargetSpeed(quint16 arg)
    {
        if (m_targetSpeed != arg) {
            m_targetSpeed = arg;
            emit targetSpeedChanged(arg);
        }
    }
    void setTargetSpeedParanthesis(quint16 arg)
    {
        if (m_targetSpeedParanthesis != arg) {
            m_targetSpeedParanthesis = arg;
            emit targetSpeedParanthesisChanged(arg);
        }
    }
};

#endif // UDPVEHICLE_H
