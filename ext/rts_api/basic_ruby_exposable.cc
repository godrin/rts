#include <basic_ruby_exposable.h>
#include <basic_ruby_exposer.h>

#include <basic_debug.h>

BasicRubyExposable::~BasicRubyExposable()
{
  CTRACE;
}

void BasicRubyExposable::addExposer(BasicRubyExposer* pExposer)
{
  CTRACE;
  mExposers.insert(pExposer);
}
void BasicRubyExposable::removeExposer(BasicRubyExposer* pExposer)
{
  CTRACE;
  mExposers.erase(pExposer);
}
void BasicRubyExposable::removeMeFromExposers()
{
  for(std::set<BasicRubyExposer*>::iterator i=mExposers.begin();i!=mExposers.end();i++) {
    (*i)->unbindCppObject();
  }
}
