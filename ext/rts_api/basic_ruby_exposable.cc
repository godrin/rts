#include <basic_ruby_exposable.h>
#include <basic_ruby_exposer.h>

BasicRubyExposable::~BasicRubyExposable()
{

}

void BasicRubyExposable::addExposer(BasicRubyExposer* pExposer)
{
  mExposers.insert(pExposer);
}
void BasicRubyExposable::removeExposer(BasicRubyExposer* pExposer)
{
  mExposers.erase(pExposer);
}
void BasicRubyExposable::removeMeFromExposers()
{
  for(std::set<BasicRubyExposer*>::iterator i=mExposers.begin();i!=mExposers.end();i++) {
    (*i)->unbindCppObject();
  }
}
