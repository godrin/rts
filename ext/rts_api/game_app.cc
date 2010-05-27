#include <game_app.h>
#include <gui_vdebug.h>
#include <basic_profiler.h>


GameApp::GameApp():scene(new Scene(800,600))
{
  CTRACE;
  shadow=true;
  mx=my=0;
  omx=-1;
  frameTime=0;
  frameCount=0;
  hx=hy=-1;
}

GameApp::GameApp(int w,int h):scene(new Scene(w,h))
{
  CTRACE;
  shadow=true;
  mx=my=0;
  omx=-1;
  frameTime=0;
  frameCount=0;
  hx=hy=-1;
}

GameApp::~GameApp() throw()
  {
    CTRACE;
    delete scene;
  }


void GameApp::draw()
  {
    STACKTRACE;
    drawGL();
    AGApplication::draw();
  }

void GameApp::drawGL()
  {
    STACKTRACE;
    glEnable(GL_DEPTH_TEST); // enable depth test
    glDepthMask(true);

    assertGL;
    scene->draw();
    assertGL;
  }

bool GameApp::eventFrame(float t)
  {
    if(hx>=0)
      {
        // check hovering
        PickResult nodes=scene->pick(hx,hy,1,1);

        if(nodes.size())
          eventHover(nodes,hb);
        hx=hy=-1;
      }
    return true;
  }

bool GameApp::eventMouseButtonDown(AGEvent *e)
  {
    mMayClick=true;

    if(e->isSDLEvent())
      {
        if(e->getButton()==5)
          {
            getScene().getCameraObject().incCameraDistance();
          }
        else if(e->getButton()==4)
          {
            getScene().getCameraObject().decCameraDistance();
          }
        else if(e->getButton()==1)
          {
            AGVector2 p=e->getMousePosition();
            omx=p[0];
            omy=p[1];
          }
      }
    return AGApplication::eventMouseButtonDown(e);
  }
bool GameApp::eventMouseButtonUp(AGEvent *e)
  {
    CTRACE;
    omx=-1;
    omy=-1;
    if(mMayClick)
      {
        if(e->isSDLEvent())
          {
            if(e->getButton()<4)
              {
                STACKTRACE;
                AGVector2 p=e->getMousePosition();
                cdebug("p:"<<p);
                PickResult nodes=scene->pick(p[0],p[1],1,1);

                eventClick(nodes,e->getButton());
              }
          }
      }
    else
      {
        cdebug("click failed");
      }
    return AGApplication::eventMouseButtonUp(e);
  }

void GameApp::eventClick(const PickResult &pNodes,int button)
  {
  }

void GameApp::eventHover(const PickResult &pNodes,int button)
  {
  }


bool GameApp::eventMouseMotion(AGEvent *e)
  {
    if(e->isSDLEvent() && omx>=0)
      {
        AGVector2 p=e->getMousePosition();
        //      AGVector4 cam=scene->getCamera();
        mx=p[0]-omx;
        my=p[1]-omy;

        setCamera(getCamera()+AGVector2(-mx*0.03,my*0.03));
        //      camera=cam+AGVector4(-mx*0.03,my*0.03,0);
        //      scene->setCamera(camera);

        omx=p[0];
        omy=p[1];
      }
    if(e->isSDLEvent())
      {
        // check hovering - delayed 
        AGVector2 p=e->getMousePosition();
        hx=p[0];
        hy=p[1];
        hb=e->getButton();
      }

    mMayClick=false;
    return AGApplication::eventMouseMotion(e);
  }

AGVector2 GameApp::getCamera() const
{
  return scene->getCamera().dim2();
}

void GameApp::setCamera(const AGVector2 &p)
  {
    scene->setCamera(AGVector4(p[0],p[1],getCameraHeight(p)));
  }

bool GameApp::eventKeyDown(AGEvent *e)
  {
    if(e->isSDLEvent())
      {
        if(e->getKey()==SDLK_s)
          {
            scene->setShadow((scene->getShadow()+1)%3);
          }
      }
    return AGApplication::eventKeyDown(e);
  }

Scene &GameApp::getScene()
  {
    assert(scene);
    return *scene;
  }


float GameApp::getCameraHeight(const AGVector2&p)
  {
    return 0;
  }
