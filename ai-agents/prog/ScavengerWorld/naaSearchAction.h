#include "ai_search.h"

namespace naa {
  enum {
    ACTION_NONE,
    ACTION_MOVE_NORTH,
    ACTION_MOVE_SOUTH,
    ACTION_MOVE_EAST,
    ACTION_MOVE_WEST,
    ACTION_MAX,
  };

  class SearchAction : public ai::Search::Action {
    public:
      SearchAction();
      SearchAction(const int action_code_in);
      virtual ~SearchAction();
      virtual void Display() const;
      int GetActionCode() const;
      bool SetActionCode(const int action_code_in);
    protected:
      int action_code;
    private:
  };
}
