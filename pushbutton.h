/*
 * File Name --> pushbutton.h
 * Author	 --> Ahmed Mohamed Abd-Elfattah
 * Version	 --> 1.0.0
 * Brief	 --> APIs for pushbutton Driver.
 * */
#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <QString>
#include <QFile>

class Pushbutton
{
private:
    const QString DeviceFilePath;
    QFile *file = new QFile(DeviceFilePath);
public:
    Pushbutton(const QString Arg_DeviceFilePath);
    bool GetPushButtonReading();

    ~Pushbutton();
};

#endif // PUSHBUTTON_H
