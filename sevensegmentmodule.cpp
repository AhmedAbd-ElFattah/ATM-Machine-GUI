#include "sevensegmentmodule.h"
#include <stdexcept>
#include <string>

SevenSegmentModule::SevenSegmentModule(const QString Arg_DeviceFilePath):DeviceFilePath(Arg_DeviceFilePath)
{
    /*Initialize all units with 0*/
    for (short int i = 0; i<DisplayUnits; i++){
        SetNumber(i, 0);
    }
}

void SevenSegmentModule::SetNumber(short int Arg_DigitUnit, short int Arg_number)
{
    if (Arg_DigitUnit > DisplayUnits){
        throw std::string("Maximum number of display units is ")+std::to_string(DisplayUnits);
    }
    if (Arg_number > MaxUnitNumber){
        throw std::string("Maximum number shown in single display unit is ")+std::to_string(MaxUnitNumber);
    }
    if(!file->open(QIODevice::WriteOnly)) {
        return;
    }
    QString line = QString::number(Arg_DigitUnit, 10) + ',' + QString::number(Arg_number, 10) + '\n';
    QTextStream stream(file);
    stream << line;
    file->close();
}

SevenSegmentModule::~SevenSegmentModule()
{
    for (short int i = 0; i<DisplayUnits; i++){
        SetNumber(i, 0);
    }
    if (nullptr != file){
        delete file;
        file = nullptr;
    }
}
