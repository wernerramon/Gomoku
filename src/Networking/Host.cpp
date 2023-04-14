#include "Host.hpp"

Host::Host(boost::asio::io_service &io_service, unsigned short port)
    : acceptor_(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
      socket_(io_service)
{

  do_accept();
}

Host::~Host()
{
  socket_.close();
}

void Host::do_accept()
{
  acceptor_.async_accept(socket_, [this](boost::system::error_code ec)
                         {
      if (!ec) {
        std::make_shared<Session>(std::move(socket_))->start();
      }

      do_accept(); });
}

bool Host::is_connected()
{
  if (socket_.is_open())
    return true;
  return false;
}
