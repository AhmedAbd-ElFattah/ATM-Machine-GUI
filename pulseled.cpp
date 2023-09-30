#include "pulseled.h"
#include <QTextStream>
PulseLed::PulseLed(const QString Arg_DeviceFilePath):DeviceFilePath(Arg_DeviceFilePath)
{

}

void PulseLed::TurnOnLedForPulse(short pulse_time_in_ms)
{
    QString line = QString("%1").arg(pulse_time_in_ms);
    if(!file->open(QIODevice::WriteOnly)) {
        return;
    }

    QTextStream stream(file);

    stream << line;

    file->close();
}

PulseLed::~PulseLed()
{
    if (nullptr != file){
        delete file;
        file = nullptr;
    }
}
