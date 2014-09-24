#include "ai_search.h"

namespace naa {
  class SearchState : public ai::Search::State {
    public:
      SearchState();
      SearchState(const double x_in, const double y_in, const double z_in, const double charge_in);
      virtual ~SearchState();
      virtual void Display() const;
      virtual bool IsEqual(const State * const state_in) const;

      double GetX() const;
      double GetY() const;
      double GetZ() const;
      double GetCharge() const;

      bool SetX(const double &x_in);
      bool SetY(const double &y_in);
      bool SetZ(const double &z_in);
      bool SetCharge(const double &charge_in);

    protected:
      double x, y, z;
      double charge;
  };
}
