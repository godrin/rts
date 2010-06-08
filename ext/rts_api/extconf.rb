require 'rubygems'
gem 'rice'
require 'mkmf-rice'
require 'pp'

if Config::MAKEFILE_CONFIG["arch"]=~/.*darwin.*/
  def append_library(libs, lib) # :no-doc:
    format('-framework %s', lib) + " " + libs
  end
end

have_library("OpenGL")
have_library("GL")
have_library("GLU")
have_library("SDL")
have_library("SDL_image")
have_library("SDL_ttf")


ok=true
ok&=find_header("SDL.h","/usr/include/SDL",'/Library/Frameworks/SDL.Framework/Headers')
ok&=find_header("SDL_image.h","/usr/include/SDL",'/Library/Frameworks/SDL_image.Framework/Headers')
ok&=find_header("SDL_ttf.h","/usr/include/SDL",'/Library/Frameworks/SDL_ttf.Framework/Headers')
ok&=find_header("SDL_mixer.h","/usr/include/SDL",'/Library/Frameworks/SDL_mixer.Framework/Headers')
ok&=find_header("gl.h",'/System/Library/Frameworks/OpenGL.framework/Headers')

unless ok
  puts "Fatal: Not all needed headers found!"
  exit
end


pngFound=find_header("png.h")

File.open("build_config.h","w"){|f|
  f.puts <<-EOT
#ifndef BUILD_CONFIG_H
#define BUILD_CONFIG_H
  EOT
  if pngFound
    f.puts "#define PNG_FOUND"
  end

  f.puts <<-EOT
#endif
  EOT
  }

cpp_include("SDL.h")
#include_path SDL !!!

create_makefile('rts_api')