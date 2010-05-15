

#include "rice/Data_Type.hpp"
#include "rice/Constructor.hpp"
#include "rice/Director.hpp"
    
#include "ag_application.h"
#include "ag_glscreen.h"
#include "ag_main.h"
#include "ag_video.h"
    
    
    using namespace Rice;

    
  void initGLScreen() {
    AGMain *m=new AGMain();
    AGVideoManager *v=new AGVideoManager();
    m->setVideo(v);
    v->initVideo(800,600,32,false,true);
  }

  void init_AGApplication() {

    Rice::Module rb_mGui = define_module("GUI");

    rb_mGui.define_module_function("initGLScreen",&initGLScreen);
    
  
    define_class_under<AGApplication>(rb_mGui,"Application")
        .define_constructor(Constructor<AGApplication>())
        .define_method("run",
           &AGApplication::run)
        ;
  }
