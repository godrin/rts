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


/*
template<class T>
Rice::Object to_ruby<T> ( T const & x ) {
    return Rice::Data_Object<T> ( new T( x ) );

}
*/
template<>
Rice::Object to_ruby<AGRect2> ( AGRect2 const & x );
template<>
Rice::Object to_ruby<AGEvent> ( AGEvent const & x );

template<>
GUIWidgetPtr from_ruby<GUIWidgetPtr> ( Rice::Object x );

template<>
void ruby_mark<AGWidget>(AGWidget*t);
template<>
void ruby_mark<AGApplication>(AGApplication*t);

#endif
