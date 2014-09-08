#include <ai_agent.h>

namespace ai
{
  namespace Agent
  {
    Object::Object()
    {
      name = "";
      location = 0;
    }
    Object::~Object()
    {
      if(location)
	{
	  delete location;
	  location = 0;
	}
    }
    bool Object::IsAlive() const
    {
      return false;
    }
    void Object::SetName(const std::string &name_in)
    {
      name = name_in;
    }
    const std::string & Object::GetName() const
    {
      return name;
    }
    void Object::SetLocation(Location *location_in)
    {
      location = location_in;
    }
    Location * Object::GetLocation()
    {
      return location;
    }
  }
}
