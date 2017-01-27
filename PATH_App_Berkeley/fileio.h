#ifndef FILEIO_H
#define FILEIO_H

#include <QObject>
#include <QVariant>


class FileIO : public QObject
{
    Q_OBJECT

public:
    Q_PROPERTY(QString source
               READ source
               WRITE setSource
               NOTIFY sourceChanged)
    explicit FileIO(QObject *parent = 0);

    Q_INVOKABLE QString read(QString platform);
    Q_INVOKABLE bool write(const QString& data,QString platform);
    Q_INVOKABLE QVariant getFilelist(QString platform);
    Q_INVOKABLE QVariant getFilelistShort(QString platform);

    QString source() { return mSource; }

public slots:
    void setSource(const QString& source) { mSource = source; }
    bool saveSettings(const QString& data);
    bool updateConnectionStatus(const QString& data);
    QString loadIP();
    bool saveIP(const QString& data);
    QString loadPathSettings();

signals:
    void sourceChanged(const QString& source);
    void error(const QString& msg);

private:
    QString mSource;
};

#endif // FILEIO_H
