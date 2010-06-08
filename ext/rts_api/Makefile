
SHELL = /bin/sh

#### Start of system configuration section. ####

srcdir = .
topdir = /System/Library/Frameworks/Ruby.framework/Versions/1.8/usr/lib/ruby/1.8/universal-darwin10.0
hdrdir = $(topdir)
VPATH = $(srcdir):$(topdir):$(hdrdir)
exec_prefix = $(prefix)
prefix = $(DESTDIR)/System/Library/Frameworks/Ruby.framework/Versions/1.8/usr
sharedstatedir = $(prefix)/com
mandir = $(DESTDIR)/usr/share/man
psdir = $(docdir)
oldincludedir = $(DESTDIR)/usr/include
localedir = $(datarootdir)/locale
bindir = $(exec_prefix)/bin
libexecdir = $(exec_prefix)/libexec
sitedir = $(DESTDIR)/Library/Ruby/Site
htmldir = $(docdir)
vendorarchdir = $(vendorlibdir)/$(sitearch)
includedir = $(prefix)/include
infodir = $(DESTDIR)/usr/share/info
vendorlibdir = $(vendordir)/$(ruby_version)
sysconfdir = $(prefix)/etc
libdir = $(exec_prefix)/lib
sbindir = $(exec_prefix)/sbin
rubylibdir = $(libdir)/ruby/$(ruby_version)
docdir = $(datarootdir)/doc/$(PACKAGE)
dvidir = $(docdir)
vendordir = $(libdir)/ruby/vendor_ruby
datarootdir = $(prefix)/share
pdfdir = $(docdir)
archdir = $(rubylibdir)/$(arch)
sitearchdir = $(sitelibdir)/$(sitearch)
datadir = $(datarootdir)
localstatedir = $(prefix)/var
sitelibdir = $(sitedir)/$(ruby_version)

CC = gcc
LIBRUBY = $(LIBRUBY_SO)
LIBRUBY_A = lib$(RUBY_SO_NAME)-static.a
LIBRUBYARG_SHARED = -l$(RUBY_SO_NAME)
LIBRUBYARG_STATIC = -lruby

RUBY_EXTCONF_H = 
CFLAGS   =  -fno-common -arch i386 -arch x86_64 -g -Os -pipe -fno-common -DENABLE_DTRACE  -fno-common  -pipe -fno-common $(cflags) 
INCFLAGS = -I. -I. -I/System/Library/Frameworks/Ruby.framework/Versions/1.8/usr/lib/ruby/1.8/universal-darwin10.0 -I. -I/Library/Frameworks/SDL.Framework/Headers -I/Library/Frameworks/SDL_image.Framework/Headers -I/Library/Frameworks/SDL_ttf.Framework/Headers -I/Library/Frameworks/SDL_mixer.Framework/Headers -I/System/Library/Frameworks/OpenGL.framework/Headers
DEFS     = 
CPPFLAGS =   -D_XOPEN_SOURCE -D_DARWIN_C_SOURCE    -I/Library/Ruby/Gems/1.8/gems/rice-1.3.2/ruby/lib/include
CXXFLAGS = $(CFLAGS)  -Wall -g
ldflags  = -L. -arch i386 -arch x86_64   -L/Library/Ruby/Gems/1.8/gems/rice-1.3.2/ruby/lib/lib
dldflags = 
archflag = 
DLDFLAGS = $(ldflags) $(dldflags) $(archflag)
LDSHARED = g++ -arch i386 -arch x86_64 -pipe -bundle -undefined dynamic_lookup
AR = ar
EXEEXT = 

RUBY_INSTALL_NAME = ruby
RUBY_SO_NAME = ruby
arch = universal-darwin10.0
sitearch = universal-darwin10.0
ruby_version = 1.8
ruby = /System/Library/Frameworks/Ruby.framework/Versions/1.8/usr/bin/ruby
RUBY = $(ruby)
RM = rm -f
MAKEDIRS = mkdir -p
INSTALL = /usr/bin/install -c
INSTALL_PROG = $(INSTALL) -m 0755
INSTALL_DATA = $(INSTALL) -m 644
COPY = cp

#### End of system configuration section. ####

preload = 

