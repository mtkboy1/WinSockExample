#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

//mymod
#define WINVER 0x0502
#define _WIN32_WINNT 0x0502
#define _WIN32_IE 0x600
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include"MySocket.h"
#define SERVER_PORT "27000"
#pragma comment(lib, "Ws2_32.lib")

int main(int argc,char *argv[]) {
    addrinfo addr,*res;
    ZeroMemory(&addr,sizeof(addr));
    WSAData wsa;
    addr.ai_family = AF_UNSPEC;
    addr.ai_socktype = SOCK_STREAM;
    addr.ai_protocol = IPPROTO_TCP;
    Client cl;
    cl.ip = "127.0.0.1";
    cl.port = "27000";
    cl.phint = addr;
    cl.pres = res;
    cl.wsaData = wsa;
    cl.initWinsock();
    if(cl.createSocket()!=1){
        cl.clientConnect();
    }
    return 0;
}