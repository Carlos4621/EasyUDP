#ifndef EASY_UDP_HEADER
#define EASY_UDP_HEADER

#include <utility>
#include <array>
#include <string>
#include <string_view>
#include <boost/asio.hpp>
#include "IOCommons.hpp"

class EasyUDP : public IOCommons {
public:

    EasyUDP(std::string_view host, std::string_view port);

    void sendData(std::string_view data) override;

    [[nodiscard]]
    std::string receiveData() override;

private:
    static constexpr size_t Receiver_Buffer_Size{ 1024 };

    std::array<char, Receiver_Buffer_Size> receiverBuffer_m{};

    boost::asio::io_context context_m{};
    boost::asio::ip::udp::endpoint receiverEndpoint_m;
    boost::asio::ip::udp::socket socket_m;

};

#endif //!EASY_UDP_HEADER