//
//  Mushu.cpp
//  ChineseCheckers
//
//  Created by Nate Armstrong on 11/7/14.
//  Copyright (c) 2014 Nate Armstrong. All rights reserved.
//

#include "naaMushu.h"

namespace naa {

  const int MAX_DEPTH = 1;
  const double MY_INFINITY = 1.e6;
  const double STRAGGLER_UTILITY_MULTIPLIER = 0.25;

  PlyData::PlyData(double utility_in) : move_ok(false), utility(utility_in) {}

  Mushu::Mushu(ai::Agent::Options *opts) {
    SetName("Mushu");

    if (opts->GetArgInt("user1") > 0) {
      utility = opts->GetArgInt("user1");
      if (utility > 1) {
        utility = FORWARDNESS_UITILITY;
      }
    }
    std::cout << "Options:" << std::endl;
    std::cout << "-U num : utility (0: Forwardness, 1: Stragglers)" << std::endl;
    std::cout << "Selected utility: " << utility << std::endl;
  }

  Mushu::~Mushu() {}

  ai::Agent::Action *Mushu::Program(const ai::Agent::Percept *percept) {
    ai::CCheckers::CCheckersAction *action = new ai::CCheckers::CCheckersAction;
    std::string board_str = percept->GetAtom("BASIC_BOARD").GetValue();
    PremiumBoard *board = new PremiumBoard(board_str);
    int player = atoi(percept->GetAtom("PLAYER_NUMBER").GetValue().c_str());

    PlyData ply_data = PickMove(board, player);

    if (ply_data.move_ok) {
      action->SetCode(ai::CCheckers::CCheckersAction::MOVE);
      action->SetMove(ply_data.move);
    }
    else {
      std::cout << "quit" << std::endl;
      action->SetCode(ai::CCheckers::CCheckersAction::QUIT);
    }
    delete board;
    return action;
  }

  PlyData Mushu::PickMove(PremiumBoard *board, int player) {
    PlyData ply_data = Max(board, player, 1, -MY_INFINITY, MY_INFINITY);
    // std::cout << "utility: " << ply_data.utility << std::endl;
    return ply_data;
  }

  PlyData Mushu::Max(PremiumBoard *board, int player, int depth, double alpha, double beta) {
    PlyData ply_data(-MY_INFINITY);
    if (board->HaveWinner()) {
      std::cout << "WE HAVE A WINNER! " << player << std::endl;
      return ply_data;
    }
    if (depth > MAX_DEPTH) {
      ply_data.utility = Evaluate(board, player, depth);
      return ply_data;
    }
    const std::vector<ai::CCheckers::MoveData> &moves = board->DetermineLegalMoves(player);
    for (int i=0; i<(int)moves.size(); i++) {
      bool moved = board->Move(player, moves[i]);
      PlyData tmp_ply_data = Min(board, player, depth + 1, alpha, beta);
      if (moved) {
        board->Unmove(player, moves[i]);
      }
      if (tmp_ply_data.utility > ply_data.utility) {
        ply_data.utility = tmp_ply_data.utility;
        ply_data.move    = moves[i];
        ply_data.move_ok = true;
        if (ply_data.utility >= beta) {
          return ply_data;
        }
        if (ply_data.utility > alpha) {
          alpha = ply_data.utility;
        }
      }
    }
    return ply_data;
  }

  PlyData Mushu::Min(PremiumBoard *board, int player, int depth, double alpha, double beta) {
    PlyData ply_data(MY_INFINITY);
    if (board->HaveWinner()) {
      std::cout << "WE HAVE A WINNER! " << player << std::endl;
      return ply_data;
    }
    if (depth > MAX_DEPTH) {
      ply_data.utility = Evaluate(board, player, depth);
      return ply_data;
    }
    int other_player = (player == 1) ? 2 : 1;
    const std::vector<ai::CCheckers::MoveData> &moves = board->DetermineLegalMoves(other_player);
    for (int i=0; i<(int)moves.size(); i++) {
      bool moved = board->Move(other_player, moves[i]);
      PlyData tmp_ply_data = Max(board, player, depth + 1, alpha, beta);
      if (moved) {
        board->Unmove(other_player, moves[i]);
      }
      if (tmp_ply_data.utility < ply_data.utility) {
        ply_data.utility = tmp_ply_data.utility;
        ply_data.move    = moves[i];
        ply_data.move_ok = true;
        if (ply_data.utility <= alpha) {
          return ply_data;
        }
        if (ply_data.utility < beta) {
          beta = ply_data.utility;
        }
      }
    }
    return ply_data;
  }

  double Mushu::Evaluate(const PremiumBoard *board, int player, int depth) {
    int other_player = (player == 1) ? 2 : 1;
    if (board->HaveWinner() == player) {
      return MY_INFINITY/depth;
    }
    else if (board->HaveWinner() == other_player) {
      return -MY_INFINITY/depth;
    }
    else {
      double strength = board->Forwardness(player) - board->Forwardness(other_player);
      if (utility == STRAGGLENESS_UTILITY) {
        strength += StragglerValue(board, player);
        strength -= StragglerValue(board, player);
        strength /= 4;
      }
      return strength;
    }
  }

  int Mushu::StragglerValue(const naa::PremiumBoard *board, int player) {
    if (player == 1)
      for (int y=0; y<=16; y++)
        for (int x=0; x<=16; x++)
          if (board->GetBoard().hole[x][y] == player)
            return y;
    if (player == 2)
      for (int y=16; y>=0; y--)
        for (int x=0; x<=16; x++)
          if (board->GetBoard().hole[x][y] == player)
            return 16-y;
    return 0;
  }
}
