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
        printf("Connection : ID: %d Address: %s\n", conn, inet_ntoa(serverAddr.sin_addr));
    }
}


void receiveData() {
    FILE *fp = fopen("in.in", "w+");
    bool flag = false;
    timeval timeval1;
    timeval1.tv_sec = 1;
    timeval1.tv_usec = 0;
    while (true) {
        int sizeC = connVector.size();
        for (int i = 0; i < sizeC; ++i) {
//            printf("DEBUG SOCKET:\n");
//	    for(int j = 0; j < sizeC; ++j) printf("In stage %d: %d -> %d\n", i, j, connVector[j]);
//	    printf("END\n");
            if (connVector[i] <= 0) continue;
            fd_set fdSet;
            FD_ZERO(&fdSet);
            int maxFd = 0;
            int returnVal = 0;
            FD_SET(connVector[i], &fdSet);
            if (maxFd < connVector[i]) maxFd = connVector[i];
            returnVal = select(maxFd + 1, &fdSet, nullptr, nullptr, &timeval1);
            if (returnVal == -1) printf("Selection Error!\n");
            else if (returnVal == 0) {
                //printf("No Message!\n");
                if (flag) {
                    fprintf(fp, "\nexit\n");
                    fclose(fp);
                    flag = false;
                    system("./code < in.in > out.out");
                    //printf("SYSTEM EXECUTED:INPUT WAITING\n");
                    //int t;
                    //scanf("%d", &t);
                    fp = fopen("in.in", "w+");
                    FILE *out = fopen("out.out", "r+");
                    char bufferB[1024000];
                    //Get Data
                    //fscanf(out, "%s", buffer);
                    int len = 0;
                    fseek(out, 0, SEEK_SET);
                    char ch = fgetc(out);
                    while (ch != EOF) {
                        bufferB[len] = (char) ch;
                        len++;
                        ch = fgetc(out);
                    }
                    bufferB[len] = '\0';
//                    fgets(bufferB, sizeof(bufferB), out);
                    printf("Send Data : [%s]\n", bufferB);
                    int sizeC = connVector.size();
                    for (int i = 0; i < sizeC; ++i)
                        send(connVector[i], bufferB, sizeof(bufferB), 0);
                }
            } else {
                char buffer[1024];
                memset(buffer, 0, sizeof(buffer));
                int length = recv(connVector[i], buffer, sizeof(buffer), 0);
                flag = true;
                printf("Received Data [%s]\n", buffer);
                if (length == 0) {
                    char bufferS[1024];
                    buffer[0] = 'B';
                    buffer[1] = 'Y';
                    buffer[2] = 'E';
                    buffer[3] = '\0';
                    printf("Sending Data : [%s]\n", buffer);
                    int sizeC = connVector.size();
                    for (int i = 0; i < sizeC; ++i)
                        send(connVector[i], buffer, sizeof(buffer), 0);
                    connVector[i] = -1;
                    flag = false;
                }
                fprintf(fp, "%s", buffer);
            }
        }
        sleep(1);
    }
}

void sendMessage() {
    while (true) {
        char buffer[1024];
        //Get Data
        fgets(buffer, sizeof(buffer), stdin);
        printf("Sending Data : [%s]\n", buffer);
        int sizeC = connVector.size();
        for (int i = 0; i < sizeC; ++i)
            send(connVector[i], buffer, sizeof(buffer), 0);
    }
}

void Timer() {
    while (true) {
        globalTimer++;
        sleep(1);
    }
}

int main() {
    s = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr(IPAddr);
    int result = bind(s, (sockaddr *) &serverAddr, sizeof(serverAddr));
    if (result == -1) {
        printf("Bind Error");
        perror("Bind");
        exit(1);
    }
    if (listen(s, 20) == -1) {
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
    while (true) {
        std::string str;
        std::cin >> str;
        if (str == "STOP") break;
    }
    close(s);
    return 0;
}
