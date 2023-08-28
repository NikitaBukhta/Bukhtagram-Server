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

#include "ClientHandlerController.hpp"
#include "ClientHandlerModel.hpp"

#include "Logger.hpp"

#include <boost/function.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/bind/bind.hpp>

namespace bukhtagram {
namespace ms {
namespace server {
namespace controllers {

ClientHandlerController::ClientHandlerController(std::weak_ptr<models::IClientHandlerModel> client_handler_model)
    : m_client_handler_model(client_handler_model.lock())
{
    DECLARE_TAG_SCOPE;
    LOG_INFO << "called";
}

void ClientHandlerController::run(void) {
    DECLARE_TAG_SCOPE;
    LOG_INFO << "called";
}

void ClientHandlerController::add(std::weak_ptr<boost::asio::ip::tcp::socket> client_socket) {
    DECLARE_TAG_SCOPE;
    
    models::ClientConnection client_connection;
    client_connection.socket = client_socket.lock();

    if (m_client_handler_model->add(client_connection)) {
        LOG_INFO << "new client added to clients list";
        
        start_read(client_connection);

    } else {
        LOG_WARNING << "Cannot to add client to clients list";
    }
}

void ClientHandlerController::start_read(models::ClientConnection &client) {
    using namespace boost::placeholders;

    DECLARE_TAG_SCOPE;
    LOG_INFO << "called";

    /* As we use async programming, the data should be destroyed at the end of the method.
       To escape the desctruction the buffer, we made this static + made optimization of method work :);
     */
    static std::array<char, STANDART_BUFFER_SIZE> buf;
    boost::system::error_code error;

    boost::function<void(std::array<char, STANDART_BUFFER_SIZE>&, const uint64_t, const boost::system::error_code, models::ClientConnection)> read_handler
        = boost::bind(&ClientHandlerController::handle_read, this, _1, _2, _3, _4);

    // TODO: fix bug with buffer overloading!;
    client.socket->async_read_some(boost::asio::buffer(buf), [read_handler, client](const boost::system::error_code &error, const uint64_t bytes_transferred){
        read_handler(buf, bytes_transferred, error, client);
    });
}

void ClientHandlerController::start_write(models::ClientConnection &recipient, const std::string &message) {
    using namespace boost::placeholders;

    DECLARE_TAG_SCOPE;
    LOG_INFO << "data size: " << message.size();

    boost::function<void(const uint64_t, const boost::system::error_code&)> write_handler = boost::bind(&ClientHandlerController::handle_write, this, _1, _2);

    recipient.socket->async_write_some(
        boost::asio::buffer(message.data(), message.size()), [write_handler](const boost::system::error_code &error, const uint64_t bytes_transferred){
            write_handler(bytes_transferred, error);
    });
}

bool ClientHandlerController::handle_error(const boost::system::error_code &error) {
    DECLARE_TAG_SCOPE;

    if (error.value() == boost::system::errc::success) {
        LOG_TRACE << "no errors handled";
        return false;
    }

    LOG_ERROR << error.what();
    return true;
}

void ClientHandlerController::handle_read(std::array<char, STANDART_BUFFER_SIZE> &data, const uint64_t DATA_SIZE, const boost::system::error_code &error, models::ClientConnection client) {
    DECLARE_TAG_SCOPE;
    std::string transformed_data(std::begin(data), std::begin(data) + DATA_SIZE);
    LOG_INFO << "bytes count: " << DATA_SIZE << "; data: " << transformed_data;
    handle_error(error);
    start_write(client, transformed_data);
    start_read(client);
}

void ClientHandlerController::handle_write(const uint64_t DATA_SIZE, const boost::system::error_code &error) {
    DECLARE_TAG_SCOPE;
    LOG_DEBUG << "counts bytes was sent:" << DATA_SIZE;
    handle_error(error);
}

}   // !controllers;
}   // !server;
}   // !ms;
}   // !bukhtagram;