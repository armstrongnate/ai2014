#include "naaModel.h"
#include <cstdio>
#include <iostream>
#include <cstring>

namespace naa {
  Cell::Cell() {
    this->id = -1;
  }

  Cell::Cell(int id, Location loc, Border border) {
    this->id = id;
    this->location = loc;
    this->border = border;
  };

  Model::Model() {
    Location loc;
    loc.x = 0.0;
    loc.y = 0.0;
    loc.z = 0.0;
    this->location = loc;
    this->goalLocation = loc;
    this->charge = 0.0;
    this->hitPoints = 0.0;
  };

  int Model::DoubleToInt(const double d) const {
    return (int)(d + 1) / 1000;
  }

  int Model::InterfaceStringToInt(const char *s) {
    if (std::strcmp(s, "plain") == 0) { return I_PLAIN; }
    else if (std::strcmp(s, "mud") == 0) { return I_MUD; }
    else if (std::strcmp(s, "rocks") == 0) { return I_ROCKS; }
    else if (std::strcmp(s, "cliff") == 0) { return I_CLIFF; }
    else if (std::strcmp(s, "wall") == 0) { return I_WALL; }
    else { return I_UNKNOWN; }
  }

  bool Model::AddCell(int id, Location loc, Border border) {
    std::pair<int,int> key(DoubleToInt(loc.x), DoubleToInt(loc.y));
    Cell c(id, loc, border);
    cells[key] = c;
    return true;
  }

}
