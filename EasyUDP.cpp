#include "EasyUDP.h"

EasyUDP::EasyUDP(std::string_view host, std::string_view port)
: receiverEndpoint_m{ *boost::asio::ip::udp::resolver{context_m}.resolve(boost::asio::ip::udp::v4(), host, port).begin() }
, socket_m{ context_m }
{
    socket_m.open(boost::asio::ip::udp::v4());
    
    boost::asio::ip::udp::endpoint local_endpoint(boost::asio::ip::udp::v4(), std::stoi(std::string(port)));
    socket_m.bind(local_endpoint);
    socket_m.non_blocking(true);
}

void EasyUDP::sendData(std::string_view data) {
    socket_m.send_to(boost::asio::buffer(data), receiverEndpoint_m);
}

std::string EasyUDP::receiveData() {
    boost::asio::ip::udp::endpoint sender_endpoint;
    boost::system::error_code ec;

    const auto bytesReceived{ socket_m.receive_from(boost::asio::buffer(receiverBuffer_m), sender_endpoint, 0, ec) };

    if (ec == boost::asio::error::would_block) {
        return "";
    }

    return std::string(receiverBuffer_m.cbegin(), receiverBuffer_m.cbegin() + bytesReceived);
}