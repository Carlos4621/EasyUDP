#ifndef EASY_UDP_HEADER
#define EASY_UDP_HEADER

#include <utility>
#include <array>
#include <string>
#include <string_view>
#include <boost/asio.hpp>
#include "IOCommons.hpp"

/// @brief Homólogo a EasyLoRa pero para comunicaciones UDP
class EasyUDP : public IOCommons {
public:

    /// @brief Constructor base
    /// @param host ip del receptor de sendData(), no es necesario si solo recibirás datos
    /// @param port puerto donde se recibirán los paquetes de un remitente
    EasyUDP(std::string_view host, std::string_view port);

    /// @brief Envía una serie de bytes al host seleccionado
    /// @param data Bytes a enviar
    void sendData(std::string_view data) override;

    /// @brief Recibe bytes del puerto seleccionado
    /// @return Bytes recibidos
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