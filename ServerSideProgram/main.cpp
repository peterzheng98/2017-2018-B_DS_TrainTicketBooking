#include <sys/types.h>
#include <sys/socket.h>
#include <cstdio>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <fcntl.h>
#include <sys/shm.h>
#include <iostream>
#include <thread>
#include <vector>

#define PORT 10774
#define IPAddr "0.0.0.0"


int s;
sockaddr_in serverAddr;
socklen_t socklen;
std::vector<int> connVector;
int globalTimer = 0;


void Connect(){
    while(true){
        int conn = accept(s, (sockaddr*) &serverAddr, &socklen);
        connVector.push_back(conn);
        printf("Connection : %d\n", conn);
    }
}

void receiveData(){
    FILE *fp;
    bool flag = false;
    timeval timeval1;
    timeval1.tv_sec = 2;
    timeval1.tv_usec = 0;
    while(true){
        int sizeC = connVector.size();
        for(int i = 0; i < sizeC; ++i){
            fd_set fdSet;
            FD_ZERO(&fdSet);
            int maxFd = 0;
            int returnVal = 0;
            FD_SET(connVector[i], &fdSet);
            if(maxFd < connVector[i]) maxFd = connVector[i];
            returnVal = select(maxFd + 1, &fdSet, nullptr, nullptr, &timeval1);
            if(returnVal == -1) printf("Selection Error!\n");
            else if(returnVal == 0) {
                printf("No Message!\n");
                if(flag){
                    fclose(fp);
                    flag = false;
                    system("./code < in.in > out.out");
                    printf("SYSTEM EXECUTED:INPUT WAITING\n");
                    int t;
                    scanf("%d", &t);
                    fp = fopen("in.in", "w+");
                    FILE *out = fopen("out.out", "r+");
                    char buffer[1024];
                    //Get Data
                    fscanf(out, "%s", buffer);
                    printf("Sending Data : [%s]\n", buffer);
                    int sizeC = connVector.size();
                    for(int i = 0; i < sizeC; ++i)
                        send(connVector[i], buffer, sizeof(buffer), 0);
                }
            }
            else {
                char buffer[1024];
                memset(buffer, 0, sizeof(buffer));
                int length = recv(connVector[i], buffer, sizeof(buffer), 0);
                printf("Received Data [%s]\n", buffer);
                fprintf(fp, "%s", buffer);
                flag = true;
            }
        }
        sleep(1);
    }
}

void sendMessage(){
    while(true){
        char buffer[1024];
        //Get Data
        fgets(buffer, sizeof(buffer), stdin);
        printf("Sending Data : [%s]\n", buffer);
        int sizeC = connVector.size();
        for(int i = 0; i < sizeC; ++i)
            send(connVector[i], buffer, sizeof(buffer), 0);
    }
}

void Timer(){ while(true){ globalTimer++;sleep(1); } }

int main(){
    s = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr(IPAddr);
    int result = bind(s, (sockaddr*)&serverAddr, sizeof(serverAddr));
    if(result == -1){
        printf("Bind Error");
        perror("Bind");
        exit(1);
    }
    if(listen(s, 20) == -1){
        printf("Listen Error");
        perror("Listen");
        exit(1);
    }

    socklen = sizeof(serverAddr);

    std::thread connect_thread(Connect), timer_thread(Timer), sendMess_thread(sendMessage), reveive_thread(receiveData);
    connect_thread.detach();
    timer_thread.detach();
    sendMess_thread.detach();
    reveive_thread.detach();
    while(true){

    }
}