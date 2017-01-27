#include "fileio.h"
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QSettings>



FileIO::FileIO(QObject *parent) :
    QObject(parent)
{

}

//[DRIVER_INFO]

//DRIVER_ID=1


//[KPI_BATCH]

//length=30


//[MIN_LENGTH_OF_DATA]

//length=20


//[SERVER_URL]

//serverURL_CSS=http://atr.tech.volvo.com/TSS_ST/IDC/CheckServerServlet
//serverURL_GFMDS=http://atr.tech.volvo.com/TSS_ST/IDC/GetFileModificationDateServlet
//serverURL_GLAMDS=http://atr.tech.volvo.com/TSS_ST/IDC/GetListAndModificationDateServlet
//serverURL_GLOFJS=http://atr.tech.volvo.com/TSS_ST/IDC/GetListOfFilesJSONServlet
//serverURL_GLOFS=http://atr.tech.volvo.com/TSS_ST/IDC/GetListOfFilesServlet
//serverURL_MVFS=http://atr.tech.volvo.com/TSS_ST/IDC/MoveFileServlet
//serverURL_RCV=http://atr.tech.volvo.com/TSS_ST/IDC/ReceiveFileServlet
//serverURL_SUS=http://atr.tech.volvo.com/TSS_ST/IDC/CreateFolderServlet

//[SCORE_PATH]
//PATH = Scores_Test
QString FileIO::loadIP(){
    QString path =QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation)[0] ; //"/storage/emulated/0/AnalyticApp/config.ini";
    QString filename="PATH2016/config.ini";

    qDebug()<<"Pathen: "<<path;
    QSettings settings(path + "/"+ filename,QSettings::IniFormat) ;
    QString thePath = settings.value("REMOTE/IP").toString();
    return thePath;
}

bool FileIO::saveIP(const QString& data){
    QString path =QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation)[0] ; //"/storage/emulated/0/AnalyticApp/config.ini";
    QString filename="PATH2016/config.ini";

    qDebug()<<"Pathen: "<<path;
    QSettings settings(path + "/"+ filename,QSettings::IniFormat) ;
    settings.setValue("REMOTE/IP", data);
    settings.sync();
    return true;
}

bool FileIO::updateConnectionStatus(const QString& data){
    QString path =QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation)[0] ; //"/storage/emulated/0/AnalyticApp/config.ini";
    QString filename="AnalyticApp/connectionFolder/connected.ini";


    QSettings settings(path + "/"+ filename,QSettings::IniFormat) ;
    settings.setValue("CONNECTION_STATUS/CONNECTED", data);
    settings.sync();

    return true;
}

bool FileIO::saveSettings(const QString& data){
    QString path =QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation)[0] ; //"/storage/emulated/0/AnalyticApp/config.ini";
    QString filename="AnalyticApp/configFiles/configHMI.ini";

    qDebug()<<"Pathen: "<<path;
    QSettings settings(path + "/"+ filename,QSettings::IniFormat) ;
    settings.setValue("DRIVER_INFO/DRIVER_ID", data);
    settings.sync();


    return true;
}

QString FileIO::loadPathSettings(){
    QString path =QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation)[0] ; //"/storage/emulated/0/AnalyticApp/config.ini";
    QString filename="AnalyticApp/configFiles/configHMI.ini";

    qDebug()<<"Pathen: "<<path;
    QSettings settings(path + "/"+ filename,QSettings::IniFormat) ;
   // qDebug()<<"settings: "<<QVariant(settings.value("SCORE_PATH/PATH"));
    QString thePath = settings.value("SCORE_PATH/PATH").toString();
    return thePath;
}



QVariant FileIO::getFilelist(QString platform){
    QString path = "driverData";
    if(platform=="ios"){
        path = QStandardPaths::standardLocations(QStandardPaths::CacheLocation).value(0)+"/"+path;
    }
    QDir dir(path);
    QStringList driverDataList;

    foreach(QFileInfo item, dir.entryInfoList() )
    {
        if(item.isFile())
            driverDataList<<item.absoluteFilePath();
    }
   // qDebug()<<"Driverdata: "<<driverDataList;
    return QVariant::fromValue(driverDataList);
}

QVariant FileIO::getFilelistShort(QString platform){
    QString path = "driverData";
    if(platform=="ios"){
        path = QStandardPaths::standardLocations(QStandardPaths::CacheLocation).value(0)+"/"+path;
    }
    QDir dir(path);
    QStringList driverFileList;

    foreach(QFileInfo item, dir.entryInfoList() )
    {
        if(item.isFile())
            driverFileList<<item.fileName();
    }
    return QVariant::fromValue(driverFileList);
}



QString FileIO::read(QString platform)
{
    if(platform=="ios"){
        //mSource=QStandardPaths::standardLocations(QStandardPaths::CacheLocation).value(0)+"/"+mSource;
    }
    if (mSource.isEmpty()){
        emit error("source is empty");
        return QString();
    }

    QFile file(mSource);
    QString fileContent;
    if ( file.open(QIODevice::ReadOnly) ) {
        QString line;
        QTextStream t( &file );
        do {
            line = t.readLine();
            fileContent += line;
         } while (!line.isNull());

        file.close();
    } else {
        emit error("Unable to open the file");
        return QString();
    }
    return fileContent;
}



bool FileIO::write(const QString& data,QString platform)
{
    //http://doc.qt.io/qt-5/qstandardpaths.html
//http://forum.qt.io/topic/45601/solved-ios-8beta-qt-5-3-1-problem-with-writing-data-to-file/2
    //QString path = QStandardPaths::standardLocations(QStandardPaths::DataLocation).value(0);
   // QString path = QStandardPaths::standardLocations(QStandardPaths::CacheLocation).value(0) + "/"+mSource;
   // qDebug()<<"Path: "<<path;

    if(platform=="ios"){
        QString path=QStandardPaths::standardLocations(QStandardPaths::CacheLocation).value(0);
        if (!path.isEmpty() && !path.endsWith("/"))
            path += "/";
        mSource=path+mSource;
    }
    if (mSource.isEmpty())
        return false;
    qDebug()<<mSource;
    QFile file(mSource);
    if (!file.open(QFile::WriteOnly | QFile::Truncate))
        return false;

    QTextStream out(&file);
    out << data;

    file.close();

    return true;
}


