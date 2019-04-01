#include <windows.h>
#include <process.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
//クラス宣言　クラス定義　ヘッダファイル　Ｃのプロトタイプ宣言

class  RS232C
{
private:
  HANDLE h_ComPort;
  std::string ComNumber;
  DCB dcb;
public:
  //HANDLE h_ComPort;
  //std::string ComNumber;
  void test();
  void OpenComPort(std::string ComNumber);
  void PortSet();
  void OutputComand();
};

//クラス実装　ソースファイル
void RS232C::test()
{
  printf("tesuto\n");
}

void RS232C::OpenComPort(std::string ComNumber)
{
  h_ComPort = CreateFile(ComNumber.c_str(),GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
  if (h_ComPort == INVALID_HANDLE_VALUE)
  {
    //printf("COMポートが開けません\n");
    std::cout << ComNumber << "ポートが開けません" << std::endl;
    CloseHandle(h_ComPort);
    return;
  }
  else{
        std::cout << ComNumber << "を開きました" << std::endl;
    //printf("%cを開きました\n",ComNumber);
  }
}


void RS232C::PortSet()
{
//	DCB dcb;
  GetCommState( h_ComPort, &dcb ); // シリアルポートの状態を取得
	dcb.BaudRate = 9600;
	dcb.DCBlength = sizeof(DCB);
	dcb.wReserved = 0;
	dcb.Parity = NOPARITY;
	dcb.fParity = FALSE;
	dcb.ByteSize = 8;
	dcb.StopBits = ONESTOPBIT;
	SetCommState( h_ComPort, &dcb );
 printf("ポート設定\n");
std::cout << "BaudRate:" << dcb.BaudRate << std::endl;
std::cout << "DCBlength:" << dcb.DCBlength << std::endl;
std::cout << "wReserved:" <<dcb.wReserved << std::endl;
int a = dcb.Parity;
std::cout << "Parity:" << a << std::endl;
std::cout << "fParity:" <<dcb.fParity << std::endl;
int b = dcb.ByteSize;
std::cout << "ByteSize:" << b << std::endl;
int c = dcb.StopBits;
std::cout << "StopBits:"  << c << std::endl;
}


void RS232C::OutputComand()
{
  char sBuf[1];
  char str[1000];
  int i=0;
  unsigned long nn;
  while(1) {
  	ReadFile( h_ComPort, sBuf, 1, &nn, 0 );
      if ( nn==1 ) {
        if ( sBuf[0]==10 || sBuf[0]==13 ) {
          if ( i!=0 ) {
  				str[i] = '\0';
  				i=0;
  				printf("%s\n",str);
  				}
  		} else {
        str[i] = sBuf[0];
  			i++;
  			}
  	}
  }

}
