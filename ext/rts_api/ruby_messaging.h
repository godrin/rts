#ifndef RUBY_MESSAGING_H
#define RUBY_MESSAGING_H

class RubyListener;

class SignalWrapper:public BasicRubyExposer {
    public:
      SignalWrapper(const SignalWrapper &w) :BasicRubyExposer(w) {
      }
     SignalWrapper(AGSignal* pExposable):BasicRubyExposer(pExposable) {
     }
     
     void sigConnect(RubyListener &pListener);
};


#endif
