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
    model = new Model();
    mode = MODE_GOAL;

    bool error = false;

    switch (opts->GetArgInt("user1")) {
      case 1:
        algorithm_type = ALG_TREE;
        break;
      case 2:
        algorithm_type = ALG_GRAPH;
        break;
      default:
        std::cerr << "(-U) => Tree: 1; Graph: 2" << std::endl;
        error = true;
        break;
    }

    switch (opts->GetArgInt("user2")) {
      case 1:
        frontier_type = FRONTIER_BFS;
        break;
      case 2:
        frontier_type = FRONTIER_UCS;
        break;
      case 3:
        frontier_type = FRONTIER_DFS;
        break;
      case 4:
        frontier_type = FRONTIER_DLS;
        break;
      default:
        std::cerr << "(-V) => BFS: 1; UCS: 2; DFS: 3; DLS: 4" << std::endl;
        error = true;
        break;
    }

    if (frontier_type == FRONTIER_DLS) {
      dls_depth = opts->GetArgInt("user3");
    }

    if (error) { exit(1); }
  }

  WyWy::~WyWy() {}

  ai::Agent::Action * WyWy::Program(const ai::Agent::Percept * percept) {
    ai::Scavenger::Action *action = new ai::Scavenger::Action;
    ParcePercepts(percept);
    if (action_queue.size() == 0) {
      if (mode == MODE_GOAL) {
        SearchForGoal();
        mode = MODE_BASE;
      }
      else if (mode == MODE_BASE) {
        SearchForGoal();
        mode = MODE_QUIT;
      }
      else if (mode == MODE_QUIT) {
        action->SetCode(ai::Scavenger::Action::QUIT);
      }
    }
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
    } else if (mode == MODE_QUIT) {
      action->SetCode(ai::Scavenger::Action::QUIT);
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
    for (i = 0; i < percept->NumAtom(); i++) {
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
    }

    return true;
  }

  void WyWy::SearchForGoal() {
    Location loc = model->GetLocation();
    SearchState *the_initial_state = new SearchState(loc.x, loc.y, loc.z, model->GetCharge());
    SearchProblem *the_problem = new SearchProblem(the_initial_state, model, mode);
    ai::Search::Fringe *the_frontier = 0;
    ai::Search::Algorithm *the_algorithm = 0;

    switch (frontier_type) {
      case FRONTIER_BFS:
        the_frontier = new ai::Search::BFFringe();
        break;
      case FRONTIER_UCS:
        the_frontier = new ai::Search::UCFringe();
        break;
      case FRONTIER_DFS:
        the_frontier = new ai::Search::DFFringe();
        break;
      case FRONTIER_DLS:
        the_frontier = new ai::Search::DLFringe(dls_depth);
        break;
    }

    switch (algorithm_type) {
      case ALG_TREE:
        the_algorithm = new ai::Search::Tree(the_problem, the_frontier);
        break;
      case ALG_GRAPH:
        the_algorithm = new ai::Search::Graph(the_problem, the_frontier);
        break;
    }

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
