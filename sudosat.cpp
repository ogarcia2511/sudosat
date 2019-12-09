/*
 * filename:            sudosat.cpp
 *
 * author:              Omar Garcia
 *
 * description:         WIP
 *
 */

#include "dependencies.hpp"
#include "network.hpp"

using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::thread;

std::mutex r_mut;

int main(int argc, char *argv[])
{
    if(argc < 2) 
    {
        cout << "port number not specified!" << endl;
        exit(EXIT_FAILURE);
    }

    network nett = network(atoi(argv[1]));

    nett.setup_conn();

    nett.run();

    exit(EXIT_SUCCESS);
}
