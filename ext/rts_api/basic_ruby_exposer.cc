#include <basic_ruby_exposer.h>
#include <basic_ruby_exposable.h>

BasicRubyExposer::BasicRubyExposer(BasicRubyExposable* pExposable):
  mExposable(pExposable)
{
  if(mExposable)
    mExposable->addExposer(this);
}

void BasicRubyExposer::unbindCppObject()
{
  mExposable=0;
}

BasicRubyExposer::~BasicRubyExposer()
{
  if(mExposable) {
    mExposable->removeExposer(this);
  }
}

