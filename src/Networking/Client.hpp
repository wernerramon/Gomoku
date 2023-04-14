#ifndef ClientNEW_HPP_
#define ClientNEW_HPP_

#include <boost/asio.hpp>
#include <memory>
#include "Session.hpp"

class Client
{
public:
    Client(boost::asio::io_service &io_service, const std::string &host, unsigned short port);

private:
    void do_connect(boost::asio::ip::tcp::resolver::iterator iterator);

    boost::asio::ip::tcp::resolver resolver_;
    boost::asio::ip::tcp::socket socket_;
};

#endif /* !ClientNEW_HPP_ */
