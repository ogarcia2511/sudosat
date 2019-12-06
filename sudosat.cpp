/*
 * filename:            sudosat.cpp
 *
 * author:              Omar Garcia
 *
 * description:         WIP
 *
 */

/* networking-related c headers */
#include "network.hpp"

/* cpp headers */
#include <cstdlib>
#include <string>
#include <iostream>
#include <chrono> 
#include <thread>

using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::thread;
using namespace std::chrono;

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
