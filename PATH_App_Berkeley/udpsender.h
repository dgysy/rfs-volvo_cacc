#ifndef UDPSENDER_H
#define UDPSENDER_H

#include <QObject>
#include <QSettings>
#include <QUdpSocket>
#include <QDebug>

class UDPSender : public QObject
{
    Q_OBJECT
public:
    explicit UDPSender(QObject *parent = 0);

signals:

private:
    QUdpSocket *udpSocket;


public slots:
    void sendCommand(QByteArray datagram,QString hostAdress,quint16 port);
    void fetchUDPdata(QVariantList datan, QVariantList typer, QVariantList ip, quint16 port);
};

#endif // UDPSENDER_H
