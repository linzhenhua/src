#ifndef COMMEN_H_INCLUDED
#define COMMEN_H_INCLUDED

#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/socket.h>
#include <sys/time.h>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <semaphore.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include <vector>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <future>
#include <memory>
#include <iostream>
#include <algorithm>

using namespace std;

inline void err_exit(const std::string &msg)
{
    perror(msg.c_str());
    exit(EXIT_FAILURE);
}
inline void err_quit(const std::string &msg)
{
    std::cerr << msg << std::endl;
    exit(EXIT_FAILURE);
}
inline void err_thread(const std::string &msg, int retno)
{
    std::cerr << msg << ": " << strerror(retno) << std::endl;
    exit(EXIT_FAILURE);
}
inline void err_check(const std::string &msg, int retno)
{
    if (retno != 0)
        err_thread(msg, retno);
}

#endif // COMMEN_H_INCLUDED
