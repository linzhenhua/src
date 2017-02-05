#ifndef SOCKET_H_INCLUDED
#define SOCKET_H_INCLUDED

#include "SocketException.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <unistd.h>
#include <fcntl.h>

class TCPSocket
{
protected:
    TCPSocket();
    virtual ~TCPSocket();

    bool create();
    bool bind(unsigned short int port, const char *ip = NULL) const;
    bool listen(int backlog = SOMAXCONN) const;
    bool accept(TCPSocket &clientSocket) const;
    bool connect(unsigned short int port, const char *ip) const;

    /**注意: TCPSocket基类并没有send/receive方法**/

    bool reuseaddr() const;
    bool isValid() const
    {
        return (m_sockfd != -1);
    }
public:
    bool close();
    int getfd() const
    {
        return m_sockfd;
    }
    //flag: true=SetNonBlock, false=SetBlock
    bool setNonBlocking(bool flag) const;

protected:
    int m_sockfd;
};
/** TCP Client **/
class TCPClient : public TCPSocket
{
private:
    struct Packet
    {
        unsigned int    msgLen;     //数据部分的长度(网络字节序)
        char            text[1024]; //报文的数据部分
    };
public:
    TCPClient(unsigned short int port, const char *ip) throw(SocketException);
    TCPClient();
    TCPClient(int clientfd);
    ~TCPClient();

    size_t send(const std::string& message) const throw(SocketException);
    size_t receive(std::string& message) const throw(SocketException);
    size_t read(void *buf, size_t count) throw(SocketException);
    void   write(const void *buf, size_t count) throw(SocketException);
    size_t write(const char *msg) throw(SocketException);
};
/** TCP Server **/
class TCPServer : public TCPSocket
{
public:
    TCPServer(unsigned short int port, const char *ip = NULL, int backlog = SOMAXCONN) throw(SocketException);
    ~TCPServer();
    void accept(TCPClient &client) const throw(SocketException);
    TCPClient accept() const throw(SocketException);
};
#endif // SOCKET_H_INCLUDED
