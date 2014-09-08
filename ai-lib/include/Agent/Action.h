#ifndef _ACTION_H_
#define _ACTION_H_

namespace ai
{
  namespace Agent
  {
    class Action;
    std::ostream & operator<<(std::ostream &os, const Action * action);
    
    class Action
    {
    public:
      Action();
      virtual ~Action();
      virtual bool TextDisplay(std::ostream &os) const = 0;
      int GetCode() const;
      void SetCode(int code_in);
    protected:
      int action_code;
    private:
      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
      {
        ar & action_code;
      }
    };
  }
}

#endif /* _ACTION_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
