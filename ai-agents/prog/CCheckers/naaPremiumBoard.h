//
//  naaPremiumBoard.h
//  ChineseCheckers
//
//  Created by Nate Armstrong on 11/8/14.
//  Copyright (c) 2014 Nate Armstrong. All rights reserved.
//

#ifndef __ChineseCheckers__naaPremiumBoard__
#define __ChineseCheckers__naaPremiumBoard__

#include <stdio.h>
#include <ai_ccheckers.h>

namespace naa {
  class PremiumBoard : public ai::CCheckers::BasicBoard {
  public:
    PremiumBoard() : ai::CCheckers::BasicBoard() {};
    PremiumBoard(const std::string &board_str_in) : ai::CCheckers::BasicBoard(board_str_in) {};
    PremiumBoard(const BasicBoard &board_in) : ai::CCheckers::BasicBoard(board_in) {};
    bool Unmove(int player, const ai::CCheckers::MoveData &move_in);
  };
}

#endif /* defined(__ChineseCheckers__naaPremiumBoard__) */
