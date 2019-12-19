#ifndef NETWORK_HEADER
#define NETWORK_HEADER

/* networking-related C headers */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>

/* for C++ standard lib threading */
#include <thread>

/* for printing errors/debugging */
#include <iostream>
#include <string.h>

class network
{
    private:
        int sock_fd, conn_fd;
	int sock_opt;
        int bind_s, listen_s;
        int port_no;

        struct sockaddr_in serv_addr;
        char *net_buff;

    public:
        network(int port_no)
        {
            this -> port_no = port_no;

            serv_addr.sin_family = AF_INET;
            serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
            serv_addr.sin_port = htons(port_no);
        }

        void setup_conn()
        {
            sock_fd = socket(AF_INET, SOCK_STREAM, 0);
            if(sock_fd < 0) 
            {
                std::cout << "error creating socket!" << std::endl;
                exit(EXIT_FAILURE);
            }

	    int reuse = 1;
	    sock_opt = setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &reuse, sizeof(int));
	    if(sock_opt)
	    {
		std::cout << "setsockopt failed!" << std::endl;
		exit(EXIT_FAILURE);
	    }
  
            bind_s = bind(sock_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
            if(bind_s < 0) 
            {
                std::cout << "error creating socket!" << std::endl;
                exit(EXIT_FAILURE);
            }
        }

        void run()
        {
            /* run with:
            * network *n = new network();     
            * std::thread net_thread(&network::run, n, [RUN() PARAMS]);
            */
            listen_s = listen(sock_fd, 1);
            if(listen_s < 0) std::cout << "error listening on port" << std::endl;

            std::cout << "listening..." << std::endl;
            
            conn_fd = accept(sock_fd, (struct sockaddr *) NULL, NULL);
            if(conn_fd < 0) std::cout << "error accepting connection" << std::endl;

            std::cout << "accepted conn!" << std::endl;
	    
	    char msg[19] = "hello from server!";
	    net_buff = "hello from server!";
    	    printf("out: %s\n", msg);
                //to_send = std::rand() % 10;
                //net_buff = '0' + to_send;
            write(conn_fd, &msg, sizeof(msg));

	    return;
        }

        ~network()
        {
            close(conn_fd);
	    close(sock_fd);
        }  
};

#endif
