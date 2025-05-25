# 🧩 TCP Client-Server Communication (C)

## 📌 Project Overview

This project implements a simple TCP-based client-server communication system in C. The program supports two modes of operation:

- **`server`**: Listens for incoming messages on TCP port **8080**  
- **`client`**: Connects to the server and sends messages interactively  

Each client message is acknowledged by the server with a response.

---

## 🛠️ Build

To compile the project using the provided `Makefile`, run:

```bash
make
```

This will produce an executable named `main`.

To clean up object files and the binary:

```bash
make clean
```

---

## 🧪 Usage

### ▶️ Start the server (on one machine):

```bash
./main server
```

### 📨 Start the client (on another machine or the same using localhost):

```bash
./main client <server_ip>
```

### Example:

```bash
./main client 192.168.1.10
```

---

## ⚙️ How It Works

### 🖥️ Server:

- Binds to port `8080`
- Waits for client connections
- Prints incoming message
- Sends fixed response: `"Server received the message."`

### 💬 Client:

- Connects to the specified server IP at port `8080`
- Allows user to type messages
- Sends message to server
- Prints server's response
- Type `exit` to terminate

---

## 🧾 Example Output

### 📤 Client Terminal:

```bash
> Enter message: Hello Server!
[CLIENT] Reply from server: Server received the message.
```

### 📥 Server Terminal:

```bash
[SERVER] Listening on port 8080...
[SERVER] Message received: Hello Server!
```

## 📌 Notes

- Make sure both devices are on the same network.
- Allow TCP port 8080 through the firewall on the server side.
- You can run both server and client on the same machine using `127.0.0.1` as IP.

---
