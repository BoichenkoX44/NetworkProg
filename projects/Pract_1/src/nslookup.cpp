#define PLATFORM_WINDOWS

#include <iostream>
#include <string.h>

#ifdef PLATFORM_WINDOWS

#include <winsock2.h>
#include <Windows.h>

#else
#include <arpa/inet.h>
#include <netdb.h>
#endif
using namespace std;

int main(int argc, char *argv[]) {
    char **pptr;
    struct hostent *hptr;
    struct in_addr sin_addr;
#ifdef PLATFORM_WINDOWS

    WSAData ws;
    WSAStartup(MAKEWORD(2, 2), &ws);
#endif
    const int hostNameSize = 256;
    char hostName[hostNameSize];
    if (argc > 1) {
        strcpy(hostName, argv[1]);
    } else {
        cout << "Enter a site name: ";
        cin.getline(hostName, hostNameSize);
    }
    cout << "Scannig IP-adresses of " << hostName << endl;
    hptr = gethostbyname(hostName);
    pptr = hptr->h_addr_list;
    for (; *pptr != NULL; pptr++) {
        memcpy(&sin_addr, *pptr, hptr->h_length);
        cout << inet_ntoa(sin_addr) << endl;
    }
#ifdef PLATFORM_WINDOWS
    WSACleanup();
#endif
    return 0;
}