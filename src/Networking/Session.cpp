#include "Session.hpp"

Session::Session(boost::asio::ip::tcp::socket socket) : socket_(std::move(socket))
{
}

void Session::start()
{
    do_read();
}

void Session::send(const std::string &message)
{
    bool write_in_progress = !write_msgs_.empty();
    write_msgs_.push_back(message + "\n");
    if (!write_in_progress)
    {
        do_write();
    }
}

void Session::do_read()
{
    boost::asio::async_read_until(socket_, input_buffer_, '\n', [this, self = shared_from_this()](boost::system::error_code ec, std::size_t bytes_transferred)
                                  {
      if (!ec) {
        // Extract the received message from the input buffer
        std::istream is(&input_buffer_);
        std::string message;
        std::getline(is, message);

        // Process the received message (e.g. interpret it as a game move)
        process_message(message);

        // Read the next message
        do_read();
      } });
}

void Session::do_write()
{
    boost::asio::async_write(socket_, boost::asio::buffer(write_msgs_.front().data(), write_msgs_.front().size()), [this, self = shared_from_this()](boost::system::error_code ec, std::size_t /*bytes_transferred*/)
                             {
      if (!ec) {
        write_msgs_.pop_front();
        if (!write_msgs_.empty()) {
          do_write();
        }
      } });
}

void Session::process_message(const std::string &message)
{
    // Interpret the message as a game move and process it
    // Example: if the message is "E4", interpret it as a move to the E4 position on the game board
    std::cout << "Received move: " << message << std::endl;
    // ...
}