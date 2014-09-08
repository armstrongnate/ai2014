#include "Symbol.h"
#include "Sentence.h"
#include "KnowledgeBase.h"

namespace ai
{
  namespace PL
  {
    Symbol::State operator++(Symbol::State &lhs, int x)
    {
      Symbol::State copy = lhs;
      switch(lhs)
				{
				case Symbol::STATE_MIN:
					lhs = Symbol::KNOWN_TRUE;
					break;
				case Symbol::KNOWN_TRUE:
					lhs = Symbol::KNOWN_FALSE;
					break;
				case Symbol::KNOWN_FALSE:
					lhs = Symbol::UNKNOWN;
					break;
				case Symbol::UNKNOWN:
					lhs = Symbol::STATE_MAX;
					break;
				case Symbol::STATE_MAX:
					// do nothing
					break;
				}
      return copy;
    }
  
    std::ostream & operator<<(std::ostream &os, const Symbol::State &rhs)
    {
      switch(rhs)
				{
				case Symbol::KNOWN_TRUE:
					os << "True";
					break;
				case Symbol::KNOWN_FALSE:
					os << "False";
					break;
				case Symbol::UNKNOWN:
					os << "Unknown";
					break;
				default:
					os << "Error";
					break;
				}
      return os;
    }

  
    Symbol::Symbol(const std::string &name_in)
    {
      name = name_in;
      value = Symbol::UNKNOWN;
    }
  
    void Symbol::SetValue(State value_in)
    {
      value = value_in;
    }
  
    std::string Symbol::GetName() const
    {
      return name;
    }
  
    Symbol::State       Symbol::GetValue() const
    {
      return value;
    }
		
		int         Symbol::GetNumber() const
		{
			return this->number;
		}
		void        Symbol::SetNumber(int number_in)
		{
			this->number = number_in;
		}
  
    bool operator==(const Symbol &lhs, const Symbol &rhs)
    {
      return lhs.GetName() == rhs.GetName();
    }
    bool operator==(const Symbol &lhs, const std::string &rhs)
    {
      return lhs.GetName() == rhs;
    }
    bool operator==(const std::string &lhs, const Symbol &rhs)
    {
      return rhs.GetName() == lhs;
    }
  
  
    std::ostream & operator<<(std::ostream &os, const Symbol &s)
    {
      os << s.GetName() << " = " << s.GetValue() << "[" << s.GetNumber() << "]";
      return os;
    }
  }
}
