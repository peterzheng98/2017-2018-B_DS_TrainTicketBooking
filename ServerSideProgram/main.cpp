#include <unistd.h>
#include <pthread.h>
#include "Timer.h"
#include "CoreData.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdio>
#include <ctime>
#include "DateAndTime.h"

#define LOGFILE "listen.lyg"
typedef unsigned long long ull;
typedef long long ll;
typedef unsigned short us;
const int Port = 10774;
const int bufferSize = 8192;

pthread_t timer, logger;
Timer globalTime;

void *TimerThread(void *arg) {
    pthread_detach(pthread_self());
    while (1) {
        globalTime++;
        sleep(1);
    }
}

void Write2File(const char *msg,
                const myAlgorithm::Date &date,
                const LogLevel lg,
                const char *model = "",
                char *filePath = LOGFILE,
                ull timer = globalTime.getTime()) {
    FILE *fp = fopen(LOGFILE, "a+");
    struct tm *t;
    time_t tt;
    time(&tt);
    t = localtime(&tt);
    printf("\n", );
    if (lg == Debug) {
#ifdef ___DEBUG_MODE
        fprintf(fp, "[%4d-%02d-%02d %02d:%02d:%02d Run:%lld second(s)]:D/%s : %s\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min,
           t->tm_sec, timer, model, msg);
        fclose(fp);
        return;
#endif
    }
    if (lg == Warning) {
        fprintf(fp, "[%4d-%02d-%02d %02d:%02d:%02d Run:%lld second%s]:W/%s : %s\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min,
                t->tm_sec, timer, (timer > 1 ? "s" : "") , model, msg);
        fclose(fp);
        return;
    }
    if (lg == Error) {
        fprintf(fp, "[%4d-%02d-%02d %02d:%02d:%02d Run:%lld second%s]:E/%s : %s\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min,
                t->tm_sec, timer, (timer > 1 ? "s" : "") , model, msg);
        fclose(fp);
        return;
    }
    if (lg == Information) {
        fprintf(fp, "[%4d-%02d-%02d %02d:%02d:%02d Run:%lld second%s]:I/%s : %s\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min,
                t->tm_sec, timer, (timer > 1 ? "s" : "") , model, msg);
        fclose(fp);
        return;
    }
    if (lg == Verbose) {
        fprintf(fp, "[%4d-%02d-%02d %02d:%02d:%02d Run:%lld second%s]:V/%s : %s\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min,
                t->tm_sec, timer, (timer > 1 ? "s" : "") , model, msg);
        fclose(fp);
        return;
    }
    fclose(fp);
}

void error(char *msg) {
    perror(msg);
    Write2File(msg, myAlgorithm::Date(2018, 6, 1), Error);
}

void dostuff(int sock) {
    int n;
    char buffer[bufferSize];

    bzero(buffer, bufferSize);
    n = read(sock, buffer, bufferSize - 1);
    if (n < 0) error("ERROR reading from socket");
    printf("Here is the message: %s\n", buffer);
    n = write(sock, "I got your message", 18);
    if (n < 0) error("ERROR writing to socket");
}

int main() {
    int err = pthread_create(&timer, nullptr, TimerThread, nullptr);
    if (err != 0) {} // TODO : Thread Create Failed.
    int sockfd, newsockfd, clientlen, n;
    char buffer[256];
    sockaddr_in serv_addr, client_addr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        //TODO : Error Opening Socket.
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(Port);
    if (bind(sockfd, (sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR on binding");
    listen(sockfd, 5);
    clientlen = sizeof(client_addr);
    while (true) {
        newsockfd = accept(sockfd, (sockaddr *) &client_addr, (socklen_t *) &clientlen);
        if (newsockfd < 0)
            error("ERROR on accept");
        int pid = fork();
        if (pid < 0) error("ERROR on Fork");
        if (pid == 0) {
            close(sockfd);
            dostuff(newsockfd);
            exit(0);
        } else close(newsockfd);
    }
    close(sockfd);
    return 0;
}

