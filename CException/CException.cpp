//
// Created by Billy on 06/03/2024.
//


#include <iostream>
#include "CException.h"


CException::CException():uiExval{ 1 }, filename{}, line{}, Exmessage{} {}

CException::CException(int id, string message, string file, const int line) : uiExval(id), Exmessage(std::move(message)), filename(std::move(file)), line(line) {}

void CException::CEXModifyMessage(const string& msg) {
    Exmessage = msg;
}

void CException::CEXModifyValue(int uiP) {
    uiExval = uiP;
}

void CException::CEXReadMessage() const {
    cerr << "Exception caught: " << Exmessage << endl
        << "In file: " << filename << endl
        << "On line: " << line << endl;
}

int CException::CEXReadValue()const {
    return uiExval;
}

