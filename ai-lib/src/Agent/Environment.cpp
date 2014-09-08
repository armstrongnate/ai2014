#include <ai_agent.h>
#ifdef WIN32
#include <windows.h>
#define sleep(x) Sleep(x*1000);
#else
#include <unistd.h>
#endif

namespace ai
{
  namespace Agent
  {
    Environment::Environment()
    {
      displays = NULL;
    }

    Environment::Environment(const RandomNumber &rand_in, std::vector<Socket *> *displays_in)
      : random_number(rand_in)
    {
      objects.resize(0,0);
      agents.resize(0,0);
      delay = 0;
      displays = displays_in;
    }
    Environment::~Environment()
    {
      unsigned int i;
      for(i = 0; i < objects.size(); i++)
	{
	  delete objects[i];
	}
      for(i = 0; i < agents.size(); i++)
	{
	  delete agents[i];
	}
      if(displays)
	{
	  for(std::vector<Socket *>::iterator i = displays->begin(); i != displays->end(); i++)
	    {
	      if(!(*i)->Send("DIE"))
		{
		  delete (*i);
		  displays->erase(i--);
		}
	    }
	}
    }
    Percept *Environment::GetPercept(Agent *agent)
    {
      Percept *percept = new Percept();
      unsigned int i;
    
      Percept *p = agent->GetPercept(agent->GetLocation());
      percept->Join(p);
      delete p;
    
      for(i = 0; i < objects.size(); i++)
	{
	  p = objects[i]->GetPercept(agent->GetLocation());
	  percept->Join(p);
	  delete p;
	}
      return percept;
    }
    bool Environment::IsDone() const
    {
      unsigned int i;
      for(i = 0; i < agents.size(); i++)
	{
	  if(agents[i]->IsAlive()) { return false; }
	}
      return true;
    }
    void Environment::Step()
    {
      std::vector<Action *> actions(0);
      unsigned int i;
      for(i = 0; i < agents.size(); i++)
	{
	  Percept *percept = GetPercept(agents[i]);
	  Action  *action  = agents[i]->Program(percept);
	  if(action)
	    {
	      actions.push_back(action);
	    }
	  delete percept;
	}
      for(i = 0; i < agents.size(); i++)
	{
	  ApplyAction(agents[i], actions[i]);
	}
      for(i = 0; i < agents.size(); i++)
	{
	  delete actions[i];
	}
      for(i = 0; i < agents.size(); i++)
	{
	  CalculatePerformance(agents[i]);
	}
      UpdateDisplays();
    } 
    void Environment::Run(const int n_steps)
    {
      int t;
      unsigned int i;
      for(i = 0; i < agents.size(); i++)
	{
	  agents[i]->SetPerformance(0);
	}
      UpdateDisplays();
      if(delay)
	{
	  sleep(delay);
	}
      for(t = 0; t < n_steps; t++)
	{
	  if(IsDone())
	    {
	      return;
	    }
	  Step();
	  if(delay)
	    {
	      sleep(delay);
	    }
	}
    }
    void Environment::AddAgent(Agent *agent, Location *location)
    {
      if(location)
	{
	  agent->SetLocation(location);
	}
      else
	{
	  agent->SetLocation(DefaultLocation());
	}
      agent->SetEnvironment(this);
      agents.push_back(agent);
    }
    void Environment::AddObject(Object *object, Location *location)
    {
      if(location)
	{
	  object->SetLocation(location);
	}
      else
	{
	  object->SetLocation(DefaultLocation());
	}
      objects.push_back(object);
    }
    void Environment::UpdateDisplays()
    {
      if(displays->size() <= 0)
        {
          return;
        }
      std::ostringstream oss;
      boost::archive::text_oarchive oa(oss);
      oa << this;
      for(std::vector<Socket *>::iterator i = displays->begin(); i != displays->end(); i++)
	{
	  if(!(*i)->Send("REDRAW") || !(*i)->Send(oss.str()))
	    {
	      delete (*i);
	      displays->erase(i--);
	    }
	}
    }
    void Environment::SetDelay(int delay_in)
    {
      delay = delay_in;
    }
    int Environment::GetPerformance(Agent *agent)
    {
      return agent->GetPerformance();
    }
    Agent * Environment::GetAgent(int agent_index)
    {
      return agents[agent_index];
    }
    const RandomNumber &Environment::GetRandomNumber() const
    {
      return random_number;
    }

  }
}
