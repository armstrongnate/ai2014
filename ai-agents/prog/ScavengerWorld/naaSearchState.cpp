#include "naaSearchState.h"
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>

namespace naa {
  SearchState::SearchState()
    : x(0), y(0), z(0), charge(0)
  {
  }

  SearchState::SearchState(const double x_in, const double y_in, const double z_in, const double charge_in)
      : x(x_in), y(y_in), z(z_in), charge(charge_in)
  {
  }

  SearchState::~SearchState() {}

  void SearchState::Display() const {
    std::cout << "state: " << x << " " << y << " " << z
              << " " << charge << std::endl;
  }

  bool SearchState::IsEqual(const State * const state_in) const {
    const SearchState * const state = dynamic_cast<const SearchState * const>(state_in);
    return ((std::fabs(x - state->x) < 0.5) &&
            (std::fabs(y - state->y) < 0.5));
  }

  double SearchState::GetX() const {
    return this->x;
  }

  double SearchState::GetY() const {
    return this->y;
  }

  double SearchState::GetZ() const {
    return this->z;
  }

  double SearchState::GetCharge() const {
    return this->charge;
  }

  bool SearchState::SetX(const double &x_in) {
    this->x = x_in;
    return true;
  }

  bool SearchState::SetY(const double &y_in) {
    this->y = y_in;
    return true;
  }

  bool SearchState::SetZ(const double &z_in) {
    this->z = z_in;
    return true;
  }

  bool SearchState::SetCharge(const double &charge_in) {
    this->charge = charge_in;
    return true;
  }
}
