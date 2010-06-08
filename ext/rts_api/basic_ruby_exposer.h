#ifndef BASIC_RUBY_EXPOSER_H
#define BASIC_RUBY_EXPOSER_H

class BasicRubyExposable;

class BasicRubyExposer {
  public:
    BasicRubyExposer(BasicRubyExposable *pExposable);
    ~BasicRubyExposer();
    void unbindCppObject();
    
    BasicRubyExposable *getDirect() {
      return mExposable;
    }
    
    template<class T> T *get() {
      return dynamic_cast<T*>(mExposable);
    }
  private:
    BasicRubyExposable *mExposable;
};

#endif
