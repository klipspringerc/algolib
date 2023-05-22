//
// Created by KSC on 22/5/23.
//

#ifndef ALGOLIB_NET_MESSAGE_H
#define ALGOLIB_NET_MESSAGE_H

#include "net_common.h"

namespace olc {
    namespace net {
        template <typename T>
        struct message_header {
            T id{};
            uint32_t size = 0;
        };

        template <typename T>
        struct message {
            message_header<T> header{};
            std::vector<uint8_t> body;
            size_t size() const {
                return sizeof(message_header<T>) + body.size();
            }
        };
    }
}

#endif //ALGOLIB_NET_MESSAGE_H
