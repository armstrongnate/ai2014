#ifndef _SEARCH_STATE_H_
#define _SEARCH_STATE_H_
#include <string>

namespace ai
{
  namespace Search
  {
    class State
    {
    public:
      
      /* virtual to insure destructor chaining */
      virtual ~State();
      
      /* Used for text display of state information
       * to std::cout */
      virtual void Display() const;
      
      /* Used for equality testing. Must use dynamic_cast
       * to convert state_in to the correct pointer type.
       */
      virtual bool IsEqual(const State * const state_in) const = 0;
      
      /* Used to quickly store in the graph "closed list".
       */
      virtual std::string HashValue() const;
      
    protected:
    private:
    };
  }
}
#endif /* _STATE_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
