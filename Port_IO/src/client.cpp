
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <string>

namespace PortIO {

class Client {
public:
    Client() {}
    void send_message_to_socket(const std::string &message) {
        int sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) {
            std::cerr << "ERROR : Client creat socket fail" << std::endl;
            return;
        }

        struct sockaddr_in server_addr;
        server_addr.sin_family      = AF_INET;
        server_addr.sin_port        = htons(PORT);
        server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

        if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
            std::cerr << "Connection failed" << std::endl;
            close(sockfd);
            return;
        }

        send(sockfd, message.c_str(), message.length(), 0);

        close(sockfd);
    }

private:
    const int PORT = 12345;
};
}  // namespace PortIO

int main() {
    std::string message = "FloatPigeon here!";
    PortIO::Client client;

    while (true) {
        client.send_message_to_socket(message);
    }
    return 0;
}