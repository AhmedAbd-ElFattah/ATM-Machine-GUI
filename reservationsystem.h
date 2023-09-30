/*
 * File Name --> reservationsystem.h
 * Author	 --> Ahmed Mohamed Abd-Elfattah
 * Version	 --> 1.0.0
 * Brief	 --> Reserve a number and print the number of current client.
 * */

#ifndef RESERVATIONSYSTEM_H
#define RESERVATIONSYSTEM_H
#include "pushbutton.h"
#include "sevensegmentmodule.h"
#include "Configurations.h"

#include <QThread>


class ReservationSystem :  public QThread
{

private:
    short int CurrentClientNumber = 0;
    short int NextClientNumber = 0;

    Pushbutton *Reserve_btn_Obj =nullptr;
    SevenSegmentModule *sevenSegmentModule_Obj = nullptr;
public:
    ReservationSystem();
    void setReservationButtonFilePath(QString Arg_ReservationButtonDeviceFile);
    void setsevenSegmentModuleFilePath(QString Arg_PushButtonDeviceFile);

    void RequestNewClient();
    void run() override;
    ~ReservationSystem();
};

#endif // RESERVATIONSYSTEM_H
