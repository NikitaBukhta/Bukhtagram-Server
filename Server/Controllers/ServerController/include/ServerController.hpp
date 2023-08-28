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

#ifndef BUKHTAGRAM_MESSENGERSERVER_SERVER_CONTROLLERS_SERVERCONTROLLER_HPP
#define BUKHTAGRAM_MESSENGERSERVER_SERVER_CONTROLLERS_SERVERCONTROLLER_HPP

#include "IServerController.hpp"
#include "IClientHandlerController.hpp"
#include "IServerModel.hpp"

#include "Logger.hpp"

#include <memory>

namespace bukhtagram {
namespace ms {
namespace server {
namespace controllers {

class ServerController : public IServerController{
public:
    ServerController(std::weak_ptr<models::IServerModel> server_model, std::weak_ptr<IClientHandlerController> client_handler_controller);
    virtual ~ServerController(void);

    // Overriding starts;

    void run(const std::string &server_address, uint16_t server_port) override;

    // Overriding ends;

private:
    void accept_connection(void);

    void handle_accept(std::weak_ptr<boost::asio::ip::tcp::socket> weak_client_socket, const boost::system::error_code &error);
    bool handle_error(const boost::system::error_code &error);

private:
    std::shared_ptr<models::IServerModel> m_server_model;
    std::shared_ptr<IClientHandlerController> m_client_handler_controller;
};

}   // !controllers;
}   // !server;
}   // !ms;
}   // !bukhtagram;


#endif  // !BUKHTAGRAM_MESSENGERSERVER_SERVER_CONTROLLERS_SERVERCONTROLLER_HPP;