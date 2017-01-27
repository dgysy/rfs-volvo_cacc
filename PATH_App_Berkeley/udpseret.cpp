#include "udpseret.h"

UdpSeret::UdpSeret(QObject *parent) :
    QObject(parent)
{
    qDebug() << "Init UDP socket: PATHAPP - 10007";
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::Any, 10007);

    setPlatooningState(0);
    setPosition(-1);
    setPopup(0);
    setExitDistance(0);
    setVehicleArray({});

    connect(udpSocket, SIGNAL(readyRead()),
            this, SLOT(readPendingDatagrams()));
}

void UdpSeret::readPendingDatagrams()
{
    QByteArray datagram;
       do {
           datagram.resize(udpSocket->pendingDatagramSize());
           udpSocket->readDatagram(datagram.data(), datagram.size());
       } while (udpSocket->hasPendingDatagrams());

    const SeretUdpStruct *rawExtraData = (const SeretUdpStruct*)datagram.constData();

   // qDebug()<<"Rawposition: "<<rawExtraData->position;
    setPlatooningState(rawExtraData->platooningState);
    setPosition(rawExtraData->position);
    setPopup(rawExtraData->popup);
    setExitDistance(rawExtraData->exitDistance);

    const StringStruct *vehicleData = (const StringStruct*)rawExtraData->vehicles;

    QVariantList test={{},{},{}};
    QVariantList sub;
    for(int i=0;i<3;i++){
        sub.append(vehicleData[i].type);
        sub.append(vehicleData[i].hasIntruder);
        sub.append(vehicleData[i].isBraking);
//        sub.append(vehicleData[i].isTemporaryLeader);
        test[i]=sub;
        sub.clear();
    }
    setVehicleArray(test);
   // qDebug()<<position();
    //qDebug() << "Incomming UDP: "<< mode() <<", "<< joiningPlatoonSubMode() <<", "<< leavingPlatoonSubMode();

}

//void UdpSeret::sendCommand(QString command,QString hostAdress,quint16 port)
//{
//    qDebug()<< "Sending UDP: " <<command<<" to "<<hostAdress<<", "<<port;
//    QByteArray datagram = command.toUtf8();
//    QHostAddress host=QHostAddress(hostAdress);
//    udpSocket->writeDatagram(datagram, host, port);
//}

void UdpSeret::sendCommand(QByteArray datagram,QString hostAdress,quint16 port)
{
    //qDebug()<< "Sending UDP to "<<hostAdress<<", "<<port<<", size: "<<datagram.length()<<", what:"<<datagram[0];
    QHostAddress host=QHostAddress(hostAdress);
    udpSocket->writeDatagram(datagram, host, port);
}

void UdpSeret::fetchUDPdata(QVariantList datan, QVariantList typer,QVariantList ip,quint16 port){
   QByteArray temp;

    for(int i=0;i<datan.length();i++){
        if(typer[i]==QString("quint8")){
            QChar convertedValue=datan[i].toChar();
            char hej=convertedValue.toLatin1();
            //qDebug()<<i<<": "<<datan[i]<<": "<<(int)hej;
            temp.append(hej);
        }else if(typer[i]==QString("qint8")){
             qint8 d=datan[i].toInt();
             temp.append(d);
        }else if(typer[i]==QString("double")){
            double d=datan[i].toDouble();
            char bArray [ sizeof( double ) ] = { 0 };
            memcpy( bArray , &d , sizeof( double ) );
            int storlek=sizeof(double);
           // qDebug()<<"Size of double; "<<storlek;
            for(int j=0;j<storlek;j++){
                temp.append(bArray[j]);
            }
            //qDebug()<<datan[i];
        }else if(typer[i]==QString("int")){
            int d=datan[i].toInt();
            char bArray [ sizeof( int ) ] = { 0 };
            memcpy( bArray , &d , sizeof( int ) );
            int storlek=sizeof(int);
           // qDebug()<<"Size of INT; "<<storlek;
            for(int j=0;j<storlek;j++){
                temp.append(bArray[j]);
            }
        }
    }
    for(int i=0;i<ip.length();i++){
        sendCommand(temp,ip[i].toString(),port);
    }
}
