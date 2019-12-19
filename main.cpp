/*
 * filename:            sudosat.cpp
 *
 * author:              Omar Garcia
 *
 * description:         Describe what this code does
 *
 * NOTE:                
 * All comments that I make will follow the word "NOTE",
 * so you can cycle through these to get all my comments.
 *
 * This is a good start! We should set this up with its own
 * directory structure. Here is what I have in mind.
 *
 *  SudoSat
 *      --> README.md
 *      --> Makefile
 *          - easier to build and run
 *          - ideally should be able to do:
 *              - make clean
 *              - make
 *      --> lib
 *          - all APIs and libraries we use, but do not develop
 *      --> src
 *          - all source code 
 *      --> build
 *          - all files generated during compilation should go
 *          here
 *      --> config
 *          - future configurations can go in here
 */

/*
 * NOTE: 
 * 
 * Overall, I like this start of the code. This will definitely be
 * the basis for the communication we will be doing. When you are back 
 * in the office we can discuss more about the architecture
 * and modularization of the code.
 *
 * Great Work,
 * - ASA
 */

/* networking-related c headers */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>

/* cpp headers */
#include <cstdlib>
#include <string>
#include <iostream>
#include <chrono> 
#include <thread>

// NOTE: OK as an application-level user, but not advised
// for data structures.
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::thread;
using namespace std::chrono;

int main(int argc, char *argv[])
{
    int socket_fd, conn_fd;
    int bind_s, listen_s;
    struct sockaddr_in serv_addr;
    char net_buff;

    if(argc < 2) 
    {
        cout << "port number not specified!" << endl;
        exit(EXIT_FAILURE);
        // NOTE: in this case, you can also do: exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    // NOTE: Errors should terminate
    // Potentially could check with a try ... catch statement
    if(socket_fd < 0) cout << "error creating socket" << endl;

    bind_s = bind(socket_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    if(bind_s < 0) cout << "error binding socket" << endl;

    listen_s = listen(socket_fd, 1);
    if(listen_s < 0) cout << "error listening on port" << endl;

    conn_fd = accept(socket_fd, (struct sockaddr *) NULL, NULL);
    if(conn_fd < 0) cout << "error accepting connection" << endl;

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    int to_send = 0; // NOTE: not descriptive variable
    while(std::chrono::steady_clock::now() - start > std::chrono::seconds(60))
    {
        to_send = std::rand() % 10;
        net_buff = '0' + to_send;
        write(conn_fd, &net_buff, sizeof(net_buff));
    }

    close(conn_fd);

    exit(EXIT_SUCCESS);
    // NOTE: in this case, you can also do: exit(EXIT_SUCCESS);
}
