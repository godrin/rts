require 'rts_api.so'

module RTS
  @@inited=false
  class << self
    def init
      unless @@inited
	GUI::initGLScreen
	@@inited=true
      end
    end
  end
end