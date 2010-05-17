#ifndef AG_GEOMETRY_EXCEPTION
#define AG_GEOMETRY_EXCEPTION

#include <string>

class GeometryException {
public:

  GeometryException(const std::string &p) : s(p) {
  }
#ifdef SWIG
  %rename(to_s) what() const;
#endif

  std::string what() const {
    return s;
  }

private:
  std::string s;
};

#endif