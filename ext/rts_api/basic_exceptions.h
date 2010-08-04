#ifndef BASIC_EXCEPTIONS_H
#define BASIC_EXCEPTIONS_H

#include <basic_exception.h>

class NotImplementedException:public AGException {
  public:
  NotImplementedException(const std::string& e):AGException(e) {
  }
};

#endif
