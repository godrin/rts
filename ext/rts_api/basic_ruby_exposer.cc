#include <basic_ruby_exposer.h>
#include <basic_ruby_exposable.h>

#include <iostream>

BasicRubyExposer::BasicRubyExposer(BasicRubyExposable* pExposable):
  mExposable(pExposable)
{
  
  if(mExposable)
    mExposable->addExposer(this);
  else
  {
    std::cerr<<"mExposable is NULL!!!!"<<std::endl;
  }
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
  mExposable=0;
}

