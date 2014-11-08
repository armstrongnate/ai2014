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

namespace naa {

  class NotSoBasicBoard : public ai::CCheckers::BasicBoard {
  public:
    NotSoBasicBoard() : ai::CCheckers::BasicBoard() {};
    NotSoBasicBoard(const std::string &board_str_in) : ai::CCheckers::BasicBoard(board_str_in) {};
    NotSoBasicBoard(const BasicBoard &board_in) : ai::CCheckers::BasicBoard(board_in) {};
    bool Unmove(int player, const ai::CCheckers::MoveData &move_in) {
      board.hole[move_in.to_x][move_in.to_y] = 0;
      board.hole[move_in.from_x][move_in.from_y] = player;
      board.player_turn = player;
      number_of_turns--;
      legal_moves_valid = false;
      return true;
    }
  };

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
    PlyData PickMove(const ai::CCheckers::BasicBoard &board, int player);
    PlyData Max(const ai::CCheckers::BasicBoard &board, int player, int depth, int alpha, int beta);
    PlyData Min(const ai::CCheckers::BasicBoard &board, int player, int depth, int alpha, int beta);
    double Evaluate(const ai::CCheckers::BasicBoard &board, int player, int depth);
  };

}

#endif /* defined(__ChineseCheckers__Mushu__) */
