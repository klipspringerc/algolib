//
// Created by SG0014000445M on 2023/5/22.
//
// https://github.com/OneLoneCoder/Javidx9/tree/master/PixelGameEngine/BiggerProjects/Networking/Parts1%262


#include <iostream>
#include <string>
#include <vector>

#define ASIO_STANDALONE
#include <asio-1.18.2/include/asio.hpp>
#include <asio-1.18.2/include/asio/ts/buffer.hpp>
#include <asio-1.18.2/include/asio/ts/internet.hpp>

int main() {
    using std::cout;
    using std::endl;
    using std::string;
    using std::vector;
    asio::error_code ec;

    // the platform specific interface. unique instance of asio, hide platform specific requirements
    asio::io_context context;

    asio::ip::tcp::endpoint endpoint(asio::ip::make_address("93.184.216.34", ec), 80);
    asio::ip::tcp::socket socket(context);
    socket.connect(endpoint, ec);

    if (!ec) {
        cout << "connected" << endl;
    } else {
        cout << "failed to connect " << ec.message() << endl;
    }
    if (socket.is_open()) {
        std::string sRequest = "GET /index.html HTTP/1.1\r\nHost: example.com\r\nConnection: close\r\n\r\n";
        socket.write_some(asio::buffer(sRequest.data(), sRequest.size()), ec);
        if (ec) {
            cout << "failed to write " << ec.message() << endl;
            return 1;
        }
        size_t bytes = socket.available();
        cout << "bytes available" << bytes << endl;
        if (bytes > 0) {
            std::vector<char> vBuffer(bytes);
            socket.read_some(asio::buffer(vBuffer.data(), vBuffer.size()), ec);
            if (ec) {
                cout << "failed to read " << ec.message() << endl;
                return 1;
            }
            for (auto c : vBuffer)
                cout << c;
        }
    }

    return  0;
}