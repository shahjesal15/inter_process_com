/**
 * @file    ipc_server.hpp
 * @author  Jesal Shah (shahjesal1510@gmail.com)
 * @brief   Header file for IPCServer class handling Unix domain socket-based IPC using select().
 * @date    2025-05-20
 * 
 * This class provides a simple implementation of an IPC (Inter-Process Communication) server 
 * using UNIX domain sockets. It uses `select()` to monitor multiple file descriptors and 
 * supports timeout-based select operations.
 */

#ifndef IPC_SERVER_HPP__
#define IPC_SERVER_HPP__

#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/select.h>
#include <unistd.h>

namespace ipc {

/**
 * @class IPCServer
 * @brief A basic IPC server using UNIX domain sockets and select().
 */
class IPCServer
{
public:
    /**
     * @brief Constructor that initializes the socket address.
     * @param addr The file system path for the UNIX domain socket.
     */
    IPCServer(std::string addr);

    /**
     * @brief Initializes the server socket and binds to the specified address.
     * @return 0 on success, non-zero on failure.
     */
    int init();

    /**
     * @brief Main execution loop that listens for and handles incoming connections using select().
     * @return Exit code (typically 0 for success).
     */
    int exec();

    /**
     * @brief Cleans up and closes the server socket.
     */
    void exit();

protected:
    int ipc_sockfd;                       ///< File descriptor for the IPC server socket.
    fd_set ipc_master_sockfd;            ///< Master set of file descriptors.
    fd_set ipc_ready_sockfd;             ///< Set of file descriptors ready for I/O.
    std::string ipc_sock_addr;           ///< Path to the UNIX domain socket.
    struct timeval timeout;              ///< Timeout structure for select().
};

}; // namespace ipc

#endif // IPC_SERVER_HPP__
