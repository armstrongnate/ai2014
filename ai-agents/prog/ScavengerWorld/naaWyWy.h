#ifndef _NAAWYWY_H_
#define _NAAWYWY_H_

#include "naaModel.h"
#include <ai_scavenger.h>

namespace naa
{
  class WyWy : public ai::Agent::AgentProgram
  {
  public:
    WyWy(ai::Agent::Options *opts);
    ~WyWy();
    virtual ai::Agent::Action * Program(const ai::Agent::Percept * percept);
    Model *model;
  protected:
  private:
  };
}

#endif /* _NAAWYWY_H_ */
