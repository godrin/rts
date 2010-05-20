#ifndef RUBY_OBJ_H
#define RUBY_OBJ_H

// INCLUDE_SWIG - used to filter, which files are included in swig-interfacing

#ifdef WIN32
#undef connect
#undef close
#endif

/**
   AGRubyObject does handling between ruby and c++ memory management.
   Ruby has a garbage collector (GC) which is not really to be influenced.
   Every object that is created in ruby is handled by the GC.
   So we have to take care of that.

   Ruby's GC has no reference counting whatsoever but it uses a mark-and-sweep
   algorithm. When the GC is run the algorithm marks any known object and then calls
   all the objects' mark-functions which therefore call mark-functions all the objects it
   knowns. When anything known is marked, the algorithm kills any object that isn't marked.

   So all we have to do is to mark any object that is connected to the current object in any way.
   Normally you would mark any object that is a children of the current one.

   To make things easier AGRubyObject takes care of objects which are not handled by ruby. They get called
   recursively anyways. So all you have to do is overriding the mark() function and then calling
   markObject(AGRubyObject *o) for any object you want to mark.

   If you need an explicit destructor-call at a specified time you must be content with a call to clear(), which
   you can override. For deletion of any AGRubyObject you should use saveDelete. This calls clear() and deletes the
   object, if it's not a ruby-managed one.

   @see saveDelete(AGRubyObject *o)
 */

// INCLUDE_SWIG - used to filter, which files are included in swig-interfacing

#include <string>
#include <set>

#include <basic_base.h>

#include <stdexcept>

#include <iostream>

class AGRubyObject;

enum IsRubyObject {
  RUBY_OBJECT_YES, RUBY_OBJECT_NO, RUBY_OBJECT_UNKNOWN
};

AGEXPORT IsRubyObject isRubyObject(void *o);
AGEXPORT bool saveDelete(AGRubyObject *o);


/** checkedDelete deletes o, but checks before if o is a AGRubyObject
 **/
template<class T>
bool checkedDelete(T *o) {
  IsRubyObject iro = isRubyObject((void*) o);
  if (iro == RUBY_OBJECT_YES) {
    std::cerr << "Possible error in checkedDelete(.)" << std::endl;
    return false;
  } else if (iro == RUBY_OBJECT_NO) {
    delete o;
    return true;
  } else {
    std::cerr << "Could not check, because rubyObjects was discarded" << std::endl;
    return false;
  }
}

/** checkedDelete deletes o, but checks before if o is a AGRubyObject
 **/
template<class T>
bool checkedDeleteArray(T *o) {
  IsRubyObject iro = isRubyObject((void*) o);
  if (iro == RUBY_OBJECT_YES) {
    std::cerr << "Possible error in checkedDelete(.)" << std::endl;
    return false;
  } else if (iro == RUBY_OBJECT_NO) {
    delete[] o;
    return true;
  } else {
    std::cerr << "Could not check, because rubyObjects was discarded" << std::endl;
    return false;
  }
}


class AGRubyObject;

class AGEXPORT AGBaseObject
{
protected:
  AGRubyObject *mp;
public:
  // AGBaseObject(.) should never throw an exception, because it may be called from ruby-functions not expection it to do so
  AGBaseObject(AGRubyObject *p) throw ();

  // ~AGBaseObject should never throw an exception, because it may be called by ruby's garbage collector
  ~AGBaseObject() throw ();
  void baseClear() throw ();

  bool valid() throw ()
    {
      return mp;
    }
};


/**
 * gc_ptr<T> is a managed ptr to a (possibly) garbage-collected object
 * it will be redirected to 0, if the targeted object is destroyed. So
 * you'll get a null-pointer exception when the object is not longer
 * present. This prevents you from accessing random memory.
 */
template<class T>
class AGEXPORT gc_ptr:public AGBaseObject
{
public:
  gc_ptr(T*t):AGBaseObject(t)
  {
  }

  T*operator->()
    {
      return (T*)mp;
    }
  T* getPtr()
  {
    if(!mp)
      throw std::runtime_error("mp not defined!");
    return (T*)mp;
  }
};

/**
 *
 * */
class AGEXPORT AGRubyObject
{
public:
  /**
     This is copied from ruby.h, so that this header-file is not included all over the place.
     FIXME: this must eventually be changed - when the ruby implementation changes
   */
  typedef unsigned long VALUE;

  AGRubyObject() throw();
  virtual ~AGRubyObject() throw();

protected:
#ifndef SWIG
  // functions shouldn't be exported and NEVER be used in ruby!
  virtual void clear() throw();
  virtual void mark() throw();
  void markObject(AGRubyObject *o,bool recursive=true) throw();

#endif
public:
#ifndef SWIG

#endif
  friend void general_markfunc(void *ptr);
  friend bool saveDelete(AGRubyObject *o);

  void addRef(AGBaseObject *o);
  void deleteRef(AGBaseObject *o);
private:
  std::set<AGBaseObject*> mReferences;
};

AGEXPORT void general_markfunc(void *ptr);

AGEXPORT void *getAddressOfRubyObject(AGRubyObject *object);
AGEXPORT bool rubyObjectExists(void *o);

AGEXPORT void setQuitting();

#endif
