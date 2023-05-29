//
// Connection abstraction
// ephemeral, when client close connection, connection object would be destroyed on both ends

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
        asio::io_context& m_ctx; // each connection would not own an individual context
        tsqueue<message<T>> q_msg_out; // holds message to be sent out, owned by this connection
        
        // input message queue, owned by the client or server, so a reference.
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
