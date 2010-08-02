
SHELL = /bin/sh

#### Start of system configuration section. ####

srcdir = .
topdir = /usr/lib/ruby/1.8/x86_64-linux
hdrdir = $(topdir)
VPATH = $(srcdir):$(topdir):$(hdrdir)
exec_prefix = $(prefix)
prefix = $(DESTDIR)/usr
sharedstatedir = $(prefix)/com
mandir = $(prefix)/share/man
psdir = $(docdir)
oldincludedir = $(DESTDIR)/usr/include
localedir = $(datarootdir)/locale
bindir = $(exec_prefix)/bin
libexecdir = $(prefix)/lib/ruby1.8
sitedir = $(DESTDIR)/usr/local/lib/site_ruby
htmldir = $(docdir)
vendorarchdir = $(vendorlibdir)/$(sitearch)
includedir = $(prefix)/include
infodir = $(prefix)/share/info
vendorlibdir = $(vendordir)/$(ruby_version)
sysconfdir = $(DESTDIR)/etc
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
localstatedir = $(DESTDIR)/var
sitelibdir = $(sitedir)/$(ruby_version)

CC = gcc
LIBRUBY = $(LIBRUBY_SO)
LIBRUBY_A = lib$(RUBY_SO_NAME)-static.a
LIBRUBYARG_SHARED = -l$(RUBY_SO_NAME)
LIBRUBYARG_STATIC = -lruby1.8-static

RUBY_EXTCONF_H = 
CFLAGS   =  -fPIC -fno-strict-aliasing -g -g -O2  -fPIC $(cflags) 
INCFLAGS = -I. -I. -I/usr/lib/ruby/1.8/x86_64-linux -I. -I/usr/include/SDL -I/usr/include/GL
DEFS     = 
CPPFLAGS =      -I/var/lib/gems/1.8/gems/rice-1.3.2/ruby/lib/include
CXXFLAGS = $(CFLAGS)  -Wall -g
ldflags  = -L. -Wl,-Bsymbolic-functions -rdynamic -Wl,-export-dynamic  -L/var/lib/gems/1.8/gems/rice-1.3.2/ruby/lib/lib
dldflags = 
archflag = 
DLDFLAGS = $(ldflags) $(dldflags) $(archflag)
LDSHARED = g++ -shared
AR = ar
EXEEXT = 

