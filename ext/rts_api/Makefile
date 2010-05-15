
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
INCFLAGS = -I. -I. -I/usr/lib/ruby/1.8/x86_64-linux -I. -I/usr/include/SDL
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
SRCS = randistrs.c GLee.c mtwist.c rk_tools.cc ag_mutex.cc sge_surface.cc vertex_array.cc ag_plugin.cc ag_geometry_inline.cc ag_radiogroup.cc glsl.cc rk_singleton.cc water.cc rk_string.cc ag_serial.cc ag_sdlpainter.cc resource.cc ag_layoutfactory.cc ag_stringstream.cc rk_logging.cc ag_frame.cc mesh_base.cc mesh_sort.cc ag_xml.cc ag_scroller.cc scene.cc rk_time.cc ag_glscreen.cc ag_decryptor.cc init.cc ag_application.cc scenenode.cc ag_text.cc ag_main.cc ag_window.cc ag_geometry.cc ag_painter.cc ag_vdebug.cc ag_config.cc scene_base.cc ag_caption.cc ag_button.cc ag_background.cc ag_video.cc ag_menuitem.cc ag_color.cc ag_colorbutton.cc ag_string_utf8.cc ag_message.cc map.cc ag_kill.cc ag_glsl.cc ag_edit.cc ag_fs.cc ag_local.cc terrain.cc ag_sdlscreen.cc mesh_2d.cc anim_mesh_data.cc boa_3d_wireframe.cc ag_projection.cc rk_config.cc ag_fontengine.cc ag_rand_base.cc path.cc ag_surface.cc minimap.cc ag_profiler.cc ag_tooltip.cc ag_singleton.cc ag_rendercontext.cc rk_utf8.cc ag_glwidget.cc mesh_2d_data.cc ag_widget.cc ag_clip_painttarget.cc ag_video_base.cc ag_listbox.cc ag_texture.cc ag_messageobject.cc rk_debug.cc rk_rubyobj.cc entity.cc ag_clip.cc ag_border.cc mesh_optimizer.cc ant_app.cc ag_theme.cc scene_2d.cc mesh_data.cc ag_screen.cc ag_combo.cc ag_texturecache.cc ag_glpainter.cc basic_algebra.cc swig_dummy.cc ag_gradient.cc ag_radio.cc ag_rand.cc rk_rtools.cc entptr.cc jobs.cc ag_theme_v2.cc ag_scrollingwidget.cc ag_table.cc ag_font.cc ag_menu.cc ag_fbo.cc height_map.cc ag_surface_internal.cc ant_renderer.cc ag_image.cc ag_surfacemanager.cc ag_gltexture.cc ag_cell.cc ant_camera.cc ag_png.cc mesh.cc ag_collector.cc ag_layoutcreators.cc heuristic.cc sge_primitives.cc ant_frustum.cc ag_serial_vec.cc ant_particle.cc anim_mesh.cc ag_mixer.cc ant_projection.cc ag_layout.cc ag_screenwidget.cc ag_checkbox.cc api_application.cpp rts_api.cpp
OBJS = randistrs.o GLee.o mtwist.o rk_tools.o ag_mutex.o sge_surface.o vertex_array.o ag_plugin.o ag_geometry_inline.o ag_radiogroup.o glsl.o rk_singleton.o water.o rk_string.o ag_serial.o ag_sdlpainter.o resource.o ag_layoutfactory.o ag_stringstream.o rk_logging.o ag_frame.o mesh_base.o mesh_sort.o ag_xml.o ag_scroller.o scene.o rk_time.o ag_glscreen.o ag_decryptor.o init.o ag_application.o scenenode.o ag_text.o ag_main.o ag_window.o ag_geometry.o ag_painter.o ag_vdebug.o ag_config.o scene_base.o ag_caption.o ag_button.o ag_background.o ag_video.o ag_menuitem.o ag_color.o ag_colorbutton.o ag_string_utf8.o ag_message.o map.o ag_kill.o ag_glsl.o ag_edit.o ag_fs.o ag_local.o terrain.o ag_sdlscreen.o mesh_2d.o anim_mesh_data.o boa_3d_wireframe.o ag_projection.o rk_config.o ag_fontengine.o ag_rand_base.o path.o ag_surface.o minimap.o ag_profiler.o ag_tooltip.o ag_singleton.o ag_rendercontext.o rk_utf8.o ag_glwidget.o mesh_2d_data.o ag_widget.o ag_clip_painttarget.o ag_video_base.o ag_listbox.o ag_texture.o ag_messageobject.o rk_debug.o rk_rubyobj.o entity.o ag_clip.o ag_border.o mesh_optimizer.o ant_app.o ag_theme.o scene_2d.o mesh_data.o ag_screen.o ag_combo.o ag_texturecache.o ag_glpainter.o basic_algebra.o swig_dummy.o ag_gradient.o ag_radio.o ag_rand.o rk_rtools.o entptr.o jobs.o ag_theme_v2.o ag_scrollingwidget.o ag_table.o ag_font.o ag_menu.o ag_fbo.o height_map.o ag_surface_internal.o ant_renderer.o ag_image.o ag_surfacemanager.o ag_gltexture.o ag_cell.o ant_camera.o ag_png.o mesh.o ag_collector.o ag_layoutcreators.o heuristic.o sge_primitives.o ant_frustum.o ag_serial_vec.o ant_particle.o anim_mesh.o ag_mixer.o ant_projection.o ag_layout.o ag_screenwidget.o ag_checkbox.o api_application.o rts_api.o
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
