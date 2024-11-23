#ifndef VCMP_PEER_SERVER_H
#define VCMP_PEER_SERVER_H

#include <cstdint>
#include <event2/event.h>
#include <string>

namespace vcmp {
struct peer_info {
    std::string username;
    std::string hostname;
};
bool peer_server_init(event_base *base, const char *ip,
                      const std::uint16_t port, peer_info info);
} // namespace vcmp

#endif // VCMP_PEER_SERVER_H
