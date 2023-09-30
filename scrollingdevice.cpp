#include "scrollingdevice.h"


ScrollingDevice::ScrollingDevice(const QString Arg_DeviceFilePath):DeviceFilePath(Arg_DeviceFilePath)
{

}

ScrollType ScrollingDevice::GetScrollReading()
{
    ScrollType state;

    if(!file->open(QIODevice::ReadOnly)) {
        state = ScrollType_ErrorInReading;
        return state;
    }
    char line = file->readLine().at(0);
    switch (line)
    {
    case '0':
        state = ScrollType_NoScroll;
        break;

    case '1':
        state = ScrollType_UpScroll;
        break;

    case '2':
        state = ScrollType_DownScroll;
        break;
    default:
        state = ScrollType_ErrorInReading;
        break;
    }

    file->close();

    return state;
}

ScrollingDevice::~ScrollingDevice()
{
    if (nullptr != file){
        delete file;
        file = nullptr;
    }
}
