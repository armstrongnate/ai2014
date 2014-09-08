#include <ai_fol.h>
#include <list>
//#include <stack>

#define DEBUG_PARSE 0
#define DEBUG_PRINT 0
#define DEBUG_DPLL 0
#define USE_PURE_SYMBOL 1
#define USE_UNIT_CLAUSE 1

namespace ai
{
  namespace FOL
  {
    /*
     * Initially know nothing
     */
    KnowledgeBase::KnowledgeBase()
      : sentences(0)
    {
    }

    /*
     * Clean up the dynamic memory
     */
    KnowledgeBase::~KnowledgeBase()
    {
      unsigned int i;
      for(i = 0; i < sentences.size(); i++)
	{
	  delete sentences[i];
	}
    
      std::map<std::string, Symbol *>::const_iterator it;
      for(it = symbols.begin(); it != symbols.end(); it++)
	{
	  delete it->second;
	}
    }

#if 0
    static void ApplyOperatorPrecedence(std::list<Sentence *> &op_stack,
					std::list<Sentence *> &postfix,
					std::list<Sentence *>::iterator op_first,
					std::list<Sentence *>::iterator op_end
					)
    {
#define PRECEDENCE_DEBUG 0
#if PRECEDENCE_DEBUG
      std::cout << "START " << std::endl;
      std::cout << op_stack;
      std::cout << postfix << std::endl;
#endif      
      /* find highest precedence operator */
      //std::list<Sentence *>::iterator op         = op_stack.begin();
      //std::list<Sentence *>::iterator op_end     = op_stack.end();
      
      std::list<Sentence *>::iterator op = op_first;
      std::list<Sentence *>::iterator op_highest = op;
      op++;
      while(op != op_end)
	{
	  if((*op)->GetOperator() < (*op_highest)->GetOperator())
	    { // lower number => higher precedence
	      op_highest = op;
	    }
	  op++;
	}
#if PRECEDENCE_DEBUG
      std::cout << "highest: " << *(*op_highest) << std::endl;
#endif
      /* now find operand(s) that go with the operator */
      std::list<Sentence *>::iterator rop        = op_stack.end();
      std::list<Sentence *>::iterator rpf        = postfix.end();
      rop--;
      rpf--;
      while(rop != op_highest)
	{
	  if((*rop)->GetType() == Sentence::T_UNARY)
	    {
#if PRECEDENCE_DEBUG
	      std::cout << "skipping: " << *(*rop) << " " << *(*rpf) << std::endl;
#endif
	      
	      rpf--;
	      rop--;
	    }
	  else if((*rop)->GetType() == Sentence::T_BINARY)
	    {
#if PRECEDENCE_DEBUG
	      std::cout << "skipping: " << *(*rop) << " " << *(*rpf) << std::endl;
	      //rpf--;
	      //std::cout << " " << *(*rpf) << std::endl;
#endif
	      rpf--;
	      rop--;
	    }
	}
      
      /* now rpf should hold the rhs to rop, which is op_highest
       * consolidate the operator and operand(s), insert into correct spot
       */
      Sentence *s = (*rop);
      op_stack.erase(rop);
      
      if(s->GetType() == Sentence::T_UNARY)
	{
	  Sentence *rhs = (*rpf);
	  s->SetRHS(rhs);
	  
	  postfix.insert(rpf, s);
	  postfix.erase(rpf);
	}
      else if(s->GetType() == Sentence::T_BINARY)
	{
	  std::list<Sentence *>::iterator rpf1 = rpf;
	  rpf1--;
	  
	  Sentence *rhs = (*rpf);
	  Sentence *lhs = *(rpf1);
	  s->SetLHS(lhs);
	  s->SetRHS(rhs);
	  
	  postfix.insert(rpf1, s);
	  postfix.erase(rpf1);
	  postfix.erase(rpf);
	}
      else
	{
	  std::cout << "error in op_stack contents" << std::endl;
	}
      
#if PRECEDENCE_DEBUG
      std::cout << op_stack;
      std::cout << postfix;
      std::cout << "END " << std::endl << std::endl;
#endif      
    }
#endif

#if 0    
    Sentence *KnowledgeBase::AddSentenceAux(std::list<Token>::const_iterator &next,
					    const std::list<Token>::const_iterator &last)
    {
      std::list<Token>::const_iterator curr = next;
      std::cout << "AddSentenceAux: " << (*curr) << std::endl;
      switch(curr->type)
	{
	case TOKEN_SYMBOL:
	  next++;
	  if( next->type == TOKEN_LEFT_PAREN )
	    { /* This should be a Predicate or a Function
	       * 1- Find the argument list
	       * 2- Determine the arity.       FIXME
	       * 3- Set as Predicate for now.  FIXME
	       */
	      Symbol   *sym = new Symbol(curr->symbol);
	      Sentence *args = AddSentenceAux(next, last);
	      
	      /* Count on next pointing at the token past the right paren now */
	      sym->SetType(Symbol::TYPE_PREDICATE);
	      sym->SetArity(0); // FIXME, count up arity from argument list
	      Sentence *s = new Sentence(sym,args);
	      return s;
	    }
	  else
	    { /* This should be a Constant or Variable
	       * Set as Constant for now.  FIXME
	       */
	      Symbol   *sym = new Symbol(curr->symbol);
	      sym->SetType(Symbol::TYPE_CONSTANT);
	      Sentence *s = new Sentence(sym);
	      return s;
	    }
	  break;
	case TOKEN_LEFT_PAREN:
	  {
	    /* This is either an argument list or a parenthesized sentence
	     * If the sub-sentence contains no connectives, then it is an argument list.
	     * If the sub-sentence contains connectives, then it is a parenthesized sentence.
	     */
	    next ++;
	    Sentence *s = AddSentenceAux(next, last);
	    if(next->type != TOKEN_RIGHT_PAREN)
	      {
		std::cerr << "Error, looking for ), but found " << (*next)
			  << " in KnowledgeBase::AddSentenceAux()" << std::endl;
		{ int *i = 0; (*i) = 0; }
	      }
	    next ++; /* skip the right paren now. */
	    if(s->ContainsConnective())
	      {
		/* do nothing */
	      }
	    else
	      {
		/* Create ARGS sentence that contains this one */
		Sentence *s2 = new Sentence(Sentence::T_ARGS, s);
		s = s2;
	      }
	    return s;
	  }
	  break;
	case TOKEN_NOT:
	  break;
	case TOKEN_AND:
	  break;
	case TOKEN_OR:
	  break;
	case TOKEN_IMPLIES:
	  break;
	case TOKEN_IFF:
	  break;
	case TOKEN_COMMA:
	  break;
	case TOKEN_FORALL:
	  break;
	case TOKEN_EXISTS:
	  break;
	  
	case TOKEN_RIGHT_PAREN:
	case TOKEN_MIN:
	case TOKEN_MAX:
	default:
	  /* Error of some sort */
	  std::cerr << "Error parsing token " << next->type
		    << " in KnowledgeBase::AddSentenceAux()" << std::endl;
	  { int *i = 0; (*i) = 0; }
	  break;
	}
      return 0;
    }
#endif
    
