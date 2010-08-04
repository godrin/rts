#ifndef AG_GEOMETRY_EXCEPTION
#define AG_GEOMETRY_EXCEPTION

#include <string>
#include <basic_exception.h>

class GeometryException:public AGException {
public:

  GeometryException(const std::string &p) : AGException(p) {
  }
};

#endif