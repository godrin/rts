module Antargis
  
  module LayoutElements
    def table(args=nil,&block)
      t=GUI::Table.new(me,self.rect)
      processArgs(t,args)
      l=TableLayout.new(t)
      add(t)
      if block
        l.instance_eval(&block)
      end
      pp "RECTS:"
      pp t.rect
      pp t.client_rect
      t.arrange
      t
    end
    
    def arrange
    end
    
    def text(args)
      image=GUI::Edit.new(@table,self.rect)
      processArgs(image,args)
      add(image)
      image
    end

    def image(args)
      image=GUI::Image.new(@table,self.rect)
      processArgs(image,args)
      add(image)
      image
    end
    
    def button(args)
      image=GUI::Button.new(@table,self.rect)
      processArgs(image,args)
      add(image)
      image
    end
    
    def rect
      GUI::Rect2.new(0,0,0,0)
    end
    
    
    def processArgs(target,args)
      if args
        args.each{|k,v|
          target.send(k.to_s+"=",v)
        }
      end
    end
  end
  
  class TableCell
    include LayoutElements
    def initialize(table,x,y)
      @table=table
      @x=x
      @y=y
    end
    
    def me
      @table
    end
    
    def add(widget)
      pp "TableCell::add"
      @table.add_child_to_cell(@x,@y,widget)
      pp "ADD TABLECELL"
      pp @table.rect
      @table.arrange
    end
    
  end
  
  class TableLayout
    def initialize(table)
      @table=table
    end
    
    def me
      @table
    end
    def arrange
      @table.arrange
    end
    
    def row(params=nil)
      if params
	if params.is_a?(Hash)
	  if params[:fixed].is_a?(Numeric)
	    @table.add_fixed_row(params[:fixed])
	  elsif params[:relative].is_a?(Numeric)
	    @table.add_row(params[:relative])
	  else
	    @table.add_row(1)
	  end
	else
	  pp params,params.class
	  raise 1
	end
      else
	@table.add_row(1)
      end
    end
    def col(params=nil)
      if params
	if params.is_a?(Hash)
	  if params[:fixed].is_a?(Numeric)
	    @table.add_fixed_column(params[:fixed])
	  elsif params[:relative].is_a?(Numeric)
	    @table.add_column(params[:relative])
	  else
	    @table.add_column(1)
	  end
	else
	  pp params,params.class
	  raise 1
	end
      else
	@table.add_column(1)
      end
    end
    def cell(x,y,&block)
      #arrange
      TableCell.new(@table,x,y).instance_eval(&block)
    end
  end
  
  class RubyLayout<GUI::RubyBaseWidget
    include LayoutElements
    def initialize(parent)
      rect=GUI::Rect2.new(0,0,GUI::screen_width,GUI::screen_height)
      
      if parent
        rect=parent.getClientRect
      end
      pp "RubyLayout"
      pp rect
      super(parent,rect)
      pp "MyRect:",self.rect
      pp "MyClientRect:",self.client_rect
      layout
    end
    
    #def rect
    #  client_rect
    #end
    
  end
  
  class MainMenuLayout<RubyLayout
    def me
      nil
    end
    def add(x)
      pp "MainMenuLayout::add"
      pp "X:",x
      pp "clientrect:",self.client_rect
      x.rect=self.client_rect
      add_child(x)
    end
    def layout
      table(:name=>"outer") {
        row(:fixed=>200)
        row(:fixed=>30)
        row
        row(:fixed=>34)
        col
        cell(0,0) {
          image(:filename=>"data/gui/antargisLogo.png")
        }
    cell(0,2)  {
       table(:name=>"menubuttons") {
         1.upto(6) {row ; row(:relative=>2) } ; row
         col(:relative=>2)
         col(:relative=>0.6)
         col(:fixed=>5)
         cell(0, 0) { button(:name=>"tutorial", :caption=>"Tutorial") }
         cell(0, 2) { button(:name=>"campaign", :caption=>"Start campaign") }
         cell(0, 4) { button(:name=>"single", :caption=>"Single Map", :enabled=>true) }
         cell(0, 6) { button(:name=>"load", :caption=>"Load game") }
         cell(0, 8) { button(:name=>"options", :caption=>"Options") }
         cell(0,10) { button(:name=>"credits", :caption=>"Credits") }
         cell(0,12) { button(:name=>"quit", :caption=>"Quit") }
       }
     }
     cell(0,0) {
      table(:name=>"forestpic") {
        row(:fixed=>5)
        row(:fixed=>456)
        row
        col
        col(:fixed=>606)
        col
        cell(1,1) { image(:filename=>"data/gui/small_forest.png") }
      }
    }
    cell(0,3) { text(:font=>"yellow.font", :align=>"center", :enabled=>false, :caption=>"(C) 2005-2007 by the Antargis-team") }
         }
    end
  end

end