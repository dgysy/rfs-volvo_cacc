#include "udpvehicle.h"

UDPVehicle::UDPVehicle(QObject *parent) :
    QObject(parent)
{
    qDebug() << "initSocket - Standard data: 9001";
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::AnyIPv4, 9001);

    setSpeed(1);
    setRpm(1);
    setBlink(0);
    setAccIcon(0);
    setAccTarget(1);
    setTargetSpeed(1);
    setTargetSpeedParanthesis(1);
    setGearMode(1);
    setGear(1);
    setGearArrowUp(1);
    setGearArrowDown(1);
    setRetarder(1);
    setRetarderIcon(1);
    setFuelLevel(1);
    setAdBlueLevel(1);
    setEngineTemperature(1);
    setOutSideTemperature(1);
    setFreezeIcon(1);
    setTripDistance2(1);
    setTotalTripDistance(1);
    setLksIcon(1);

    connect(udpSocket, SIGNAL(readyRead()),this, SLOT(readPendingDatagrams()));
}

void UDPVehicle::sendCommand(QByteArray datagram,QString hostAdress,quint16 port)
{
    qDebug()<< "Sending UDP to "<<hostAdress<<", "<<port<<", size: "<<datagram.length();
    QHostAddress host=QHostAddress(hostAdress);
    udpSocket->writeDatagram(datagram, host, port);
}

void UDPVehicle::fetchUDPdata(QVariantList datan, QVariantList typer,QVariantList ip,quint16 port){
   QByteArray temp;
    for(int i=0;i<datan.length();i++){
        if(typer[i]==QString("quint8")){
            QChar convertedValue=datan[i].toChar();
            char hej=convertedValue.toLatin1();
           // qDebug()<<i<<": "<<datan[i]<<": "<<(int)hej;
            temp.append(hej);
        }else if(typer[i]==QString("double")){
            double d=datan[i].toDouble();
            char bArray [ sizeof( double ) ] = { 0 };
            memcpy( bArray , &d , sizeof( double ) );
            int storlek=sizeof(double);
            for(int j=0;j<storlek;j++){
                temp.append(bArray[j]);
            }
        }else if(typer[i]==QString("int")){
            int d=datan[i].toInt();
            char bArray [ sizeof( int ) ] = { 0 };
            memcpy( bArray , &d , sizeof( int ) );
            int storlek=sizeof(int);
            for(int j=0;j<storlek;j++){
                temp.append(bArray[j]);
            }
        }
    }
    for(int i=0;i<ip.length();i++){
        sendCommand(temp,ip[i].toString(),port);
    }
}
void UDPVehicle::triggLinuxSound(QString path){
    QProcess process;
    bool processReslut;
    processReslut = process.startDetached("aplay",QStringList()<<path);
    qDebug()<<"process success: "<<processReslut;
}

void UDPVehicle::readPendingDatagrams()
{
    QByteArray datagram;
       do {
           datagram.resize(udpSocket->pendingDatagramSize());
           udpSocket->readDatagram(datagram.data(), datagram.size());
       } while (udpSocket->hasPendingDatagrams());


    const VehicleStruct *rawVehicleData = (const VehicleStruct*)datagram.constData();

    setSpeed(rawVehicleData->speed);
    setRpm(rawVehicleData->rpm);
    setBlink(rawVehicleData->blink);
    setAccIcon(rawVehicleData->accIcon);
    setAccTarget(rawVehicleData->accTarget);
    setTargetSpeed(rawVehicleData->targetSpeed);
    setTargetSpeedParanthesis(rawVehicleData->targetSpeedParanthesis);
    setGearMode(rawVehicleData->gearMode);
    setGear(rawVehicleData->gear);
    setGearArrowUp(rawVehicleData->gearArrowUp);
    setGearArrowDown(rawVehicleData->gearArrowDown);
    setRetarder(rawVehicleData->retarder);
    setRetarderIcon(rawVehicleData->retarderIcon);
    setFuelLevel(rawVehicleData->fuelLevel);
    setAdBlueLevel(rawVehicleData->adBlueLevel);
    setEngineTemperature(rawVehicleData->engineTemperature);
    setOutSideTemperature(rawVehicleData->outsideTemperature);
    setFreezeIcon(rawVehicleData->freezeIcon);
    setTripDistance2(rawVehicleData->tripDistance2);
    setTotalTripDistance(rawVehicleData->totalTripDistance);
    setLksIcon(rawVehicleData->lksIcon);


    //qDebug() << "ACC: " << m_adBlueLevel;

}
