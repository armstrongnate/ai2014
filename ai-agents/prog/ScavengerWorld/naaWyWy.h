#ifndef _NAAWYWY_H_
#define _NAAWYWY_H_

#include "naaSearchAction.h"
#include "naaSearchState.h"
#include "naaSearchProblem.h"
#include <ai_scavenger.h>
#include <list>

namespace naa
{
  class WyWy : public ai::Agent::AgentProgram
  {
  public:
    WyWy(ai::Agent::Options *opts);
    ~WyWy();
    virtual ai::Agent::Action * Program(const ai::Agent::Percept * percept);
    Model *model;
    std::list<SearchAction> action_queue;
  protected:
  private:
    bool ParcePercepts(const ai::Agent::Percept *percept);
    void SearchForGoal();
  };
}

#endif /* _NAAWYWY_H_ */
