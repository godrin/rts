require 'pp'

require File.expand_path('../layouts/mainmenu_layout.rb',__FILE__)

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
      
      @mainMenu=MainMenuLayout.new(nil)
      
      self.main_widget=@mainMenu
      c=@mainMenu.get_child("quit")
      sig=c.sig_click
      sig.connect{||
        pp "QUIT"
        self.event_quit
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
    
    def event_quit
      try_quit
    end
  end
  
  
end