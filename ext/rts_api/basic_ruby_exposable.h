#ifndef BASIC_RUBY_EXPOSABLE_H
#define BASIC_RUBY_EXPOSABLE_H

#include <set>

class BasicRubyExposer;

class BasicRubyExposable {
  public:
    ~BasicRubyExposable();
    void addExposer(BasicRubyExposer *pExposer);
    void removeExposer(BasicRubyExposer *pExposer);
    
  private:
    void removeMeFromExposers();
    
    std::set<BasicRubyExposer*> mExposers;
};


#endif
