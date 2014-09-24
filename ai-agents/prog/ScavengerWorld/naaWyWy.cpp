#include "naaWyWy.h"
#include <cstdio>
#include <cstring>

namespace naa {
        /* For more on options look at the files:
   * ai-lib/include/Agent/Options.h
   * ai-lib/src/Agent/Options.cpp
   * al-lib/src/Agent/AgentDriver.cpp
   */
        /*
   * Run with:
   * ./RunProg ./SA_Test -a s -U 1
   */
  WyWy::WyWy(ai::Agent::Options *opts) {
    SetName("WyWy");
    std::cout << "The value of the -U option is: " << opts->GetArgInt("user1") << std::endl;
    model = new Model();
  }

  WyWy::~WyWy() {}

  ai::Agent::Action * WyWy::Program(const ai::Agent::Percept * percept) {
    ai::Scavenger::Action *action = new ai::Scavenger::Action;
    ParcePercepts(percept);
    if (action_queue.size() == 0) {
      SearchForGoal();
    }
    if (action_queue.size() == 0) {
      action->SetCode(ai::Scavenger::Action::QUIT);
    } else {
      SearchAction a = action_queue.front();
      action_queue.pop_front();
      switch (a.GetActionCode()) {
        case ACTION_MOVE_NORTH:
          action->SetCode(ai::Scavenger::Action::GO_NORTH);
          break;
        case ACTION_MOVE_SOUTH:
          action->SetCode(ai::Scavenger::Action::GO_SOUTH);
          break;
        case ACTION_MOVE_EAST:
          action->SetCode(ai::Scavenger::Action::GO_EAST);
          break;
        case ACTION_MOVE_WEST:
          action->SetCode(ai::Scavenger::Action::GO_WEST);
          break;
      }
    }

    return action;
  }

  bool WyWy::ParcePercepts(const ai::Agent::Percept *percept) {
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

    return true;
  }

  void WyWy::SearchForGoal() {
    Location loc = model->GetLocation();
    SearchState *the_initial_state = new SearchState(loc.x, loc.y, loc.z, model->GetCharge());
    SearchProblem *the_problem = new SearchProblem(the_initial_state, model);
    ai::Search::Fringe *the_frontier = new ai::Search::BFFringe();
    ai::Search::Algorithm *the_algorithm = new ai::Search::Graph(the_problem, the_frontier);

    if (the_algorithm->Search()) {
      std::cout << "A path was found!" << std::endl;
      std::list<ai::Search::Node *> *solution = the_algorithm->GetSolution().GetList();
      std::list<ai::Search::Node *>::const_iterator it;
      double cost = 0;
      int depth = 0;

      for(it = solution->begin(); it != solution->end(); it++) {
        if ((*it)->GetAction()) {
          const SearchAction * const action = dynamic_cast<const SearchAction * const>((*it)->GetAction());
          action_queue.push_back(*action);
        }
        cost = (*it)->GetPathCost();
        depth = (*it)->GetDepth();
      }
    } else {
      std::cout << "A path was not found!" << std::endl;
    }

    the_algorithm->GetSolution().Display();
    delete the_algorithm;
  }
}
