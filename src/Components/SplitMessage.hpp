#ifndef SPLITMESSAGE_HPP_
#define SPLITMESSAGE_HPP_

#include <vector>
#include <string>
#include <boost/asio.hpp>
#include <boost/algorithm/string.hpp>

inline void split_message(const std::string &message, std::vector<std::string> &parts)
{
    boost::split(parts, message, boost::is_any_of(";"));
}

#endif /* !SPLITMESSAGE_HPP_ */
