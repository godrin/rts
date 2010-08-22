#ifndef GUI_WIDGET_PTR_H
#define GUI_WIDGET_PTR_H

#include <basic_object.h>
//#include <ruby_messaging.h>
#include "rice_tree_node.h"


class AGWidget;

typedef ObjectTreeNode<AGWidget>::Ptr GUIWidgetPtr;

/*
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

*/

#endif
