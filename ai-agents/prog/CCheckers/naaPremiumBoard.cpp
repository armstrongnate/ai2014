//
//  naaPremiumBoard.cpp
//  ChineseCheckers
//
//  Created by Nate Armstrong on 11/8/14.
//  Copyright (c) 2014 Nate Armstrong. All rights reserved.
//

#include "naaPremiumBoard.h"

namespace naa {
  bool PremiumBoard::Unmove(int player, const ai::CCheckers::MoveData &move_in) {
    board.hole[move_in.to_x][move_in.to_y] = 0;
    board.hole[move_in.from_x][move_in.from_y] = player;
    board.player_turn = player;
    number_of_turns--;
    legal_moves_valid = false;
    return true;
  }
}
