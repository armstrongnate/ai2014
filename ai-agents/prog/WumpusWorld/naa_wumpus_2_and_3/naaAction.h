//
//  naaAction.h
//  WumpusWorld
//
//  Created by Nate Armstrong on 11/19/14.
//  Copyright (c) 2014 Nate Armstrong. All rights reserved.
//

#ifndef __WumpusWorld__naaAction__
#define __WumpusWorld__naaAction__

#include <stdio.h>
#include <ai_search.h>

namespace naa {

  enum { GRAB = 1, SHOOT, TURN_RIGHT, TURN_LEFT, FORWARD, QUIT, YELL, NOOP };

  class Action : public ai::Search::Action {
  public:
    Action();
    Action(const int code_in);
    virtual ~Action();
    virtual void Display() const;

    int code;
  };

}


#endif /* defined(__WumpusWorld__naaAction__) */
