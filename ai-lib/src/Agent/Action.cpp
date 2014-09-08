#include <ai_agent.h>

namespace ai
{
  namespace Agent
  {
    Action::Action()
    {
      action_code = -1;
    }
    Action::~Action()
    {
    }
    int Action::GetCode() const
    {
      return action_code;
    }
    void Action::SetCode(int code_in)
    {
      action_code = code_in;
    }
    
    std::ostream & operator<<(std::ostream &os, const Action * action)
    {
      action->TextDisplay(os);
      return os;
    }
  }
}
