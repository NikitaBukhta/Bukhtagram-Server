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
#include "MessageConfig.hpp"

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

ClientHandlerController::~ClientHandlerController(void) {
    DECLARE_TAG_SCOPE;
    LOG_INFO << "clients count = " << m_client_handler_model->size();
    while (m_client_handler_model->size()) {
        auto client = m_client_handler_model->begin();
        disconnect(*client);
    }
}

void ClientHandlerController::run(void) {
    DECLARE_TAG_SCOPE;
    LOG_INFO << "called";
}

void ClientHandlerController::add(std::weak_ptr<boost::asio::ip::tcp::socket> client_socket) {
    DECLARE_TAG_SCOPE;
    
    auto client_connection = std::make_shared<models::ClientConnection>();
    client_connection->socket = client_socket.lock();

    if (m_client_handler_model->add(*client_connection)) {
        LOG_INFO << "new client added to clients list";
        
        start_read(client_connection);

    } else {
        LOG_WARNING << "Cannot to add client to clients list";
    }
}

void ClientHandlerController::disconnect(const models::ClientConnection &client) {
    DECLARE_TAG_SCOPE;

    if (client.socket.get()) {
        auto client_remote_endpoint = client.socket->remote_endpoint();
        LOG_INFO << "Remove client ip:" << client_remote_endpoint.address().to_string() << "; port: " << client_remote_endpoint.port();
        client.socket->close();
        // client.socket.
        if (!m_client_handler_model->remove(client)) {
            LOG_ERROR << "Cannot to remove client from the server";
        }
        LOG_DEBUG << "Count clients are connected to the server: " << m_client_handler_model->size();
    } else {
        LOG_WARNING << "Client is not detected";
    }
}

void ClientHandlerController::start_read(std::weak_ptr<models::ClientConnection> weak_client) {
    using namespace boost::placeholders;

    DECLARE_TAG_SCOPE;
    LOG_INFO << "called";

    auto client = weak_client.lock();

    /* As we use async programming, the data should be destroyed at the end of the method.
       To escape the desctruction the buffer, we made this static + made optimization of method work :);
     */
    static std::vector<char> buf;
    buf.resize(message_config::BASE_BUFFER_SIZE);
    boost::system::error_code error;

    boost::function<void(std::vector<char>&, const uint64_t, const boost::system::error_code, std::weak_ptr<models::ClientConnection>)> read_handler
        = boost::bind(&ClientHandlerController::handle_read, this, _1, _2, _3, _4);

    // TODO: fix bug with buffer overloading!;
    client->socket->async_read_some(boost::asio::buffer(buf, message_config::BASE_BUFFER_SIZE), [read_handler, client](const boost::system::error_code &error, const uint64_t bytes_transferred){
        read_handler(buf, bytes_transferred, error, client);
    });
}

void ClientHandlerController::start_write(std::weak_ptr<models::ClientConnection> weak_recipient) {
    using namespace boost::placeholders;

    DECLARE_TAG_SCOPE;

    auto recipient = weak_recipient.lock();

    LOG_INFO << "data size: " << recipient->message.size() << "; data: " << recipient->message;

    boost::function<void(const uint64_t, const boost::system::error_code&, std::weak_ptr<models::ClientConnection>)> write_handler = boost::bind(&ClientHandlerController::handle_write, this, _1, _2, _3);

    recipient->socket->async_write_some(
        boost::asio::buffer(recipient->message.data(), recipient->message.size()), [write_handler, recipient](const boost::system::error_code &error, const uint64_t bytes_transferred){
            write_handler(bytes_transferred, error, recipient);
    });
}

bool ClientHandlerController::handle_error(const boost::system::error_code &error) {
    DECLARE_TAG_SCOPE;

    bool ret = false;

    if (error.value() != boost::system::errc::success) {
        LOG_ERROR << "Error #" << error.value() << ": " << error.message();
        ret = true;
    }

    return ret;
}

bool ClientHandlerController::handle_error(const boost::system::error_code &error, std::weak_ptr<models::ClientConnection> weak_client) {
    DECLARE_TAG_SCOPE;

    bool ret = false;
    
    if (error == boost::asio::error::connection_reset || error.value() == boost::asio::error::eof) {
        auto client = weak_client.lock();
        if (client.get()) {
            disconnect(*client);
        }

        ret = true;
    } else {
        ret = handle_error(error);
    }

    return ret;
}

void ClientHandlerController::handle_read(std::vector<char> &data, const uint64_t DATA_SIZE, const boost::system::error_code &error, std::weak_ptr<models::ClientConnection> weak_client) {
    DECLARE_TAG_SCOPE;
    auto client = weak_client.lock();
    std::string transformed_data(std::begin(data), std::begin(data) + DATA_SIZE);
    auto client_remote_endpoint = client->socket->remote_endpoint();
        LOG_INFO << "Remote client ip:" << client_remote_endpoint.address().to_string() << "; port: " << client_remote_endpoint.port();
    LOG_DEBUG << "Client ip:" << client_remote_endpoint.address().to_string() << "; port: " << client_remote_endpoint.port() 
        << "; bytes count: " << DATA_SIZE << "; data: " << transformed_data;

    handle_error(error, client);

    if (client->socket->is_open()) {
        client->message.append(transformed_data);

        if (client->message.back() == message_config::MESSAGE_EOF) {
            start_write(client);
        }

        start_read(client);
    }
}

void ClientHandlerController::handle_write(const uint64_t DATA_SIZE, const boost::system::error_code &error, std::weak_ptr<models::ClientConnection> weak_recipient) {
    DECLARE_TAG_SCOPE;
    LOG_DEBUG << "counts bytes was sent:" << DATA_SIZE;

    auto recipitient = weak_recipient.lock();
    recipitient->message.erase(0, DATA_SIZE);

    handle_error(error);
}

}   // !controllers;
}   // !server;
}   // !ms;
}   // !bukhtagram;