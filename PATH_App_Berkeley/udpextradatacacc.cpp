#include "udpextradatacacc.h"

udpExtraDataCACC::udpExtraDataCACC(QObject *parent) : QObject(parent)
{
    qDebug() << "initSocket - extraDataCACC: 10005";
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::AnyIPv4, 10005);

    setCACCState(0);
    setCACCTargetActive(0);
    setCACCDegraded(0);
    setCACCActiveConnectionToTarget(0);
    setCACCActiveConnectionFromTarget(0);
    setTimeGapActive(0);
    setCACCTimeGap(0);
    setACCTimeGap(0);
    setCACCEvents(0);
    setPlatooningState(0);
    setCounter(0);
    setUdpActive(false);

    connect(udpSocket, SIGNAL(readyRead()),
            this, SLOT(readPendingDatagrams()));
}

void udpExtraDataCACC::readPendingDatagrams()
{
    QByteArray datagram;
       do {
           datagram.resize(udpSocket->pendingDatagramSize());
           udpSocket->readDatagram(datagram.data(), datagram.size());
       } while (udpSocket->hasPendingDatagrams());

    const ExtraDataCACCStruct *rawExtraData = (const ExtraDataCACCStruct*)datagram.constData();

    setCACCState(rawExtraData->CACCState);
    setCACCTargetActive(rawExtraData->CACCTargetActive);
    setCACCDegraded(rawExtraData->CACCDegraded);
    setCACCActiveConnectionToTarget(rawExtraData->CACCActiveConnectionToTarget);
    setCACCActiveConnectionFromTarget(rawExtraData->CACCActiveConnectionFromFollower);
  //  setTimeGapActive(rawExtraData->timeGapActive);
    setCACCTimeGap(rawExtraData->CACCTimeGap);
    setACCTimeGap(rawExtraData->ACCTimeGap);
    setCACCEvents(rawExtraData->CACCEvents);
    setPlatooningState(rawExtraData->platooningState);
    setCounter(rawExtraData->counter);

    if(!udpActive()){
        setUdpActive(true);
    }
    //qDebug()<<"ration: "<<platooningState();

}

