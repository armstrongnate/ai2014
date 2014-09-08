#ifndef _OBJECT_H_
#define _OBJECT_H_

namespace ai
{
  namespace Agent
  {
    class Object
    {
    public:
      Object();
      virtual ~Object();
      virtual bool IsAlive() const;
      void SetName(const std::string &name_in);
      const std::string & GetName() const;
      void SetLocation(Location *location_in);
      Location * GetLocation();
      virtual Percept *GetPercept(const Location *location_in) = 0;
    protected:
      std::string name;
      Location *location;
    private:
      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
      {
        ar & name;
        ar & location;
      }
    };
  }
}

#endif /* _OBJECT_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
