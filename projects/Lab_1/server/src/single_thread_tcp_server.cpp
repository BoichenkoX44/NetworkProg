#include "single_thread_tcp_server.h"

int AverageNumber(int mas[]);
int MinNumber(int mas[]);
int MaxNumber(int mas[]);

void handle_connection(SOCKET socket, sockaddr_in* addr) {
    char* str_in_addr = inet_ntoa(addr->sin_addr);
    printf("[%s]>>%s\n", str_in_addr, "Establish new connection");

    while (true) {
        char buffer[30] = "";
        int mas[30];
        int rc = recv(socket, buffer, sizeof(buffer), 0);
        if (rc > 0) {
            printf("Received: %s\n", buffer);
            int length = 5;
            int i = 0;
            char *cds = strtok(buffer, " ");

            while (cds) {
                if (i < length) {
                    mas[i++] = atoi(cds);
                }
                cds = strtok(NULL, " ");
            }
            printf("Minimal number: %d\n", MinNumber(mas));
            printf("Maximal number: %d\n", MaxNumber(mas));
            printf("Average number: %d\n", AverageNumber(mas));
        }
        else {
            break;
        }
    }

    close_socket(socket);
    printf("[%s]>>%s", str_in_addr, "Close incomming connection\n");
}

int AverageNumber(int mas[]){
    int sum = 0;
    int avg = 0;
    int length = 5;
    for(int i = 0; i < length; i++){
        sum += mas[i];
    }
    avg = sum / length;
    return avg;
}

int MinNumber(int mas[]){
    int min = mas[0];
    int length = 5;
    for(int i = 0; i < length; i++){
        if(min > mas[i]){
            min = mas[i];
        }
    }
    return min;
}

int MaxNumber(int mas[]){
    int max = mas[0];
    int length = 5;
    for(int i = 0; i < length; i++){
        if(max < mas[i]){
            max = mas[i];
        }
    }
    return max;
}

