//
//  naaHunter.h
//  WumpusWorld
//
//  Created by Nate Armstrong on 11/19/14.
//  Copyright (c) 2014 Nate Armstrong. All rights reserved.
//

#ifndef WumpusWorld_naaHunter_h
#define WumpusWorld_naaHunter_h

#include <ai_wumpus.h>
#include <ai_pl.h>

#include "naaKnowledge.h"
#include "naaState.h"

namespace naa {
  class Hunter : public ai::Agent::AgentProgram {
  public:
    Hunter();
    ~Hunter();
    virtual ai::Agent::Action * Program(const ai::Agent::Percept * percept);
    void Visit(int x, int y);
    bool HasVisited(int x, int y);
    MyKnowledgeBase GetKnowledgeBase();
  protected:
    MyKnowledgeBase kb;
    State state;
    bool visited[4][4];
  };
}

#endif
