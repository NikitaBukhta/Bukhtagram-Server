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

#include "ClientHandlerModel.hpp"

namespace bukhtagram {
namespace ms {
namespace server {
namespace models {

/*
 * ClientHandlerModel method realization starts;
 */

bool ClientHandlerModel::add(const ClientConnection &val) {
    return m_client_connection_set.insert(val).second;
}

bool ClientHandlerModel::add(ClientConnection &&val) {
    return m_client_connection_set.insert(std::move(val)).second;
}

std::unordered_set<ClientConnection>::const_iterator ClientHandlerModel::begin(void) const {
    return std::begin(m_client_connection_set);
}

std::unordered_set<ClientConnection>::const_iterator ClientHandlerModel::end(void) const {
    return std::end(m_client_connection_set);
}

/*
 * ClientHandlerModel method realization ends;
 */

}   // !models;
}   // !server;
}   // !ms;
}   // !bukhtagram;