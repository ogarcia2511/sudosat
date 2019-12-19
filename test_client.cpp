/* all necessary c headers */
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <time.h>
#include <stdlib.h>

/* timing and printing */
#include <iostream>
#include <chrono>

#define PORT 5000 
   
int main(int argc, char *argv[]) 
{
    if(argc < 2)
    {
        std::cout << "wrong number of args!" << std::endl;
        exit(EXIT_FAILURE);
    }


    int sock_fd = 0; 
    int r;

    struct sockaddr_in serv_addr; 

    char *msg = "testing functionality!"; 

    char buffer[1024] = {0}; 

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) 
    { 
        std::cout << "error making socket!" << std::endl; 
        exit(EXIT_FAILURE);
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, (char *)argv[1], &serv_addr.sin_addr)<=0)  
    { 
        std::cout << "address error!" << std::endl; 
        exit(EXIT_FAILURE);
    } 

    auto t_start = std::chrono::system_clock::now();

   
    if (connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        std::cout << "error creating connection!" << std::endl; 
        exit(EXIT_FAILURE);
    } 

    send(sock_fd, msg, strlen(msg), 0);  
    r = read(sock_fd, buffer, 1024); 
    send(sock_fd, msg, strlen(msg), 0); 
    r = read(sock_fd, buffer, 1024);  
    send(sock_fd, msg, strlen(msg), 0); 
    r = read(sock_fd, buffer, 1024); 

    auto t_end = std::chrono::system_clock::now();
    double elapsed_time = std::chrono::duration<double>(t_end - t_start).count();
    
    std::cout << "total time taken: " << elapsed_time << " s" << std::endl;
    
    return 0; 
} 