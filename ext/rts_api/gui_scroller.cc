/*
 * Copyright (c) 2005 by David Kamphausen. All rights reserved.
 *
 * ag_scroller.cc
 * by David Kamphausen (david.kamphausen@web.de)
 *
 * The "Antargis" project, including all files needed to compile it,
 * is free software; you can redistribute it and/or use it and/or modify it
 * under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 2 of the License,
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program.
 */


#include <gui_scroller.h>
#include <gui_button.h>
#include <gui_border.h>
#include <gui_background.h>
#include <basic_debug.h>

#include <rice/Data_Type.hpp>

AGScroller::AGScroller(Rice::Object pSelf):
  AGWidget(pSelf),
  sigValueChanged(this,"sigValueChanged"),
  mHorizontal(true),
  mB1(Create<AGButton>()),
  mB2(Create<AGButton>()),
  mScroller(Create<AGButton>())
  {
    mBorder=new AGBorder("button.border.normal");
    mBackground=new AGBackground("button.background.normal");

    mMax=1;
    mMin=0;
    mValueWidth=0.3;
    mValue=0.2;
    mStepping=0.1;

    mVirtualValue=mValue;

    mBorderWidth=2;
    
    setHorizontal(mHorizontal);


    addChild(mB1);
    addChild(mB2);
    addChild(mScroller);

    mScroller->sigDragBy.connect(slot(this,&AGScroller::eventDragBy));
    mB1->sigClick.connect(slot(this,&AGScroller::eventUpClick));
    mB2->sigClick.connect(slot(this,&AGScroller::eventDownClick));

    updateScroller();

    mB1->setCaching(false);
    mB2->setCaching(false);
    mScroller->setCaching(false);
    setCaching(true);
  }

AGScroller::~AGScroller() throw()
  {
    delete mBorder;
    delete mBackground;
  }
  
  
void AGScroller::setHorizontal(bool b) {
 //FIXME: set correct surfaces 
  mHorizontal=b;
    if(mHorizontal)
      {
        mB1->setRect(AGRect2(mBorderWidth,mBorderWidth,getRect().height()-mBorderWidth*2,getRect().height()-mBorderWidth*2));
        mB2->setRect(AGRect2(getRect().width()+mBorderWidth-getRect().height(),mBorderWidth,getRect().height()-mBorderWidth*2,getRect().height()-mBorderWidth*2));

        mScroller->setRect(AGRect2(mBorderWidth+getRect().height(),mBorderWidth,(getRect().width()-2*getRect().height())*0.5  ,getRect().height()-mBorderWidth*2));

        //      mScroller->setSurface(AGSurface::load("data/gui/v_bars.png"));
      }
    else
      {
        mB1->setRect(AGRect2(mBorderWidth,mBorderWidth,getRect().width()-mBorderWidth*2,getRect().width()-mBorderWidth*2));
        mB2->setRect(AGRect2(mBorderWidth,getRect().height()+mBorderWidth-getRect().width(),getRect().width()-mBorderWidth*2,getRect().width()-mBorderWidth*2));

        mScroller->setRect(AGRect2(mBorderWidth,mBorderWidth+getRect().width(),getRect().width()-mBorderWidth*2,(getRect().height()-2*getRect().width())*0.5));

        //      mScroller->setSurface(AGSurface::load("data/gui/h_bars.png"));
      }
      
    if(mHorizontal)
      {
        mB1->setSurface(AGSurface::load("data/gui/arrow_left.png"));
        mB2->setSurface(AGSurface::load("data/gui/arrow_right.png"));
        mScroller->setSurface(AGSurface::load("data/gui/v_bars.png"));
      }
    else
      {
        mB1->setSurface(AGSurface::load("data/gui/arrow_up.png"));
        mB2->setSurface(AGSurface::load("data/gui/arrow_down.png"));
        mScroller->setSurface(AGSurface::load("data/gui/h_bars.png"));
      }


}

void AGScroller::draw(AGPainter &p)
  {
    AGRect2 pr=getRect().origin();
    mBackground->draw(pr,p);
    mBorder->draw(pr,p);
  }


