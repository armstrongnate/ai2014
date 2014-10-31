#include "naaModel.h"
#include <cstdio>
#include <iostream>
#include <cstring>

namespace naa {

  Cell::Cell() {
    id = -1;
    border.north = border.east = border.south = border.west = I_UNKNOWN;
  }

  Cell::Cell(int id, Location loc, Border border) {
    this->id = id;
    this->location = loc;
    this->border = border;
  };

  bool Cell::IsValid() {
    return id > -1;
  }

  bool Cell::Visited() {
    return border.north != I_UNKNOWN &&
    border.east != I_UNKNOWN &&
    border.south != I_UNKNOWN &&
    border.east != I_UNKNOWN;
  }

  bool Cell::Touched() {
    return border.north != I_UNKNOWN ||
    border.east != I_UNKNOWN ||
    border.south != I_UNKNOWN ||
    border.east != I_UNKNOWN;
  }

  void Cell::Display() {
    std::cout << "CELL: "
    << "id: " << id << ", "
    << "border: " << border.north << ", "
      << border.east << ", "
      << border.south << ", "
      << border.west << ", "
    << "location: " << location.x << ", "
      << location.y << ", "
      << location.z
    << std::endl;
  }

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

  void Model::SetLocation(Location loc) {
    location = loc;
  }

  void Model::SetGoalLocation(Location loc) {
    goalLocation = loc;
  }

  Location Model::GetLocation() {
    return location;
  }

  Location Model::GetGoalLocation() {
    return goalLocation;
  }

  bool Model::CellExists(double x, double y) {
    std::pair<int,int> key(DoubleToInt(x), DoubleToInt(y));
    return !(cells.find(key) == cells.end());
  }

  Cell Model::FindCell(double x, double y) {
    std::pair<int,int> key(DoubleToInt(x), DoubleToInt(y));
    Cell cell = cells[key];
    cell.location.x = x;
    cell.location.y = y;
    return cell;
  }

  Cell Model::GetGoalCell() {
    std::pair<int,int> key(DoubleToInt(goalLocation.x), DoubleToInt(goalLocation.y));
    return cells[key];
  }

  double Model::GetCharge() {
    return charge;
  }

  void Model::SetCharge(double charge) {
    this->charge = charge;
  }

  int Model::GetCurrentInterface(int dir) {
    Cell cell = FindCell(location.x, location.y);
    int interface = I_UNKNOWN;
    if (!cell.IsValid()) { return interface; }
    switch (dir) {
      case LOOK_DIRECTION_NORTH:
        interface = cell.border.north;
        break;
      case LOOK_DIRECTION_EAST:
        interface = cell.border.east;
      case LOOK_DIRECTION_SOUTH:
        interface = cell.border.south;
        break;
      case LOOK_DIRECTION_WEST:
        interface = cell.border.west;
        break;
      default:
        break;
    }
    return interface;
  }

}
