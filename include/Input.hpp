#include <string>
struct Pos;

const std::string QUIT_KEY = "q";
const std::string SELECTION_KEY = "s";

// class for exception handling
class Input {
public:
  static std::string getStr();
  static Pos getPos();
  static void pressEnter();
};
