#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>
#include <pthread.h>

using namespace std;

#define maxSizeMess 4096
#define maxFileMess 1024000
#define SERVERPORT 10774
#define SERVERADDR "0.0.0.0"
#define MAXSOCKSTHREAD 20
class TCPServer {
public:
    int sockfd, newsockfd, n, pid;
    sockaddr_in serverAddr;
    sockaddr_in clientAddr;
    pthread_t serverThread;
    char msg[maxSizeMess];
    static string Message;

    TCPServer(){
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        memset(&serverAddr, 0, sizeof(serverAddr));
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(SERVERPORT);
        serverAddr.sin_addr.s_addr = inet_addr(SERVERADDR);
        bind(sockfd, (sockaddr*) &serverAddr, sizeof(serverAddr));
        listen(sockfd, MAXSOCKSTHREAD);
    }

    string receive(){
        string ret;
        while(true){
            socklen_t size = sizeof(clientAddr);
            newsockfd = accept(sockfd, (sockaddr*) &clientAddr, &size);
            ret = inet_ntoa(clientAddr.sin_addr);
            pthread_create(&serverThread, NULL,&ThreadWork, (void*)newsockfd);
        }
        return ret;
    }

    string receMess(){
        return Message;
    }

    void sendMess(const string &msg){
        send(newsockfd, msg.c_str(), msg.length(), 0);
    }

    void stop(){
        close(sockfd);
        close(newsockfd);
    }

    void clean(){
        Message = "";
        memset(msg, 0, maxSizeMess);
    }

private:
    static void* ThreadWork(void* ret);
};

void* TCPServer::ThreadWork(void* ret) {

}
string TCPServer::Message;

TCPServer server;

void* mainServer(void* mask){
    pthread_detach(pthread_self());
    while(true){
        string ret = server.receMess();
        if(ret != ""){
            cout << "Message Received:\n==============================================================================\n";
            cout << ret << "=============================================================================="
                           << endl;
            server.sendMess("Receive Message :[" + ret + "]");
            server.clean();
        }
        usleep(1000);
    }
    server.stop();
}

int main(){
    pthread_t dat;
    int code = pthread_create(&dat, nullptr, mainServer, nullptr);
    if(code == 0) server.receive();
    return 0;
}