bool AGScroller::eventDragBy(AGEvent *pEvent)
  {
    AGVector2 v=pEvent->getVector();
    if(mHorizontal)
      {
        mVirtualValue+=v[0]/getMovingWidth()*(mMax-mMin);
        mVirtualValue=std::max(mVirtualValue,mMin);
        mVirtualValue=std::min(mVirtualValue,mMax);
        updateScroller();
      }
    else
      {
        mVirtualValue+=v[1]/getMovingWidth()*(mMax-mMin);
        mVirtualValue=std::max(mVirtualValue,mMin);
        mVirtualValue=std::min(mVirtualValue,mMax);
        updateScroller();
      }
    return true;
  }

float AGScroller::getScrollerWidth()
  {
    float v=0;
    if(mHorizontal)
      v=(getRect().width()-mBorderWidth*2-getScrollerHeight()*2);
    else
      v=(getRect().height()-mBorderWidth*2-getScrollerHeight()*2);

    if(mMax!=mMin)
      v*=mValueWidth/(mMax-mMin);
    return v;

  }
float AGScroller::getScrollerHeight()
  {
    if(mHorizontal)
      return (getRect().height()-mBorderWidth*2);
    else
      return (getRect().width()-mBorderWidth*2);

  }
float AGScroller::getMovingWidth()
  {
    if(mHorizontal)
      return getRect().width()-getScrollerWidth()-2*mBorderWidth-2*getScrollerHeight();
    else
      {
        return getRect().height()-getScrollerWidth()-2*mBorderWidth-2*getScrollerHeight();
      }
  }

void AGScroller::updateScroller()
  {
    mVirtualValue=std::max(mVirtualValue,mMin);
    mVirtualValue=std::min(mVirtualValue,mMax);


    float nv=int((mVirtualValue-mMin)/mStepping+0.5)*mStepping+mMin;

    if(nv!=mValue)
      {
        mValue=nv;
        sigValueChanged(new AGEvent(this,"sigValueChanged"));
      }


    if(mHorizontal)
      {
        float x=mBorderWidth+getScrollerHeight();
        if(mMax!=mMin)
          x+=getMovingWidth()*(mValue-mMin)/(mMax-mMin);
        float y=mBorderWidth;
        float w=getScrollerWidth();
        float h=getScrollerHeight();
        mScroller->setRect(AGRect2(x,y,w,h));
      }
    else
      {
        float x=mBorderWidth;
        float y=mBorderWidth+getScrollerHeight();

        if(mMax!=mMin)
          y+=getMovingWidth()*(mValue-mMin)/(mMax-mMin);
        float h=getScrollerWidth();
        float w=getScrollerHeight();

        mScroller->setRect(AGRect2(x,y,w,h));
      }
    queryRedraw();
  }

bool AGScroller::eventUpClick(AGEvent *pEvent)
  {
    mVirtualValue-=mStepping;
    mVirtualValue=std::max(mVirtualValue,mMin);
    mVirtualValue=std::min(mVirtualValue,mMax);
    updateScroller();
    return true;
  }
bool AGScroller::eventDownClick(AGEvent *pEvent)
  {
    mVirtualValue+=mStepping;
    mVirtualValue=std::max(mVirtualValue,mMin);
    mVirtualValue=std::min(mVirtualValue,mMax);
    updateScroller();
    return true;
  }

void AGScroller::setValue(float pValue)
  {
    mVirtualValue=pValue;
    updateScroller();
  }
void AGScroller::setScrollerSize(float pSize)
  {
    mValueWidth=pSize;
    updateScroller();
  }
void AGScroller::setInterval(float pMin,float pMax)
  {
    mMin=pMin;
    mMax=pMax;
    assert(mMin<=mMax);
    updateScroller();
  }
void AGScroller::setStepping(float pStep)
  {
    mStepping=pStep;
    updateScroller();
  }


float AGScroller::getValue() const
{
  return mValue;
}
float AGScroller::getMin() const
{
  return mMin;
}
float AGScroller::getMax() const
{
  return mMax;
}
