#ifndef ClientNEW_HPP_
#define ClientNEW_HPP_

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/algorithm/string.hpp>
#include <memory>
#include <iostream>
#include "../Components/SplitMessage.hpp"

class Client
{
public:
    Client(boost::asio::io_service &io_service, const std::string &host, unsigned short port);
    bool isConnected() const;
    void setCurrentPlayerNb(int t_nb);
    void setHostSymbol(char t_char);
    void setClientSymbol(char t_char);
    void setStart(bool t_start);
    void setBoardSize(std::size_t t_size);
    void start_connect();
    void start_receive();
    void handle_message(const std::vector<std::string> &message);
    void send_message(const std::string &message);
    void handle_game_setup(const std::vector<std::string> &message);

    std::size_t getBoardSize();
    int getSymbolClient();
    bool getStartingPlayer();

    void send_turn(const char t_symbol, const int t_x, const int t_y);
    void updateBoard(const int t_player_nb, const int t_x, const int t_y);
    std::vector<std::vector<int>> getBoard();

    void handle_turn(const std::vector<std::string> &message);
    void handle_draw(const std::vector<std::string> &message);
    void handle_win(const std::vector<std::string> &message);
    void handle_restart(const std::vector<std::string> &message);
    void handle_quit(const std::vector<std::string> &message);
    void handle_stats(const std::vector<std::string> &message);

    int getScoreCross() { return score_cross; };
    int getScoreCirc() { return score_circ; };
    int getNbMoves() { return nb_move; };
    bool getStartGame() { return start_game; };
    void handleMsgQ();

private:
    boost::asio::io_service &io_service_;
    boost::asio::ip::tcp::socket socket_;
    std::vector<std::vector<int>> board_;
    std::size_t board_size_;
    int current_player_;
    char host_symbol_;
    char client_symbol_;
    bool game_started_;
    int startingPlayer_;
    int score_cross;
    int score_circ;
    int nb_move;
    bool connected;
    bool start_game;
    boost::asio::streambuf receive_buffer_;
    std::deque<std::string> m_message_queue;
    boost::thread m_thread;
    std::string host_;
    unsigned short port_;
};

#endif /* !ClientNEW_HPP_ */
