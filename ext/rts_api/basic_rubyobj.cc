#include <basic_base.h>
#include <basic_rubyobj.h>
#include <assert.h>
#include <typeinfo>
#include <set>
#include <map>
#include <iostream>
#include <basic_logging.h>


#ifdef __WIN32__
#include <winsock2.h> // fix problem with fd_set
#endif
#include <ruby.h>

bool mRubyQuitting = false;
bool mRubyObjectsExistant = false;

void deleteCppReference(AGRubyObject *cObject);


class RubyObjects : public std::set<AGRubyObject*> {
public:

  RubyObjects() {
    mRubyObjectsExistant = true;
  }

  virtual ~RubyObjects() {
    mRubyObjectsExistant = false;
  }
};

// this set keeps track of all valid instances of AGRubyObject
RubyObjects mRubyObjects;
std::set<AGRubyObject*> mRemovedRubyObjects;

void setQuitting() {
  mRubyQuitting = true;
}

AGEXPORT void *getAddressOfRubyObject(AGRubyObject *o) {
  return o;
}


AGRubyObject::AGRubyObject() throw () {
  logger::gc << "new AGRubyObject:" << this << logger::endl;
  if(mRubyObjects.find(this) != mRubyObjects.end())
    logger::err<< "RubyObject does already exist ????"<<logger::endl;
  // assert(mRubyObjects.find(this) == mRubyObjects.end());
  mRubyObjects.insert(this);
  size_t oSize = mRemovedRubyObjects.size();

  mRemovedRubyObjects.erase(this);
  if (oSize != mRemovedRubyObjects.size())
    logger::gc<< "Collision - removed rubyobject's address is overwritten!" << logger::endl;
  logger::gc << "current ruby#:" << mRubyObjects.size() << " removed:" << mRemovedRubyObjects.size() << logger::endl;
}

AGRubyObject::~AGRubyObject() throw () {
  logger::gc << "removed AGRubyObject:" << this << logger::endl;
  assert(mRubyObjects.find(this) != mRubyObjects.end());
  assert(mRemovedRubyObjects.find(this) == mRemovedRubyObjects.end());
  //std::cerr<<"AGRubyObject::Removed:"<<this<<std::endl;
  for (std::set<AGBaseObject*>::iterator i = mReferences.begin(); i != mReferences.end(); i++)
    (*i)->baseClear();
  mRubyObjects.erase(this);
  mRemovedRubyObjects.insert(this);
  //deleteCppReference(this);
}


/// override this function to mark your children

void AGRubyObject::mark() throw () {
}


void AGRubyObject::clear() throw () {
}

void AGRubyObject::addRef(AGBaseObject *o) {
  mReferences.insert(o);
}

void AGRubyObject::deleteRef(AGBaseObject *o) {
  mReferences.erase(o);
}



/// this is the marking function, that gets called by ruby
/// it handles all the AGRubyObjects


IsRubyObject isRubyObject(void *o) {
  AGRubyObject *ro = (AGRubyObject*) o;

  if (!mRubyObjectsExistant) {
    logger::err << "Could not check, because rubyObjects was discarded" << logger::endl;
    return RUBY_OBJECT_UNKNOWN;
  }

  if (mRubyObjects.find(ro) == mRubyObjects.end())
    return RUBY_OBJECT_NO;
  else
    return RUBY_OBJECT_YES;

}

AGBaseObject::AGBaseObject(AGRubyObject *p) throw ()
: mp(p) {
  if (p)
    p->addRef(this);
}

AGBaseObject::~AGBaseObject() throw () {
  if (mp)
    mp->deleteRef(this);
}

void AGBaseObject::baseClear() throw () {
  mp = 0;
}
