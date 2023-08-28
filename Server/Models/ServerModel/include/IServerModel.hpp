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

#ifndef BUKHTAGRAM_MESSENGERSERVER_SERVER_MODELS_ISERVERMODELS_HPP
#define BUKHTAGRAM_MESSENGERSERVER_SERVER_MODELS_ISERVERMODELS_HPP

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <inttypes.h>

namespace bukhtagram {
namespace ms {
namespace server {
namespace models {

class IServerModel {
public:
    // Getters starts;

    virtual std::weak_ptr<boost::asio::io_context> io_context(void) = 0;
    virtual std::weak_ptr<boost::asio::ip::tcp::acceptor> acceptor(void) = 0;

    // Getters ends;

    // Setters starts;
    
    // Setters ends;
};

}   // !models;
}   // !server;
}   // !ms;
}   // !bukhtagram;

#endif  // !BUKHTAGRAM_MESSENGERSERVER_SERVER_MODELS_ISERVERMODELS_HPP;