#include "pushbutton.h"

Pushbutton::Pushbutton(const QString Arg_DeviceFilePath):DeviceFilePath(Arg_DeviceFilePath)
{

}

bool Pushbutton::GetPushButtonReading()
{
    bool state =false;

    if(!file->open(QIODevice::ReadOnly)) {
        return false;
    }
    char line = file->readLine().at(0);
    switch (line)
    {
    case '0':
        state = false;
        break;
    case '1':
        state = true;
        break;
    default:
        break;
    }

    file->close();

    return state;
}

Pushbutton::~Pushbutton()
{
    if (nullptr != file){
        delete file;
        file = nullptr;
    }
}
