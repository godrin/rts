#ifndef GUI_RUBY_WIDGET_H
#define GUI_RUBY_WIDGET_H

#include <gui_widget.h>

class GuiRubyWidget:public AGWidget {
  public:
  GuiRubyWidget(const GUIWidgetPtr &pParent,const AGRect2 &r);
};


#endif