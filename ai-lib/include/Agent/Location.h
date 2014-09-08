#ifndef _LOCATION_H_
#define _LOCATION_H_

namespace ai
{
  namespace Agent
  {
    class Location
    {
    public:
      virtual ~Location();
      virtual void PlaceHolder() { };
    protected:
    private:
      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
      {
      }
    };
  }
}

#endif /* _LOCATION_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
