#ifndef _NAAWYWY_H_
#define _NAAWYWY_H_

#include "naaSearchAction.h"
#include "naaSearchState.h"
#include "naaSearchProblem.h"
#include <ai_scavenger.h>
#include <list>

namespace naa {
  enum {
    ALG_TREE,
    ALG_GRAPH,
  };

  enum {
    FRONTIER_BFS,
    FRONTIER_UCS,
    FRONTIER_DFS,
    FRONTIER_DLS,
  };

  enum {
    MODE_GOAL,
    MODE_BASE,
    MODE_QUIT,
  };

  class WyWy : public ai::Agent::AgentProgram {
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
    int frontier_type;
    int algorithm_type;
    int dls_depth;
    int mode;
  };
}

#endif /* _NAAWYWY_H_ */
