#include "ai_search.h"
#include <iostream>

namespace ai
{
  namespace Search
  {
    /*
     * PROBLEM CLASS
     */
    
    Problem::Problem(State *initial_state_in)
    {
      initial_state = initial_state_in;
    }
    
    Problem::~Problem()
    {
    }
    
    State *Problem::GetInitialState()
    {
      return initial_state;
    }
    
    void   Problem::Display() const
    {
      std::cout << "Problem Display" << std::endl;
    }
    
    double Problem::Heuristic(const State  * const state_in) const
    {
      return 0.0;
    }
    
  }
} /* ai */
