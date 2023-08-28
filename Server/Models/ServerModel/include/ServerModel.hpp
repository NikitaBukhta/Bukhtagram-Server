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

#ifndef BUKHTAGRAM_MESSENGERSERVER_SERVER_MODELS_SERVERMODELS_HPP
#define BUKHTAGRAM_MESSENGERSERVER_SERVER_MODELS_SERVERMODELS_HPP

#include "IServerModel.hpp"

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <memory>
#include <mutex>

namespace bukhtagram {
namespace ms {
namespace server {
namespace models {

class ServerModel : public IServerModel {
public:
    ServerModel(std::weak_ptr<boost::asio::io_context> io_context);
    virtual ~ServerModel(void) = default;

    // Getters starts;

    std::weak_ptr<boost::asio::io_context> io_context(void) override;
    std::weak_ptr<boost::asio::ip::tcp::acceptor> acceptor(void) override;

    // Getters ends;

    // Setters starts;

    
    
    // Setters ends;

private:
    // Private Setters starts;
    
    bool set_io_context(std::weak_ptr<boost::asio::io_context> val);

    // Private Setters ends;

    // Private Update methods starts;

    bool update_acceptor(void);

    // Private Update methods ends;

private:
    std::mutex m_io_context_mutex;
    std::shared_ptr<boost::asio::io_context> m_io_context;

    std::mutex m_accpetor_mutex;
    std::shared_ptr<boost::asio::ip::tcp::acceptor> m_acceptor;
    
};

}   // !models;
}   // !server;
}   // !ms;
}   // !bukhtagram;

#endif  // !BUKHTAGRAM_MESSENGERSERVER_SERVER_MODELS_SERVERMODELS_HPP;