#include "pulsebuzzer.h"
#include <QTextStream>

PulseBuzzer::PulseBuzzer(const QString Arg_DeviceFilePath):DeviceFilePath(Arg_DeviceFilePath)
{

}

void PulseBuzzer::TurnOnBuzzerForPulse(short pulse_time_in_ms)
{
    QString line = QString("%1").arg(pulse_time_in_ms);
    if(!file->open(QIODevice::WriteOnly)) {
        return;
    }

    QTextStream stream(file);

    stream << line;

    file->close();
}

PulseBuzzer::~PulseBuzzer()
{
    if (nullptr != file){
        delete file;
        file = nullptr;
    }
}
