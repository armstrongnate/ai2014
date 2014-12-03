//
//  naaKnowledge.h
//  WumpusWorld
//
//  Created by Nate Armstrong on 11/19/14.
//  Copyright (c) 2014 Nate Armstrong. All rights reserved.
//

#ifndef WumpusWorld_naaKnowledge_h
#define WumpusWorld_naaKnowledge_h

#include <ai_pl.h>
#include <ai_search.h>

namespace naa {
  class MyKnowledgeBase : public ai::PL::KnowledgeBase {
  public:
    MyKnowledgeBase();
    ~MyKnowledgeBase();

    void TellBreeze(int x, int y);
    void TellNoBreeze(int x, int y);
    bool AskPit(int x, int y);

    void TellStench(int x, int y);
    void TellNoStench(int x, int y);
    bool AskWumpus(int x, int y);

    bool AskSafe(const ai::Search::State * const state_in);
  protected:
    void SecureTheBorder();
    void TellPercept(std::string &p, std::string &condition, int x, int y);
  };
}

#endif
