#include "NetworkManager.h"

#include <iostream>

//#include <boost/asio.hpp>
//#include <boost/array.hpp>


const uint16_t port = 32789;
const std::string host = "127.0.0.1";

NetworkManager::NetworkManager() //:
//    connectionStatus_(ConnectionStatus::Disconnect)
{

}

void NetworkManager::sendString(const std::string & message)
{
//    boost::asio::io_service ios;
//    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(host), port);
//    boost::asio::ip::tcp::socket socket(ios);
//    socket.connect(endpoint);

//    boost::array<char, 1024> buf;
//    std::copy(message.begin(),message.end(),buf.begin());
//    boost::system::error_code error;
//    socket.write_some(boost::asio::buffer(buf, message.size()), error);

//    socket.close();
}

void NetworkManager::connect()
{

}
