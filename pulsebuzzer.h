/*
 * File Name --> pulsebuzzer.h
 * Author	 --> Ahmed Mohamed Abd-Elfattah
 * Version	 --> 1.0.0
 * Brief	 --> APIs for pulse buzzer Driver.
 * */

#ifndef PULSEBUZZER_H
#define PULSEBUZZER_H

#include <QString>
#include <QFile>

class PulseBuzzer
{
private:
    const QString DeviceFilePath;
    QFile *file = new QFile(DeviceFilePath);
public:
    PulseBuzzer(const QString Arg_DeviceFilePath);
    void TurnOnBuzzerForPulse(short int pulse_time_in_ms);

    ~PulseBuzzer();
};
#endif // PULSEBUZZER_H
