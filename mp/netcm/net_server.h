#pragma once

#include "net_common.h"
#include "net_message.h"
#include "net_connection.h"

namespace olc {
    namespace net {
        template <typename T>
        class server_interface {
        protected:
            tsqueue<owned_message<T>> q_msg_in;

            // container of active validated conn
            std::deque<std::shared_ptr<connection<T>>> m_deq_connections;

            // order of declaration is also order of initialization
            asio::io_context m_asio_ctx;
            std::thread m_thr_ctx;

            // need to get socket to clients
            asio::ip::tcp::acceptor m_asio_acceptor;
            // numerical client id simpler than ip addresses
            uint32_t nIDCounter = 10000;

        public:
            server_interface(uint16_t port) : m_asio_acceptor(m_asio_ctx, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)) {

            }
            virtual ~server_interface() {
                Stop();
            }
            bool Start() {
                try {
                    WaitForClientConnection();
                    // start the context after client connection, so the initialized asio context would not run out of work and close
                    m_thr_ctx = std::thread([this](){m_asio_ctx.run();});

                } catch(std::exception & e) {
                    std::cerr<< "[Server] exception: " << e.what() << endl;
                    return false;
                }
                std::cout << "[Server] Started\n";
                return true;
            }
            void Stop() {
                // request context to close, may take some time
                m_asio_ctx.stop();
                // wait for context stop
                if (m_thr_ctx.joinable()) m_thr_ctx.join();
                std::cout << "[Sever] Stopped\n";
            }

            // Async - instruct asio to wait for connection
            void WaitForClientConnection() {
                // pass a lambda that would be called when accept a new connection
                m_asio_acceptor.async_accept([this](std::error_code ec, asio::ips::tcp::socket socket))
                {
                    if (!ec) {
                        std::cout << "[Server] New connection: " << socket.remote_endpoint() << std::endl;
                        // socket and context is passed to the new connection
                        // => connections share the context of server
                        std::shared_ptr<connection<T>> newconn = std::make_shared<connection<T>> 
                        (connection<T>::owner::server, m_asio_ctx, std::move(socket), q_msg_in);
                        // callback to user, user could chose to reject connection
                        if(OnClientConnect(newconn)) {
                            m_deq_connections.push_back(std::move(newconn));
                            m_deq_connections.back()->ConnectToClient(nIDCounter++);

                            std::cout << "[" << m_deq_connections.back()->GetID() << "] Connection Approved\n";
                        }
                    } else {
                        std::cout << "[Server] New connection err: " << ec.message() << std::endl;
                        
                    }
                }
            }

            void MessageClient(std::shared_ptr<connection<T> client, consg message<T> & msg) {

            }

            void MessageAllClients(const message<T> & msg, std::shared_ptr<connection<T>> ignore_clt) {

            }

            // called when a client connects. return false to reject conneciton
            virtual bool OnClientConnect(std::shared_ptr<connection<T>> client) {
                return false;
            }

            virtual void OnClientDisconnect(std::shared_ptr<connection<T>> client) {
            }

            // called when msg arrives
            virtual void OnMessage(std::shared_ptr<connection<T> client, message<T> & msg) {

            }


        };
    }
}