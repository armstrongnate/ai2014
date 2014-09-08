#include "ai_search.h"
#include <iostream>

namespace ai
{
  namespace Search
  {
    /*
     * ACTION CLASS
     */
    Action::~Action()
    {
    }
    
    void   Action::Display() const
    {
      std::cout << "Action Display" << std::endl;
    }

  }
}
