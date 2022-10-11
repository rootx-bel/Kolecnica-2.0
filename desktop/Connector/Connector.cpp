#include <iostream>
#include <sstream>
#include <string>
#include <windows.h>

HANDLE hSerial;

int opencom(char *numport) {
    std::string temp = numport;
    std::string sPortName = "COM" + temp;
    std::wstring stemp = std::wstring(sPortName.begin(), sPortName.end());
    LPCWSTR sn = stemp.c_str();
    hSerial = CreateFile(sn, GENERIC_READ | GENERIC_WRITE,
        0,
        0,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        0);
    if (hSerial == INVALID_HANDLE_VALUE) {
        if (GetLastError() == ERROR_FILE_NOT_FOUND) {
            //serial port not found. Handle error here.
        }
        //any other error. Handle error here.
    }
    DCB dcbSerialParam = { 0 };
    dcbSerialParam.DCBlength = sizeof(dcbSerialParam);

    if (!GetCommState(hSerial, &dcbSerialParam)) {
        //handle error here
    }

    dcbSerialParam.BaudRate = CBR_9600;
    dcbSerialParam.ByteSize = 8;
    dcbSerialParam.StopBits = ONESTOPBIT;
    dcbSerialParam.Parity = NOPARITY;

    if (!SetCommState(hSerial, &dcbSerialParam)) {
        //handle error here
    }
    COMMTIMEOUTS timeout = { 0 };
    timeout.ReadIntervalTimeout = 60;
    timeout.ReadTotalTimeoutConstant = 60;
    timeout.ReadTotalTimeoutMultiplier = 15;
    timeout.WriteTotalTimeoutConstant = 60;
    timeout.WriteTotalTimeoutMultiplier = 8;
    if (!SetCommTimeouts(hSerial, &timeout)) {
        //handle error here
    }
    const int n = 100;
    char sBuff[n + 1] = { 0 };
    DWORD dwRead = 0;
    Sleep(4000);
    if (!ReadFile(hSerial, sBuff, n, &dwRead, NULL)) {
        //handle error here
    }
    std::cout << dwRead;
    return 0;
}

int main(int argc, char* argv[])
{
    std::stringstream convert{ argv[1] };
    int com{};
    if (!(convert >> com)) {
        std::cout << "err\n";
        return 1;
    }
    if (argv[2] != NULL) {
        std::cout << "Run debug \n";
        std::string addrurl = argv[2];
        opencom(argv[1]);
    }
    std::string addrurl = "http://entropy31.ru/";
}