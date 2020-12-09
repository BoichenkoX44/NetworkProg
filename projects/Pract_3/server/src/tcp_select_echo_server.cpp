#include "common_utils.h"
#include <vector>
using namespace std;
int main(int argc,char* argv[]) {
    SOCKET listenSocket;
    sockaddr_in serverAddr, clientAddr;
    int nPort = 5150, ret;
    vector<SOCKET> sockList;

    char error[] = "Error";
    int clientAddrLen;

    char strPort[6];
//Отримуємо порт серверу з командного рядка
    if (getParameter(argv, argc, "-port", strPort, ':')) {
        int tempPort = atoi(strPort);
        if (tempPort > 0)
            nPort = tempPort;
        else {
            cout << "\nError command argument " << argv[0] << "";
            cout << "-port:<integer value>\n";
            cout << "\nUsage " << argv[0] << " -port:<integer value>\n";
        }
    }
    fd_set rfds, afds;
    if (initSocketAPI()) {
        return socketError(TRUE, error);
    }
    listenSocket = socket(AF_INET, SOCK_STREAM,IPPROTO_TCP);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(nPort);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
//Зв’язуємо сокет з адресою серверу
    if (bind(listenSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr) < 0)) {
        closeSocket(listenSocket);
        return socketError(TRUE, error, TRUE);
    };
//Переводимо сокет у режим очікування з’єднань
    listen(listenSocket, LINEQ);
//Додаємо сокет серверу до множини сокетів
    FD_ZERO(&afds);
    FD_SET(listenSocket, &afds);
    sockList.push_back(listenSocket);
    printInfo(argv[0]);
    cout << "Waiting connections in port " << nPort;
//Нескінченний цикл очікування
    while (1) {

        unsigned int fdndx;
        memcpy(&rfds, &afds, sizeof(rfds));
        if (select(FD_SETSIZE, &rfds, (fd_set *) 0,
                   (fd_set *) 0, NULL) < 0) {
            socketError(TRUE, error);
            continue;
        }
        if (FD_ISSET(listenSocket, &rfds)) {
            SOCKET ssock;
            ssock = accept(listenSocket, (struct sockaddr *) &clientAddr, (&clientAddrLen));
            cout << "\nConnected client: ";
            cout << inet_ntoa(clientAddr.sin_addr) << ": ";
            cout << ntohs(clientAddr.sin_port);
            FD_SET(ssock, &afds);
            sockList.push_back(ssock);
            continue;
        }
        for (fdndx = 0; fdndx < sockList.size(); ++fdndx) {
            {
                SOCKET fd = sockList[fdndx];
                if (fd != listenSocket && FD_ISSET(fd, &rfds)) {
                    getpeername(fd, (struct sockaddr *) &clientAddr, (&clientAddrLen));
                    char buf[BUFFER_SIZE];
                    memset(buf, 0, BUFFER_SIZE);
                    ret = readLine(fd, buf);
                    if (ret < 0 ||
                        stricmp(buf, disconnetClientCmd) == 0) {
                        closeSocket(fd);
                        FD_CLR(fd, &afds);
                        sockList.erase(sockList.begin() + fdndx);
                        cout << "\nClient " << inet_ntoa(clientAddr.sin_addr);
                        cout << ntohs(clientAddr.sin_port) << " disconnect\n";
                    } else {
                        if (ret == 0)
                            continue;
                        ret = send(fd, buf, ret, 0);
                        cout << "\nReflected " << ret << " bytes from ";
                        cout << inet_ntoa(clientAddr.sin_addr) << ":";
                        cout << ntohs(clientAddr.sin_port);
                    }
                }
            }//for
        }//while
        deinitSocketAPI();
        return 0;
    }
}