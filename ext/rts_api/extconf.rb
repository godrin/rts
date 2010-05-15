require 'rubygems'
gem 'rice'
require 'mkmf-rice'
require 'pp'
ok=true
ok&=find_header("SDL.h",["/usr/include/SDL"])
ok&=find_header("SDL_image.h",["/usr/include/SDL"])
ok&=find_header("SDL_ttf.h",["/usr/include/SDL"])
ok&=find_header("SDL_mixer.h",["/usr/include/SDL"])

unless ok
  puts "Fatal: Not all needed headers found!"
  exit
end

have_library("GL")
have_library("SDL")
have_library("SDL_image")
have_library("SDL_ttf")

cpp_include("SDL.h")
#include_path SDL !!!

create_makefile('rts_api')