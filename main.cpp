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

#include "ServerController.hpp"
#include "ClientHandlerController.hpp"

#include "ServerModel.hpp"
#include "ClientHandlerModel.hpp"

#include <boost/asio/io_context.hpp>

#include <memory>
#include <iostream>

int main(int argc, char **argv) {
    using namespace bukhtagram::ms::server;

    auto io_context = std::make_shared<boost::asio::io_context>();

    auto server_model = std::make_shared<models::ServerModel>(io_context);
    auto client_handler_model = std::make_shared<models::ClientHandlerModel>();

    auto client_handler_controller = std::make_shared<controllers::ClientHandlerController>(client_handler_model);
    auto server_controller = std::make_shared<controllers::ServerController>(server_model, client_handler_controller);

    try {
        server_controller->run("127.0.0.1", 12345);
        client_handler_controller->run();
        io_context->run();
    } catch (std::exception &error) {
        std::cerr << error.what() << std::endl;
    }

    return 0;
}