    /* Parse an input string, add as sentence to the KB
     *
     */
    void KnowledgeBase::AddSentence(const std::string &s_in)
    {
      /* Symbol     := "[a-zA-Z][a-zA-Z0-9_]*"
       * Operators  := !   -- NOT
       *               &   -- AND
       *               |   -- OR
       *               =>  -- IMPLICATION
       *               <=> -- BICONDITIONAL
       * Predicate  := Symbol(Symbol,...)
       *
       * Parens can be used override precedence, or left-to-right processing
       * Whitespace is ignored
       */
      Parser p;
      Sentence *s = p.Parse(s_in);
      if(s)
	{
#if DEBUG_PARSE
	  std::cout << *s << std::endl;
#endif
	  sentences.push_back(s);
	}

#if 0
      std::list<Token> tokens;
      KnowledgeBase::Tokenize(s_in, tokens);
#if DEBUG_PARSE
      std::cout << tokens << std::endl;
#endif
      std::list<Token>::const_iterator begin = tokens.begin();
      std::list<Token>::const_iterator last  = tokens.end();
      Sentence *s = AddSentenceAux(begin, last);
      if(s)
	{
	  sentences.push_back(s);
	}
#endif

#if 0
      
      std::string::const_iterator it     = s_in.begin();
      std::string::const_iterator it_end = s_in.end();
      std::string::const_iterator token_start;
      std::string::const_iterator token_end;

      std::list<Sentence *>      postfix;
      std::list<Sentence *>      op_stack;
    
      while(it != it_end)
	{
	  if(isspace(*it))
	    { // remove space
	      it ++;
	    }
	  else if(isalpha(*it))
	    { // must be a symbol
	      token_start = it;
	      token_end   = it;
	      while((it != it_end) && (isalnum(*it) || *it == '_'))
		{
		  it ++;
		  token_end = it; // token_end is really 1 past the end.
		}
	      std::string sym(token_start, token_end);
	      Symbol   *symbol   = AddSymbol(sym);
	      Sentence *sentence = new Sentence(symbol);
	      postfix.push_back(sentence);
	    }
	  else if(*it == '(')
	    { // 
	      Sentence *sentence = new Sentence(Sentence::T_LEFT_PAREN);
	      op_stack.push_back(sentence);
	      it++;
	    }
	  else if(*it == ')')
	    { //
	      while(op_stack.back()->GetType() != Sentence::T_LEFT_PAREN)
		{
		  std::list<Sentence *>::iterator rop = op_stack.end();
		  rop--;
		  while((*rop)->GetType() != Sentence::T_LEFT_PAREN)
		    {
		      rop--;
		    }
		  rop++; // Do not allow the left-paren into consideration 
		  ApplyOperatorPrecedence(op_stack, postfix, rop, op_stack.end());
		}
	      // delete the left-paren from the operator stack
	      delete op_stack.back();
	      op_stack.pop_back();
	      it++;
	    }
	  else if(*it == '!')
	    { // 
	      Sentence *sentence = new Sentence(Sentence::T_UNARY,
						Sentence::O_NOT);
	      op_stack.push_back(sentence);
	      it++;
	    }
	  else if(*it == '&')
	    { // 
	      Sentence *sentence = new Sentence(Sentence::T_BINARY,
						Sentence::O_AND);
	      op_stack.push_back(sentence);
	      it++;
	    }
	  else if(*it == '|')
	    { // 
	      Sentence *sentence = new Sentence(Sentence::T_BINARY,
						Sentence::O_OR);
	      op_stack.push_back(sentence);
	      it++;
	    }
	  else if((*it == '=') && (*(it+1) == '>'))
	    { // 
	      Sentence *sentence = new Sentence(Sentence::T_BINARY,
						Sentence::O_IMPLIES);
	      op_stack.push_back(sentence);
	      it+=2;
	    }
	  else if((*it == '<') && (*(it+1) == '=') && (*(it+2) == '>'))
	    { // 
	      Sentence *sentence = new Sentence(Sentence::T_BINARY,
						Sentence::O_IFF);
	      op_stack.push_back(sentence);
	      it+=3;
	    }
	  else
	    { // skipping for now
	      std::cout << "ERROR! Skipping unknown character: " << *it << std::endl;
	      it++;
	    }
	}
    
      while(!op_stack.empty())
	{
	  ApplyOperatorPrecedence(op_stack, postfix, op_stack.begin(), op_stack.end());
	}

      // SHOULD ONLY BE ONE SENTENCE IN postfix HERE
      while(!postfix.empty())
	{
	  Sentence *s = postfix.back();
	  postfix.pop_back();
	  sentences.push_back(s);
	}
#endif
    }

