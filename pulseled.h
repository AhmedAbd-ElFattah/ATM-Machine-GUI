/*
 * File Name --> pulseled.h
 * Author	 --> Ahmed Mohamed Abd-Elfattah
 * Version	 --> 1.0.0
 * Brief	 --> APIs for pulse led Driver.
 * */

#ifndef PULSELED_H
#define PULSELED_H

#include <QString>
#include <QFile>


class PulseLed
{
private:
    const QString DeviceFilePath;
    QFile *file = new QFile(DeviceFilePath);
public:
    PulseLed(const QString Arg_DeviceFilePath);
    void TurnOnLedForPulse(short int pulse_time_in_ms);

    ~PulseLed();
};

#endif // PULSELED_H
