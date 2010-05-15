require 'rubygems'
require 'rbplusplus'
require 'fileutils'
include RbPlusPlus

CUR_DIR=File.dirname(__FILE__)

Extension.new "noise" do |e|
 # e.working_dir = File.join(OGRE_RB_ROOT, "generated", "noise")
  e.sources [
      File.join(CUR_DIR, "rts.h"),
    ],
#    :library_paths => File.join(OGRE_RB_ROOT, "lib", "noise"),
    :include_paths => CUR_DIR #File.join(OGRE_RB_ROOT, "tmp", "noise", "include"),
   # :libraries => "noise",
   # :include_source_dir => File.join(HERE_DIR, "code")

  e.module "Rts" do |m|
    node = m.namespace "rts"

   # m.module "Model" do |model|
   #   node = model.namespace "model"
   # end
  end
end