/*
#include <gui_widgetptr.h>
#include <basic_debug.h>
#include <gui_widget.h>

#include <rice/Data_Type_defn.hpp>
#include <rice/Data_Type.hpp>

GUIWidgetPtr::GUIWidgetPtr () {
  CTRACE;
  mWidget=0;
  mRubyWidget=0;
}

GUIWidgetPtr::GUIWidgetPtr(const GUIWidgetPtr& p)
{
  CTRACE;
  mRubyWidget=0;
  mWidget=p.mWidget;
  if(p.mRubyWidget)
  {
    if(mWidget) {
      std::cout<<"mWidget:"<<mWidget<<"  "<<typeid(*mWidget).name()<<std::endl;
    } else {
      std::cout<<"ruby widget !=null but mWidget==null !!!"<<std::endl;
    }
      
    mRubyWidget=new Rice::Data_Object<AGWidget>(*p.mRubyWidget);
    std::cout<<"created:"<<mRubyWidget<<" from :"<<p.mRubyWidget<<std::endl;
  }
  if(mWidget)
    mWidget->regPtr(this);
}

GUIWidgetPtr::GUIWidgetPtr ( AGWidget *w ) {
  CTRACE;
  mWidget=w;
  mRubyWidget=0;
//  assert(mWidget);
  if(mWidget) {
    mWidget->regPtr(this);
  }
}
GUIWidgetPtr::GUIWidgetPtr ( const Rice::Data_Object<AGWidget> &w ) {
  CTRACE;
  mRubyWidget=new Rice::Data_Object<AGWidget> ( w );
  mWidget=mRubyWidget->get();
  assert(mWidget);
  if(mWidget) {
    mWidget->regPtr(this);
  }
}

GUIWidgetPtr::GUIWidgetPtr ( const Rice::Object &w ) {
  CTRACE;
  mWidget=0;
  if ( w.is_nil() ) {
    mRubyWidget=0;
    mWidget=0;
  } else {
    std::cout<<typeid(w).name()<<std::endl;
    const Rice::Data_Object<AGWidget> *x=dynamic_cast<const Rice::Data_Object<AGWidget>* > ( &w );
    if(w.is_nil()) {
      mRubyWidget=0;
      mWidget=0; 
    } else if(w.is_a(Rice::Data_Type<AGWidget>::klass())){
      const Rice::Data_Type<AGWidget> &dt=Rice::Data_Type<AGWidget>::klass();
      VALUE rv=w.value();
      
      Rice::Data_Object<AGWidget> foo2(rv, dt);
      std::cout<<"FOO:"<<foo2.get()<<std::endl;
      if(x==0) {
        std::cout<<"X is null:"<<x<<std::endl;
      }
      //mRubyWidget=new foo2; //w.w.value();
      mRubyWidget=new Rice::Data_Object<AGWidget> ( foo2 );
      mWidget=mRubyWidget->get();
    } else {
      std::cout<<"w is neither nil nor AGWidget!"<<std::endl;
      std::cout<<"classname:"<<w.class_of().name()<<std::endl;
      std::cout<<"inspect:"<<w.inspect()<<std::endl;
      throw AGException("pointer is niL");
    }
  }
  if(mWidget) {
    mWidget->regPtr(this);
  }
}


GUIWidgetPtr::~GUIWidgetPtr() {
  CTRACE;
  if(mWidget) {
    mWidget->unregPtr(this);
  }
  std::cout<<"mrubywidget:"<<mRubyWidget<<std::endl;
  delete mRubyWidget;  WTF!!!!
}

void GUIWidgetPtr::clear()
{
  mWidget=0;
}


GUIWidgetPtr &GUIWidgetPtr::operator=(const GUIWidgetPtr &p) {
  if(mRubyWidget)
    delete mRubyWidget;
  if(mWidget)
    mWidget->unregPtr(this);
  mRubyWidget=0;
  mWidget=p.mWidget;
  if(p.mRubyWidget)
  {
    mRubyWidget=new Rice::Data_Object<AGWidget>(*p.mRubyWidget);
    std::cout<<"created:"<<mRubyWidget<<" from :"<<p.mRubyWidget<<std::endl;
  }
  if(mWidget)
    mWidget->regPtr(this);
  
  
  return *this;
}


AGWidget *GUIWidgetPtr::widget() const{
  return mWidget;
}
bool GUIWidgetPtr::isRuby() const {
  return mRubyWidget;
}

Rice::Data_Object<AGWidget> *GUIWidgetPtr::ruby() const{
  assert ( mRubyWidget );
  return mRubyWidget;
}
( GUIWidgetPtr::operator bool ) () const {
  return mWidget;
}

//AGWidget *GUIWidgetPtr::operator->() {
//    return mWidget;
//}

AGWidget *GUIWidgetPtr::operator->() const {
  return mWidget;
}
*/
