

#include "rice/Data_Type.hpp"
#include "rice/Constructor.hpp"
#include "rice/Director.hpp"

#include <gui_application.h>
#include <gui_glscreen.h>
#include <gui_main.h>
#include <gui_video.h>
#include <basic_ruby_exposer.h>

#include <ruby_listener.h>
#include <ruby_mappings.h>

#include <basic_debug.h>

using namespace Rice;


void initGLScreen()
{
  AGMain *m=new AGMain();
  AGVideoManager *v=new AGVideoManager();
  m->setVideo ( v );
  v->initVideo ( 1024,768,32,false,true );
}

int apiScreenWidth() {
  return getScreen().getWidth();
}
int apiScreenHeight() {
  return getScreen().getHeight();
}

void init_GUIWidgets(Rice::Module &rb_mGui);


void init_AGApplication()
{
  Rice::Module rb_mGui = define_module ( "GUI" );
  
  
  define_class_under<AGRect2>(rb_mGui,"Rect2")
  .define_constructor(Constructor<AGRect2,float,float,float,float>())
  .define_method("to_s",&AGRect2::toString);
  

  rb_mGui.define_module_function ( "initGLScreen",&initGLScreen )
  .define_module_function("screen_width",&apiScreenWidth)
  .define_module_function("screen_height",&apiScreenHeight);

  define_class_under<AGApplication> ( rb_mGui,"Application" )
  .define_constructor ( Constructor<AGApplication>() )
  .define_method ( "run", &AGApplication::run )
  .define_method ( "main_widget=",&AGApplication::setMainWidget )
  .define_method ( "try_quit",&AGApplication::tryQuit );

  define_class_under<BasicRubyExposer> ( rb_mGui,"BasicRubyExposer" );

  define_class_under<AGEvent> ( rb_mGui,"AGEvent" );

  define_class_under<AGListener> ( rb_mGui,"AGListener" );
  define_class_under<RubyListener,AGListener> ( rb_mGui,"Listener" )
  .define_director<RubyListener>()
  .define_constructor ( Constructor<RubyListener, Rice::Object>() )

  .define_method ( "signal",&RubyListener::default_signal );

  typedef void ( SignalWrapper::*mrb_connect ) ( AGListener &pListener );

  define_class_under<SignalWrapper> ( rb_mGui,"Signal" )
  .define_method ( "connect_cpp",mrb_connect ( &SignalWrapper::sigConnect ) );

  define_class_under<AGWidget> ( rb_mGui,"Widget" ).
  define_method("add_child",&AGWidget::addChild).
  define_method ( "get_child",&AGWidget::getChild ).
  define_method ( "name=",&AGWidget::setName).
  define_method("rect",&AGWidget::getRect).
  define_method("rect=",&AGWidget::setRectInterface).
  define_method("client_rect",&AGWidget::getClientRect).

  // FIXME: add wrapper class like GUIWidgetPtr
  define_method ( "sig_click",&AGWidget::getSigClick );

  init_GUIWidgets(rb_mGui);

}

// kate: indent-mode cstyle; space-indent on; indent-width 2; 
