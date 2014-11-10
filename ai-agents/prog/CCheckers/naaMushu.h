//
//  Mushu.h
//  ChineseCheckers
//
//  Created by Nate Armstrong on 11/7/14.
//  Copyright (c) 2014 Nate Armstrong. All rights reserved.
//

#ifndef __ChineseCheckers__Mushu__
#define __ChineseCheckers__Mushu__

#include <stdio.h>
#include <ai_ccheckers.h>

#include "naaPremiumBoard.h"

namespace naa {

  class PlyData {
  public:
    PlyData(double utility_in);
    bool move_ok;
    ai::CCheckers::MoveData move;
    double utility;
  };

  class Mushu : public ai::Agent::AgentProgram {
  public:
    Mushu();
    ~Mushu();
    virtual ai::Agent::Action *Program(const ai::Agent::Percept *percept);
  protected:
    PlyData PickMove(PremiumBoard *board, int player);
    PlyData Max(PremiumBoard *board, int player, int depth, double alpha, double beta);
    PlyData Min(PremiumBoard *board, int player, int depth, double alpha, double beta);
    double Evaluate(const PremiumBoard *board, int player, int depth);
  };

}

#endif /* defined(__ChineseCheckers__Mushu__) */
