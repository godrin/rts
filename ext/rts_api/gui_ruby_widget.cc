#include <gui_ruby_widget.h>

GuiRubyWidget::GuiRubyWidget ( const GUIWidgetPtr &pParent,const AGRect2 &r ) :
    AGWidget ( pParent,r ) {
  std::cout<<"GuiRubyWidget::GuiRubyWidget  Rect:"<<r.toString()<<std::endl;
  std::cout<<"GuiRubyWidget::GuiRubyWidget  getRect:"<<getRect().toString()<<std::endl;
}
// kate: indent-mode cstyle; space-indent on; indent-width 2; 