CXX = g++
libpath = . $(libdir)
LIBPATH =  -L. -L$(libdir)
DEFFILE = 

CLEANFILES = mkmf.log
DISTCLEANFILES = 

extout = 
extout_prefix = 
target_prefix = 
LOCAL_LIBS = 
LIBS = -framework SDL_ttf -framework SDL_image -framework SDL -framework OpenGL -lrice -lruby -lpthread -ldl  
SRCS = GLee.c mtwist.c randistrs.c a3d_anim_mesh.cc a3d_anim_mesh_data.cc a3d_frustum.cc a3d_glsl.cc a3d_mesh.cc a3d_mesh_base.cc a3d_mesh_data.cc a3d_mesh_optimizer.cc a3d_mesh_sort.cc a3d_particle.cc a3d_projection.cc a3d_renderer.cc a3d_scene.cc a3d_scene_base.cc a3d_scenenode.cc a3d_vertex_array.cc basic_algebra.cc basic_config.cc basic_debug.cc basic_fs.cc basic_logging.cc basic_mutex.cc basic_profiler.cc basic_rand.cc basic_rand_base.cc basic_rtools.cc basic_ruby_exposable.cc basic_ruby_exposer.cc basic_serial.cc basic_singleton.cc basic_string.cc basic_string_utf8.cc basic_stringstream.cc basic_time.cc basic_tools.cc basic_utf8.cc basic_xml.cc game_app.cc game_camera.cc game_entity.cc game_height_map.cc game_heuristic.cc game_jobs.cc game_map.cc game_minimap.cc game_path.cc game_resource.cc game_terrain.cc game_water.cc gui_application.cc gui_background.cc gui_border.cc gui_button.cc gui_caption.cc gui_cell.cc gui_checkbox.cc gui_clip.cc gui_clip_painttarget.cc gui_color.cc gui_colorbutton.cc gui_combo.cc gui_config.cc gui_edit.cc gui_fbo.cc gui_font.cc gui_fontengine.cc gui_frame.cc gui_geometry.cc gui_geometry_inline.cc gui_glpainter.cc gui_glscreen.cc gui_glsl.cc gui_gltexture.cc gui_glwidget.cc gui_gradient.cc gui_image.cc gui_layout.cc gui_layoutcreators.cc gui_layoutfactory.cc gui_listbox.cc gui_local.cc gui_main.cc gui_menu.cc gui_menuitem.cc gui_message.cc gui_messageobject.cc gui_painter.cc gui_png.cc gui_projection.cc gui_radio.cc gui_radiogroup.cc gui_rendercontext.cc gui_screen.cc gui_screenwidget.cc gui_scroller.cc gui_scrollingwidget.cc gui_sdlpainter.cc gui_sdlscreen.cc gui_serial_vec.cc gui_surface.cc gui_surface_internal.cc gui_surfacemanager.cc gui_table.cc gui_text.cc gui_texture.cc gui_texturecache.cc gui_theme.cc gui_theme_v2.cc gui_tooltip.cc gui_vdebug.cc gui_video.cc gui_video_base.cc gui_widget.cc gui_window.cc sge_primitives.cc sge_surface.cc sound_mixer.cc api_application.cpp api_game.cpp rts_api.cpp
OBJS = GLee.o mtwist.o randistrs.o a3d_anim_mesh.o a3d_anim_mesh_data.o a3d_frustum.o a3d_glsl.o a3d_mesh.o a3d_mesh_base.o a3d_mesh_data.o a3d_mesh_optimizer.o a3d_mesh_sort.o a3d_particle.o a3d_projection.o a3d_renderer.o a3d_scene.o a3d_scene_base.o a3d_scenenode.o a3d_vertex_array.o basic_algebra.o basic_config.o basic_debug.o basic_fs.o basic_logging.o basic_mutex.o basic_profiler.o basic_rand.o basic_rand_base.o basic_rtools.o basic_ruby_exposable.o basic_ruby_exposer.o basic_serial.o basic_singleton.o basic_string.o basic_string_utf8.o basic_stringstream.o basic_time.o basic_tools.o basic_utf8.o basic_xml.o game_app.o game_camera.o game_entity.o game_height_map.o game_heuristic.o game_jobs.o game_map.o game_minimap.o game_path.o game_resource.o game_terrain.o game_water.o gui_application.o gui_background.o gui_border.o gui_button.o gui_caption.o gui_cell.o gui_checkbox.o gui_clip.o gui_clip_painttarget.o gui_color.o gui_colorbutton.o gui_combo.o gui_config.o gui_edit.o gui_fbo.o gui_font.o gui_fontengine.o gui_frame.o gui_geometry.o gui_geometry_inline.o gui_glpainter.o gui_glscreen.o gui_glsl.o gui_gltexture.o gui_glwidget.o gui_gradient.o gui_image.o gui_layout.o gui_layoutcreators.o gui_layoutfactory.o gui_listbox.o gui_local.o gui_main.o gui_menu.o gui_menuitem.o gui_message.o gui_messageobject.o gui_painter.o gui_png.o gui_projection.o gui_radio.o gui_radiogroup.o gui_rendercontext.o gui_screen.o gui_screenwidget.o gui_scroller.o gui_scrollingwidget.o gui_sdlpainter.o gui_sdlscreen.o gui_serial_vec.o gui_surface.o gui_surface_internal.o gui_surfacemanager.o gui_table.o gui_text.o gui_texture.o gui_texturecache.o gui_theme.o gui_theme_v2.o gui_tooltip.o gui_vdebug.o gui_video.o gui_video_base.o gui_widget.o gui_window.o sge_primitives.o sge_surface.o sound_mixer.o api_application.o api_game.o rts_api.o
TARGET = rts_api
DLLIB = $(TARGET).bundle
EXTSTATIC = 
STATIC_LIB = 

