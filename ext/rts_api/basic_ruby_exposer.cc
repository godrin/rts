#include <basic_ruby_exposer.h>
#include <basic_ruby_exposable.h>

#include <iostream>
#include <basic_debug.h>

BasicRubyExposer::BasicRubyExposer(BasicRubyExposable* pExposable):
  mExposable(pExposable)
{
  CTRACE;
  std::cout<<"BasicRubyExposer:"<<this<<"::::"<<pExposable<<std::endl;
  
  if(mExposable)
    mExposable->addExposer(this);
  else
  {
    std::cerr<<"mExposable is NULL!!!!"<<std::endl;
  }
}
BasicRubyExposer::BasicRubyExposer(const BasicRubyExposer &orig):mExposable(orig.mExposable) {
  CTRACE;
  std::cout<<"BasicRubyExposer:"<<this<<"::::"<<mExposable<<std::endl;
  
  if(mExposable)
    mExposable->addExposer(this);
  else
  {
    std::cerr<<"mExposable is NULL!!!!"<<std::endl;
  }
}



void BasicRubyExposer::unbindCppObject()
{
  std::cout<<"unbindCppObject"<<std::endl;
  CTRACE;
  mExposable=0;
}

BasicRubyExposer::~BasicRubyExposer()
{
  std::cout<<"clean:"<<this<<std::endl;
  CTRACE;
  if(mExposable) {
    mExposable->removeExposer(this);
  }
  mExposable=0;
}

BasicRubyExposer &BasicRubyExposer::operator=(const BasicRubyExposer &e) {
  throw int();
  return *this;
}


BasicRubyExposable *BasicRubyExposer::getDirect() {
  std::cout<<"getDirect:"<<this<<"::"<<mExposable<<std::endl;
      return mExposable;
    }
