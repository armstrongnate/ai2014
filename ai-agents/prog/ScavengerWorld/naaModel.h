#include <utility>
#include <map>

namespace naa {
  enum {
    I_UNKNOWN,
    I_PLAIN,
    I_MUD,
    I_ROCKS,
    I_WALL,
    I_CLIFF,
  };

  struct Location {
    double x, y, z;
  };

  struct Border {
    int north, south, east, west;
  };

  class Cell {
    public:
      Cell();
      Cell(int id, Location loc, Border border);
      bool IsValid();
      int id; // id is -1 for non-cells
      Location location;
      Border border;
  };

  class Model {
    public:
      Model();
      ~Model();
      bool AddCell(int id, Location loc, Border border);
      Cell FindCell(double x, double y);
      Cell GetGoalCell();
      static int InterfaceStringToInt(const char *s);
      void SetLocation(Location loc);
      void SetGoalLocation(Location loc);
      Location GetLocation();
      Location GetGoalLocation();
    protected:
    private:
      int DoubleToInt(const double d) const;
      std::map<std::pair<int,int>, Cell> cells;
      Location location;
      Location goalLocation;
      double charge;
      double hitPoints;
  };
}
