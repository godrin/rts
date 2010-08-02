#include <ruby_mappings.h>
#include <gui_table.h>

#include <basic_debug.h>

template<>
GUIWidgetPtr from_ruby<GUIWidgetPtr> ( Rice::Object x )
{
  return GUIWidgetPtr ( x );
}

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
Rice::Object to_ruby<GUIWidgetPtr> ( GUIWidgetPtr const & x )
{
  return *x.ruby();
}

template<>
void ruby_mark<AGWidget>(AGWidget*t) {
  TRACE;
  t->mark();
}
