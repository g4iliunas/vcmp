#ifndef VCMP_WS_SERVER
#define VCMP_WS_SERVER

#include <cstdint>
#include <event2/event.h>

namespace vcmp {
bool ws_server_init(event_base *base, const char *ip, const std::uint16_t port);
}

#endif // VCMP_WS_SERVER