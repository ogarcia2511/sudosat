/* networking-related C headers */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/poll.h>

/* for C++ standard lib threading */
#include <thread>

/* for printing errors/debugging */
#include <iostream>
#include <string.h>

/* shared dependencies (put into one header lol (OR MACRO GUARD)) */
#include "worker.hpp"

#define MAX_CONN 10

class network
{
    private:
        int sock_fd, conn_fd;
	    int sock_opt;
        int bind_s, listen_s;
        int port_no;
        int rc;
        int on;
        int num_conns;

        struct sockaddr_in serv_addr;
        char *net_buff;

        // struct pollfd fds[MAX_CONN];
        // int num_fds;

    public:
        network(int port_no)
        {
            this -> port_no = port_no;

            serv_addr.sin_family = AF_INET;
            serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
            serv_addr.sin_port = htons(port_no);

            on = 1;
            num_conns = 0;
        }

        void setup_conn()
        {
            sock_fd = socket(AF_INET, SOCK_STREAM, 0);
            if(sock_fd < 0) 
            {
                std::cout << "error creating socket!" << std::endl;
                exit(EXIT_FAILURE);
            }

            rc = setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(int));
            if(rc)
            {
                std::cout << "setsockopt failed!" << std::endl;
                exit(EXIT_FAILURE);
            }

            // rc = ioctl(sock_fd, FIONBIO, (char *)&on);
            // if (rc < 0)
            // {
            //     std::cout << "ioctl failed!" << std::endl;
            //     close(sock_fd);
            //     exit(EXIT_FAILURE);
            // }
  
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
            while(true)
            {           
                listen_s = listen(sock_fd, 1); // 2nd argument is "backlog"
                if(listen_s < 0) std::cout << "error listening on port" << std::endl;

                std::cout << "listening..." << std::endl;
                
                conn_fd = accept(sock_fd, (struct sockaddr *) NULL, NULL);
                if(conn_fd < 0) std::cout << "error accepting connection" << std::endl;
                else std::cout << "accepted conn!" << std::endl; 

                // if(num_conns < 2)
                // {
                worker *w = new worker(conn_fd);
                std::thread w_thr(&worker::work, w);

                w_thr.detach();


                // }
                // else
                // {
                    // send "connections full!" message
                // }
                
                // std::cout << "accepted conn!" << std::endl;
                //w_thr.detach(); or join // TODO: maybe detach here?
            }

	        // char msg[19] = "hello from server!";
	        // net_buff = "hello from server!";
    	    // printf("out: %s\n", msg);
            //     //to_send = std::rand() % 10;
            //     //net_buff = '0' + to_send;
            // write(conn_fd, &msg, sizeof(msg));

	        return;
        }

        ~network()
        {
	        close(sock_fd);
        }  
};
