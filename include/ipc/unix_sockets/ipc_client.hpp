/**
 * @file    ipc_client.hpp
 * @author  Jesal Shah (shahjesal1510@gmail.com)
 * @brief   Header file for IPCClient class handling client-side UNIX domain socket communication.
 * @date    2025-05-20
 *
 * This class provides a simple client interface for inter-process communication using
 * UNIX domain sockets. It allows connecting to a server socket and performing basic operations.
 */

#ifndef IPC_CLIENT_HPP__
#define IPC_CLIENT_HPP__

#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

namespace ipc {

/**
 * @class IPCClient
 * @brief A simple UNIX domain socket client for IPC.
 */
class IPCClient
{
public:
    /**
     * @brief Constructor that sets the target socket address.
     * @param addr The file system path to the server's UNIX domain socket.
     */
    IPCClient(std::string addr);

    /**
     * @brief Initializes the client socket and connects to the server.
     * @return 0 on success, non-zero on failure.
     */
    int init();

    /**
     * @brief Main execution function for client-side logic.
     * @return Exit code (typically 0 for success).
     */
    int exec();

    /**
     * @brief Cleans up and closes the socket.
     */
    void exit();

protected:
    int ipc_sockfd;              ///< File descriptor for the client socket.
    std::string ipc_sock_addr;   ///< Path to the UNIX domain socket.
};

} // namespace ipc

#endif // IPC_CLIENT_HPP__
