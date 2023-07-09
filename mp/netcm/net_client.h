#pragma once

#include "net_common.h"
#include "net_message.h"
#include "net_tsqueue.h"
#include "net_connection.h"

namespace olc {
    namespace net {
        template <typename T>
        class client_interface {
        protected:

            asio::io_context m_ctx; // client own the context
            std::thread thr_ctx; // need a thread to execute client's work commands
            // client would set up the connection
            asio::ip::tcp::socket m_socket;
            // client holds a single instance of a "connection" object
            std::unique_ptr<connection<T>> m_connection;
        private:
            // incoming message from server
            tsqueue<owned_message<T>> m_msg_in;
        public:
            client_interface(): m_socket(m_ctx) {

            }

            virtual ~client_interface() {
                Disconnect();
            }


            bool Connect(const std::string & host, const uint16_t port) {
                try {
                    m_connection = std::make_unique<connection<T>>(owner::client, m_ctx, m_socket, m_msg_in); // TODO: init conn
                    asio::ip::tcp::resolver resolver(m_ctx);
                    m_endpoints = resolver.resolve(host, std::to_string(port)); // could fail with exception

                    m_connection->ConnectToServer(m_endpoints);
                    thr_ctx = std::thread([this]() { m_ctx.run(); });

                } catch (std::exception & e) {
                    std::cerr << "client exception: " << e.what() << std::endl;
                    return false;
                }
                return false;
            }

            void Disconnect() {
                if (IsConnected()) {
                    m_connection->Disconnect();
                }
                m_ctx.stop();
                if (thr_ctx.joinable())
                    thr_ctx.join();
                m_connection.release();
            }
            bool IsConnected() {
                if (m_connection)
                    return m_connection->IsConnected();
                return false;
            }
        };
    }
}
