#include <ai_agent.h>

namespace ai
{
  namespace Agent
  {
    Agent::Agent()
    {
      sock = NULL;
    }

    Agent::Agent(Socket * sock_in)
    {
      sock = sock_in;
      if(!sock->Send("NAME") || !sock->Recv(name))
	exit(1);
      alive = true;
      trace = false;
      performance = 0;
      environment = 0;
    }
    Agent::~Agent()
    {
      if(sock && !sock->Send("DIE"))
	exit(1);
    }
    bool Agent::IsAlive() const
    {
      return alive;
    }
    void Agent::Kill()
    {
      alive = false;
    }
    Action * Agent::Program(const Percept *percept)
    {
      std::ostringstream oss;
      boost::archive::text_oarchive oa(oss);
      oa << (const ai::Agent::Percept)*percept;
      std::string buffer;
      if(!sock->Send("PERCEPT") || !sock->Send(oss.str()) || !sock->Recv(buffer))
	{
	  std::cout << this    << " socket communication failed.  Terminating agent."  << std::endl;
	  Kill();
	  return NULL;
	}
      
      std::istringstream iss(buffer);
      boost::archive::text_iarchive ia(iss);
      ai::Agent::Action * action;
      ia >> action;
      if(trace)
	{
	  std::cout << this    << " perceives "
		    << percept << " and does "
		    << action  << std::endl;
	}
      return action;
    }
    bool Agent::TextDisplay(std::ostream & os) const
    {
      os << name;
      return true;
    }
    void Agent::Trace()
    {
      trace = true;
    }
    void Agent::NoTrace()
    {
      trace = false;
    }
  
    void Agent::SetPerformance(int value_in)
    {
      performance = value_in;
    }
    void Agent::AddPerformance(int value_in)
    {
      performance += value_in;
    }
    int Agent::GetPerformance() const
    {
      return performance;
    }
    void Agent::SetEnvironment(Environment *env_in)
    {
      environment = env_in;
    }
    Environment * Agent::GetEnvironment() const
    {
      return environment;
    }
    Socket * Agent::GetSocket() const
    {
      return sock;
    }
    
    
    std::ostream & operator<<(std::ostream &os, const Agent * agent)
    {
      agent->TextDisplay(os);
      return os;
    }
  
  }

}
