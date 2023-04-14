#ifndef Session_HPP_
#define Session_HPP_

#include <boost/asio.hpp>
#include <deque>
#include <iostream>
#include <string>

class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(boost::asio::ip::tcp::socket socket);

    void start();

    void send(const std::string &message);

private:
    void do_read();

    void do_write();

    void process_message(const std::string &message);

    boost::asio::ip::tcp::socket socket_;
    boost::asio::streambuf input_buffer_;
    std::deque<std::string> write_msgs_;
};

#endif /* !Session_HPP_ */
