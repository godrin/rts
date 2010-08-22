#ifndef BASIC_NULLABLE_H
#define BASIC_NULLABLE_H

inline void crashassert(bool x) {
  if(!x) {
    char *x=0;
    *x=123;
  }
}

template<class T>
class Nullable {
  T*t;
  public:
    Nullable():t(0) {
    }
    Nullable(int x):t(0) {
      crashassert(x==0);
    }
    Nullable(const T &p) {
      crashassert(!p.is_nil());
      crashassert(p.get());
      t=new T(p);
    }
    ~Nullable() {
      reset();
    }
    void reset() {
      delete t;
      t=0;
    }
    
    Nullable &operator=(const T &p) {
      crashassert(!p.is_nil());
      crashassert(p.get());
      delete t;
      t=new T(p);
      return *this;
    }
    Nullable &operator=(const Nullable &p) {
      delete t;
      if(p.t)
        t=new T(*p.t);
      else
        t=0;
      return *this;
    }
    
    bool operator==(const T&p) const {
      if(t) {
        return (*t)==p;
      }
      return false;
    }
    bool operator!=(const T&p) const {
      return !operator==(p);
    }
    
    (operator bool)() {
      return t;
    }
    T &operator*() {
      crashassert(t);
      crashassert(!t->is_nil());
      crashassert(t->get());
      return *t;
    }
    T *operator->() {
      crashassert(t);
      crashassert(!t->is_nil());
      crashassert(t->get());
      return t;
    }
    const T &operator*() const {
      crashassert(t);
      crashassert(!t->is_nil());
      crashassert(t->get());
      return *t;
    }
    const T *operator->() const {
      crashassert(t);
      crashassert(!t->is_nil());
      crashassert(t->get());
      return t;
    }
};

#endif
