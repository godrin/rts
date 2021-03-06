
#include "rice/Data_Type.hpp"
#include "rice/Constructor.hpp"
#include "rice/Director.hpp"

#include <gui_widget.h>
#include <gui_button.h>
#include <gui_table.h>
#include <gui_image.h>
#include <gui_ruby_widget.h>
#include <gui_edit.h>
#include <gui_tooltip.h>

#include <ruby_mappings.h>

using namespace Rice;

 void handle_my_exception(AGException const & ex)
    {
      std::cout<<"HANDLE_MY_ECXEPTION"<<std::endl;
      throw Rice::Exception(rb_eRuntimeError, ex.what());
    }


void init_GUIWidgets ( Rice::Module &rb_mGui ) {
  define_class_under<GuiRubyWidget,AGWidget> (rb_mGui,"RubyBaseWidget")
  .define_constructor(Constructor<GuiRubyWidget,Rice::Object>());
  
    define_class_under<AGButton,AGWidget> ( rb_mGui,"Button" )
    .define_director<AGButton>()
    .define_constructor ( Constructor<AGButton,Rice::Object>() )
    .define_method("caption=",&AGButton::setCaption)
    .define_method("enabled=",&AGButton::setEnabled);
    //.define_method ( "loadXML",&AGLayout::loadXML );

    
  typedef void ( AGTable::*table_addChild) (int,int,GUIWidgetPtr);

  //FIXME: Mark function must be used !!!! - problem it's implemented within Data_Object<>()
  
  define_class_under<AGTable,AGWidget>(rb_mGui,"Table")
  .define_director<AGTable>()
  //.add_handler<AGException>(handle_my_exception)
  .define_constructor(Constructor<AGTable,Rice::Object>())
  .define_method("add_fixed_row",&AGTable::addFixedRow)
  .define_method("add_row",&AGTable::addRow)
  .define_method("add_fixed_column",&AGTable::addFixedColumn)
  .define_method("add_column",&AGTable::addColumn)
  .define_method("add_child_to_cell",table_addChild(&AGTable::addChild))
  .define_method("arrange",&AGTable::arrange)
  .define_method("structure_finished",&AGTable::structureFinished)
  .define_method("cell_client_rect",&AGTable::getClientRect)
  .define_method("cols",&AGTable::getColumns)
  .define_method("rows",&AGTable::getRows);
  
  
  define_class_under<AGImage,AGWidget>(rb_mGui,"Image")
  .define_director<AGImage>()
  .define_constructor(Constructor<AGImage,Rice::Object>())
  .define_method("filename=",&AGImage::setFilename)
  .define_method("center=",&AGImage::setCenter)
  .define_method("center",&AGImage::getCenter);
  
  define_class_under<AGEdit,AGWidget>(rb_mGui,"Edit")
  .define_director<AGEdit>()
  .define_constructor(Constructor<AGEdit,Rice::Object>())
  .define_method("enabled=",&AGEdit::setMutable)
  .define_method("font=",&AGEdit::setFontByFilename)
  .define_method("caption=",&AGEdit::setText)
  .define_method("align=",&AGEdit::setAlignString)
  .define_method("vertical_align=",&AGEdit::setVAlignString);
  
  define_class_under<AGTooltip,AGWidget>(rb_mGui,"Tooltip")
  .define_director<AGTooltip>()
  .define_constructor(Constructor<AGTooltip,Rice::Object>());
    
}
// kate: indent-mode cstyle; space-indent on; indent-width 2; 
