#include "ai_search.h"

namespace ai
{
  namespace Search
  {
    Tree::Tree(Problem *problem_in, Fringe *fringe_in)
      : Algorithm(problem_in, fringe_in)
    {
    }
		
    Tree::~Tree()
    {
    }
		
    bool Tree::Search()
    {
      if(!SearchInit())
	{
	  return false;
	}
      return SearchNext();
    }
    
    bool Tree::SearchInit()
    {
      if(root)
	{
	  delete root;
	  root   = 0;
	}
      root = new Node(problem->GetInitialState(), 0, 0, 0.0, problem->Heuristic(problem->GetInitialState()), 0);
      fringe->Insert(root);
      return true;
    }
    
    bool Tree::SearchNext()
    {
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
	      if(! fringe->Insert(new_node) )
		{ // depth limited stack is full
		  delete new_node;
		}
	      else
		{
		  node->AddChild(new_node);
		}
	    }
	  if(max_nodes_stored < fringe->Size())
	    {
	      max_nodes_stored = fringe->Size();
	    }
	  if((successors.size() == 0 ||
	      node->GetChildCount() == 0) &&
	     (node->GetParent() != 0))
	    {
	      /* This node is a leaf, don't keep it in RAM */
	      delete node;
	    }
	}
      return false;
    }
  }
}
