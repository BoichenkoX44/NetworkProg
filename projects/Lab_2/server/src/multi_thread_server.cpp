#include "ping.h"

int AverageNumber(int mas[]);
int MinNumber(int mas[]);
int MaxNumber(int mas[]);

THREAD_VOID handle_connection(void* psocket) {
	CHECK_VOID_IO(psocket, "Empty connection thread data\n");
	SOCKET socket;
	CHECK_VOID_IO((socket = ((SOCKET)psocket)) > 0, "Invalid connection thread data\n");
	sockaddr_in addr;
	socklen_t addr_len = sizeof(addr);
	CHECK_VOID_IO(!getpeername(socket, (sockaddr*)&addr, &addr_len), "Error retrieving peer info\n");
	char* str_in_addr = inet_ntoa(addr.sin_addr);
	printf("[%s:%d]>>%s\n", str_in_addr, ntohs(addr.sin_port), "Establish new connection");

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
	printf("[%s:%d]>>%s\n", str_in_addr, ntohs(addr.sin_port), "Close incoming connection");
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