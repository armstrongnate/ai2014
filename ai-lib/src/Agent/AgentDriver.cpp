#include <ai_agent.h>

namespace ai
{
  namespace Agent
  {
    static struct Option options[] = 
      {
	{"agent", 'a', "?", "Agent program"},
	{"host",  'h', "localhost", "Environment hostname or IP address"},
	{"port",  'p', "7777",      "Environment TCP port"},
	{"trace", 't', "1", "Enable/disable tracing"},
	{"user1", 'U', "0", "User variable 1"},
	{"user2", 'V', "0", "User variable 2"},
	{"user3", 'W', "0", "User variable 3"},
	{"user4", 'X', "0", "User variable 4"},
	{"user5", 'Y', "0", "User variable 5"},
	{"user6", 'Z', "0", "User variable 6"},
	{"", 0, "", ""}
      };
    
    AgentDriver::AgentDriver(int argc, char **argv)
    {
      mOptions.AddOptions(options);
      mOptions.Initialize(argc, argv);
      mAgentProgram = AgentProgramSelect(&mOptions);
    }
    
    void AgentDriver::Run()
    {
      if(!mSocket.Connect(mOptions.GetArg("host"),mOptions.GetArgInt("port")))
	exit(1);
      std::cerr << "Connected! Waiting for environment..." << std::endl;
      
      std::string buffer;
      while(1)
	{
	  if(!mAgentProgram)
	    mAgentProgram = AgentProgramSelect(&mOptions);
	  if(!mSocket.Recv(buffer))
	    break;
	  if(buffer == "IDENT")
	    {
	      if(!mSocket.Send("AGENT"))
		break;
	    }
	  else if(buffer == "DIE")
	    {
	      delete mAgentProgram;
	      mAgentProgram = NULL;
	    }
	  else if(buffer == "NAME")
	    {
	      if(!mSocket.Send(mAgentProgram->GetName()))
		break;
	    }
	  else if(buffer == "PERCEPT")
	    {
	      if(!mSocket.Recv(buffer))
		break;
	      std::istringstream iss(buffer);
	      boost::archive::text_iarchive ia(iss);
	      Percept percept;
	      ia >> percept;
	      Action * const action = mAgentProgram->Program(&percept);
	      std::ostringstream oss;
	      boost::archive::text_oarchive oa(oss);
	      oa << action;
	      if(mOptions.GetArgInt("trace"))
		{
		  std::cout << mAgentProgram->GetName() << " perceives "
			    << &percept << " and does "
			    << action << std::endl;
		}
	      delete action;
	      if(!mSocket.Send(oss.str()))
		break;
	    }
	  else
	    {
	      std::cerr << "Unexpected command from environment!" << std::endl;
	      break;
	    }
	}
    }
  }
}
