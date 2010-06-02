#module Antargis
#  class << self
    def loadFile(fileName)
      File.open(fileName,"r"){|f|f.read}
    end
#  end
#end