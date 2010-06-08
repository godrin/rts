#ifndef RUBY_LISTENER_H
#define RUBY_LISTENER_H

#include "rice/Data_Type.hpp"
#include "rice/Constructor.hpp"
#include "rice/Director.hpp"

#include <gui_messageobject.h>


class RubyListener:public AGListener,public Rice::Director {
    public:
  RubyListener(Rice::Object self) : Rice::Director(self) { }
  
  virtual ~RubyListener() throw () {
    }
  virtual bool signal(AGEvent *m) {
      return from_ruby<bool>(getSelf().call("signal",to_ruby<AGEvent*>(m)));
  }
  bool default_signal(AGEvent *m) {
      return AGListener::signal(m);
  }

};


#endif