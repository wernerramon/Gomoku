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
#include <boost/thread.hpp>
#include <boost/algorithm/string.hpp>
#include "../Components/SplitMessage.hpp"

class Host
{
public:
    Host(boost::asio::io_service &io_service, unsigned short port);
    bool isReady() const;
    void setCurrentPlayerNb(int t_nb);
    void setHostSymbol(char t_char);
    void setClientSymbol(char t_char);
    void setStart(bool t_start);
    void setBoardSize(std::size_t t_size);
    void handle_accept();
    void start_receive();
    void handle_message(const std::vector<std::string> &message);
    void send_message(const std::string &message);
    void start_accept();
    void send_game_setup(const int starting_player, const char player_symbol_host, const char player_symbol_client, const unsigned int board_size);
    bool getStartingPlayer();
    void send_turn(const char t_symbol, const int t_x, const int t_y);
    void updateBoard(const int t_player_nb, const int t_x, const int t_y);
    std::vector<std::vector<int>> getBoard();
    void send_win(const char t_symbol);
    void send_draw();
    void send_restart();
    void send_stats(const int t_score_cross, const int t_score_circ, const int t_nb_turn);

    void handle_quit(const std::vector<std::string> &message);
    void handle_turn(const std::vector<std::string> &message);

    int getScoreCross() { return score_cross; };
    int getScoreCirc() { return score_circ; };
    int getNbMoves() { return nb_move; };
    void handleMsgQ();
    bool getGameStarted() { return game_started_; };

private:
    boost::asio::ip::tcp::acceptor acceptor_;
    boost::asio::ip::tcp::socket socket_;
    std::vector<std::vector<int>> board_;
    boost::asio::io_service m_io_service;
    std::size_t board_size_;
    int current_player_;
    char host_symbol_;
    char client_symbol_;
    bool game_started_;
    bool client_connected_;
    int starting_player_;
    int score_cross;
    int score_circ;
    int nb_move;
    boost::asio::streambuf receive_buffer_;
    std::deque<std::string> m_message_queue;
    boost::thread m_thread;
};

#endif /* !Host_HPP_ */
