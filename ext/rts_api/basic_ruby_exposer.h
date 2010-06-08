#ifndef BASIC_RUBY_EXPOSER_H
#define BASIC_RUBY_EXPOSER_H

class BasicRubyExposable;

class BasicRubyExposer {
  public:
    BasicRubyExposer(BasicRubyExposable *pExposable);
    BasicRubyExposer(const BasicRubyExposer &orig);
    virtual ~BasicRubyExposer();
    void unbindCppObject();
    
    BasicRubyExposable *getDirect(); 
    
    template<class T> T *get() {
      return dynamic_cast<T*>(getDirect());
    }
  private:
    BasicRubyExposable *mExposable;
};

#endif
