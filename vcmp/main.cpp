#include <event2/event.h>
#include <spdlog/spdlog.h>

#include <vcmp/peer_server.h>
#include <vcmp/ws_server.h>

#include <fstream>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>

#include <openssl/crypto.h>

int main(void)
{
    spdlog::info("=== VCMP ===");

    /* Display library versions */
    spdlog::info("Libevent version: {}", LIBEVENT_VERSION);
    spdlog::info("OpenSSL version: {}",
                 OpenSSL_version(OPENSSL_FULL_VERSION_STRING));

    /* Parse config */
    std::ifstream f("config.json");
    rapidjson::IStreamWrapper isw(f);
    rapidjson::Document document;
    document.ParseStream(isw);
    f.close();

    rapidjson::Value &servers = document["servers"];

    /* Parse listener server details */
    rapidjson::Value &listener = servers["listener"];
    const char *listener_addr = listener["address"].GetString();
    const uint16_t listener_port = listener["port"].GetUint();

    /* Parse websocket server details */
    rapidjson::Value &websocket = servers["websocket"];
    const char *websocket_addr = websocket["address"].GetString();
    const uint16_t websocket_port = websocket["port"].GetUint();

    /* Parse TOR proxy details */
    rapidjson::Value &tor = document["tor_service"];
    const char *tor_addr = tor["address"].GetString();
    const uint16_t tor_port = tor["port"].GetUint();

    /* Parse details about local peer */
    const char *username = document["username"].GetString();
    const char *hostname = document["hostname"].GetString();

    /* Display config */
    spdlog::info("Listener server listening on {}:{}", listener_addr,
                 listener_port);
    spdlog::info("Websocket server listening on {}:{}", websocket_addr,
                 websocket_port);
    spdlog::info("TOR proxy: {}:{}", tor_addr, tor_port);
    spdlog::info("Username: {}", username);
    spdlog::info("Hostname: {}", hostname);

    /* Initialize event base */
    event_base *base = event_base_new();
    if (!base) {
        spdlog::error("Failed to allocate event base");
        return 1;
    }

    /* Initialize peer listener & websocket server */
    if (!vcmp::peer_server_init(base, listener_addr, listener_port,
                                {username, hostname})) {
        spdlog::error("Failed to initialize peer server");
        event_base_free(base);
        return 1;
    }

    if (!vcmp::ws_server_init(base, websocket_addr, websocket_port)) {
        spdlog::error("Failed to initialize websocket server");
        event_base_free(base);
        return 1;
    }

    spdlog::info("Dispatching event loop");
    event_base_dispatch(base);
    spdlog::info("Event loop ended, exitting program");

    event_base_free(base);
    return 0;
}