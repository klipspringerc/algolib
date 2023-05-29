#pragma once

#include "net_common.h"
#include "net_message.h"
#include "net_connection.h"

namespace olc {
    namespace net {
        template <typename T>
        class server_interface {
        public:
            server_interface(uint16_t port) {

            }
            virtual ~server_interface() {

            }
            bool Start() {

            }
            void Stop() {

            }

            // Async - instruct asio to wait for connection
            void WaitForClientConnection() {

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

            protected:
            tsqueue<owned_message<T>> q_msg_in;

            // order of declaration is also order of initialization
            asio::io_context m_asio_ctx;
            std::thread m_thr_ctx;


        };
    }
}