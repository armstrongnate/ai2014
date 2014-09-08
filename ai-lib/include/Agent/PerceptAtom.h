#ifndef _PERCEPTATOM_H_
#define _PERCEPTATOM_H_

namespace ai
{
  namespace Agent
  {
    class PerceptAtom
    {
    public:
      PerceptAtom();
      PerceptAtom(const std::string &name_in, const std::string &value_in);
      const std::string &GetName() const;
      const std::string &GetValue() const;
      void SetValue(const std::string &value_in);
    protected:
      std::string name;
      std::string value;
    private:
      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
      {
        ar & name;
        ar & value;
      }
    };
  }
}

#endif /* _PERCEPTATOM_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
