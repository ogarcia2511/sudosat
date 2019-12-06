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
#include <cstdlib>

class worker
{
    private:
        int worker_id;
        int connection;
        char buffer[256];
        fd_set read_set;
        struct timeval timeout;

    public:
        worker(int conn_fd)
        {
            srand(time(NULL));
            worker_id = rand() % 255;
            connection = conn_fd;
            FD_ZERO(&read_set);
            FD_SET(connection, &read_set);

            timeout.tv_sec = 5;
            timeout.tv_usec = 0;
        }

        void work()
        {
            std::cout << "in worker!" << worker_id << std::endl;

            while(true)
            {

                int s = select(connection + 1, &read_set, NULL, NULL, &timeout);

                if(s < 0) //error case
                {
                    std::cout << "socket error!" << worker_id << std::endl;
                    close(connection);
                    break;
                }
            
                if(s == 0) // timeout case
                {
                    // close connection and exit thread
                    std::cout << "timeout!" << std::endl;
                    close(connection);
                    break;

                }

                if(s > 0) // data to be read
                {
                    std::cout << "data to be read!" << std::endl;

                    read(connection, &buffer, sizeof(buffer));

                    std::cout << "data: " << buffer << std::endl;
                }

            }

            return;
        }
};