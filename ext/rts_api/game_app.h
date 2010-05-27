#ifndef ANT_APP_H
#define ANT_APP_H

// INCLUDE_SWIG - used to filter, which files are included in swig-interfacing

/**
 *
 * \mainpage Battles of Antargis - C++ documentation
 *  \section Overview
 *    This is the C++ part of the API-documentation.
 *    It consists of three major parts:
 *    \see AntargisGUI
 *    \see Engine3d
 *    \see GameEngine
 *
 *    For information about the overall-architecture please refer to the ruby-documentation at: ../ruby/index.html
 *
  */



#include <a3d_scene.h>
#include <a3d_renderer.h>

#include <gui_application.h>
#include <gui_main.h>
#include <gui_geometry.h>

#include <basic_debug.h>

#include <iostream>
#include <fstream>

#ifndef SWIG
extern std::ofstream out;
#endif

class AGEXPORT GameApp:public AGApplication
{
  bool shadow;
  float mx,my;
  float omx,omy;
  AGVector4 camera;
  float frameTime;
  size_t frameCount;

  bool mMayClick;

  float hx,hy;
  int hb;

protected:
  Scene *scene;

public:
  GameApp();
  GameApp(int w,int h);
  ~GameApp() throw();

  virtual void draw();
  void drawGL();

  bool eventFrame(float t);

  virtual void eventClick(const PickResult &pNodes,int button);
  virtual void eventHover(const PickResult &pNodes,int button);

  virtual bool eventMouseButtonDown(AGEvent *m);
  virtual bool eventMouseButtonUp(AGEvent *m);
  virtual bool eventMouseMotion(AGEvent *m);
  virtual bool eventKeyDown(AGEvent *m);

  Scene &getScene();

  virtual float getCameraHeight(const AGVector2&p);
  virtual void setCamera(const AGVector2&p);
  AGVector2 getCamera() const;

};



#endif
