//
//  naaHunter.cpp
//  WumpusWorld
//
//  Created by Nate Armstrong on 11/19/14.
//  Copyright (c) 2014 Nate Armstrong. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>

#include "naaHunter.h"
#include "naaProblem.h"
#include "naaAction.h"

namespace naa {

  Hunter::Hunter() {
    SetName("Hunter");
    state.x = 0;
    state.y = 0;
    state.direction = DIRECTION_EAST;
    for (int i=0; i<4; i++) {
      for (int j=0; j<4; j++) {
        visited[i][j] = false;
      }
    }
  }

  Hunter::~Hunter() {}

  ai::Agent::Action * Hunter::Program(const ai::Agent::Percept * percept) {
    std::cout << "I am in cell: " << state.x << ", " << state.y << std::endl;
    Visit(state.x, state.y);
    ai::Agent::Action *action = new ai::Agent::WumpusAction;

    for (int i = 0; i < percept->NumAtom(); i++) {
      ai::Agent::PerceptAtom a = percept->GetAtom(i);

      // gold
      // if (a.GetName() == "GOLD" && a.GetValue() == "1") {
      //   std::cout << "FOUND GOLD!" << std::endl;
      //   action->SetCode(ai::Agent::WumpusAction::QUIT);
      //   return action;
      // }

      // // glitter
      // if (a.GetName() == "GLITTER") {
      //   std::cout << "GRABBING GOLD!" << std::endl;
      //   action->SetCode(ai::Agent::WumpusAction::GRAB);
      //   return action;
      // }

      // breeze
      if (a.GetName() == "BREEZE") {
        std::cout << "WHOO! BREEZY!" << std::endl;
        kb.TellBreeze(state.x, state.y);
      }
      else {
        kb.TellNoBreeze(state.x, state.y);
      }

      // stench
      if (a.GetName() == "STENCH") {
        kb.TellStench(state.x, state.y);
      }
      else {
        kb.TellNoStench(state.x, state.y);
      }
    }

    State *stateCopy = new State(state.x, state.y);
    stateCopy->direction = state.direction;
    Problem *problem = new Problem(stateCopy, visited, &kb);
    ai::Search::UCFringe * fringe = new ai::Search::UCFringe();
    ai::Search::Algorithm * algorithm = new ai::Search::Graph(problem, fringe);
    std::list<ai::Search::Node *> * solution = algorithm->GetSolution().GetList();

    if (algorithm->Search()) {
      std::cout << "Goal found! Be there in: " << solution->size() << std::endl;
      while (solution->size() > 0) {
        if (solution->front()->GetAction()) {
          Action *nextAction = dynamic_cast<Action *>(solution->front()->GetAction());
          action->SetCode(nextAction->code);
          State *solutionState = dynamic_cast<State *>(solution->front()->GetState());
          state.x = solutionState->x;
          state.y = solutionState->y;
          state.direction = solutionState->direction;
          if (kb.AskWumpus(state.x, state.y)) {
            std::cout << "YELLING! <<<<<<<<<<<<<<<<<<<" << std::endl;
            action->SetCode(ai::Agent::WumpusAction::YELL);
            return action;
          }
          solution->pop_front();
          return action;
        }
        else {
          solution->pop_front();
        }
      }
    }

    std::cout << "NO SOLUTION FOUND. QUITTING..." << std::endl;
    action->SetCode(ai::Agent::WumpusAction::QUIT);
    return action;
  }

  void Hunter::Visit(int x, int y) {
    visited[x][y] = true;
  }

  bool Hunter::HasVisited(int x, int y) {
    return visited[x][y];
  }

  MyKnowledgeBase Hunter::GetKnowledgeBase() {
    return kb;
  }
}
