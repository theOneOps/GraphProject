//
// Created by Billy on 19/03/2024.
//


#include <iostream>
#include "CException.h"


CException::CException() :uiExval{ 1 }, filename{}, line{}, Exmessage{} {}

CException::CException(int id, string message, string file, const int line): uiExval(id), Exmessage(move(message)), filename(move(file)), line(line) {}

void CException::EXCModifyMessage(const string& msg) 
{
    // we change the error's message of the exception
    Exmessage = msg;
}

void CException::EXCModifyValue(int uiP) {
    uiExval = uiP;
}

void CException::EXCReadMessage() const {
    cerr << "Exception caught: " << Exmessage << endl
        << "In file: " << filename << endl
        << "On line: " << line << endl;
}

int CException::EXCReadValue()const {
    return uiExval;
}

