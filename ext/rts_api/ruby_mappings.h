#ifndef RUBY_MAPPINGS_H
#define RUBY_MAPPINGS_H

#include <gui_widget.h>


#include "rice/Data_Type.hpp"
#include "rice/Constructor.hpp"

template<>
GUIWidgetPtr from_ruby<GUIWidgetPtr> ( Rice::Object x );

template<>
AGString from_ruby<AGString> ( Rice::Object x );

template<>
Rice::Object to_ruby<AGString> (AGString const &a);

template<>
AGStringUtf8 from_ruby<AGStringUtf8> ( Rice::Object x );

template<>
Rice::Object to_ruby<SignalWrapper> ( SignalWrapper const & x );

template<>
Rice::Object to_ruby<GUIWidgetPtr> ( GUIWidgetPtr const & x );


template<>
GUIWidgetPtr from_ruby<GUIWidgetPtr> ( Rice::Object x );

template<>
void ruby_mark<AGWidget>(AGWidget*t);

#endif
