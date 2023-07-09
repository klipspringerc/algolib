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
    public:
        enum class owner
			{
				server,
				client
			};
    protected:
        asio::ip::tcp::socket m_socket;
        asio::io_context& m_ctx; // each connection would not own an individual context
        tsqueue<message<T>> q_msg_out; // holds message to be sent out, owned by this connection
        
        // input message queue, owned by the client or server, so a reference.
        tsqueue<owned_message<T>> & q_msg_in;

        // act as a buffer: incoming message are constructed asynchronously here. Until it is ready.
        message<T> m_msg_tmp_in;

        owner m_owner_type = owner::server;
        uint32_t id;


    public:
        
        connection(owner parent, asio::io_context& ctx, asio::ip::tcp::socket socket, tsqueue<owned_message<T>> & qin)
        : m_ctx(ctx), m_socket(std::move(socket)), q_msg_in(qin){
            m_owner_type = parent;
        }
        virtual ~connection() {}

        uint32_t GetID() const {
            return id;
        }

        void ConnectToClient(uint32_t uid=0) {
            if (m_owner_type == owner::server) {
                if(m_socket.is_open()) {
                    id = uid;
                    ReadHeader();
                }
            }
        }
        bool ConnectToServer(const asio::ip::tcp::resolver::results_type& endpoints) {
            if (m_owner_type == owner::client) {
                asio::async_connect(m_socket, endpoints, [this](std::error_code ec, asio::ip::tcp::endpoint endpoint) {
                    if(!ec) {
                        ReadHeader();
                    }
                });
            }

        }
        bool Disconnect(){
            if (IsConnected()) 
                asio::post(m_ctx, [this](){m_socket.close();});
        }
    
        bool IsConnected() const {
            return m_socket.is_open();
        };

        // each connection is one-to-one
        bool Send(const message<T> & msg) {
            asio::post(m_ctx, [this, msg]() {
                // queue has message, push current msg into queue. Otherwise start writing to socket

            });
        };


    private:
        // prime the context ready to read a message header
        void ReadHeader() {
            // If this function is called, we are expecting asio to wait until it receives enough bytes to form
            // a header.
            asio::async_read(m_socket, asio::buffer(&m_msg_tmp_in.header, sizeof(m_msg_tmp_in.header)),
            [this](std::error_code ec, std::size_t length) {
                if (!ec) {
                    // A complete message header has been read, check if this message
                    // has a body to follow...
                    if (m_msg_tmp_in.header.size > 0)
                    {
                        // ...it does, so allocate enough space in the messages' body
                        // vector, and issue asio with the task to read the body.
                        m_msg_tmp_in.body.resize(m_msg_tmp_in.header.size);
                        ReadBody();
                    }
                    else
                    {
                        // add this bodyless message to the connections
                        // incoming message queue
                        AddToIncomingMessageQueue();
                    }
                } else {
                    std::cout << "[" << id << "] Read Body Fail.\n";
                    m_socket.close();
                }
            });
        }
        // ASYNC - Prime context ready to read a message body
        void ReadBody()
        {
            // If this function is called, a header has already been read, and that header
            // request we read a body, The space for that body has already been allocated
            // in the temporary message object, so just wait for the bytes to arrive...
            asio::async_read(m_socket, asio::buffer(m_msg_tmp_in.body.data(), m_msg_tmp_in.body.size()),
                [this](std::error_code ec, std::size_t length)
                {						
                    if (!ec)
                    {
                        // ...and they have! The message is now complete, so add
                        // the whole message to incoming queue
                        AddToIncomingMessageQueue();
                    }
                    else
                    {
                        // As above!
                        std::cout << "[" << id << "] Read Body Fail.\n";
                        m_socket.close();
                    }
                });
        }
        // Once a full message is received, add it to the incoming queue
        void AddToIncomingMessageQueue()
        {				
            // Shove it in queue, converting it to an "owned message", by initialising
            // with the a shared pointer from this connection object
            if(m_owner_type == owner::server)
                q_msg_in.push_back({ this->shared_from_this(), m_msg_tmp_in });
            else
                q_msg_in.push_back({ nullptr, m_msg_tmp_in });
            // Must re prime the asio context to receive the next message. It 
            // will just sit and wait for bytes to arrive, and the message construction
            // process repeats itself.
            ReadHeader();
        }
    };
    }
}

#endif //ALGOLIB_NET_CONNECTION_H
