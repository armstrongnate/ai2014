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

  enum {
    FORWARDNESS_UITILITY,
    STRAGGLENESS_UTILITY
  };

  class Mushu : public ai::Agent::AgentProgram {
  public:
    Mushu(ai::Agent::Options *opts);
    ~Mushu();
    virtual ai::Agent::Action *Program(const ai::Agent::Percept *percept);
  protected:
    PlyData PickMove(PremiumBoard *board, int player);
    PlyData Max(PremiumBoard *board, int player, int depth, double alpha, double beta);
    PlyData Min(PremiumBoard *board, int player, int depth, double alpha, double beta);
    PlyData BookMove(int move);
    ai::CCheckers::MoveData GetMove(int from_x, int from_y, int to_x, int to_y);
    double Evaluate(const PremiumBoard *board, int player, int depth);
    int StragglerValue(const PremiumBoard *board, int player);
    int ConservativeValue(const PremiumBoard *board, int player);
    int onMove;
    int utility;
  };

}

#endif /* defined(__ChineseCheckers__Mushu__) */
