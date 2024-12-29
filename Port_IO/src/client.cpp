
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <string>

namespace PortIO {

class Client {
public:
    Client() {
        server_addr.sin_family      = AF_INET;
        server_addr.sin_port        = htons(PORT);
        server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    }

    void send_message_to_socket(const std::string &message) {
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) {
            std::cerr << "ERROR : Client creat socket fail" << std::endl;
            return;
        }

        if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
            std::cerr << "Connection failed" << std::endl;
            close(sockfd);
            return;
        }

        send(sockfd, message.data(), message.length(), 0);
        std::cout << "Send Success, Message : " << message << std::endl;
        close(sockfd);
    }

    template <typename T>
    void send_message_to_socket(const T &message) {
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) {
            std::cerr << "ERROR : Client creat socket fail" << std::endl;
            return;
        }

        if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
            std::cerr << "Connection failed" << std::endl;
            close(sockfd);
            return;
        }

        std::string buffer = std::to_string(message);

        send(sockfd, buffer.data(), buffer.size(), 0);
        std::cout << "Send Success, Message : " << message << std::endl;
        close(sockfd);
    }

private:
    const int PORT = 12345;
    int sockfd;
    struct sockaddr_in server_addr;
};
}  // namespace PortIO

int main() {
    PortIO::Client client;
    std::string message_string = "FloatPigeon here!";
    double message_double      = 100.0;
    int message_int            = 66;
    int count                  = 0;

    while (true) {
        switch (count) {
            case 0: client.send_message_to_socket(message_string); break;
            case 1: client.send_message_to_socket(message_double); break;
            case 2: client.send_message_to_socket(message_int); break;
            default: break;
        }
        count = ++count % 3;
        sleep(1);
    }
    return 0;
}