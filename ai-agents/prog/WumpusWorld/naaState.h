//
//  naaState.h
//  WumpusWorld
//
//  Created by Nate Armstrong on 11/19/14.
//  Copyright (c) 2014 Nate Armstrong. All rights reserved.
//

#ifndef __WumpusWorld__naaState__
#define __WumpusWorld__naaState__

#include <stdio.h>
#include <ai_search.h>

enum {
  DIRECTION_NORTH,
  DIRECTION_EAST,
  DIRECTION_SOUTH,
  DIRECTION_WEST
};

namespace naa {
  class State : public ai::Search::State {
  public:
    State();
    State(const double x_in, const double y_in);
    virtual ~State();
    virtual void Display() const;
    virtual bool IsEqual(const ai::Search::State * const state_in) const;
    virtual std::string HashValue() const;
    State *TurnLeft() const;
    State *TurnRight() const;

    int x, y, direction;
  };
}

#endif /* defined(__WumpusWorld__naaState__) */
