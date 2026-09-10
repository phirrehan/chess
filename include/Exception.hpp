#include <string>

// base class
class Exception {
private:
  std::string str;

public:
  Exception(std::string s) : str(s) {}
  std::string what() const { return str; }
};

// child classes
class ReturnToSelection : public Exception {
public:
  ReturnToSelection(std::string s) : Exception(s) {}
};
class Terminate : public Exception {
public:
  Terminate(std::string s) : Exception(s) {}
};
class InvalidInput : public Exception {
public:
  InvalidInput(std::string s) : Exception(s) {}
};
class InvalidPos : public Exception {
public:
  InvalidPos(std::string s) : Exception(s) {}
};
class InvalidMove : public Exception {
public:
  InvalidMove(std::string s) : Exception(s) {}
};
