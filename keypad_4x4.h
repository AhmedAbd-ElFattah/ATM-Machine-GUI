/*
 * File Name --> keypad_4x4.h
 * Author	 --> Ahmed Mohamed Abd-Elfattah
 * Version	 --> 1.0.0
 * Brief	 --> APIs for reading keypad pressed button.
 * */

#ifndef KEYPAD_4X4_H
#define KEYPAD_4X4_H

#include <string>


class Keypad_4x4
{
private:
    const std::string DeviceFilePath;
    const char key_pad_idx_mapping[4][4] ={
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'},
    };

    const short int Keys_Num=16;

public:
    Keypad_4x4(const std::string Arg_DeviceFilePath);
    char GetActiveKey();

    ~Keypad_4x4();
};

#endif // KEYPAD_4X4_H
