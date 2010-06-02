#ifndef BASIC_RUBY_EXPOSER_H
#define BASIC_RUBY_EXPOSER_H

class BasicRubyExposable;

class BasicRubyExposer {
  public:
    BasicRubyExposer(BasicRubyExposable *pExposable);
    ~BasicRubyExposer();
    void unbindCppObject();
  private:
    BasicRubyExposable *mExposable;
};

#endif
