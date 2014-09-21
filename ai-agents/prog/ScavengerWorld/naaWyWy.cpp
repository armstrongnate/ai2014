#include "naaWyWy.h"
#include <cstdio>
#include <cstring>

namespace naa
{
        /* For more on options look at the files:
   * ai-lib/include/Agent/Options.h
   * ai-lib/src/Agent/Options.cpp
   * al-lib/src/Agent/AgentDriver.cpp
   */
        /*
   * Run with:
   * ./RunProg ./SA_Test -a s -U 1
   */
  WyWy::WyWy(ai::Agent::Options *opts)
  {
    SetName("WyWy");
    std::cout << "The value of the -U option is: " << opts->GetArgInt("user1") << std::endl;
    model = new Model();
  }

  WyWy::~WyWy()
  {
  }

  ai::Agent::Action * WyWy::Program(const ai::Agent::Percept * percept)
  {
    ai::Scavenger::Action *action = new ai::Scavenger::Action;
    unsigned int i;

    /* position */
    Location loc;
    loc.x = atof(percept->GetAtom("X_LOC").GetValue().c_str());
    loc.y = atof(percept->GetAtom("Y_LOC").GetValue().c_str());
    loc.z = atof(percept->GetAtom("Z_LOC").GetValue().c_str());
    model->SetLocation(loc);

    /* goal */
    static bool first = true;
    double x, y, z;
    Location goalLoc;
    const char *v;
    char *values, *s;
    if (first) {
      v = percept->GetAtom("GOAL_LOC").GetValue().c_str();
      values = new char[std::strlen(v) + 1];
      std::strcpy(values, v);
      s = std::strtok(values, ","); std::sscanf(s, "%lf", &x);
      s = std::strtok(NULL, ","); std::sscanf(s, "%lf", &y);
      s = std::strtok(NULL, ","); std::sscanf(s, "%lf", &z);
      goalLoc.x = x; goalLoc.y = y; goalLoc.z = z;
      model->SetGoalLocation(goalLoc);
    }
    first = false;

    /* cells */
    static bool cellsFirst = true;
    for (i = 0; i < percept->NumAtom() && cellsFirst; i++) {
      ai::Agent::PerceptAtom a = percept->GetAtom(i);
      if (std::strncmp(a.GetName().c_str(), "CELL_", 5) == 0) {
        int id;
        double x,y,z;

        std::sscanf(a.GetName().c_str(), "CELL_%d", &id);
        const char *v = a.GetValue().c_str();
        char *values = new char[std::strlen(v) + 1];
        std::strcpy(values, v);
        char *s = std::strtok(values, ",");
        std::sscanf(s, "%lf", &x);
        s = std::strtok(NULL, ",");
        std::sscanf(s, "%lf", &y);
        s = std::strtok(NULL, ",");
        std::sscanf(s, "%lf", &z);
        char *north = std::strtok(NULL, ",");
        char *south = std::strtok(NULL, ",");
        char *east  = std::strtok(NULL, ",");
        char *west  = std::strtok(NULL, ",");
        Location loc;
        loc.x = x;
        loc.y = y;
        loc.z = z;
        Border border;
        border.north = Model::InterfaceStringToInt(north);
        border.south = Model::InterfaceStringToInt(south);
        border.east = Model::InterfaceStringToInt(east);
        border.west = Model::InterfaceStringToInt(west);
        model->AddCell(id, loc, border);
        delete [] values;
      } else {
        std::cout << a.GetName() << ": " << a.GetValue() << std::endl;
      }
      first = false;
    }

#if 0

    double x, y, z;

    x = atof(percept->GetAtom("X_LOC").GetValue().c_str());
    y = atof(percept->GetAtom("Y_LOC").GetValue().c_str());
    z = atof(percept->GetAtom("Z_LOC").GetValue().c_str());

    std::cout << x << ", " << y << ", " << z << std::endl;
#endif

    {
      int r = rand() % 2;
      int d = rand() % 4;
      if(r == 0)
      {
        switch(d)
        {
        case 0:
          action->SetCode(ai::Scavenger::Action::GO_NORTH);
          break;
        case 1:
          action->SetCode(ai::Scavenger::Action::GO_SOUTH);
          break;
        case 2:
          action->SetCode(ai::Scavenger::Action::GO_EAST);
          break;
        case 3:
          action->SetCode(ai::Scavenger::Action::GO_WEST);
          break;
        }
      }
      else
      {
        action->SetCode(ai::Scavenger::Action::LOOK);
        switch(d)
        {
        case 0:
          action->SetDirection(ai::Scavenger::Location::NORTH);
          break;
        case 1:
          action->SetDirection(ai::Scavenger::Location::SOUTH);
          break;
        case 2:
          action->SetDirection(ai::Scavenger::Location::EAST);
          break;
        case 3:
          action->SetDirection(ai::Scavenger::Location::WEST);
          break;
        }
      }
    }

    return action;
  }
}
