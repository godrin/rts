
#include "rice/Data_Type.hpp"
#include "rice/Constructor.hpp"
#include "rice/Director.hpp"
    
#include <game_app.h>
    
using namespace Rice;

void init_Game() {
    Rice::Module rb_mGame = define_module("Game");
    //Rice::Object agApp(rb_eval_string("GUI::Application"));
    
    define_class_under<GameApp,AGApplication>(rb_mGame,"Application")
        .define_constructor(Constructor<GameApp>())
        .define_method("run",
           &GameApp::run)
        ;

  
}