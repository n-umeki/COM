#include <windows.h>
#include <process.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "RS232C.cpp"

int main(void){
  //OpenComPort();
//  opencom.OpenComPort()
  std::string OpenCom = "COM3";
  RS232C COM1;
  COM1.test();
  COM1.OpenComPort(OpenCom);
  COM1.PortSet();
  COM1.OutputComand();
 getchar();
}
