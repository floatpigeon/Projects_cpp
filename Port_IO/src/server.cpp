
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

namespace PortIO {

class Server {
public:
    void receive_message_from_socket() {
        int server_fd, new_sock;
        struct sockaddr_in server_addr, client_addr;
        socklen_t addr_len = sizeof(client_addr);

        server_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (server_fd < 0) {
            std::cerr << "ERROR : Server creat socket fail" << std::endl;
            return;
        }

        server_addr.sin_family      = AF_INET;
        server_addr.sin_addr.s_addr = INADDR_ANY;
        server_addr.sin_port        = htons(PORT);

        if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
            std::cerr << "Bind failed" << std::endl;
            close(server_fd);
            return;
        }
        listen(server_fd, 3);

        std::cout << "Server listening on port " << PORT << "..." << std::endl;

        while (true) {
            new_sock = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
            if (new_sock < 0) {
                std::cerr << "Accept faild" << std::endl;
                continue;
            }

            char buffer[1024] = {0};
            int read_size     = read(new_sock, buffer, sizeof(buffer) - 1);
            if (read_size > 0) {
                buffer[read_size] = '\0';
                std::cout << "Received message: " << buffer << std::endl;
            }

            close(new_sock);
        }
        close(server_fd);
    }

private:
    const int PORT = 12345;
};
}  // namespace PortIO

int main() {
    PortIO::Server server;
    server.receive_message_from_socket();
    return 0;
}