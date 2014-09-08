#ifndef _PERCEPT_H_
#define _PERCEPT_H_
#include <map>
#include <vector>

namespace ai
{
  namespace Agent
  {
    class Percept
    {
    public:
      Percept();
      virtual ~Percept();
      virtual bool TextDisplay(std::ostream &os) const;
      virtual void Join(Percept *percept_in);
      virtual void JoinAtom(const PerceptAtom &atom_in);
      virtual unsigned int NumAtom() const;
      virtual PerceptAtom GetAtom(const int i) const;
      virtual PerceptAtom GetAtom(const std::string &name) const;
    protected:
      std::map<std::string, PerceptAtom> atoms;
      std::vector<std::string> atom_keys;
    private:
      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
      {
        ar & atoms;
        ar & atom_keys;
      }
    };
    
    std::ostream & operator<<(std::ostream &os, const Percept * percept);
  }
}

#endif /* _PERCEPT_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
