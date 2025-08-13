#include "EasyUDP.h"

EasyUDP::EasyUDP(std::string_view host, std::string_view port)
: receiverEndpoint_m{ *boost::asio::ip::udp::resolver{context_m}.resolve(boost::asio::ip::udp::v4(), host, port).begin() }
, socket_m{ context_m }
{
    socket_m.open(boost::asio::ip::udp::v4());
}

void EasyUDP::sendData(std::string_view data) {
    socket_m.send_to(boost::asio::buffer(data), receiverEndpoint_m);
}

std::string EasyUDP::receiveData() {
    const auto bytesReceived{ socket_m.receive_from(boost::asio::buffer(receiverBuffer_m), receiverEndpoint_m) };
    return std::string(receiverBuffer_m.cbegin(), bytesReceived);
}