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

#include <unordered_set>

#ifndef BUKHTAGRAM_MESSENGERSERVER_SERVER_MODELS_CLIENTHANDLERMODEL_HPP
#define BUKHTAGRAM_MESSENGERSERVER_SERVER_MODELS_CLIENTHANDLERMODEL_HPP

namespace bukhtagram {
namespace ms {
namespace server {
namespace models {

class ClientHandlerModel : public IClientHandlerModel{
public:
    bool add(const ClientConnection &val);
    bool add(ClientConnection &&val);

    std::unordered_set<ClientConnection>::const_iterator begin(void) const;
    std::unordered_set<ClientConnection>::const_iterator end(void) const;

private:
    std::unordered_set<ClientConnection> m_client_connection_set;

};

}   // !models;
}   // !server;
}   // !ms;
}   // !bukhtagram;

#endif  // !BUKHTAGRAM_MESSENGERSERVER_SERVER_MODELS_CLIENTHANDLERMODEL_HPP;