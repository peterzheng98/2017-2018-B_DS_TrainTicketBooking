//
// Created by Peter Zheng on 2018/06/14.
//

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <cstdlib>
#include <pthread.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

//#define __DEBUG__
#define ServerAddr "0.0.0.0"
#define ServerPort 10774
#define ServerMaxUser 20

int globalTimer = 0;

enum LogDirection {
    file, stdOUT
};

void *Timer(void *m) {
    pthread_detach(pthread_self());
    while (true) {
        globalTimer++;
        sleep(1);
    }
}

void error(const char *msg) {
    printf("Runtime Error %s{at Runtime %d%s}\n", msg, globalTimer, (globalTimer <= 1 ? " second" : " seconds"));
    perror(msg);
    exit(1);
}

void logSys(const char *msg, LogDirection log) {
    if (log == file) {

    } else {
        printf("Runtime Message %s{at Runtime %d%s}\n", msg, globalTimer, (globalTimer <= 1 ? " second" : " seconds"));
    }
}

void fun(int sock) {
    int result;
    char bufferReceive[1024], bufferSend[1024000];

    //效果等价于memset
    bzero(bufferReceive, 1024);
    bzero(bufferSend, 1024000);
    result = read(sock, bufferReceive, 1023);
    if (result < 0) error("Error : Reading");
    printf("Runtime Message %s [%s]{at Runtime %d%s}\n", "Receive Message:", bufferReceive, globalTimer,
           (globalTimer <= 1 ? " second" : " seconds"));
#ifndef __DEBUG__
    //数据进入后端
    FILE *fin = fopen("in.in", "w+");
    fprintf(fin, "%s\nexit\n", bufferReceive);
    fclose(fin);
    system("./code < in.in > out.out");
    FILE *fout = fopen("out.out", "r+");

    char ch = fgetc(fout);
    int len = 0;
    while (ch != EOF) {
        bufferSend[len] = ch;
        len++;
        ch = fgetc(fout);
    }
    bufferSend[len] = '\0';
    result = write(sock, bufferSend, len);
    if (result < 0) error("Error : Writing");
    printf("Runtime Message %s [%s]{at Runtime %d%s}\n", "Sending Message:", bufferSend, globalTimer,
           (globalTimer <= 1 ? " second" : " seconds"));
#endif
#ifdef __DEBUG__
    result = write(sock, "Received!",9);
    if (result < 0) error("Error : Writing");
    printf("Runtime Message %s [%s]{at Runtime %d%s}\n", "Sending Message:", "Received!", globalTimer,
           (globalTimer <= 1 ? " second" : " seconds"));
#endif
}
pthread_t timer;
int main() {
    int ret = pthread_create(&timer, NULL, Timer, NULL);
    if(ret != 0) error("Error : Timer Thread.");
    int sockfd, newsockfd, pid;
    socklen_t clientTotal;
    sockaddr_in serv_addr, cli_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) error("Error : Opening Socket");
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(ServerPort);
    serv_addr.sin_family = AF_INET;

    int bindResult = bind(sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr));
    if(bindResult < 0) error("Error : Binding");

    listen(sockfd, ServerMaxUser);
    clientTotal = sizeof(cli_addr);
    while(true){
        newsockfd = accept(sockfd, (sockaddr*) &cli_addr, &clientTotal);
        if(newsockfd < 0) error("Error : Accepting");
        pid = fork();
        if(pid < 0) error("Error : Forking");
        else if(pid == 0){
            close(sockfd);
            fun(newsockfd);
            exit(0);
        } else close(newsockfd);
    }
    close(newsockfd);
    return 0;
}