#ifndef R_TYPE_CLIENT_ACTION_HPP
#define R_TYPE_CLIENT_ACTION_HPP

#include <string>
#include <vector>

#include "./IAction.hpp"
#include "../Encapsulation/GraphicDataTypes.hpp"

extern int action_counter;

class Action : public IAction
{
public:
  enum ActionType
  {
    PREP,
    START,   // ACTION_ID;START;PLAYER;
    RESTART, // ACTION_ID;RESTART;
    TURN,    // ACTION_ID;TURN;PLAYER;X;Y;
    CREATE,  // ACTION_ID;CREATE;ID;TYPE;TYPE_DATA
    // TYPE = CROSS, CIRCLE
    // TYPE_DATA = X;Y;PATH_TO_SPRITE
    INCREASE, // ACTION_ID;INCREASE;ID;TYPE;VALUE
    // TYPE = MOVE, SCOREP1, SCOREP2
    END,               // ACTION_ID;END; OR END;PORT_NB
    JOINLOBBY,         // ACTION_ID;LOBBY_IP;LOBBY_ID;PLAYERNAME
    CREATELOBBY,       // ACTION_ID;LOBBY_IP;PLAYERNAME
    LEAVELOBBY,        // ACTION_ID;LOBBY_IP;PLAYERNAME
    JOINSUCCESSFULL,   // ACTION_ID;
    CREATESUCCESSFULL, // ACTION_ID;
    WIN,               // ACTION_ID;WIN;PLAYER
    DRAW,              // ACTION_ID;DRAW;
    ERROR,
  };
  enum ObjectType
  {
    PLAYERP1,
    PLAYERP2,
    CROSS,
    CIRCLE,
    ERROR_O
  };
  enum IncreaseType
  {
    MOVE,
    SCOREP1,
    SCOREP2,
    ERROR_I
  };

  Action(ActionType type, EntityID id);
  Action(ActionType type, EntityID id, int t_action_id);
  ~Action();

  std::string getCommand() const override;

  virtual std::string getTypeAsString() const;
  int getActionId() const;
  ActionType getType() const;
  EntityID getId() const override;

  bool isTriggeredByUser() const;

  ObjectType getCreateType() const;
  GOM::Vector2f getCreatePosition() const;
  std::string getCreateSpritePath() const;

  IncreaseType getIncreaseType() const;
  int getIncreaseValue() const;

  void setPlayerId(EntityID t_id);

  int getClientId() const;
  void setClientId(int t_client_id);

  void setLobbyId(int t_lobby_id);
  int getLobbyId() const;

  void setPlayerName(std::string t_player_name);
  std::string getPlayerName() const;

  void setLobbyIp(std::string t_lobby_ip);
  std::string getLobbyIp() const;

  void setLobbyPlayerNames(std::vector<std::string> t_lobby_player_names);
  std::vector<std::string> getLobbyPlayerNames() const;

protected:
  int m_action_id;
  ActionType m_type;
  EntityID m_id;

  int m_level = 1;
  bool m_triggered_by_user = false;
  ObjectType m_object_type = ObjectType::ERROR_O;
  GOM::Vector2f m_position = {0, 0};
  std::string m_sprite_path;
  IncreaseType m_increase_type = IncreaseType::ERROR_I;
  int m_value = 0;
  int m_item_type = 0;
  int m_client_id = 0;
  std::string m_player_name = "";
  std::string m_lobby_ip = "";
  std::vector<std::string> m_lobby_player_names;
  int m_lobby_id = 0;
};

#endif // R_TYPE_CLIENT_ACTION_HPP
