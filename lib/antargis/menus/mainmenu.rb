require 'pp'

module Antargis
  
  class MainMenu<::Game::Application
     class << self
       def start
	 RTS::init
	 app=MainMenu.new
	 app.run
       end
     end
     
     
    def initialize
      super
      #@menues=[]
      
      @mainMenu=GUI::Layout.new(nil)
      c=loadFile("data/gui/layout/mainmenu.xml")
      puts c
      @mainMenu.loadXML(c)
      #@menues.push(@mainMenu)
      self.mainWidget=@mainMenu
      
      sig=@mainMenu.getChild("quit").sigClick
      sig.connect{||
        pp self
        self.eventQuit
        exit
      }
      
      if false
	addHandler(@mainMenu.getChild("quit"),:sigClick,:eventQuit)
	addHandler(@mainMenu.getChild("credits"),:sigClick,:eventCredits)
	addHandler(@mainMenu.getChild("campaign"),:sigClick,:eventCampaign)
	addHandler(@mainMenu.getChild("single"),:sigClick,:eventSingle)
	addHandler(@mainMenu.getChild("tutorial"),:sigClick,:eventTutorial)
	addHandler(@mainMenu.getChild("load"),:sigClick,:eventLoadGame)
	addHandler(@mainMenu.getChild("options"),:sigClick,:eventOptions)
      end
    end
    
    def eventQuit
      tryQuit
    end
  end
  
  
end