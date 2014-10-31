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

  enum {
    LOOK_DIRECTION_NORTH,
    LOOK_DIRECTION_EAST,
    LOOK_DIRECTION_SOUTH,
    LOOK_DIRECTION_WEST,
    LOOK_DIRECTION_MAX,
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
      bool Visited();
      bool Touched();
      void Display();
      int id; // id is -1 for non-cells
      Location location;
      Border border;
  };

  class Model {
    public:
      Model();
      ~Model();
      bool AddCell(int id, Location loc, Border border);
      bool CellExists(double x, double y);
      Cell FindCell(double x, double y);
      Cell GetGoalCell();
      static int InterfaceStringToInt(const char *s);
      void SetLocation(Location loc);
      void SetGoalLocation(Location loc);
      Location GetLocation();
      Location GetGoalLocation();
      double GetCharge();
      void SetCharge(double charge);
      int GetCurrentInterface(int dir);
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
