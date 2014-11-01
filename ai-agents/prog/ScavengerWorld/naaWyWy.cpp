#include "naaWyWy.h"
#include <cstdio>
#include <cstring>

namespace naa {

  int oppositeInterface(int interface) {
    int opposite = I_UNKNOWN;
    switch (interface) {
      case I_CLIFF:
        opposite = I_WALL;
        break;
      case I_WALL:
        opposite = I_CLIFF;
        break;
      default:
        opposite = interface;
        break;
    }
    return opposite;
  };


  WyWy::WyWy(ai::Agent::Options *opts) {
    SetName("WyWy");
    model = new Model();
    mode = MODE_LOOK;
    lookDirection = LOOK_DIRECTION_NORTH;
  }

  WyWy::~WyWy() {}

  ai::Agent::Action * WyWy::Program(const ai::Agent::Percept * percept) {
    ParsePercepts(percept);
    ai::Scavenger::Action *action = new ai::Scavenger::Action;

    if (mode == MODE_BASE && model->GetLocation().x == 0 && model->GetLocation().y == 0) {
      if (model->GetCharge() >= 100.0) {
        mode = MODE_SCAVENGE;
      }
      else {
        action->SetCode(ai::Scavenger::Action::RECHARGE);
        return action;
      }
    }

    if (mode == MODE_LOOK) {
      if (model->GetCurrentInterface(lookDirection) == I_UNKNOWN) {
        action->SetCode(ai::Scavenger::Action::LOOK);
        action->SetDirection(LookLocation());
        mode = MODE_LOOKED;
        return action;
      }
      else {
        Look();
      }
    }

    if (action_queue.size() == 0) {
      if (SearchForGoal()) {
        std::cout << "Path to unvisited cell found!" << std::endl;
      }
      else {
        std::cout << "Path to unvisited cell NOT found!" << std::endl;
        if (model->GetLocation().x == 0 && model->GetLocation().y == 0) {
          action->SetCode(ai::Scavenger::Action::QUIT);
          return action;
        }
        mode = MODE_BASE;
        if (SearchForGoal()) {
          std::cout << "Path to base found!" << std::endl;
        }
        else {
          std::cout << "Path to base NOT found!" << std::endl;
        }
      }
		}

    if (action_queue.size() > 0) {
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
    else {
      mode = MODE_LOOK;
    }

    return action;
  }

  void WyWy::LookAtCell(Location loc, int interface) {
    Cell cell = model->FindCell(loc.x, loc.y);
    Border border = cell.border;
    switch (lookDirection) {
      case LOOK_DIRECTION_NORTH:
        border.north = interface;
        break;
      case LOOK_DIRECTION_EAST:
        border.east = interface;
        break;
      case LOOK_DIRECTION_SOUTH:
        border.south = interface;
        break;
      case LOOK_DIRECTION_WEST:
        border.west = interface;
        break;
    }
    cell.Display();
    model->AddCell(0, loc, border);
  }

  void WyWy::AddNeighborCell(Cell cell) {
  }

  ai::Scavenger::Location::Direction WyWy::LookLocation() {
    ai::Scavenger::Location::Direction loc = ai::Scavenger::Location::NORTH;
    switch (lookDirection) {
      case LOOK_DIRECTION_NORTH:
        loc = ai::Scavenger::Location::NORTH;
        break;
      case LOOK_DIRECTION_EAST:
        loc = ai::Scavenger::Location::EAST;
        break;
      case LOOK_DIRECTION_SOUTH:
        loc = ai::Scavenger::Location::SOUTH;
        break;
      case LOOK_DIRECTION_WEST:
        loc = ai::Scavenger::Location::WEST;
        break;
    }
    return loc;
  }

  bool WyWy::ParsePercepts(const ai::Agent::Percept *percept) {
    GetCurrentLocation(percept);
    for (unsigned int i = 0; i < percept->NumAtom(); i++) {
      ai::Agent::PerceptAtom a = percept->GetAtom(i);
      ParseCell(a);
    }
    if (mode == MODE_LOOKED) {
      const char *look = percept->GetAtom("LOOK").GetValue().c_str();
      int interface = Model::InterfaceStringToInt(look);
      LookAtCell(model->GetLocation(), interface);
      Look();
    }
    return true;
  }

  void WyWy::Look() {
    lookDirection++;
    if (lookDirection >= LOOK_DIRECTION_MAX) {
      mode = MODE_SCAVENGE;
      lookDirection = LOOK_DIRECTION_NORTH;
    }
    else {
      mode = MODE_LOOK;
    }
  }

  bool WyWy::SearchForGoal() {
    Location loc = model->GetLocation();
    SearchState *state = new SearchState(loc.x, loc.y, loc.z, model->GetCharge());
    SearchProblem *problem = new SearchProblem(state, model, mode);
    ai::Search::Graph *exploreAlgo = new ai::Search::Graph(problem, new ai::Search::UCFringe());
    bool goalFound = false;

    if (exploreAlgo->Search()) {
      goalFound = true;
      std::list<ai::Search::Node *> *solution = exploreAlgo->GetSolution().GetList();
      std::list<ai::Search::Node *>::const_iterator it;
      for(it = solution->begin(); it != solution->end(); it++) {
        if ((*it)->GetAction()) {
          const SearchAction * const action = dynamic_cast<const SearchAction * const>((*it)->GetAction());
          action_queue.push_back(*action);
        }
      }
    }

    delete exploreAlgo;
    return goalFound;
  }

  void WyWy::ParseCell(ai::Agent::PerceptAtom a) {
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
    }
    else {
      std::cout << a.GetName() << ": " << a.GetValue() << std::endl;
    }
  }


  void WyWy::GetCurrentLocation(const ai::Agent::Percept *percept) {
    Location loc;
    loc.x = atof(percept->GetAtom("X_LOC").GetValue().c_str());
    loc.y = atof(percept->GetAtom("Y_LOC").GetValue().c_str());
    loc.z = atof(percept->GetAtom("Z_LOC").GetValue().c_str());
    double charge = atof(percept->GetAtom("CHARGE").GetValue().c_str());
    model->SetLocation(loc);
    model->SetCharge(charge);
  }

}