    /* Add the string as a new symbol in the KB, unless already exists.
     */
    Symbol *KnowledgeBase::AddSymbol(const std::string &s_in)
    {
      std::map<std::string, Symbol *>::const_iterator it;
      it = symbols.find(s_in);
      if(it != symbols.end())
	{
	  return it->second;
	}

      // doesn't already exist;
      Symbol *s = new Symbol(s_in);
      symbols[s_in] = s;
      return s;
    }
    
    const std::map<std::string, Symbol *> &KnowledgeBase::GetSymbols() const
    {
      return symbols;
    }
    const std::vector<Sentence *> &KnowledgeBase::GetSentences() const
    {
      return sentences;
    }
  
    std::ostream & operator<<(std::ostream &os, const KnowledgeBase &kb)
    {
      const std::map<std::string, Symbol *> &symbols   = kb.GetSymbols();
      const std::vector<Sentence *>         &sentences = kb.GetSentences();

      std::map<std::string, Symbol *>::const_iterator sym_it = symbols.begin();
      std::vector<Sentence *>::const_iterator         sen_it = sentences.begin();

      while(sym_it != symbols.end())
	{
	  os << *(sym_it->second) << std::endl;
	  sym_it ++;
	}
      while(sen_it != sentences.end())
	{
	  os << *(*sen_it) << std::endl;
	  sen_it ++;
	}
    
      return os;
    }

  }
}
