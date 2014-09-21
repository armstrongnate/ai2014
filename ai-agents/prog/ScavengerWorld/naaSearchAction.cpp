#include "naaSearchAction.h"
#include <iostream>

namespace naa {

  SearchAction::SearchAction()
    : action_code(0) {}

  SearchAction::SearchAction(const int action_code_in) {
    action_code = action_code_in;
  }

  SearchAction::~SearchAction() {}

  void SearchAction::Display() const {
    std::cout << "ActionCode: " << action_code << std::endl;
  }

  int SearchAction::GetActionCode() const {
    return action_code;
  }

  bool SearchAction::SetActionCode(const int action_code_in) {
    action_code = action_code_in;
    return true;
  }

}
