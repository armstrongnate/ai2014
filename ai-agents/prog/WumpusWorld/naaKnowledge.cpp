//
//  naaKnowledge.cpp
//  WumpusWorld
//
//  Created by Nate Armstrong on 11/9/14.
//  Copyright (c) 2014 Nate Armstrong. All rights reserved.
//

#include <ai_pl.h>
#include <string>
#include <cstdio>
#include <sstream>
#include <assert.h>

static const int BUF_SIZE = 1024;
static char buf[BUF_SIZE];

static const int SIZE = 4;

namespace naa {
  class MyKnowledgeBase : public ai::PL::KnowledgeBase {
  public:
    MyKnowledgeBase();
    ~MyKnowledgeBase();

    void TellBreeze(int x, int y);
    void TellNoBreeze(int x, int y);
    bool AskPit(int x, int y);

    void TellStench(int x, int y);
    void TellNoStench(int x, int y);
    bool AskWumpus(int x, int y);
  protected:
    void SecureTheBorder();
    void TellPercept(std::string &p, std::string &condition, int x, int y);
  private:
  };
}

namespace naa {

  int n(int toNormalize) {
    return toNormalize + 1;
  }

  MyKnowledgeBase::MyKnowledgeBase() {
    // only wun Wumpus in wun cell
    for (int i=0; i<SIZE; i++) {
      for (int j=0; j<SIZE; j++) {
        bool first = true;
        std::stringstream sentence;
        sentence << "W_" << n(i) << "_" << n(j) << " <=> (";
        for (int k=0; k<SIZE; k++) {
          for (int l=0; l<SIZE; l++) {
            if (!(i == k && j == l)) {
              if (!first) {
                sentence << " & ";
              }
              else {
                first = false;
              }
              sentence << "(!W_" << n(k) << "_" << n(l) << ")";
            }
          }
        }
        sentence << ")";
        AddSentence(sentence.str());
      }
    }
  }

  MyKnowledgeBase::~MyKnowledgeBase() {}

  void MyKnowledgeBase::SecureTheBorder() {
    int i, x, y;
    for (i=0; i<SIZE; i++) {
      /*
       —— —— —— ——



      */
      x = n(i);
      y = n(SIZE);
      std::sprintf(buf, "(!P_%d_%d) & (!W_%d_%d)", x, y, x, y);
      AddSentence(buf);

      /*
       |
       |
       |
       |
      */
      x = n(-1);
      y = n(i);
      std::sprintf(buf, "(!P_%d_%d) & (!W_%d_%d)", x, y, x, y);
      AddSentence(buf);

      /*
                  |
                  |
                  |
                  |
       */
      x = n(SIZE);
      y = n(i);
      std::sprintf(buf, "(!P_%d_%d) & (!W_%d_%d)", x, y, x, y);
      AddSentence(buf);

      /*
       
       


       —— —— —— ——
      */
      x = n(i);
      y = n(-1);
      std::sprintf(buf, "(!P_%d_%d) & (!W_%d_%d)", x, y, x, y);
      AddSentence(buf);
    }
  }

  void MyKnowledgeBase::TellBreeze(int x, int y) {
    std::string percept = "P";
    std::string condition = "|";
    TellPercept(percept, condition, x, y);
  }

  void MyKnowledgeBase::TellNoBreeze(int x, int y) {
    std::string percept = "!P";
    std::string condition = "&";
    TellPercept(percept, condition, x, y);
  }

  void MyKnowledgeBase::TellStench(int x, int y) {
    std::string percept = "W";
    std::string condition = "|";
    TellPercept(percept, condition, x, y);
  }

  void MyKnowledgeBase::TellNoStench(int x, int y) {
    std::string percept = "!W";
    std::string condition = "&";
    TellPercept(percept, condition, x, y);
  }

  void MyKnowledgeBase::TellPercept(std::string &p, std::string &condition, int x, int y) {
    std::sprintf(buf, "(%s_%d_%d) %s (%s_%d_%d) %s (%s_%d_%d) %s (%s_%d_%d)",
                 p.c_str(), n(x+1), n(y),
                 condition.c_str(),
                 p.c_str(), n(x-1), n(y),
                 condition.c_str(),
                 p.c_str(), n(x), n(y+1),
                 condition.c_str(),
                 p.c_str(), n(x), n(y-1));
    AddSentence(buf);
    std::sprintf(buf, "(!P_%d_%d) & (!W_%d_%d)", n(x), n(y), n(x), n(y));
    AddSentence(buf);
    SecureTheBorder();

  }

  bool MyKnowledgeBase::AskPit(int x, int y) {
    bool rval;
    ai::PL::KnowledgeBase question;
    std::sprintf(buf, "P_%d_%d", n(x), n(y));
    question.AddSentence(buf);
    rval = (DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
    return rval;
  }

  bool MyKnowledgeBase::AskWumpus(int x, int y) {
    bool rval;
    ai::PL::KnowledgeBase question;
    std::sprintf(buf, "W_%d_%d", n(x), n(y));
    question.AddSentence(buf);
    rval = (DPLL_Entails(question) == ai::PL::Symbol::KNOWN_TRUE);
    return rval;
  }

}

void test_problem() {

  /*
   B_x_y <=> ( P_x+1_y | P_x-1_y | P_x_y+1 | P_x_y-1 )
   B_x_y <=> (!P_x_y)
   !B_x_y <=> ( !P_x+1_y & !P_x-1_y & !P_x_y+1 & !P_x_y-1 )
   
   # Semantics of symbols.
   B: Breeze
   P: Pit
   W: Wumpus
   B_x_y: there is a Breeze at (x, y)
  */

  naa::MyKnowledgeBase kb;

  /*
   |———————————————|
   | P |   |   |   |
   |-——————————————|
   |   |   | W |   |
   |———————————————|
   |   |   |   |   |
   |———————————————|
   |   |   |   |   |
   |———————————————|
   */

  // 0, 0
  kb.TellNoBreeze(0, 0);
  kb.TellNoStench(0, 0);

  // 0, 1
  kb.TellNoBreeze(0, 1);
  kb.TellNoStench(0, 1);

  // 0, 2
  kb.TellBreeze(0, 2);
  kb.TellNoStench(0, 2);

  // 0, 1

  // 1, 1
  kb.TellNoBreeze(1, 1);
  kb.TellNoStench(1, 1);
  assert(kb.AskPit(0, 3));
  assert(!kb.AskPit(1, 2)); // sanity check

  // 1, 2
  kb.TellNoBreeze(1, 2);
  kb.TellStench(1, 2);
  assert(!kb.AskWumpus(2, 2));

  // 1, 1

  // 2, 1
  kb.TellNoBreeze(2, 1);
  kb.TellStench(2, 1);
  assert(kb.AskWumpus(2, 2));
  assert(!kb.AskWumpus(1, 3)); // sanity check
}

int main(int argc, char **argv) {
  test_problem();
  return 0;
}