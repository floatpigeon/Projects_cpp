
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <chrono>
#include <cmath>
#include <cstring>
#include <iostream>
#include <numbers>
#include <string>
#include <thread>

namespace PortIO {

class Client {
public:
    Client() {
        server_addr.sin_family      = AF_INET;
        server_addr.sin_port        = htons(PORT);
        server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    }

    void update() {
        count++;
        double message_double      = 10 * (sin(count / 1000.0 * std::numbers::pi) + 1);
        std::string message_string = "hello";
        send_message_to_socket(message_double);
    }

private:
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

    const int PORT = 12345;
    int sockfd;
    struct sockaddr_in server_addr;
    double count = 0;
};
}  // namespace PortIO

int main() {
    PortIO::Client client;

    const int fps       = 1000;
    const auto interval = std::chrono::microseconds(1000000 / fps);

    for (;;) {
        auto start_time = std::chrono::steady_clock::now();

        client.update();

        auto end_time     = std::chrono::steady_clock::now();
        auto elapsed_time = end_time - start_time;

        if (elapsed_time < interval) {
            std::this_thread::sleep_for(interval - elapsed_time);
        }
    }
    return 0;
}
