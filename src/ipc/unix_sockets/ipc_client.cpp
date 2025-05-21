#include "ipc/unix_sockets/ipc_client.hpp"

namespace ipc
{
    IPCClient::IPCClient(std::string addr) : ipc_sock_addr(addr)
    {
    }

    int IPCClient::init()
    {
        ipc_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
        if (ipc_sockfd == -1)
        {
            std::cerr << "Error creating socket" << std::endl;
            return 1;
        }

        struct sockaddr_un addr;
        memset(&addr, 0, sizeof(addr));
        addr.sun_family = AF_UNIX;
        strncpy(addr.sun_path, ipc_sock_addr.c_str(), sizeof(addr.sun_path) - 1);

        if (connect(ipc_sockfd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
        {
            std::cerr << "Error connecting to server" << std::endl;
            close(ipc_sockfd);
            return 1;
        }

        std::cout << "* connected to server" << std::endl;
        return 0;
    }

    int IPCClient::exec()
    {
        char *buffer = "hello";
        send(ipc_sockfd, buffer, strlen(buffer), 0);
        
        char *recv_buffer = (char *)malloc(6);
        if (recv(ipc_sockfd, recv_buffer, 6, 0) < 0) {
            std::cerr << "! error receiving message" << std::endl;
            return 1;
        } else {
            std::cout << "* message from server : " << recv_buffer << std::endl;
        }
            
        std::cin.get();
        
        return 0;
    }

    void IPCClient::exit()
    {
        close(ipc_sockfd);
    }
}