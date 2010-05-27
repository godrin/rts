Dir[File.expand_path('../menus/*.rb',__FILE__)].each{|file|
  require file
}