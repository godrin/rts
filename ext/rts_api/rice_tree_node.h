#ifndef RICE_TREE_NODE_H
#define RICE_TREE_NODE_H

#include <rice/Director.hpp>
#include <rice/Data_Object.hpp>
#include <list>

#include <basic_nullable.h>

template<class T>
class ObjectTreeNode:public Rice::Director {
  public:
    typedef typename Rice::Data_Object<T> Ptr;
    typedef typename std::list<Ptr> ObjectList;
    typedef typename ObjectList::iterator ObjectIterator;
    typedef typename ObjectList::reverse_iterator ObjectRIterator;
    typedef typename std::list<T*> ParentList;
    typedef typename ParentList::iterator ParentIterator;
    private:
    ObjectList mChildren;
    ParentList mParents;
    
    public:
      ObjectTreeNode(Rice::Object me):Director(me) {
        std::cout<<"ObjectTreeNode"<<std::endl;
      }
      virtual ~ObjectTreeNode() {
        std::cout<<"~ObjectTreeNode "<<std::endl;
        clear();
      }
      void clear() {
        ObjectList cChildren=mChildren;
        ParentList cParents=mParents;
        mChildren.clear();
        mParents.clear();
        for(ObjectIterator i=cChildren.begin();i!=cChildren.end();i++) {
          (*i)->removeParent((T*)this); // no dynamic cast, because parent type may be discarded in desctrutor already !
        }
        for(ParentIterator i=cParents.begin();i!=cParents.end();i++) {
          (*i)->removeChild(getSelf());
        }
      }
      virtual void eventChildrenDeleted(const Ptr &pWidget) {
      }
      
      template<class Y>
      Nullable<Rice::Data_Object<Y> > seekParent() {
        Nullable<Rice::Data_Object<Y> > result;
        if(dynamic_cast<Y*>(this))
          return Rice::Data_Object<Y>(getSelf());
        
        for(ParentIterator i=mParents.begin();i!=mParents.end();i++) {
          result=(*i)->seekParent<Y>();
          if(result)
            break;
        }
        return result;
      }
      
      void addChildBack(const Ptr &pChild) {
        assert(pChild);
        crashassert(!pChild.is_nil());
        crashassert(pChild.get());
        mChildren.push_back(pChild);
        pChild->addParent(dynamic_cast<T*>(this));
      }
      void addChildFront(const Ptr &pChild) {
        assert(pChild);
        crashassert(!pChild.is_nil());
        crashassert(pChild.get());
        mChildren.push_front(pChild);
        pChild->addParent(dynamic_cast<T*>(this));
      }
      bool isParent(const Ptr &pObject) {
        typename std::list<T*>::iterator i=std::find(mParents.begin(),mParents.end(),pObject.get());
        return i!=mParents.end();
      }
      
      bool hasChild(const Ptr &pChild) {
        ObjectIterator i=std::find(mChildren.begin(),mChildren.end(),pChild);
        return i!=mChildren.end();
      }
      bool hasChildren() {
        return mChildren.size()>0;
      }
      void removeChild(const Ptr &pChild) {
        assert(pChild);
        pChild->removeParent(dynamic_cast<T*>(this));
        mChildren.remove(pChild);
        eventChildrenDeleted(pChild);
      }
      Ptr ptr() {
        return Ptr(getSelf());
      }
      ObjectList getChildren() const {
        return mChildren;
      }
      ObjectList getParents() const {
        ObjectList l;
        for(typename std::list<T*>::const_iterator i=mParents.begin();i!=mParents.end();i++) {
          l.push_back((*i)->getSelf());
        }
        return l;
      }
      void mark() throw() {
        for(ObjectIterator i=mChildren.begin();i!=mChildren.end();i++) {
          i->mark();
        }
      }
      template<class Y>
      Nullable<Rice::Data_Object<Y> > casted() {
        Nullable<Rice::Data_Object<Y> > r;
        if(dynamic_cast<Y*>(this))
          r=getSelf();
        return r;
      }
      
    private:
      void addParent(T*pParent) {
        crashassert(pParent);
        mParents.push_back(pParent);
      }
      void removeParent(T* pParent) {
        mParents.remove(pParent);
      }
  
};

template<class T>
typename T::Ptr Create() {
  VALUE klass=Rice::Data_Type<T>::klass();
  VALUE val=Rice::detail::default_allocation_func<T>(klass);
  T* t=new T(val);
  DATA_PTR(val)=t;
  std::cout<<"val:"<<(void*)val<<std::endl;
  std::cout<<"t->ptr:"<<(void*)t->ptr().value()<<std::endl;
  return t->ptr();
}
#endif