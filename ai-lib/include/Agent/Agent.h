#ifndef _AGENT_H_
#define _AGENT_H_

namespace ai
{
  namespace Agent
  {

    class Environment;
    class Agent;
    std::ostream & operator<<(std::ostream &os, const Agent * agent);
    
    class Agent: public Object
    {
    public:
      Agent();
      Agent(Socket * sock_in);
      virtual ~Agent();
      virtual bool IsAlive() const;
      virtual void Kill();
      virtual Action * Program(const Percept *percept);
      virtual bool TextDisplay(std::ostream & os) const;
      void Trace();
      void NoTrace();
      void SetPerformance(int value_in);
      void AddPerformance(int value_in);
      int GetPerformance() const;
      void SetEnvironment(Environment *env_in);
      Environment * GetEnvironment() const;
      Socket * GetSocket() const;
    protected:
      Socket * sock;
      bool alive;
      bool trace;
      int  performance;
      Environment  *environment;
    private:
      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
      {
        ar & boost::serialization::base_object<Object>(*this);
        ar & alive;
        ar & trace;
        ar & performance;
        ar & environment;
      }
    };
  }
}

#endif /* _AGENT_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
