/**********************************************************************************************************************
 * Bukhtagram                                                                                                         *
 *                                                                                                                    *
 * Author: Bukhta Mykyta                                                                                              *
 *                                                                                                                    *
 * Copyright ©2023 Bukhta Mykyta                                                                                      *
 *                                                                                                                    *
 * This software is distributed under the following license:                                                          *
 *                                                                                                                    *
 * 1. This code may not be modified, redistributed, or used to create derivative works.                               *
 * 2. Any use of this code for commercial purposes is prohibited without prior written permission of the author.      *
 * 3. The author is not liable for any damages caused by the use of this software.                                    *
 * 4. Copies of this license or references to it must be included in all copies or significant parts of the software. *
 *                                                                                                                    *
 * For permission for commercial use, contact the author at the following address: nikita.bukhta.dev@gmail.com.       *
 **********************************************************************************************************************                                                                                                                    *
 */

// TODO: create a method to check if socket is ready to read with socket.available;

#ifndef BUKHTAGRAM_MESSENGERSERVER_SERVER_CONTROLLERS_CLIENTHANDLERCONTROLLER_HPP
#define BUKHTAGRAM_MESSENGERSERVER_SERVER_CONTROLLERS_CLIENTHANDLERCONTROLLER_HPP

#include "IClientHandlerController.hpp"
#include "IClientHandlerModel.hpp"

#include <array>
#include <memory>
#include <string>

#define STANDART_BUFFER_SIZE 128    // TODO: temp, create a config file!;

namespace bukhtagram {
namespace ms {
namespace server {
namespace controllers {

class ClientHandlerController : public IClientHandlerController {
public:
    ClientHandlerController(std::weak_ptr<models::IClientHandlerModel> client_handler_model);
    virtual ~ClientHandlerController(void) = default;

    void run(void) override;
    void add(std::weak_ptr<boost::asio::ip::tcp::socket> client_socket) override;

private:
    void start_read(models::ClientConnection &client);
    void start_write(models::ClientConnection &recipient, const std::string &message);

    bool handle_error(const boost::system::error_code &error);
    void handle_read(std::array<char, STANDART_BUFFER_SIZE> &data, const uint64_t DATA_SIZE, const boost::system::error_code &error, models::ClientConnection client);
    void handle_write(const uint64_t DATA_SIZE, const boost::system::error_code &error);

private:
    std::shared_ptr<models::IClientHandlerModel> m_client_handler_model;
};

}   // !controllers;
}   // !server;
}   // !ms;
}   // !bukhtagram;

#endif  // !BUKHTAGRAM_MESSENGERSERVER_SERVER_CONTROLLERS_CLIENTHANDLERCONTROLLER_HPP;