

#include "rice/Data_Type.hpp"
#include "rice/Constructor.hpp"
#include "rice/Director.hpp"

#include <gui_application.h>
#include <gui_glscreen.h>
#include <gui_main.h>
#include <gui_video.h>
#include <gui_layout.h>
#include <basic_ruby_exposer.h>

#include <ruby_listener.h>

#include <basic_debug.h>

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
    Object to_ruby<SignalWrapper>(SignalWrapper const & x) {
        TRACE;
        return Data_Object<SignalWrapper>(new SignalWrapper(x));
    }



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
    
    typedef void (SignalWrapper::*mrb_connect)(AGListener &pListener);

    define_class_under<SignalWrapper>(rb_mGui,"Signal")
    .define_method("connectCPP",mrb_connect(&SignalWrapper::sigConnect));

    define_class_under<AGWidget>(rb_mGui,"Widget").
    define_method("getChild",&AGWidget::getChild).
    
    // FIXME: add wrapper class like GUIWidgetPtr
    define_method("sigClick",&AGWidget::getSigClick);
    
    define_class_under<AGLayout,AGWidget>(rb_mGui,"Layout")
    .define_constructor(Constructor<AGLayout,GUIWidgetPtr>())
    .define_method("loadXML",&AGLayout::loadXML);
    
}

// kate: indent-mode cstyle; space-indent on; indent-width 4; 
