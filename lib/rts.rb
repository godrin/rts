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

module GUI
  class RubyListener<Listener
    def initialize(block)
      super()
      @block=block
    end
    def signal(event)
      result=@block.call(event)
      if result
	true
      else
	false
      end
    end
  end
  class Signal
    def connect(&block)
      connectCPP(RubyListener.new(block))
    end
  end
end