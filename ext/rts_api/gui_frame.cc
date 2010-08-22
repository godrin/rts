#include <gui_frame.h>
#include <gui_screen.h>

#include <basic_debug.h>

AGFrame::AGFrame(Rice::Object pSelf):AGWidget(pSelf)
{
  mTextureInited=false;
  mUseTexture=true;
  mBg=0;
}
/*
AGFrame::AGFrame(Rice::Object pSelf,const GUIWidgetPtr &pParent,const AGRect2 &pRect,const AGBorder &pBorder):AGWidget(pSelf,pParent,pRect),
mWidth(pBorder.getWidth()),mWidthH(pBorder.getWidth()),mBorder(new AGBorder(pBorder)),mTexture((int)width(),(int)height())
{
  mTextureInited=false;
  mUseTexture=true;
  mBg=0;
}*/

AGFrame::~AGFrame() throw()
  {
    delete mBorder;
    delete mBg;
  }

AGRect2 AGFrame::getClientRect() const
{
  return getRect().origin().shrink(mWidth,mWidthH);
}

void AGFrame::prepareDraw()
  {
    if(mUseTexture && mBorder)
      {
        //      if(!mTextureInited)
        if(!mTexture.hasTexture())
          {
            AGPainter p(mTexture);
            mBorder->draw(getRect().origin(),p);
            mTextureInited=true;

          }
      }
    AGWidget::prepareDraw();
  }

void AGFrame::draw(AGPainter &p)
  {
    //  CTRACE;
    if(mBg)
      {
        mBg->draw(getRect().origin(),p);
      }
    if(mBorder)
      {
        if(mUseTexture && mTextureInited)
          p.blit(mTexture,mTexture.getRect());
        else
          mBorder->draw(getRect().origin(),p);
      }
  }

void AGFrame::setBackground(const AGBackground &pBg)
  {
    mBg=new AGBackground(pBg);
  }
