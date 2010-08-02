#ifndef GUI_WIDGET_PTR_H
#define GUI_WIDGET_PTR_H

#include "rice/Data_Object.hpp"

#include <ruby_messaging.h>

class AGWidget;

class GUIWidgetPtr {
  public:
    GUIWidgetPtr();
    GUIWidgetPtr(const GUIWidgetPtr &p);
    explicit GUIWidgetPtr(AGWidget *w);
    explicit GUIWidgetPtr(const Rice::Data_Object<AGWidget> &w);
    explicit GUIWidgetPtr(const Rice::Object &w);
    ~GUIWidgetPtr();
    
    AGWidget *widget() const;
    Rice::Data_Object<AGWidget> *ruby() const;
    bool isRuby() const;

    (operator bool)() const;
    //AGWidget *operator->();
    AGWidget *operator->() const;
    GUIWidgetPtr &operator=(const GUIWidgetPtr &p);
    
    void clear();
    
  private:
    
    AGWidget *mWidget;
    
    Rice::Data_Object<AGWidget> *mRubyWidget;
};



#endif
