//
//  naaProblem.h
//  WumpusWorld
//
//  Created by Nate Armstrong on 11/19/14.
//  Copyright (c) 2014 Nate Armstrong. All rights reserved.
//

#ifndef __WumpusWorld__naaProblem__
#define __WumpusWorld__naaProblem__

#include <stdio.h>
#include <ai_search.h>

#include "naaHunter.h"

namespace naa {
  class Problem : public ai::Search::Problem {
  public:
    Problem(ai::Search::State *initial_state_in, bool visited[4][4], MyKnowledgeBase *knowledge);
    virtual ~Problem();

    virtual void Display() const;

    virtual bool GoalTest(const ai::Search::State * const state_in) const;
    virtual bool FindSuccessors(const ai::Search::State * const state_in,
                                std::vector<ai::Search::ActionStatePair> &results_out) const;
    virtual double StepCost(const ai::Search::State  * const state1_in,
                            const ai::Search::Action * const action_in,
                            const ai::Search::State  * const state2_in) const;
    virtual double Heuristic(const ai::Search::State  * const state_in) const;

  protected:
    bool visited[4][4];
    MyKnowledgeBase *knowledge;
  private:
  };
}

#endif /* defined(__WumpusWorld__naaProblem__) */
