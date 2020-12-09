#include "common_utils.h"
using namespace std;
int main(int argc,char* argv[]){
//Буфер повідомлень
    char dataBuffer[BUFFER_SIZE];
    SOCKET clientSocket;
    struct sockaddr_in serverAddr;
    char serverName[BUFFER_SIZE];
    strcpy(serverName,"localhost");
    int nPort = 5150;
    char error[] = "Error";
    getServerPort(argv,argc,"-server",serverName,nPort);
    memset(&serverAddr,0,sizeof(serverAddr));
    if (initSocketAPI()){

        socketError(TRUE,error);
        return -1;
    }
//Створюємо слухаючий сокет
    if ((clientSocket=socket(AF_INET,SOCK_STREAM,
                             IPPROTO_TCP))<=0){
        socketError(TRUE,error);
        return -2;
    }
//Заповнюємо структуру serverAddr
    serverAddr.sin_family = AF_INET;
//Переходимо до мережевого порядку байт
    serverAddr.sin_port = htons(nPort);
//Вказуємо адресу серверу
    struct hostent* hptr;
    hptr = gethostbyname(serverName);
    memcpy(&serverAddr.sin_addr.s_addr,hptr->h_addr_list[0],
           hptr->h_length);
    if (connect(clientSocket,(struct sockaddr*)&serverAddr,
                sizeof(serverAddr))!=0){
        closeSocket(clientSocket);
        socketError(TRUE,error);
        return -2;
    }
    printInfo(argv[0],NULL,FALSE);
    cout<<"Connected to server: "<<serverName;
    cout<<": "<<nPort<<endl;
    do{
        cout<<"Enter message: ";
        memset(dataBuffer,0,BUFFER_SIZE);
        cin.getline(dataBuffer,BUFFER_SIZE);
        char command[BUFFER_SIZE];
        strcpy(command,dataBuffer);
        int nsend=send(clientSocket,dataBuffer,BUFFER_SIZE,0);
        if (nsend<0){
            closeSocket(clientSocket);
            socketError(TRUE,error);
            return -3;
        }
        else {
            int nrec = recv(clientSocket,dataBuffer,nsend,0);
            if (nrec<0){
                closeSocket(clientSocket);
                socketError(TRUE,error);
                return -4;
            }
            else{
                cout<<"Echo from server: "<<dataBuffer<<endl;
            }
        }
    }while (stricmp(dataBuffer,disconnetClientCmd)!=0);
//Закриваємо сокет і звільняємо системні ресурси
    closeSocket(clientSocket);
    deinitSocketAPI();
    return 0;
}