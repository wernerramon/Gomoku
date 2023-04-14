#include "./Action.hpp"
#include <iostream>

Action::Action(ActionType type, EntityID id) : m_type(type), m_id(id)
{
  m_action_id = action_counter++;
}

Action::Action(ActionType type, EntityID id, int t_action_id)
    : m_type(type), m_id(id)
{
  m_action_id = t_action_id;
}

Action::~Action() {}

std::string Action::getTypeAsString() const
{
  switch (m_type)
  {
  case ActionType::PREP:
    return "PREP";
  case ActionType::START:
    return "START";
  case ActionType::RESTART:
    return "RESTART";
  case ActionType::TURN:
    return "TURN";
  case ActionType::CREATE:
    return "CREATE";
  case ActionType::INCREASE:
    return "INCREASE";
  case ActionType::END:
    return "END";
  case ActionType::CREATELOBBY:
    return "CREATELOBBY";
  case ActionType::CREATESUCCESSFULL:
    return "CREATESUCCESSFULL";
  case ActionType::JOINLOBBY:
    return "JOINLOBBY";
  case ActionType::JOINSUCCESSFULL:
    return "JOINSUCCESSFULL";
  case ActionType::WIN:
    return "WIN";
  case ActionType::DRAW:
    return "DRAW";
  case ActionType::ERROR:
    return "ERROR";
  }
  return "ERROR";
}

std::string Action::getCommand() const
{
  std::string type_string = getTypeAsString();
  std::string data = "";
  std::string names = "";
  std::string leaderboardline = "";
  std::string lobby_code = "";

  switch (m_type)
  {
  case ActionType::PREP:
    if (m_lobby_ip != "")
    {
      lobby_code = m_lobby_ip;
    }
    return std::to_string(m_action_id) + ";" + type_string + ";" +
           std::to_string(m_id) + ";" + lobby_code + ";" +
           std::to_string(m_client_id) + ";" + m_player_name + ";";
  case ActionType::START:
    return std::to_string(m_action_id) + ";" + type_string + ";" +
           std::to_string(m_client_id) + ";";
  case ActionType::END:
    return std::to_string(m_action_id) + ";" + type_string + ";" +
           std::to_string(m_id) + ";";
  case ActionType::RESTART:
    return std::to_string(m_action_id) + ";" + type_string + ";" +
           std::to_string(m_id) + ";" + std::to_string(m_triggered_by_user) +
           ";";
  case ActionType::TURN:
    return std::to_string(m_action_id) + ";" + type_string + ";" +
           std::to_string(m_id) + ";" + std::to_string(m_position.x) + ";" +
           std::to_string(m_position.y) + ";";
  case ActionType::INCREASE:
    return std::to_string(m_action_id) + ";INCREASE;" + std::to_string(m_id) +
           ";" + std::to_string(m_increase_type) + ";" +
           std::to_string(m_value) + ";";
  case ActionType::CREATELOBBY:
    return std::to_string(m_action_id) + ";CREATELOBBY;" +
           std::to_string(m_id) + ";" + m_lobby_ip + ";" + m_player_name +
           ";";
  case ActionType::LEAVELOBBY:
    return std::to_string(m_action_id) + ";LEAVELOBBY;" +
           std::to_string(m_id) + ";" + m_lobby_ip + ";" + m_player_name +
           ";";
  case ActionType::JOINLOBBY:
    return std::to_string(m_action_id) + ";JOINLOBBY;" +
           std::to_string(m_id) + ";" + m_lobby_ip + ";" + m_player_name +
           ";";
  case ActionType::JOINSUCCESSFULL:
    for (int i = 0; i < m_lobby_player_names.size(); i++)
    {
      names += m_lobby_player_names[i];
      names += ";";
    }
    return std::to_string(m_action_id) + ";JOINSUCCESSFULL;" +
           std::to_string(m_id) + ";" + names;
  case ActionType::CREATESUCCESSFULL:
    return std::to_string(m_action_id) + ";CREATESUCCESSFULL;" +
           std::to_string(m_id) + ";";
  case ActionType::WIN:
    return std::to_string(m_action_id) + ";WIN;" + std::to_string(m_client_id) + ";";
  case ActionType::DRAW:
    return std::to_string(m_action_id) + ";DRAW;";
  }
  return std::to_string(m_action_id) + ";" + type_string + ";" +
         std::to_string(m_id) + ";";
}

int Action::getActionId() const { return m_action_id; }
Action::ActionType Action::getType() const { return m_type; }
EntityID Action::getId() const { return m_id; }

bool Action::isTriggeredByUser() const { return m_triggered_by_user; }

Action::ObjectType Action::getCreateType() const { return m_object_type; }

GOM::Vector2f Action::getCreatePosition() const { return m_position; }

std::string Action::getCreateSpritePath() const { return m_sprite_path; }

Action::IncreaseType Action::getIncreaseType() const { return m_increase_type; }

int Action::getIncreaseValue() const { return m_value; }

void Action::setPlayerId(EntityID t_id) { m_id = t_id; }

int Action::getClientId() const { return m_client_id; }

void Action::setClientId(int t_client_id) { m_client_id = t_client_id; }

void Action::setLobbyId(int t_lobby_id) { m_lobby_id = t_lobby_id; }

int Action::getLobbyId() const { return m_lobby_id; }

void Action::setPlayerName(std::string t_player_name)
{
  m_player_name = t_player_name;
}

std::string Action::getPlayerName() const { return m_player_name; }

void Action::setLobbyIp(std::string t_lobby_ip) { m_lobby_ip = t_lobby_ip; }

std::string Action::getLobbyIp() const { return m_lobby_ip; }

void Action::setLobbyPlayerNames(
    std::vector<std::string> t_lobby_player_names)
{
  m_lobby_player_names = t_lobby_player_names;
}

std::vector<std::string> Action::getLobbyPlayerNames() const
{
  return m_lobby_player_names;
}
