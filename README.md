# VCMP - Very Cool Message Platform
**VCMP** stands for **Very Cool Message Platform**, a peer-to-peer chat platform with privacy at its core. VCMP emphasizes Tor-based anonymity and secure, RSA-encrypted communication.

### Technical Highlights
- **Backend**: Built entirely in C++ for optimized performance.
- **Frontend Compatibility**: Any language that supports WebSocket communication can be used for frontend development, enabling flexibility across different platforms.

# Getting started
## Libraries
Ensure the following libraries are installed:
- `libuuid-devel`
- [libevent](https://github.com/libevent/libevent)
- [OpenSSL](https://github.com/openssl/openssl)
- [spdlog](https://github.com/gabime/spdlog)

### Building & Running
```bash
git clone https://github.com/g4iliunas/vcmp.git
cd vcmp/vcmp
mkdir build
cd build
cmake ..
cmake --build .
./vcmp
```

# License
This project is licensed under the MIT License. For more details, please refer to the [LICENSE](./LICENSE)