#include <iostream>
#include <string.h>
#include <fstream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>

using namespace std;

int execution(string content, fstream& logFile){
    //cout << content << " function text"<<"\n";
    int socketfd, connectfd; //file descriptors
    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    //checking the socket connection
    if (socketfd == -1 /*|| socketfd == INVA*/) {
        cout << "Failed to create socket...\n";
        logFile << "Client: Failed to create socket...\n";
        exit (0);
    } else {
        cout << "client Socket created successfully..\n";
        logFile << "client: Socket created successfully..\n";
    }


    // 
    sockaddr_in sock;
    bzero(&sock, sizeof(sock));
    sock.sin_family = AF_INET;
    sock.sin_addr.s_addr = inet_addr("127.0.0.1"); //10.0.2.15
    sock.sin_port = htons(8888);

    connectfd = connect(socketfd, (sockaddr*)&sock, sizeof(sock));
    // if connection succeeds, zero is returned. If error, -1 is returned.
    if (connectfd == -1){
            cout << "socket connection failed....\n";
            logFile << "Client: socket connection failed....\n";
            cout << errno << "\n";
    }else{
        cout << "connection established with server...\n";
        logFile << "client : connection established with server...\n";
        int sendRes = send(socketfd, content.c_str(), content.size()+1,0);
        if (sendRes == -1){
            cout << "Client: could not send the content to server....\n";
            logFile << "Client: could not send the content to server....\n";
            logFile << "content : " << content << " \n";
            cout << "content : " << content << " \n";
        } else {
            logFile << "content sent to server... \n";
            cout << "content sent to server... \n";
            logFile << "content : " << content << " \n";
            cout << "content : " << content << " \n";
        }
    }
    close(socketfd);

   // cout << content << "function text"<<"\n";
    return 0;
}

int main()
{

 //   int accountID, amnt, timeStamp;
 //   string type;
    //opening and reading the transaction file
    fstream transactionFile;
    fstream logFile;
    logFile.open("./log file.txt", ios::out);
    transactionFile.open("./Transactions.txt", ios::in);
    if (transactionFile.is_open()){
        string content;
        while (getline(transactionFile, content)){
            cout << content <<"\n";
            execution(content, logFile);
            
        }
        transactionFile.close();
    }
    logFile.close();
    return 0;
}
