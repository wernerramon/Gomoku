#include "Client.hpp"

Client::Client(boost::asio::io_service &io_service, const std::string &host, unsigned short port)
    : io_service_(io_service), socket_(io_service), host_(host), port_(port),
      board_size_(15), current_player_(1), connected(false), start_game(false)
{
  board_.resize(board_size_, std::vector<int>(board_size_, 0));
  start_connect();
  m_thread = boost::thread([&io_service]()
                           { io_service.run(); });
}

void Client::start_connect()
{
  boost::asio::ip::tcp::resolver resolver(io_service_);
  boost::asio::ip::tcp::resolver::query query(host_, std::to_string(port_));
  boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);

  boost::asio::async_connect(socket_, iterator,
                             [this](const boost::system::error_code &error, boost::asio::ip::tcp::resolver::iterator)
                             {
                               if (!error)
                               {
                                 std::cout << "Client: Connected to host.\n";
                                 connected = true;
                                 start_receive();
                               }
                               else
                               {
                                 std::cerr << "Client: Error connecting to host: " << error.message() << std::endl;
                               }
                             });
}

void Client::start_receive()
{
  boost::asio::async_read_until(socket_, receive_buffer_, '\n',
                                [this](const boost::system::error_code &error, std::size_t bytes_transferred)
                                {
                                  if (!error)
                                  {
                                    std::string message(boost::asio::buffer_cast<const char *>(receive_buffer_.data()), bytes_transferred);
                                    std::cout << "Message received: " << message << std::endl;
                                    receive_buffer_.consume(bytes_transferred);
                                    m_message_queue.push_back(message);
                                    handleMsgQ();
                                    start_receive();
                                  }
                                  else if (error == boost::asio::error::eof)
                                  {
                                    std::cerr << "Client: Connection closed by host." << std::endl;
                                    socket_.close();
                                  }
                                  else
                                  {
                                    std::cerr << "Client: Error receiving message from host: " << error.message() << std::endl;
                                  }
                                });
}

void Client::handleMsgQ()
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

void Client::handle_message(const std::vector<std::string> &message)
{
  std::cout << "Client: received following cmd: " << message[0] << std::endl;
  if (message[0] == "game_setup")
  {
    std::cout << "Client: received game_setup\n";
    handle_game_setup(message);
    start_game = true;
  }
  else if (message[0] == "turn")
  {
    std::cout << "Client: received turn\n";
    handle_turn(message);
  }
  else if (message[0] == "draw")
  {
    std::cout << "Client: received draw\n";
    handle_draw(message);
  }
  else if (message[0] == "win")
  {
    std::cout << "Client: received win\n";
    handle_win(message);
  }
  else if (message[0] == "restart")
  {
    std::cout << "Client: received restart\n";
    handle_restart(message);
  }
  else if (message[0] == "quit")
  {
    std::cout << "Client: received quit\n";
  }
  else if (message[0] == "stats")
  {
    std::cout << "Client: received stats\n";
    handle_stats(message);
  }
}

void Client::send_message(const std::string &message)
{
  std::cout << message << std::endl;
  if (!socket_.is_open())
  {
    std::cerr << "Client: Socket is not open." << std::endl;
    return;
  }
  boost::asio::async_write(socket_, boost::asio::buffer(message),
                           [this, message](const boost::system::error_code &error, std::size_t bytes_transferred)
                           {
                             if (error)
                             {
                               std::cerr << "Client: Error sending message: " << error.message() << std::endl;
                             }
                             else
                             {
                               std::cout << "Client: Sent message: " << message << std::endl;
                             }
                           });
}

bool Client::isConnected() const
{
  return socket_.is_open() && connected;
}

void Client::setCurrentPlayerNb(int t_nb)
{
  current_player_ = t_nb;
}

void Client::setHostSymbol(char t_char)
{
  host_symbol_ = t_char;
}

void Client::setClientSymbol(char t_char)
{
  client_symbol_ = t_char;
}
void Client::setStart(bool t_start)
{
  game_started_ = t_start;
}

void Client::setBoardSize(std::size_t t_size)
{
  board_size_ = t_size;
}

void Client::handle_game_setup(const std::vector<std::string> &message)
{
  std::cout << message.size() << std::endl;
  if (message.size() != 5)
  {
    std::cerr << "Client: Error in game_setup message: wrong number of arguments\n";
    send_message("error\n");
    return;
  }
  startingPlayer_ = std::stoi(message[1]);
  host_symbol_ = message[2][0];
  client_symbol_ = message[3][0];
  board_size_ = std::stoi(message[4]);
  game_started_ = true;
}

std::size_t Client::getBoardSize()
{
  return board_size_;
}

int Client::getSymbolClient()
{
  return client_symbol_;
}

bool Client::getStartingPlayer()
{
  if (startingPlayer_ == 1)
    return true;
  else
    return false;
}

void Client::send_turn(const char t_symbol, const int t_x, const int t_y)
{
  std::stringstream ss;
  ss << "turn;" << t_symbol << ";" << t_x << ";" << t_y << "\n";
  std::string message = ss.str();

  boost::asio::async_write(socket_, boost::asio::buffer(message),
                           [this](const boost::system::error_code &error, std::size_t bytes_transferred)
                           {
                             if (!error)
                             {
                               std::cout << "Client: Sent turn message to host.\n";
                             }
                             else
                             {
                               std::cerr << "Client: Error sending turn message to host: " << error.message() << std::endl;
                             }
                           });
}

void Client::updateBoard(const int t_player_nb, const int t_x, const int t_y)
{
  board_[t_y][t_x] = t_player_nb;
}

std::vector<std::vector<int>> Client::getBoard()
{
  return board_;
}

void Client::handle_turn(const std::vector<std::string> &message)
{
  std::cout << "handle trn\n";
  if (message.size() != 5)
  {
    std::cerr << "Client: Error in game_setup message: wrong number of arguments\n";
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

void Client::handle_draw(const std::vector<std::string> &message)
{
  if (message.size() != 2)
  {
    std::cerr << "Client: Error in game_setup message: wrong number of arguments\n";
    send_message("error\n");
    return;
  }
}

void Client::handle_win(const std::vector<std::string> &message)
{
  if (message.size() != 3)
  {
    std::cerr << "Client: Error in game_setup message: wrong number of arguments\n";
    send_message("error\n");
    return;
  }
  std::string winner = message[1];

  if (winner == "X")
  {
    score_cross++;
  }
  else if (winner == "O")
  {
    score_circ++;
  }
}

void Client::handle_stats(const std::vector<std::string> &message)
{
  if (message.size() != 5)
  {
    std::cerr << "Client: Error in game_setup message: wrong number of arguments\n";
    send_message("error\n");
    return;
  }
  int t_score_cross = std::atoi(message[1].c_str());
  int t_score_circ = std::atoi(message[2].c_str());
  int t_nb_move = std::atoi(message[3].c_str());

  if (t_score_cross != score_cross)
  {
    score_cross = t_score_cross;
  }
  if (t_score_circ != score_circ)
  {
    score_circ = t_score_circ;
  }
  if (t_nb_move != nb_move)
  {
    nb_move = t_nb_move;
  }
}

void Client::handle_restart(const std::vector<std::string> &message)
{
  if (message.size() != 2)
  {
    std::cerr << "Client: Error in game_setup message: wrong number of arguments\n";
    send_message("error\n");
    return;
  }
  board_.resize(board_size_, std::vector<int>(board_size_, 0));
  nb_move = 0;
}