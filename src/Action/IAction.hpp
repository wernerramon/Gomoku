#ifndef IACTION_HPP
#define IACTION_HPP

#include <string>

typedef unsigned long long EntityID;

extern int action_counter;

class IAction
{
public:
  virtual ~IAction() = default;

  virtual std::string getCommand() const = 0;

  // virtual ActionType getType() const = 0;
  virtual EntityID getId() const = 0;

protected:
  int m_action_id;
  // ActionType m_type;
  EntityID m_id;
};

#endif // IACTION_HPP