BINDIR        = $(bindir)
RUBYCOMMONDIR = $(sitedir)$(target_prefix)
RUBYLIBDIR    = $(sitelibdir)$(target_prefix)
RUBYARCHDIR   = $(sitearchdir)$(target_prefix)

TARGET_SO     = $(DLLIB)
CLEANLIBS     = $(TARGET).bundle $(TARGET).il? $(TARGET).tds $(TARGET).map
CLEANOBJS     = *.o *.a *.s[ol] *.pdb *.exp *.bak

all:		$(DLLIB)
static:		$(STATIC_LIB)

clean:
		@-$(RM) $(CLEANLIBS) $(CLEANOBJS) $(CLEANFILES)

distclean:	clean
		@-$(RM) Makefile $(RUBY_EXTCONF_H) conftest.* mkmf.log
		@-$(RM) core ruby$(EXEEXT) *~ $(DISTCLEANFILES)

realclean:	distclean
install: install-so install-rb

install-so: $(RUBYARCHDIR)
install-so: $(RUBYARCHDIR)/$(DLLIB)
$(RUBYARCHDIR)/$(DLLIB): $(DLLIB)
	$(INSTALL_PROG) $(DLLIB) $(RUBYARCHDIR)
install-rb: pre-install-rb install-rb-default
install-rb-default: pre-install-rb-default
pre-install-rb: Makefile
pre-install-rb-default: Makefile
$(RUBYARCHDIR):
	$(MAKEDIRS) $@

site-install: site-install-so site-install-rb
site-install-so: install-so
site-install-rb: install-rb

.SUFFIXES: .c .m .cc .cxx .cpp .C .o

.cc.o:
	$(CXX) $(INCFLAGS) $(CPPFLAGS) $(CXXFLAGS) -c $<

.cxx.o:
	$(CXX) $(INCFLAGS) $(CPPFLAGS) $(CXXFLAGS) -c $<

.cpp.o:
	$(CXX) $(INCFLAGS) $(CPPFLAGS) $(CXXFLAGS) -c $<

.C.o:
	$(CXX) $(INCFLAGS) $(CPPFLAGS) $(CXXFLAGS) -c $<

.c.o:
	$(CC) $(INCFLAGS) $(CPPFLAGS) $(CFLAGS) -c $<

$(DLLIB): $(OBJS) Makefile
	@-$(RM) $@
	$(LDSHARED) -o $@ $(OBJS) $(LIBPATH) $(DLDFLAGS) $(LOCAL_LIBS) $(LIBS)



$(OBJS): ruby.h defines.h
