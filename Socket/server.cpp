#include "commen.h"
#include "Socket.h"
#include "SocketException.h"

void sigHandler(int signo)
{
    while (waitpid(-1, NULL, WNOHANG) > 0)
        ;
}

int main(int argc, char **argv)
{
    signal(SIGCHLD, sigHandler);
    signal(SIGPIPE, SIG_IGN);
    try
    {
        TCPServer server(8001);
        std::string msg;
        while (true)
        {
            TCPClient client = server.accept();
            pid_t pid = fork();
            if (pid == -1)
                err_exit("fork error");
            else if (pid > 0)
                client.close();
            else if (pid == 0)
            {
                try
                {
                    while (true)
                    {
                        client.receive(msg);
                        cout << msg << endl;
                        client.send(msg);
                    }
                }
                catch (const SocketException &e)
                {
                    cerr << e.what() << endl;
                    exit(EXIT_FAILURE);
                }
                exit(EXIT_SUCCESS);
            }
        }
    }
    catch (const SocketException &e)
    {
        cerr << e.what() << endl;
        exit(EXIT_FAILURE);
    }
}
