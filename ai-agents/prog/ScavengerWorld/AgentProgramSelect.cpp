
#include <ai_agent.h>

#include "Snorlax.h"
#include "Manual.h"
#include "naaWyWy.h"

namespace ai
{
  namespace Agent
  {
    AgentProgram *AgentProgramSelect(Options *opts)
    {
      AgentProgram *agent_program = 0;
      switch(opts->GetArgChr("agent"))
        {
        case 's':
          agent_program = new ai::Sample::Snorlax(opts);
          break;
        case 'm':
          agent_program = new ai::Sample::Manual();
          break;
        case 'w':
          agent_program = new naa::WyWy(opts);
          break;

        default:
          std::cout << "Unknown agent program " << std::endl
                    << "s : Snorlax" << std::endl
                    << "m : Manual" << std::endl
                    << "w : WyWy" << std::endl
      
		    << std::endl;
          exit(1);
          break;
        }
      return agent_program;
    }
  }
}
