#ifndef _ENVIRONMENT_H_
#define _ENVIRONMENT_H_

namespace ai
{
  namespace Agent
  {
    class EnvironmentDisplay;
    
    class Environment
    {
      friend class ai::Agent::EnvironmentDisplay;
    public:
      Environment();
      Environment(const RandomNumber &rand_in, std::vector<Socket *> *displays_in);
      virtual ~Environment();
      virtual bool ApplyAction(Agent *agent, Action *action) = 0;
      virtual void CalculatePerformance(Agent *agent) = 0;
      virtual Percept *GetPercept(Agent *agent);
      bool IsDone() const;
      virtual void Step();
      virtual void Run(const int n_steps);
      virtual void AddAgent(Agent *agent, Location *location);
      virtual void AddObject(Object *object, Location *location);
      virtual Location *DefaultLocation() const = 0;
      void UpdateDisplays();
      void SetDelay(int delay_in);
      int GetPerformance(Agent *agent);
      Agent * GetAgent(int agent_index);
      const RandomNumber &GetRandomNumber() const;
    protected:
      std::vector<Object *> objects;
      std::vector<Agent *>  agents;
      std::vector<Socket *> *displays;
      //ai::Agent::EnvironmentDisplay   *display;
      int                   delay;
      RandomNumber          random_number;
    private:
      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
      {
        ar & objects;
        ar & agents;
        ar & delay;
        ar & random_number;
      }
    };
  }
}

#endif /* _ENVIRONMENT_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
