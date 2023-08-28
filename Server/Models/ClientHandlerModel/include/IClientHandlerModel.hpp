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

#ifndef BUKHTAGRAM_MESSENGERSERVER_SERVER_MODELS_ICLIENTHANDLERMODEL_HPP
#define BUKHTAGRAM_MESSENGERSERVER_SERVER_MODELS_ICLIENTHANDLERMODEL_HPP

#include <boost/asio/ip/tcp.hpp>

#include <boost/functional/hash.hpp>

#include <functional>
#include <memory>
#include <unordered_set>

namespace bukhtagram {
namespace ms {
namespace server {
namespace models {

struct ClientConnection {
    std::shared_ptr<boost::asio::ip::tcp::socket> socket;

public:
    ClientConnection(void) = default;
    ClientConnection(const ClientConnection &other);
    bool operator==(const ClientConnection &other) const noexcept;
};

}   // !models;
}   // !server;
}   // !ms;
}   // !bukhtagram;

namespace std {

using namespace bukhtagram::ms::server::models;

template <> struct hash<ClientConnection>
{
    size_t operator()(const ClientConnection &val) const;
};

}   // !std;

namespace bukhtagram {
namespace ms {
namespace server {
namespace models {

class IClientHandlerModel {
public:
    virtual bool add(const ClientConnection &val) = 0;
    virtual bool add(ClientConnection &&val) = 0;

    virtual std::unordered_set<ClientConnection>::const_iterator begin(void) const = 0;
    virtual std::unordered_set<ClientConnection>::const_iterator end(void) const = 0;
};

}   // !models;
}   // !server;
}   // !ms;
}   // !bukhtagram;

#endif  // !BUKHTAGRAM_MESSENGERSERVER_SERVER_MODELS_ICLIENTHANDLERMODEL_HPP;