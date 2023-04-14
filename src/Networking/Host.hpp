/*
** EPITECH PROJECT, 2023
** Gomoku
** File description:
** Host
*/

#ifndef Host_HPP_
#define Host_HPP_

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "Session.hpp"

class Host
{
public:
    Host(boost::asio::io_service &io_service, unsigned short port);
    ~Host();
    bool is_connected();

private:
    void do_accept();

    boost::asio::ip::tcp::acceptor acceptor_;
    boost::asio::ip::tcp::socket socket_;
};

#endif /* !Host_HPP_ */
