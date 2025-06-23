#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

//mymod
#define WINVER 0x0502
#define _WIN32_WINNT 0x0502
#define _WIN32_IE 0x600
#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
class Client{
    public:
        PCSTR ip;
        WSADATA wsaData;
        PCSTR port;
        addrinfo phint;
        addrinfo *pres;
        SOCKET client;
        int initWinsock(){
            WSADATA wsaData;
            // Initialize Winsock
            int res = WSAStartup(MAKEWORD(2,2), &wsaData);
            if (res != 0) {
                printf("WSAStartup failed: %d\n", res);
                return 1;
            }
            return 0;
        }
        int createSocket(){
            int iRes = getaddrinfo(ip,port,&phint,&pres);
            if(iRes!=0){
                printf("Error \"createSocket:\"%i",iRes);
                WSACleanup();
                return 1;
            }
            client = socket(pres->ai_family,pres->ai_socktype,pres->ai_protocol);
            if(client == INVALID_SOCKET){
                printf("Error \"createSocket:\"%ln",WSAGetLastError());
                freeaddrinfo(pres);
                WSACleanup();
                return 1;
            }
            return 0;
        }
        int clientConnect(){
            int iRes = connect(client,pres->ai_addr, (int)pres->ai_addrlen);
            if (iRes == SOCKET_ERROR) {
                closesocket(client);
                client = INVALID_SOCKET;
            }
            freeaddrinfo(pres);

            if (client == INVALID_SOCKET) {
                printf("Unable to connect to server!\n");
                WSACleanup();
                return 1;
            }
            return 0;
        }
        int sendData(const char *buf,int len){
            int res = send(client,buf,len,0);
            if(res == SOCKET_ERROR){
                printf("Unable to send buffer to server!\n");
                closesocket(client);
                WSACleanup();
                return 1;
            }
            res = shutdown(client,SD_SEND);
            if(res == SOCKET_ERROR){
                printf("Unable to shutdown output stream!\n");
                closesocket(client);
                WSACleanup();
                return 1;
            }
            return 0;
        }
        int readData(char* b, int len){
            int res = 1;
            do{
                res = recv(client, b, len, 0);
                //printf("%i",res);
            } while(res>0);
        }
    private:
};