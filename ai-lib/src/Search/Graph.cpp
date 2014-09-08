#include "ai_search.h"

namespace ai
{
  namespace Search
  {
    Graph::Graph(Problem *problem_in, Fringe *fringe_in)
      : Algorithm(problem_in, fringe_in)
    {
    }
		
    Graph::~Graph()
    {
    }
		
    bool Graph::Search()
    {
      number_nodes_generated = 0;
      max_nodes_stored       = 0;
      
      root = new Node(problem->GetInitialState(), 0, 0, 0.0, problem->Heuristic(problem->GetInitialState()), 0);
      fringe->Insert(root);
      closed.Clear();
      
      while(!fringe->Empty() &&
	    (generation_limit == 0 || generation_limit > number_nodes_generated) &&
	    (store_limit == 0 || store_limit > max_nodes_stored)
	    )
	{
	  Node *node = fringe->Remove();
	  if(problem->GoalTest(node->GetState()))
	    {
	      solution.SetFromNode(node);
	      return true;
	    }
	  if(!closed.Contains(node))
	    {
	      closed.Insert(node);
	      std::vector<ActionStatePair> successors;
	      problem->FindSuccessors(node->GetState(), successors);
	      std::vector<ActionStatePair>::iterator i;
				
	      number_nodes_generated += successors.size();
				
	      for(i = successors.begin(); i != successors.end(); i++)
		{
		  Node *new_node = new Node(i->GetState(),
					    node,
					    i->GetAction(),
					    (node->GetPathCost() +
					     problem->StepCost(node->GetState(), i->GetAction(), i->GetState())),
					    problem->Heuristic(i->GetState()),
					    (node->GetDepth() + 1)
					    );
		  node->AddChild(new_node);
		  fringe->Insert(new_node);
		}
	      /* Graph doesn't forget anything */
	      /* STILL NOT CORRECT. y11m09d15 - CGL */
	      max_nodes_stored += successors.size();
	      /*
	      if(max_nodes_stored < fringe->Size())
		{
		  max_nodes_stored = fringe->Size();
		}
	      if(max_nodes_stored < closed.Size())
		{
		  max_nodes_stored = closed.Size();
		}
	      */
	    }
	}
      return false;
    }
		
  }
}
