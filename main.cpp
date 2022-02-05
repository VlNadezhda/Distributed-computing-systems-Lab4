#include <cstdio>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <mutex>
#include <thread>
#include <iostream>
#include <string>

#define PORT1 8080
#define PORT2 7999
#define SIZE 50


bool end = false;
std::string syn;

void task1(){
    char vot[SIZE];

    struct sockaddr_in serv_addr1;
    int sock1 = 0;
    if ((sock1 = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        std::cout<<"\n Socket creation error \n";
        exit(1);
    }

    serv_addr1.sin_family = AF_INET;
    serv_addr1.sin_port = htons(PORT1);

    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr1.sin_addr)<=0){
        std::cout <<"\nInvalid address/ Address not supported \n";
    }

    if (connect(sock1, (struct sockaddr *)&serv_addr1, sizeof(serv_addr1)) < 0){
        std::cout <<"\nConnection Failed \n";
        exit(2);
    }

    char buffer[SIZE] = {""};
    while(true){
//        std::cout <<"TASK 1\n";
        std::string str;
        std::cout << "Введите запрос: ";
        std::cin >> str;
        strcpy(buffer,str.c_str());
        buffer[str.size()] = '\0';
        send(sock1 ,buffer , sizeof(buffer) , 0 );
        if(str == "q()"){
            end = true;
            break;
        }
        recv(sock1, vot, sizeof(vot), 0);
        syn+= vot;
        if(!strcmp(vot,"EOF")){
            end = true;
            break;
        }
//        std::cout << "The client received  sync.txt: "<< vot << std::endl;
    }
    close(sock1);
}

void task2(){
    struct sockaddr_in serv_addr2;
    int sock2 = 0;

    if ((sock2 = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        std::cout <<"\n Socket creation error \n";
        exit(1);
    }

    serv_addr2.sin_family = AF_INET;
    serv_addr2.sin_port = htons(PORT2);

    if(inet_pton(AF_INET, "127.0.0.2", &serv_addr2.sin_addr)<=0){
        std::cout <<"\nInvalid address/ Address not supported \n";
    }


    if (connect(sock2, (struct sockaddr *)&serv_addr2, sizeof(serv_addr2)) < 0){
        std::cout <<"\nConnection Failed \n";
    }

    char buffer[SIZE] = {0};

    while(recv(sock2 ,buffer , sizeof buffer,0)>0){
//        std::cout <<"TASK 2\n";
        if(!strcmp(buffer,"EOF") || end)
            break;
        if(syn.find(buffer)){
            syn += '+';
            send(sock2 ,syn.c_str() , sizeof(syn) , 0 );
        }else{
            syn +='-';
            send(sock2 ,syn.c_str() , sizeof(syn) , 0 );
        }
    }
    close(sock2);
}

int main(){
    std::thread th2(task2);
    task1();
    th2.join();

    return 0;
}