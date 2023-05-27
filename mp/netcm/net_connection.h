//
// Created by SG0014000445M on 2023/5/26.
//

#ifndef ALGOLIB_NET_CONNECTION_H
#define ALGOLIB_NET_CONNECTION_H

#include "net_common.h"
#include "net_message.h"
#include "net_tsqueue.h"

namespace olc {
    namespace net {
        template <typename T>
    class connection: public std::enable_shared_from_this<connection<T>> {
    protected:
        asio::ip::tcp::socket m_socket;
        asio::io_context& m_ctx;
        tsqueue<message<T>> q_msg_out; // holds message to be sent out
        
        // input messages, owned by connection. so this is a reference to queue.
        tsqueue<owned_message<T>> & q_msg_in;


    public:
        connection(){}
        virtual ~connection() {}

        bool ConnectToServer();
        bool Disconnect();
        bool IsConnected() const;

        bool Send(const message<T> & msg);

    };
    }
}

#endif //ALGOLIB_NET_CONNECTION_H
