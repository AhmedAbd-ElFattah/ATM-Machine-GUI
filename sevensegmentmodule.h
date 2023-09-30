/*
 * File Name --> sevensegmentmodule.h
 * Author	 --> Ahmed Mohamed Abd-Elfattah
 * Version	 --> 1.0.0
 * Brief	 --> APIs for Seven Segment Module Driver.
 * */

#ifndef SEVENSEGMENTMODULE_H
#define SEVENSEGMENTMODULE_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include "Configurations.h"
#include <math.h>

class SevenSegmentModule
{
private:
    // Number of display units in single module
    const short int DisplayUnits=CONFIG_SEVEN_SEGMENT_MODULE_DISPLAY_UNITS;
    /*
     * If unit has 3 digits maximum number can be showed in single display is
     * 10^3-1 = 1000 - 1 = 999
    */
    const short int MaxUnitNumber = pow(10, CONFIG_SEVEN_SEGMENT_MODULE_DIGITS_PER_UNIT) -1;
    const QString DeviceFilePath;
    QFile *file = new QFile(DeviceFilePath) ;
public:
    SevenSegmentModule(const QString Arg_DeviceFilePath);
    void SetNumber(short int Arg_DigitUnit, short int Arg_number);

    ~SevenSegmentModule();
};


#endif // SEVENSEGMENTMODULE_H
