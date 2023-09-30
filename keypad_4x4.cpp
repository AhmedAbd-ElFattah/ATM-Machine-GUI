#include "keypad_4x4.h"
#include <fstream>

Keypad_4x4::Keypad_4x4(const std::string Arg_DeviceFilePath):DeviceFilePath(Arg_DeviceFilePath)
{

}

char Keypad_4x4:: GetActiveKey()
{

    char ActiveKey = 'Z';
    std::string line;

    std::ifstream file(DeviceFilePath);


    if (!file.is_open()) {

        return ActiveKey;
    }
    /*Note: Reading is flatten array*/
    std::getline(file, line);

    for (short int i = 0; i<Keys_Num ; i++){
        if ('1'==line.at(i)){
            ActiveKey = key_pad_idx_mapping[i/4][i%4];
            break;
        }
    }


    file.close();

    return ActiveKey;
}

Keypad_4x4::~Keypad_4x4()
{
}
