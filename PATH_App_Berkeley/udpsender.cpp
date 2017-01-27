#include "udpsender.h"

UDPSender::UDPSender(QObject *parent) : QObject(parent)
{
    qDebug() << "initSocket - sender PATH buttons";
    udpSocket = new QUdpSocket(this);
}
void UDPSender::sendCommand(QByteArray datagram,QString hostAdress,quint16 port)
{
    //qDebug()<< "Sending UDP to "<<hostAdress<<", "<<port<<", size: "<<datagram.length();
    QHostAddress host=QHostAddress(hostAdress);
    udpSocket->writeDatagram(datagram, host, port);
}

void UDPSender::fetchUDPdata(QVariantList datan, QVariantList typer,QVariantList ip,quint16 port){
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



