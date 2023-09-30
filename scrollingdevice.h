/*
 * File Name --> scrollingdevice.h
 * Author	 --> Ahmed Mohamed Abd-Elfattah
 * Version	 --> 1.0.0
 * Brief	 --> APIs for reading state of scrolling device.
 * */

#ifndef SCROLLINGDEVICE_H
#define SCROLLINGDEVICE_H

#include <QString>
#include <QFile>

enum ScrollType{
    ScrollType_ErrorInReading,
    ScrollType_NoScroll,
    ScrollType_UpScroll,
    ScrollType_DownScroll,
};

class ScrollingDevice
{
private:
    const QString DeviceFilePath;
    QFile *file = new QFile(DeviceFilePath);
public:
    ScrollingDevice(const QString Arg_DeviceFilePath);
    ScrollType GetScrollReading();

    ~ScrollingDevice();
};

#endif // SCROLLINGDEVICE_H
