#include "ipc/unix_sockets/ipc_server.hpp"

namespace ipc
{
    IPCServer::IPCServer(std::string addr) : ipc_sock_addr(addr)
    {
    }

    int IPCServer::init()
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

        if (bind(ipc_sockfd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
        {
            std::cerr << "Error binding socket" << std::endl;
            close(ipc_sockfd);
            return 1;
        }

        if (listen(ipc_sockfd, 3) < 0)
        {
            perror("error listening to clients");
            return 1;
        }

        FD_ZERO(&ipc_master_sockfd);
        FD_SET(ipc_sockfd, &ipc_master_sockfd);

        timeout.tv_sec = 0;
        timeout.tv_usec = 1000;

        return 0;
    }

    int IPCServer::exec()
    {
        ipc_ready_sockfd = ipc_master_sockfd;

        if (select(FD_SETSIZE, &ipc_ready_sockfd, nullptr, nullptr, &timeout) < 0)
        {
            std::cerr << "error occurred for while selecting." << std::endl;
            return 1;
        }

        if (FD_ISSET(ipc_sockfd, &ipc_ready_sockfd))
        {
            int client_sockfd = accept(ipc_sockfd, nullptr, nullptr);
            setsockopt(client_sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
            FD_SET(client_sockfd, &ipc_master_sockfd);
            std::cout << "* connected to client : " << client_sockfd << std::endl;
        }

        for (int idx = 0; idx < FD_SETSIZE; idx++)
        {
            if (idx == ipc_sockfd)
                continue;

            if (FD_ISSET(idx, &ipc_ready_sockfd))
            {
                char buffer[5];

                if (recv(idx, buffer, 5, 0) <= 0)
                {
                    close(idx);
                    FD_CLR(idx, &ipc_master_sockfd);
                    std::cout << "! closed connection with client : " << idx << std::endl;
                }
                else
                {
                    std::cout << "* message from " << idx << " : " << buffer << std::endl;
                    char *send_buffer = "hello!";
                    if (send(idx, send_buffer, strlen(send_buffer), 0) < 0)
                    {
                        close(idx);
                        FD_CLR(idx, &ipc_master_sockfd);
                        std::cout << "! closed connection with client : " << idx << std::endl;
                        return 1;
                    }
            }
        }
    }

    return 0;
}

void IPCServer::exit()
{
    close(ipc_sockfd);
    unlink(ipc_sock_addr.c_str());
}
}
;