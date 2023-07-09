//
// lock guard wrapped deque
//
#pragma once

#include "net_common.h"

namespace olc {
    namespace net {
        using std::mutex;
        template <typename T>
        class tsqueue {
        protected:
            std::mutex mux;
            std::deque<T> deq;
        public:
            tsqueue() = default;
            tsqueue(const tsqueue<T> &) = delete; // do not allow copying
            virtual ~tsqueue() {
                clear();
            }

            const T & front() {
                std::lock_guard<mutex> lock(mux);
                return deq.front();
            }

            const T & back() {
                std::lock_guard<mutex> lock(mux);
                return deq.back();
            }

            void push_back(const T & item) {
                std::lock_guard<mutex> lock(mux);
                deq.emplace_back(std::move(item));
            }

            void push_front(const T & item) {
                std::lock_guard<mutex> lock(mux);
                deq.emplace_front(std::move(item));
            }

            T pop_front() {
                std::lock_guard<mutex> lock(mux);
                auto item = std::move(deq.front());
                deq.pop_front();
                return item;
            }

            T pop_back() {
                std::lock_guard<mutex> lock(mux);
                auto item = std::move(deq.back());
                deq.pop_back();
                return item;
            }

            bool empty() {
                std::lock_guard<mutex> lock(mux);
                return deq.empty();
            }

            size_t count() {
                std::lock_guard<mutex> lock(mux);
                return deq.size();
            }

            void clear() {
                std::lock_guard<mutex> lock(mux);
                deq.clear();
            }
        };

    }
}