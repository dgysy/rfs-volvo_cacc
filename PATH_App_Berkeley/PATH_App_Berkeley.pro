TEMPLATE = app

QT += qml quick multimedia
CONFIG += c++11

SOURCES += main.cpp \
    udpseret.cpp \
    udpextradatacacc.cpp \
    udpsender.cpp \
    fileio.cpp \
    udpvehicle.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = C:\Qt\Qt5.7.1\5.7\android_armv7\qml


# Default rules for deployment.
include(deployment.pri)


HEADERS += \
    udpseret.h \
    udpextradatacacc.h \
    udpsender.h \
    fileio.h \
    udpvehicle.h

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
    Images/PATH/CruiseSetSpeed - background-mi.png

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

