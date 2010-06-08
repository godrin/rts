module Antargis
  class MainMenuLayout<GUI::Layout
    class << self
      def layout
	table {
	  row(:fixed=>200)
	  row(:fixed=>30)
          row
    row(:fixed=>34)
    col
          cell(0,0) {
      image(:filename=>"data/gui/antargisLogo.png",:enabled=false))
    }
    cell(0,2)  {
       table {
         row
         col(:relative=>2)
         col(:relative=>0.6)
         col(:fixed=>5)
         cell( 0,0) { button(:name=>"tutorial", :caption=>"Tutorial") }
         cell( 2,0) { button(:name=>"campaign", :caption=>"Start campaign") }
         cell( 4,0) { button(:name=>"single", :caption=>"Single Map", :enabled=>true) }
         cell( 6,0) { button(:name=>"load", :caption=>"Load game") }
         cell( 8,0) { button(:name=>"options", :caption=>"Options") }
         cell(10,0) { button(:name=>"credits", :caption=>"Credits") }
         cell(12,0) { button(:name=>"quit", :caption=>"Quit") }
       }
     cell(0,0) {
      table {
	row(:fixed=>5)
        row(:fixed=>456)
	row
	col
	col(:fixed=>606)
	col
	cell(1,1) { image(:filename="data/gui/small_forest.png", :enabled=>false) }
      }
    }
    cell(0,3) { text(:font=>"yellow.font", :align=>"center", :enabled=>false, :caption="(C) 2005-2007 by the Antargis-team") }
	       }
      end
    end
  end

end