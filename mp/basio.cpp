//
// Created by SG0014000445M on 2023/5/22.
//
// https://github.com/OneLoneCoder/Javidx9/tree/master/PixelGameEngine/BiggerProjects/Networking/Parts1%262


#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>

#define ASIO_STANDALONE
// asio-1.18.2/include/
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

std::vector<char> vBuffer(1 *1024);

void GrabSomeData(asio::ip::tcp::socket & socket) {

    // each time would read at most vBuffer.size bytes
    socket.async_read_some(asio::buffer(vBuffer.data(), vBuffer.size()), [&](std::error_code ec, std::size_t length) {
        // params: error code and amount of data read
        if(!ec) {
            std::cout << "\n\nRead " << length << " bytes " << std::endl;
            for (int i = 0; i < length ; i++)
                std::cout << vBuffer[i];

            GrabSomeData(socket); // note this is not recursion. GrabSomeData simply push another handler to the async routine
        }
    });
}

int main() {
    using std::cout;
    using std::endl;
    using std::string;
    using std::vector;
    using std::thread;
    asio::error_code ec;

    // the platform specific interface. unique instance of asio, hide platform specific requirements
    asio::io_context context;

    asio::io_context::work idleWork(context); // give fake work to keep context alive

    // ask context to run on another thread
    // context run would exit as soon as the context has run out of things to do
    thread thrCtx = thread([&]() {
        context.run();
    });

    asio::ip::tcp::endpoint endpoint(asio::ip::make_address("93.184.216.34", ec), 80);
    asio::ip::tcp::socket socket(context);
    socket.connect(endpoint, ec);

    if (!ec) {
        cout << "connected" << endl;
    } else {
        cout << "failed to connect " << ec.message() << endl;
    }
    if (socket.is_open()) {
        GrabSomeData(socket); // give asio context task of reading from this socket

        std::string sRequest = "GET /index.html HTTP/1.1\r\nHost: example.com\r\nConnection: close\r\n\r\n";
        socket.write_some(asio::buffer(sRequest.data(), sRequest.size()), ec);
        if (ec) {
            cout << "failed to write " << ec.message() << endl;
            return 1;
        }
        // need to solve 2 problem: 1) we don't know when would server response 2) how many bytes would server send


        //std::this_thread::sleep_for(std::chrono::seconds(1)); // not good idea
        // Example: sync wait for response
//        socket.wait(socket.wait_read); // wait until data available
//        size_t bytes = socket.available(); // immediately read response would return zero bytes available
//
//        cout << "bytes available" << bytes << endl;
//        if (bytes > 0) {
//            std::vector<char> vBuffer(bytes);
//            socket.read_some(asio::buffer(vBuffer.data(), vBuffer.size()), ec);
//            if (ec) {
//                cout << "failed to read " << ec.message() << endl;
//                return 1;
//            }
//            for (auto c : vBuffer)
//                cout << c;
//        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return  0;
}