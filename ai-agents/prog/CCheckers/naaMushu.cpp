//
//  Mushu.cpp
//  ChineseCheckers
//
//  Created by Nate Armstrong on 11/7/14.
//  Copyright (c) 2014 Nate Armstrong. All rights reserved.
//

#include "naaMushu.h"

namespace naa {

  const int MAX_DEPTH = 6;
  const int MY_INFINITY = 1.e6;

  PlyData::PlyData(double utility_in) : move_ok(false), utility(utility_in) {}

  Mushu::Mushu() {
    SetName("Mushu");
  }

  Mushu::~Mushu() {}

  ai::Agent::Action *Mushu::Program(const ai::Agent::Percept *percept) {
    ai::CCheckers::CCheckersAction *action = new ai::CCheckers::CCheckersAction;
    std::string board_str = percept->GetAtom("BASIC_BOARD").GetValue();
    ai::CCheckers::BasicBoard board(board_str);
    int player = atoi(percept->GetAtom("PLAYER_NUMBER").GetValue().c_str());

    PlyData ply_data = PickMove(board, player);

    if (ply_data.move_ok) {
      action->SetCode(ai::CCheckers::CCheckersAction::MOVE);
      action->SetMove(ply_data.move);
    }
    else {
      action->SetCode(ai::CCheckers::CCheckersAction::QUIT);
    }
    return action;
  }

  PlyData Mushu::PickMove(const ai::CCheckers::BasicBoard &board, int player) {
    return Max(board, player, 1, -MY_INFINITY, MY_INFINITY);
  }

  PlyData Mushu::Max(const ai::CCheckers::BasicBoard &board, int player, int depth, int alpha, int beta) {
    PlyData ply_data(-MY_INFINITY);
    if (board.HaveWinner() || depth > MAX_DEPTH) {
      ply_data.utility = Evaluate(board, player, depth);
      return ply_data;
    }
    ai::CCheckers::BasicBoard my_board(board);
    const std::vector<ai::CCheckers::MoveData> &moves = my_board.DetermineLegalMoves(player);
    for (int i=0; i<(int)moves.size(); i++) {
      ai::CCheckers::BasicBoard tmp_board(board);
      tmp_board.Move(player, moves[i]);
      PlyData tmp_ply_data = Min(tmp_board, player, depth + 1, alpha, beta);
      if (tmp_ply_data.utility > ply_data.utility) {
        ply_data.utility = tmp_ply_data.utility;
        ply_data.move    = moves[i];
        ply_data.move_ok = true;
        if (ply_data.utility >= beta) {
          break;
        }
        if (ply_data.utility > alpha) {
          alpha = ply_data.utility;
        }
      }
    }
    return ply_data;
  }

  PlyData Mushu::Min(const ai::CCheckers::BasicBoard &board, int player, int depth, int alpha, int beta) {
    PlyData ply_data(MY_INFINITY);
    if (board.HaveWinner() || depth > MAX_DEPTH) {
      ply_data.utility = Evaluate(board, player, depth);
      return ply_data;
    }
    int other_player = (player == 1) ? 2 : 1;
    ai::CCheckers::BasicBoard my_board(board);
    const std::vector<ai::CCheckers::MoveData> &moves = my_board.DetermineLegalMoves(other_player);
    for (int i=0; i<(int)moves.size(); i++) {
      ai::CCheckers::BasicBoard tmp_board(board);
      tmp_board.Move(other_player, moves[i]);
      PlyData tmp_ply_data = Max(tmp_board, player, depth + 1, alpha, beta);
      if (tmp_ply_data.utility < ply_data.utility) {
        ply_data.utility = tmp_ply_data.utility;
        ply_data.move    = moves[i];
        ply_data.move_ok = true;
        if (ply_data.utility <= alpha) {
          break;
        }
        if (ply_data.utility < beta) {
          beta = ply_data.utility;
        }
      }
    }
    return ply_data;
  }

  double Mushu::Evaluate(const ai::CCheckers::BasicBoard &board, int player, int depth) {
    int winner = board.HaveWinner();
    int other_player = (player == 1) ? 2 : 1;
    if (winner == 3) {
      return 0.0;
    }
    else if (winner == player) {
      return 1.0;
    }
    else if (winner == other_player) {
      return -1.0;
    }
    else {
      return board.Forwardness(player) - board.Forwardness(other_player);
    }
  }
}
