#include "ai_local_search.h"

namespace ai
{
  namespace LocalSearch
  {
    HillClimbing::HillClimbing(Problem *problem_in)
      : Algorithm(problem_in)
    {
    }
    HillClimbing::~HillClimbing()
    {
    }
    bool HillClimbing::Search()
    {
      State *state = this->problem->RandomState();
      this->states_generated++;
      double current_value  = state->Value();
			
      State *best_state = this->problem->BestNeighbor(state);
      this->states_generated++;
      double best_value = best_state->Value();
	  
      while(best_value > current_value)
	{
	  delete state;
	  state = best_state;
	  current_value = best_value;
		  
	  best_state = this->problem->BestNeighbor(state);
	  this->states_generated++;
	  best_value = best_state->Value();
	}
      if(!this->solution)
	{
	  this->solution = state;
	}
      else
	{
	  if(this->solution->Value() < state->Value())
	    {
	      delete this->solution;
	      this->solution = state;
	    }
	  else
	    {
	      delete state;
	    }
	}
      delete best_state;
      return true;
    }
  }
}
