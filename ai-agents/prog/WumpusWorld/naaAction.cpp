//
//  naaAction.cpp
//  WumpusWorld
//
//  Created by Nate Armstrong on 11/19/14.
//  Copyright (c) 2014 Nate Armstrong. All rights reserved.
//

#include "naaAction.h"

namespace naa {

  Action::Action() : code(NOOP) {}
  Action::Action(const int code_in) : code(code_in) {}
  Action::~Action() {}
  void Action::Display() const {}

}