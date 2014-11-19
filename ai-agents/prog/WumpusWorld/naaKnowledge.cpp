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
    void SecureTheBorder();
  protected:
  private:
  };
}

namespace naa {

  MyKnowledgeBase::MyKnowledgeBase()
  : ai::PL::KnowledgeBase() {}

  MyKnowledgeBase::~MyKnowledgeBase() {}

  int n(int toNormalize) {
    return toNormalize + 1;
  }

  void MyKnowledgeBase::SecureTheBorder() {
    int i;
    for (i=0; i<SIZE; i++) {
      /*
       |
       |
       |
       |
      */
      std::sprintf(buf, "!P_%d_%d", n(-1), n(i));
      AddSentence(buf);

      /*
       
       


       —— —— —— ——
      */
      std::sprintf(buf, "!P_%d_%d", n(i), n(-1));
      AddSentence(buf);

      /*
                  |
                  |
                  |
                  |
       */
      std::sprintf(buf, "!P_%d_%d", n(SIZE), n(i));
      AddSentence(buf);

      /*
       —— —— —— ——
       
       
       
      */
      std::sprintf(buf, "!P_%d_%d", n(i), n(SIZE));
      AddSentence(buf);
    }
  }

  void MyKnowledgeBase::TellBreeze(int x, int y) {
    std::sprintf(buf, "P_%d_%d | P_%d_%d | P_%d_%d | P_%d_%d",
                 n(x+1), n(y),
                 n(x-1), n(y),
                 n(x), n(y+1),
                 n(x), n(y-1));
    AddSentence(buf);
    std::sprintf(buf, "(!P_%d_%d)", n(x), n(y));
    AddSentence(buf);
    SecureTheBorder();
  }

  void MyKnowledgeBase::TellNoBreeze(int x, int y) {
    std::sprintf(buf, "(!P_%d_%d) & (!P_%d_%d) & (!P_%d_%d) & (!P_%d_%d)",
                 n(x+1), n(y),
                 n(x-1), n(y),
                 n(x), n(y+1),
                 n(x), n(y-1));
    AddSentence(buf);
    std::sprintf(buf, "!P_%d_%d", n(x), n(y));
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

}

void test_problem() {

  /*
   B_x_y <=> ( P_x+1_y | P_x-1_y | P_x_y+1 | P_x_y-1 )
   B_x_y <=> (!P_x_y)
   !B_x_y <=> ( !P_x+1_y & !P_x-1_y & !P_x_y+1 & !P_x_y-1 )
   
   # Semantics of symbols.
   B: Breeze
   P: Pit
   x: x
   y: y
   B_x_y: there is a Breeze at (x, y)
  */

  naa::MyKnowledgeBase kb;
  kb.TellNoBreeze(0, 0);
  kb.TellBreeze(0, 1);
  kb.TellNoBreeze(1, 0);
  std::cout << "Is there a pit at 0, 2?" << std::endl;
  if (kb.AskPit(0, 2)) {
    std::cout << "Yes" << std::endl;
  }
  else {
    std::cout << "No" << std::endl;
  }
}

int main(int argc, char **argv) {
  test_problem();
  return 0;
}