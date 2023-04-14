#include "Client.hpp"

Client::Client(boost::asio::io_service &io_service, const std::string &host, unsigned short port)
    : resolver_(io_service), socket_(io_service)
{
    boost::asio::ip::tcp::resolver::query query(host, std::to_string(port));
    resolver_.async_resolve(query, [this](boost::system::error_code ec, boost::asio::ip::tcp::resolver::iterator iterator)
                            {
      if (!ec) {
        do_connect(iterator);
      } });
}

void Client::do_connect(boost::asio::ip::tcp::resolver::iterator iterator)
{
    boost::asio::async_connect(socket_, iterator, [this](boost::system::error_code ec, boost::asio::ip::tcp::resolver::iterator)
                               {
      if (!ec) {
        std::make_shared<Session>(std::move(socket_))->start();
      } });
}
