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
    end
  end
  
  
end