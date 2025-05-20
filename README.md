# IPC Communication System (UNIX Domain Sockets in C++)

A lightweight inter-process communication (IPC) system using UNIX domain sockets implemented in modern C++. This project includes both a server and a client, designed to communicate over a local socket file using a clean, class-based interface.

---

## ✨ Features

- Uses **UNIX domain sockets** (`AF_UNIX`, `SOCK_STREAM`)
- Handles **multiple clients** using `select()`
---

## 🛠️ Build Instructions

### 🔧 Requirements

- Linux or Unix-based system
- C++17 or newer
- CMake 3.10+

### ⚙️ Building the project

```bash
# Clone the repository
git clone https://github.com/your-username/ipc_communication.git
cd ipc_communication

# Create and enter the build directory
./BUILD
```
---
### 🚀 Usage
The application supports two modes: parent (server) and child (client).

Run the server (parent)
```bash
./inter_process_com --type parent
```
Run the client (child)
```bash
./inter_process_com --type child
```
---

### Maintainer
- Jesal Shah (shahjesal1510@gmail.com)
