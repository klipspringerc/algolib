//
// Created by SG0014000445M on 2023/5/23.
//

#include "netcm/net_message.h"

enum class CustomMsgTypes: uint32_t {
    FireBullet, MovePlayer
};

int main() {
    olc::net::message<CustomMsgTypes> msg;
    msg.header.id = CustomMsgTypes::FireBullet;
    int a = 1;
    bool b = true;
    float c = 32.15f;
    struct {
        float x = 1.0;
        float y = 0.0;
    } d [5];
    msg << a << b << c << d; // 49 bytes
    std::cout << msg.size() << std::endl;  // with header 8 bytes, total 57 bytes
    a = 13;
    msg >> d >>c >> b >> a;
    std::cout << a << " "<< b << " " << c << " " << d[1].x << std::endl;
    return 0;

}