

#include "rice/Data_Type.hpp"
#include "rice/Constructor.hpp"
#include "rice/Director.hpp"

#include <gui_application.h>
#include <gui_glscreen.h>
#include <gui_main.h>
#include <gui_video.h>
#include <gui_layout.h>
#include <basic_ruby_exposer.h>

using namespace Rice;


void initGLScreen() {
    AGMain *m=new AGMain();
    AGVideoManager *v=new AGVideoManager();
    m->setVideo ( v );
    v->initVideo ( 1024,768,32,false,true );
}

template<>
GUIWidgetPtr from_ruby<GUIWidgetPtr>(Object x) {
   return GUIWidgetPtr(x);
}

template<>
AGString from_ruby<AGString>(Object x) {
    Rice::String s=(Rice::String)x;
    return AGString(s.str());
}

template<>
Object to_ruby<AGSignal*>(AGSignal * const &x ) {
    return Data_Object<BasicRubyExposer>(new BasicRubyExposer(x));
}
/*
template<>
Object to_ruby<AGWidget*>(AFWidget * const &x ) {
    return Data_Object<BasicRubyExposer>(new BasicRubyExposer(x));
}*/

/*
template<>
Object to_ruby<AGSignal*>(AGSignal * const&x) {
    return Data_Object<AGSignal>(x);
}
  
template<>
AGSignal* from_ruby<AGSignal*>(Object x) {
    Data_Object<AGSignal> s=(Data_Object<AGSignal> )(x);
    return s.get();
}
  */
  
class RubyListener:public AGListener,public Rice::Director {
    public:
         RubyListener(Object self) : Rice::Director(self) { }
  

    virtual ~RubyListener() throw () {
    }
  virtual bool signal(AGEvent *m) {
      return from_ruby<bool>(getSelf().call("signal",to_ruby<AGEvent*>(m)));
  }
  bool default_signal(AGEvent *m) {
      return AGListener::signal(m);
  }

};




void init_AGApplication() {
    AGLayout::registerLayouts();
    
    Rice::Module rb_mGui = define_module ( "GUI" );
    
    //Data_Object<AGSignal> d=new Data_Object<AGSignal>(

    rb_mGui.define_module_function ( "initGLScreen",&initGLScreen );

    define_class_under<AGApplication> ( rb_mGui,"Application" )
    .define_constructor ( Constructor<AGApplication>() )
    .define_method ( "run", &AGApplication::run )
    .define_method("mainWidget=",&AGApplication::setMainWidget)
    .define_method("tryQuit",&AGApplication::tryQuit);
    
    define_class_under<BasicRubyExposer>(rb_mGui,"BasicRubyExposer");
    
    define_class_under<AGEvent>(rb_mGui,"AGEvent");
    
    define_class_under<AGListener>(rb_mGui,"AGListener");
    define_class_under<RubyListener,AGListener>(rb_mGui,"Listener")
     .define_director<RubyListener>()
      .define_constructor(Constructor<RubyListener, Rice::Object>())

    .define_method("signal",&RubyListener::default_signal);
    
    typedef void (AGSignal::*mrb_connect)(AGListener &pListener);

    define_class_under<AGSignal>(rb_mGui,"Signal")
    .define_method("connectCPP",mrb_connect(&AGSignal::connect));

    define_class_under<AGWidget>(rb_mGui,"Widget").
    define_method("getChild",&AGWidget::getChild).
    
    // FIXME: add wrapper class like GUIWidgetPtr
    define_method("sigClick",&AGWidget::getSigClick);
    
    define_class_under<AGLayout,AGWidget>(rb_mGui,"Layout")
    .define_constructor(Constructor<AGLayout,GUIWidgetPtr>())
    .define_method("loadXML",&AGLayout::loadXML);
    
}

// kate: indent-mode cstyle; space-indent on; indent-width 4; 
