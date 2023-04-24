#include "Host.hpp"

Host::Host(boost::asio::io_service &io_service, unsigned short port)
    : acceptor_(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
      socket_(io_service), board_size_(15), current_player_(1)
{
  game_started_ = false;
  board_.resize(board_size_, std::vector<int>(board_size_, 0));
  start_accept();
  m_thread = boost::thread([&io_service]()
                           { io_service.run(); });
}

void Host::handle_accept()
{
  std::cout << "Host: Client connected.\n";
  client_connected_ = true;
  start_receive();
}

void Host::start_receive()
{
  if (!socket_.is_open())
  {
    std::cerr << "Host: Socket is not open." << std::endl;
    return;
  }
  boost::asio::async_read_until(socket_, receive_buffer_, '\n',
                                [this](const boost::system::error_code &error, std::size_t bytes_transferred)
                                {
                                  if (!error)
                                  {
                                    std::string message(boost::asio::buffer_cast<const char *>(receive_buffer_.data()), bytes_transferred);
                                    receive_buffer_.consume(bytes_transferred);
                                    m_message_queue.push_back(message);
                                    std::cout << "Host: Received message: " << message << std::endl;
                                    handleMsgQ();
                                    start_receive();
                                  }
                                  else if (error == boost::asio::error::eof)
                                  {
                                    std::cerr << "Host: Connection closed by client." << std::endl;
                                    socket_.close();
                                  }
                                  else
                                  {
                                    std::cerr << "Host: Error receiving message from client: " << error.message() << std::endl;
                                  }
                                });
}

void Host::handleMsgQ()
{
  while (!m_message_queue.empty())
  {
    std::string message = m_message_queue.front();
    m_message_queue.pop_front();
    std::vector<std::string> parts;
    split_message(message, parts);
    handle_message(parts);
  }
}

void Host::handle_message(const std::vector<std::string> &message)
{
  if (message[0] == "ok" && game_started_ == false)
  {
    std::cout << "handle ok\n";
    game_started_ = true;
  }
  else if (message[0] == "turn")
  {
    handle_turn(message);
  }
  else if (message[0] == "quit")
  {
  }
}

void Host::send_message(const std::string &message)
{
  std::cout << "Host send message\n";
  boost::asio::write(socket_, boost::asio::buffer(message));
}

bool Host::isReady() const
{
  return socket_.is_open();
}

void Host::setCurrentPlayerNb(int t_nb)
{
  current_player_ = t_nb;
}

void Host::setHostSymbol(char t_char)
{
  host_symbol_ = t_char;
}

void Host::setClientSymbol(char t_char)
{
  client_symbol_ = t_char;
}
void Host::setStart(bool t_start)
{
  game_started_ = t_start;
}

void Host::setBoardSize(std::size_t t_size)
{
  board_size_ = t_size;
}

void Host::start_accept()
{
  std::cout << "Host: Waiting for client to connect...\n";

  acceptor_.async_accept(socket_,
                         [this](boost::system::error_code ec)
                         {
                           if (!ec)
                           {
                             std::cout << "Host: Client connected.\n";
                             client_connected_ = true;
                             start_receive();
                           }
                           else
                           {
                             std::cerr << "Host: Error accepting connection: " << ec.message() << "\n";
                             boost::asio::steady_timer timer(acceptor_.get_executor(), std::chrono::seconds(1));
                             timer.async_wait([this](const boost::system::error_code &ec)
                                              {
          if (!ec)
          {
            start_accept();
          } });
                           }
                         });
}

void Host::send_game_setup(const int starting_player, const char player_symbol_host, const char player_symbol_client, const unsigned int board_size)
{
  starting_player_ = starting_player;
  std::stringstream ss;
  ss << "game_setup;" << starting_player << ";" << player_symbol_host << ";" << player_symbol_client << ";" << board_size << "\n";
  std::string message = ss.str();

  boost::system::error_code error;
  boost::asio::write(socket_, boost::asio::buffer(message), error);

  if (!error)
  {
    std::cout << "Host: Sent game setup message to client.\n";
  }
  else
  {
    std::cerr << "Host: Error sending game setup message to client: " << error.message() << std::endl;
  }
}

bool Host::getStartingPlayer()
{
  if (starting_player_ == 1)
    return true;
  else
    return false;
}

void Host::send_turn(const char t_symbol, const int t_x, const int t_y)
{
  std::stringstream ss;
  ss << "turn;" << t_symbol << ";" << t_x << ";" << t_y << "\n";
  std::string message = ss.str();

  boost::system::error_code error;
  boost::asio::write(socket_, boost::asio::buffer(message), error);

  if (!error)
  {
    std::cout << "Host: Sent turn message to client.\n";
  }
  else
  {
    std::cerr << "Host: Error sending turn message to client: " << error.message() << std::endl;
  }
}

void Host::updateBoard(const int t_player_nb, const int t_x, const int t_y)
{
  board_[t_y][t_x] = t_player_nb;
}

std::vector<std::vector<int>> Host::getBoard()
{
  return board_;
}

void Host::send_win(const char t_symbol)
{
  std::stringstream ss;
  ss << "win;" << t_symbol << "\n";
  std::string message = ss.str();

  boost::system::error_code error;
  boost::asio::write(socket_, boost::asio::buffer(message), error);

  if (!error)
  {
    std::cout << "Host: Sent win message to client.\n";
  }
  else
  {
    std::cerr << "Host: Error sending win message to client: " << error.message() << std::endl;
  }
}

void Host::send_draw()
{
  std::stringstream ss;
  ss << "draw\n";
  std::string message = ss.str();

  boost::system::error_code error;
  boost::asio::write(socket_, boost::asio::buffer(message), error);

  if (!error)
  {
    std::cout << "Host: Sent draw message to client.\n";
  }
  else
  {
    std::cerr << "Host: Error sending draw message to client: " << error.message() << std::endl;
  }
}

void Host::send_stats(const int t_score_cross, const int t_score_circ, const int t_nb_turn)
{
  std::stringstream ss;
  ss << "stats;" << t_score_cross << ";" << t_score_circ << ";" << t_nb_turn << "\n";
  std::string message = ss.str();

  boost::system::error_code error;
  boost::asio::write(socket_, boost::asio::buffer(message), error);

  if (!error)
  {
    std::cout << "Host: Sent stats message to client.\n";
  }
  else
  {
    std::cerr << "Host: Error sending stats message to client: " << error.message() << std::endl;
  }
}

void Host::send_restart()
{
  std::stringstream ss;
  ss << "restart\n";
  std::string message = ss.str();

  boost::system::error_code error;
  boost::asio::write(socket_, boost::asio::buffer(message), error);

  if (!error)
  {
    std::cout << "Host: Sent draw message to client.\n";
  }
  else
  {
    std::cerr << "Host: Error sending draw message to client: " << error.message() << std::endl;
  }
}

void Host::handle_turn(const std::vector<std::string> &message)
{
  if (message.size() != 4)
  {
    std::cerr << "Host: Error in turn message: wrong number of arguments\n";
    send_message("error\n");
    return;
  }
  std::string player = message[1];
  int posx = std::atoi(message[2].c_str());
  int posy = std::atoi(message[3].c_str());

  if (player == "X")
    updateBoard(1, posx, posy);
  else
    updateBoard(2, posx, posy);
}