RUBY_INSTALL_NAME = ruby1.8
RUBY_SO_NAME = ruby1.8
arch = x86_64-linux
sitearch = x86_64-linux
ruby_version = 1.8
ruby = /usr/bin/ruby1.8
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
LIBS = -lSDL_ttf -lSDL_image -lSDL -lGLU -lGL -lrice -lruby1.8 -lpthread -lrt -ldl -lcrypt -lm   -lc
SRCS = randistrs.c GLee.c mtwist.c gui_caption.cc sge_surface.cc gui_color.cc gui_button.cc gui_glwidget.cc gui_video_base.cc gui_glpainter.cc gui_menuitem.cc gui_widget.cc basic_time.cc a3d_anim_mesh_data.cc gui_surface.cc a3d_vertex_array.cc game_heuristic.cc gui_theme_v2.cc sound_mixer.cc gui_geometry.cc gui_scrollingwidget.cc game_camera.cc gui_background.cc a3d_renderer.cc basic_ruby_exposer.cc game_resource.cc basic_debug.cc gui_texturecache.cc game_app.cc basic_ruby_exposable.cc a3d_mesh_data.cc gui_colorbutton.cc gui_vdebug.cc gui_texture.cc gui_radio.cc game_entity.cc gui_combo.cc gui_config.cc gui_tooltip.cc gui_messageobject.cc gui_screen.cc gui_border.cc gui_text.cc gui_cell.cc a3d_scene.cc gui_main.cc basic_serial.cc gui_local.cc game_height_map.cc a3d_glsl.cc gui_glscreen.cc gui_checkbox.cc basic_utf8.cc basic_xml.cc gui_scroller.cc basic_profiler.cc basic_logging.cc basic_string_utf8.cc gui_listbox.cc gui_application.cc gui_glsl.cc gui_fbo.cc basic_tools.cc a3d_scene_base.cc gui_sdlscreen.cc basic_rand_base.cc gui_gltexture.cc gui_rendercontext.cc a3d_scenenode.cc gui_sdlpainter.cc basic_string.cc a3d_particle.cc a3d_mesh.cc gui_projection.cc a3d_frustum.cc basic_mutex.cc gui_frame.cc game_jobs.cc gui_gradient.cc a3d_mesh_base.cc gui_font.cc gui_theme.cc a3d_anim_mesh.cc gui_table.cc a3d_mesh_optimizer.cc gui_serial_vec.cc gui_clip.cc game_map.cc game_water.cc gui_ruby_widget.cc basic_rand.cc game_minimap.cc basic_stringstream.cc basic_rtools.cc gui_window.cc gui_edit.cc gui_surface_internal.cc basic_algebra.cc basic_fs.cc game_path.cc gui_message.cc gui_radiogroup.cc gui_surfacemanager.cc gui_fontengine.cc gui_clip_painttarget.cc gui_video.cc gui_geometry_inline.cc gui_image.cc basic_singleton.cc gui_screenwidget.cc gui_widgetptr.cc sge_primitives.cc gui_menu.cc gui_png.cc gui_painter.cc a3d_mesh_sort.cc game_terrain.cc a3d_projection.cc basic_config.cc api_application.cpp api_game.cpp ruby_mappings.cpp rts_api.cpp api_widgets.cpp
OBJS = randistrs.o GLee.o mtwist.o gui_caption.o sge_surface.o gui_color.o gui_button.o gui_glwidget.o gui_video_base.o gui_glpainter.o gui_menuitem.o gui_widget.o basic_time.o a3d_anim_mesh_data.o gui_surface.o a3d_vertex_array.o game_heuristic.o gui_theme_v2.o sound_mixer.o gui_geometry.o gui_scrollingwidget.o game_camera.o gui_background.o a3d_renderer.o basic_ruby_exposer.o game_resource.o basic_debug.o gui_texturecache.o game_app.o basic_ruby_exposable.o a3d_mesh_data.o gui_colorbutton.o gui_vdebug.o gui_texture.o gui_radio.o game_entity.o gui_combo.o gui_config.o gui_tooltip.o gui_messageobject.o gui_screen.o gui_border.o gui_text.o gui_cell.o a3d_scene.o gui_main.o basic_serial.o gui_local.o game_height_map.o a3d_glsl.o gui_glscreen.o gui_checkbox.o basic_utf8.o basic_xml.o gui_scroller.o basic_profiler.o basic_logging.o basic_string_utf8.o gui_listbox.o gui_application.o gui_glsl.o gui_fbo.o basic_tools.o a3d_scene_base.o gui_sdlscreen.o basic_rand_base.o gui_gltexture.o gui_rendercontext.o a3d_scenenode.o gui_sdlpainter.o basic_string.o a3d_particle.o a3d_mesh.o gui_projection.o a3d_frustum.o basic_mutex.o gui_frame.o game_jobs.o gui_gradient.o a3d_mesh_base.o gui_font.o gui_theme.o a3d_anim_mesh.o gui_table.o a3d_mesh_optimizer.o gui_serial_vec.o gui_clip.o game_map.o game_water.o gui_ruby_widget.o basic_rand.o game_minimap.o basic_stringstream.o basic_rtools.o gui_window.o gui_edit.o gui_surface_internal.o basic_algebra.o basic_fs.o game_path.o gui_message.o gui_radiogroup.o gui_surfacemanager.o gui_fontengine.o gui_clip_painttarget.o gui_video.o gui_geometry_inline.o gui_image.o basic_singleton.o gui_screenwidget.o gui_widgetptr.o sge_primitives.o gui_menu.o gui_png.o gui_painter.o a3d_mesh_sort.o game_terrain.o a3d_projection.o basic_config.o api_application.o api_game.o ruby_mappings.o rts_api.o api_widgets.o
TARGET = rts_api
DLLIB = $(TARGET).so
EXTSTATIC = 
STATIC_LIB = 

BINDIR        = $(bindir)
RUBYCOMMONDIR = $(sitedir)$(target_prefix)
RUBYLIBDIR    = $(sitelibdir)$(target_prefix)
RUBYARCHDIR   = $(sitearchdir)$(target_prefix)

TARGET_SO     = $(DLLIB)
CLEANLIBS     = $(TARGET).so $(TARGET).il? $(TARGET).tds $(TARGET).map
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
