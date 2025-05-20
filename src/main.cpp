#include <iostream>
#include <thread>
#include <cstring>
#include <csignal>

#include "ipc/ipc_server.hpp"
#include "ipc/ipc_client.hpp"

bool is_active = true;

void print_usage()
{
    std::cout << "Usage:\tinter_process_com <options>\n\n--type\ttype of the process <parent/child>\n"
              << std::endl;
}

int handle_args(char **argv, char *&type)
{
    if (strcmp(argv[1], "--type") != 0)
        return -1;

    if (!(strcmp(argv[2], "parent") == 0 || strcmp(argv[2], "child") == 0))
        return -1;

    type = argv[2];

    return 0;
}

void handle_signals(int signals)
{
    std::cout << "stop signaled" << std::endl;
    is_active = false;
}

void handle_child()
{
    ipc::IPCClient child("/tmp/strider");

    if (child.init() != 0)
        return;

    while (child.exec() == 0 && is_active)
        usleep(1000);

    child.exit();
}

void handle_parent()
{
    ipc::IPCServer parent("/tmp/strider");

    if (parent.init() != 0)
        return;

    while (parent.exec() == 0 && is_active)
        usleep(1000);

    parent.exit();
}

int main(int argc, char **argv)
{
    char *type = nullptr;

    if ((argc < 3 || argc > 3) || handle_args(argv, type) != 0)
    {
        print_usage();
        return -1;
    }

    signal(SIGINT, handle_signals);

    if (strcmp(type, "parent") == 0)
        handle_parent();
    else
        handle_child();

    return 0;
}