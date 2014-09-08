#ifndef _RANDOMNUMBER_H_
#define _RANDOMNUMBER_H_

namespace ai
{
  namespace Agent
  {
    class RandomNumber
    {
    public:
      RandomNumber();
      RandomNumber(int iseed_in);
      RandomNumber(const RandomNumber &rhs);
      void Reseed(int iseed_in);
      double Rand();
      RandomNumber &operator=(const RandomNumber &rhs);
    protected:
    private:
      double fac;
      int mz;
      int mbig;
      int mseed;
      int ma[55];
      int inext;
      int inextp;
      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
      {
        ar & fac;
        ar & mz;
        ar & mbig;
        ar & mseed;
        ar & ma;
        ar & inext;
        ar & inextp;
      }
    };
  }
}

#endif /* _RANDOMNUMBER_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
