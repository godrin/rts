#ifndef BASIC_OBJECT_H
#define BASIC_OBJECT_H

#include <rice/Data_Object.hpp>
#include <basic_debug.h>

/*
namespace Basic {
  using namespace Rice;
  template<class T>
  class Object {
      Data_Object<T> *t;
    private:
      Object<T>(const Rice::Object &o) {
        if(o.is_nil()) {
          t=0;
        } else {
          t=new Data_Object<T>(o);
          std::cout<<"27PTR:"<<t->get()<<std::endl;
        }
      }
      Object<T>(T*p) {
        if(!p) {
          t=0;
        } else {
          
          t=new Data_Object<T>(p);
          std::cout<<"36PTR:"<<t->get()<<std::endl;
//          p->setSelf(*this);
        }
      }
      Object<T> &operator=(const Rice::Object &p) {
        if(p.is_nil()) {
          t=0;
        } else {
          t=new Data_Object<T>(p);
          if(!t->get()) {
            delete t;
            t=0;
            char *a=0;
            *a=123;
          }
          std::cout<<"45PTR:"<<t->get()<<std::endl;
        }
        return *this;
      }

    public:
      Object<T>() {
        t=0;
      }
      Object<T>(const Object<T> &p) {
        if(p.t) {
          t=new Data_Object<T>(*p.t);
        } else {
          t=0;
        }
      }
      Object<T>(const Rice::Data_Object<T> &p) {
        if(!p.is_nil()) {
          t=new Data_Object<T>(p);
        } else {
          t=0;
        }
      }
      Object<T> &operator=(const Object<T> &p) {
        if(p.t) {
          t=new Data_Object<T>(*p.t);
          std::cout<<"51PTR:"<<t->get()<<std::endl;
        } else {
          t=0;
        }
        return *this;
      }
      
      ~Object<T>() {
        CTRACE;
        delete t;
      }
      
      
      bool is_nil() const {
        return !(*this);
      }
      
      void mark() {
        if(t) 
          t->mark();
      }
      
      T&(operator*)() {
        return *t->get();
      }
      T*(operator->)() {
        return t->get();
      }
      T*(operator->)() const {
        return t->get();
      }
      
      template<class Y>
      (operator Object<Y>)() {
        if(t)
        return Object<Y>(*t);
        return Object<Y>();
      }
      
      (operator bool)() const{
        std::cout<<"(op bool):"<<t<<std::endl;
        if(t) {
          std::cout<<"PTR:"<<t->get()<<std::endl;
          return true;
        }
        return false;
      }
      
      Rice::Object ruby() {
        if(t)
          return *t;
        return Rice::Nil;
      }
      
      T*get() {
        if(t)
        return t->get();
        return 0;
      }
      
      bool operator==(const Basic::Object<T> &p) {
        CTRACE;
        std::cout<<"other (p):"<<(void*)&p<<std::endl;
        if(is_nil() && p.is_nil())
          return true;
        if(is_nil() || p.is_nil())
          return false;
        std::cout<<t->value()<<":::"<<p.t->value()<<std::endl;
        std::cout<<"me:"<<t->get()<<std::endl;
        std::cout<<"o:"<<p.t->get()<<std::endl;
        return *t==*p.t;
      }

      
   
  };
}
template<class T>
inline std::ostream &operator<<(std::ostream &o, Basic::Object<T> &x) {
  o<<"<BasicObject "<<x.ruby().value()<<"  "<<x.get()<<">";
  return o;
}
*/
#endif