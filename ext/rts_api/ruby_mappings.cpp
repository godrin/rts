#include <ruby_mappings.h>
#include <gui_table.h>
#include <gui_application.h>
#include <game_app.h>

#include <basic_debug.h>



template<>
AGString from_ruby<AGString> ( Rice::Object x )
{
  Rice::String s= ( Rice::String ) x;
  return AGString ( s.str() );
}

template<>
Rice::Object to_ruby<AGString> (AGString const &a) {
  return Rice::String(a);
}


template<>
AGStringUtf8 from_ruby<AGStringUtf8> ( Rice::Object x )
{
  Rice::String s= ( Rice::String ) x;
  return AGStringUtf8 ( s.str());
}


template<>
Rice::Object to_ruby<SignalWrapper> ( SignalWrapper const & x )
{
  return Rice::Data_Object<SignalWrapper> ( new SignalWrapper ( x ) );
}


template<>
Rice::Object to_ruby<AGRect2> ( AGRect2 const & x ) {
  return Rice::Data_Object<AGRect2> ( new AGRect2( x ) );
  
}


template<>
GUIWidgetPtr from_ruby<GUIWidgetPtr> ( Rice::Object x )
{
  return GUIWidgetPtr ( x);
}



template<>
Rice::Object to_ruby<GUIWidgetPtr> ( GUIWidgetPtr const & x ) {
  return const_cast<GUIWidgetPtr&>(x);
  
}




template<>
void ruby_mark(AGWidget*t) {
  TRACE;
  std::cout<<"ruby_mark"<<std::endl;
  t->mark();
}

template<>
void ruby_mark(AGApplication*t) {
  TRACE;
  std::cout<<"ruby_mark"<<std::endl;
  t->mark();
}

template<>
void ruby_mark(GameApp*t) {
  TRACE;
  std::cout<<"ruby_mark"<<std::endl;
  t->mark();
}
template<>
void ruby_mark(AGTable*t) {
  TRACE;
  std::cout<<"ruby_mark"<<std::endl;
  t->mark();
}
