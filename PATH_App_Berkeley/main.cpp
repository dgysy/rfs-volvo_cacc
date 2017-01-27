#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml>
#include "udpseret.h"
#include "udpextradatacacc.h"
#include "udpsender.h"
#include "fileio.h"
#include "udpvehicle.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    UdpSeret * udpSeret = new UdpSeret(&app);
    udpExtraDataCACC * udpXDataCACC = new udpExtraDataCACC(&app);
    UDPSender * udpSender = new UDPSender(&app);
    UDPVehicle * udpVehicle=new UDPVehicle(&app);


    QQmlContext * rc = engine.rootContext();
    rc->setContextProperty("udpSeret", udpSeret);
    rc->setContextProperty("udpXDataCACC", udpXDataCACC);
    rc->setContextProperty("udpSender",udpSender);
    rc->setContextProperty("udpVehicle",udpVehicle);

    qmlRegisterType<FileIO, 1>("FileIO", 1, 0, "FileIO");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

