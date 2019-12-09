#ifndef DEPENDENCIES_H
#define DEPENDENCIES_H

/* networking-related c headers */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ioctl.h>

/* cpp headers */
#include <cstdlib>
#include <string>
#include <iostream>

/* for printing errors/debugging */
#include <string.h>
#include <stdlib.h>

/* thread headers */
#include <thread>
#include <mutex>
#include <condition_variable>

#define MAX_CONN 10

int conns = 0;
std::mutex c_mut;

#endif 