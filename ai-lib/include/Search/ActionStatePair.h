#ifndef _SEAARCH_ACTIONSTATEPAIR_H_
#define _SEAARCH_ACTIONSTATEPAIR_H_

namespace ai
{
  namespace Search
  {
    class ActionStatePair
    {
    public:
      ActionStatePair();
      ActionStatePair(State *state_in, Action *action_in);
      virtual ~ActionStatePair();
      
      virtual void   Display() const;
      
      State  *GetState() const;
      Action *GetAction() const;
      
    protected:
      State  *state;
      Action *action;
      
    private:
    };

  }
}

#endif /* _ACTIONSTATEPAIR_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
