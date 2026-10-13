# YacineHomeMadeServer

A lightweight HTTP server built with **C++ and Windows Winsock**. This project explores the fundamentals of web servers, including TCP socket communication, HTTP request handling, and serving static website files.

## Features

- TCP socket communication using Windows Winsock.
- HTTP request reception and handling.
- Static file serving from a configurable website directory.
- Configurable listening port and default index file.
- Custom 404 error page.
- Request metadata and logging.
- Modular source code organized into implementation, header, configuration, and public-file directories.

## Requirements

- Windows
- GCC with MinGW-w64
- A terminal such as PowerShell or Command Prompt

## Project structure

```text
server-http/
├── config/
│   └── config.txt
│
├── include/
│   ├── define.h
│   ├── init.h
│   ├── files.h
│   ├── metadata.h
│   ├── receive.h
│   ├── requests.h
│   └── send.h
│
├── src/
│   ├── main.cpp
│   ├── init.cpp
│   ├── files.cpp
│   ├── metadata.cpp
│   ├── receive.cpp
│   ├── requests.cpp
│   └── send.cpp
│
├── public/
│   ├── 404.html
│   └── responsive-website-restaurant-main/
│
├── server.exe
└── README.md
```

## Getting started

### 1. Clone the repository

```bash
git clone https://github.com/ycn3310/server-http.git
cd server-http
```

### 2. Configure the server

Edit `config/config.txt` to configure the server.

Example configuration:

```text
port: 6767
root_path: public
index_file: index.html
```

| Setting | Description |
|---|---|
| `port` | TCP port used by the server |
| `root_path` | Directory containing the website files |
| `index_file` | Default file served when the root URL is requested |

**Note:** The example assumes your program accepts relative paths from the project root and that `public/index.html` exists. Adjust these values to match your implementation.

### 3. Compile

Open a terminal in the project root and run:

```powershell
g++ -std=c++17 -Wall -Wextra -I include src/*.cpp -o server.exe -lws2_32
```

This command:

- Compiles all existing `.cpp` files in `src/`.
- Uses `include/` to locate header files.
- Links against `ws2_32`, the Windows Winsock library.
- Generates `server.exe` in the project root.

Make sure every source file is included in the compilation command.

### 4. Run the server

```powershell
.\server.exe
```

### 5. Access the server

If your configured port is `6767`, open:

```text
http://localhost:6767/
```

You can also test it using `curl`:

```bash
curl -i http://localhost:6767/
```

Replace `6767` with your configured port.

## How it works

The server follows the basic HTTP request-response cycle:

1. Initializes Winsock and the required socket resources.
2. Creates and binds a TCP socket to the configured port.
3. Listens for incoming client connections.
4. Receives an HTTP request.
5. Processes the requested resource.
6. Reads the corresponding file when applicable.
7. Sends the HTTP response to the client.

## Technology stack

- **Language:** C++
- **Networking:** Windows Winsock
- **Compiler:** GCC / MinGW-w64
- **Protocol:** HTTP over TCP

## Current limitations

This project is primarily intended for learning and experimentation.

- Windows-specific networking implementation.
- Limited HTTP method support.
- No assumption of production-grade security or concurrency.
- Static file access and request parsing require appropriate validation before public deployment.

## Future improvements

- [ ] Improve HTTP request parsing and validation.
- [ ] Add MIME type detection for static files.
- [ ] Improve HTTP status codes and response headers.
- [ ] Add directory traversal protection.
- [ ] Support concurrent client connections.
- [ ] Improve configuration validation and error handling.
- [ ] Add automated tests.
- [ ] Add graceful server shutdown.

## Contributing

Suggestions and contributions are welcome. Feel free to open an issue or submit a pull request.

## License

No license has been specified yet. Add a license file if you intend to define how others may use, modify, and redistribute this project.
