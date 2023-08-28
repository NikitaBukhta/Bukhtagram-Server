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

#include "IClientHandlerModel.hpp"

namespace bukhtagram {
namespace ms {
namespace server {
namespace models {

ClientConnection::ClientConnection(const ClientConnection &other) {
    this->socket = other.socket;
}

bool ClientConnection::operator==(const ClientConnection &other) const noexcept {
    return this->socket == other.socket;
}

}   // !models;
}   // !server;
}   // !ms;
}   // !bukhtagram;

namespace std {
    using namespace bukhtagram::ms::server::models;
    
    size_t hash<ClientConnection>::operator()(const ClientConnection &val) const
    {
        size_t ret = 0;
        
        boost::hash_combine(ret, val.socket);

        return ret;
    }
}   // !std;