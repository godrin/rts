#include "rk_rubyobj.h"

#ifdef __WIN32__
#include <winsock2.h> // fix problem with fd_set
#endif
#include <ruby.h>

VALUE convertCpp2Ruby(AGRubyObject *cObject)
  {
    return Qnil;
  }
