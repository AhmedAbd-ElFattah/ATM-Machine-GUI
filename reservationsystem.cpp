#include "reservationsystem.h"
#include <QDebug>

ReservationSystem::ReservationSystem()
{

}

void ReservationSystem::setReservationButtonFilePath(QString Arg_ReservationButtonDeviceFile)
{
    Reserve_btn_Obj = new Pushbutton(Arg_ReservationButtonDeviceFile);
}

void ReservationSystem::setsevenSegmentModuleFilePath(QString Arg_PushButtonDeviceFile)
{
    sevenSegmentModule_Obj = new SevenSegmentModule(Arg_PushButtonDeviceFile);
    sevenSegmentModule_Obj->SetNumber(0, CurrentClientNumber);
    sevenSegmentModule_Obj->SetNumber(1, NextClientNumber);
}


void ReservationSystem::RequestNewClient()
{
    sevenSegmentModule_Obj->SetNumber(0, ++CurrentClientNumber);
}

void ReservationSystem::run()
{
    while(1){
        if (nullptr == Reserve_btn_Obj){
            continue;
        }

        if (nullptr == sevenSegmentModule_Obj){
            continue;
        }
        if (Reserve_btn_Obj->GetPushButtonReading()){
            sevenSegmentModule_Obj->SetNumber(1, ++NextClientNumber);
            QThread::msleep(1000*CONFIG_CONSECUTIVE_TIME_BETWEEN_PRESSED_BUTTONS_IN_SECONDS);
        }
        else{
            /*Tolerance 10%
             * For example, If time is 2 seconds
             * Max time = 2.2 seconds
             */
            QThread::msleep(100*CONFIG_CONSECUTIVE_TIME_BETWEEN_PRESSED_BUTTONS_IN_SECONDS);
        }
    }
}

ReservationSystem::~ReservationSystem(){
    if (nullptr != Reserve_btn_Obj){
        delete Reserve_btn_Obj;
        Reserve_btn_Obj = nullptr;
    }

    if (nullptr != sevenSegmentModule_Obj){
        delete sevenSegmentModule_Obj;
        sevenSegmentModule_Obj = nullptr;
    }
}

